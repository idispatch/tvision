/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.
 * Modified by Salvador E. Tropea (added insertChar, middle button paste and
 * other stuff).
 * This class was reworked to support Unicode 16 by Salvador E. Tropea
 * Copyright (c) 2003
 * I basically created a new class TInputLineBase that's pure virtual and
 * contains code that can be used for any cell size.
 * Then I moved the cell size dependent code to TInputLine and created another
 * new class called TInputLineU16 suitable for Unicode 16.
 * A lot of internal details changed.
 *
 *
 */
#include <tv.h>

unsigned TInputLine::defaultModeOptions = 0;

// TODO: Not used here should be moved away
char hotKey(const char *s) {
    const char *p;

    if ((p = strchr(s, '~')) != 0)
        return uctoupper(p[1]);
    else
        return 0;
}

#define cpInputLine "\x13\x13\x14\x15"

TInputLine::TInputLine(const TRect& bounds, int aMaxLen) :
                TView(bounds),
                curPos(0),
                firstPos(0),
                selStart(0),
                selEnd(0),
                validator(NULL),
                maxLen(aMaxLen - 1),
                dataLen(0) {
    state |= sfCursorVis;
    options |= ofSelectable | ofFirstClick;
    modeOptions = defaultModeOptions;
    data = new char[aMaxLen];
    *data = EOS;
}

void TInputLine::SetValidator(TValidator * aValidator) {
    destroy(validator);
    validator = aValidator;
    if (validator)
        validator->SetOwner(this);
}

TInputLine::~TInputLine() {
    delete[] data;
    destroy(validator);
}

Boolean TInputLine::canScroll(int delta) {
    if (delta < 0)
        return Boolean(firstPos > 0);
    else if (delta > 0)
        return Boolean(dataLen - firstPos + 2 > size.x);
    else
        return False;
}

// Optimized for size, it could be 2 specialized members avoiding a generic
// multiply.
uint32 TInputLine::dataSize() {
    return (maxLen + 1);
}

void TInputLine::getData(void *rec) {
    memcpy(rec, data, dataSize());
}

TPalette& TInputLine::getPalette() const {
    static TPalette palette(cpInputLine, sizeof(cpInputLine) - 1);
    return palette;
}

int TInputLine::mouseDelta(TEvent& event) {
    TPoint mouse = makeLocal(event.mouse.where);

    if (mouse.x <= 0)
        return -1;
    else if (mouse.x >= size.x - 1)
        return 1;
    else
        return 0;
}

int TInputLine::mousePos(TEvent& event) {
    TPoint mouse = makeLocal(event.mouse.where);
    mouse.x = max(mouse.x, 1);
    int pos = mouse.x + firstPos - 1;
    pos = max(pos, 0);
    pos = min(pos, dataLen);
    return pos;
}

// Also optimize for size
void TInputLine::deleteSelect() {
    if (selStart < selEnd) {
        memcpy(data+selStart, data+selEnd, (dataLen-selEnd+1));
        dataLen -= selEnd - selStart;
        curPos = selStart;
    }
}

/**[txh]********************************************************************

 Description:
 Inserts a character at the cursor position. If the text is currently
 selected it's removed. If a validator is defined it's called. This basic
 input line have a fixed size and will refuse to insert the character if
 there is not enough space, but the virtual resizeData() is called giving
 a chance to create variable size input lines.@*
 I (SET) moved it to allow insertions from sources other than the keyboard
 emulating it's behavior.

 Return: False if the validator canceled the character, otherwise True.

 ***************************************************************************/
// TODO: The validator can't be 8 bits for an Unicode class.
//       I think IsValidInput should support one char.
Boolean TInputLine::insertChar(unsigned value) {
    if (validator) {
        char tmp[2];
        tmp[0] = value;
        tmp[1] = 0;
        if (validator->IsValidInput(tmp, False) == False)
            return False;
    }
    if (insertModeOn())
        deleteSelect();
    if ((insertModeOn() && lineIsFull()) || (!insertModeOn() && posIsEnd()))
        resizeData();
    if (insertModeOn()) {
        if (!lineIsFull()) {
            memmove(data + curPos + 1,
                    data + curPos,
                    dataLen - curPos + 1);
            dataLen++;
            if (firstPos > curPos)
                firstPos = curPos;
            assignPos(curPos++, value);
        }
    } else if (dataLen == curPos) {
        assignPos(curPos + 1, 0);
        data[curPos + 1] = 0;
    } else {
        if (firstPos > curPos)
            firstPos = curPos;
        if (curPos == dataLen)
            dataLen++;
        assignPos(curPos++, value);
    }
    return True;
}

Boolean TInputLine::insertCharEv(TEvent &event) {
    if (event.keyDown.charScan.charCode >= ' ') {
        if (!insertChar(event.keyDown.charScan.charCode))
            clearEvent(event);
        return True;
    }
    return False;
}

/**[txh]********************************************************************

 Description:
 Used internally to ensure the cursor is at a visible position, unselect
 the text and force a draw.

 ***************************************************************************/

void TInputLine::makeVisible() {
    selStart = 0;
    selEnd = 0;
    if (firstPos > curPos)
        firstPos = curPos;
    int i = curPos - size.x + 2;
    if (firstPos < i)
        firstPos = i;
    drawView();
}

void TInputLine::handleEvent(TEvent& event) {
    TView::handleEvent(event);

    int delta, anchor;
    if ((state & sfSelected) != 0)
        switch (event.what) {
        case evMouseDown:
            if (event.mouse.buttons == mbMiddleButton && TVOSClipboard::isAvailable() > 1) {
                pasteFromOSClipboard();
            } else if (canScroll(delta = mouseDelta(event))) {
                do {
                    if (canScroll(delta)) {
                        firstPos += delta;
                        drawView();
                    }
                } while (mouseEvent(event, evMouseAuto));
            } else if (event.mouse.doubleClick) {
                selectAll(True);
            } else {
                anchor = mousePos(event);
                do {
                    if (event.what == evMouseAuto && canScroll(delta = mouseDelta(event)))
                        firstPos += delta;
                    curPos = mousePos(event);
                    if (curPos < anchor) {
                        selStart = curPos;
                        selEnd = anchor;
                    } else {
                        selStart = anchor;
                        selEnd = curPos;
                    }
                    drawView();
                } while (mouseEvent(event, evMouseMove | evMouseAuto));
                if (TVOSClipboard::isAvailable() > 1)
                    copyToOSClipboard();
            }
            clearEvent(event);
            break;

        case evKeyDown:
            switch (ctrlToArrow(event.keyDown.keyCode)) {
            case kbLeft:
                if (curPos > 0)
                    curPos--;
                break;
            case kbRight:
                if (!posIsEnd())
                    curPos++;
                break;
            case kbHome:
                curPos = 0;
                break;
            case kbEnd:
                curPos = dataLen;
                break;
            case kbBack:
                if (curPos > 0) {
                    selStart = curPos - 1;
                    selEnd = curPos;
                    deleteSelect();
                    if (firstPos > 0)
                        firstPos--;
                }
                break;
            case kbDel:
                if (selStart == selEnd)
                    if (!posIsEnd()) {
                        selStart = curPos;
                        selEnd = curPos + 1;
                    }
                deleteSelect();
                break;
            case kbIns:
                setState(sfCursorIns, Boolean(!(state & sfCursorIns)));
                break;
            case kbCtrlY:
                assignPos(0, EOS);
                curPos = 0;
                break;
                // Let them pass even if these contains a strange ASCII (SET)
            case kbEnter:
            case kbTab:
                return;
            default:
                if (!insertCharEv(event))
                    return;
                break;
            }
            makeVisible();
            clearEvent(event);
            break;
        }
}

void TInputLine::selectAll(Boolean enable) {
    selStart = 0;
    if (enable)
        curPos = selEnd = dataLen;
    else
        curPos = selEnd = 0;
    firstPos = max(0, curPos - size.x + 2);
    if (TVOSClipboard::isAvailable() > 1)
        copyToOSClipboard();
    drawView();
}

void TInputLine::setState(ushort aState, Boolean enable) {
    if (validator && // We have a validator
            (modeOptions & ilValidatorBlocks) && // We want to block if invalid
            owner && (owner->state & sfActive) && // The owner is visible
            aState == sfFocused && enable == False) // We are losing the focus
    {
        TValidator *v = validator;
        validator = NULL; // Avoid nested tests
        Boolean ret = v->Valid(data); // Check if we have valid data
        validator = v;
        if (!ret) // If not refuse the focus change
            return;
    }
    TView::setState(aState, enable);
    if (aState == sfSelected || (aState == sfActive && (state & sfSelected)))
        selectAll(enable);
}

#if !defined( NO_STREAM )
void TInputLine::write(opstream& os)
{
    TView::write(os);
    os << maxLen << curPos << firstPos
    << selStart << selEnd;
    writeData(os);
    os << validator;
}

void TInputLine::writeData(opstream& os)
{
    os.writeString((T *)data);
}

void *TInputLine::read(ipstream& is)
{
    TView::read(is);
    is >> maxLen >> curPos >> firstPos
    >> selStart >> selEnd;
    readData(is);
    state|=sfCursorVis;
    is >> validator;
    return this;
}

void *TInputLine::readData(ipstream& is)
{
    cellSize=sizeof(T);
    data=(char *)new T[maxLen+1];
    is.readString((T *)data,maxLen+1);
    return data;
}

TStreamable *TInputLine::build()
{
    return new TInputLine(streamableInit);
}

TInputLine::TInputLine(StreamableInit) :
        TView(streamableInit),
        validator(NULL)
{
}

#endif // NO_STREAM

Boolean TInputLine::valid(ushort) {
    Boolean ret = True;
    if (validator) {
        ret = validator->Valid(data);
        if (ret == True) {
            validator->Format(data);
            drawView();
        }
    }
    return ret;
}

void TInputLine::setData(void *rec) {
    uint32 ds = dataSize() - sizeof(char);
    memcpy(data, rec, ds);
    *(data + ds) = EOS;
    dataLen = strlen(data);
    selectAll(True);
}

void TInputLine::setDataFromStr(void *str) {
    unsigned ds = dataSize() / sizeof(char) - 1, i;
    char *s = (char *) str;
    char *d = data;
    for (i = 0; i < ds && s[i]; i++)
        d[i] = s[i];
    d[i] = EOS;
    dataLen = i;
}

void TInputLine::assignPos(int index, unsigned val) {
    data[index] = val;
}

Boolean TInputLine::pasteFromOSClipboard() {
    unsigned size, i;
    char *p = (char *) TVOSClipboard::paste(1, size);
    if (p) {
        for (i = 0; i < size; i++) {
            insertChar(p[i]);
            selStart = selEnd = 0; // Reset the selection or we will delete the last insertion
        }
        delete [] p;
        makeVisible();
        return True;
    }
    return False;
}

void TInputLine::copyToOSClipboard() {
    TVOSClipboard::copy(1, data + selStart, selEnd - selStart);
}

void TInputLine::draw() {
    int l, r;
    TDrawBuffer b;

    uchar color = (state & sfFocused) ? getColor(2) : getColor(1);

    b.moveChar(0, ' ', color, size.x);
    b.moveStr(1, data + firstPos, color, size.x - 2);

    if (canScroll(1))
        b.moveChar(size.x - 1, rightArrow, (uchar) getColor(4), 1);
    if (canScroll(-1))
        b.moveChar(0, leftArrow, (uchar) getColor(4), 1);
    if (state & sfSelected) {
        l = selStart - firstPos;
        r = selEnd - firstPos;
        l = max(0, l);
        r = min(size.x - 2, r);
        if (l < r)
            b.moveChar(l + 1, 0, (uchar) getColor(3), r - l);
    }
    writeLine(0, 0, size.x, size.y, b);
    setCursor(curPos - firstPos + 1, 0);
}

