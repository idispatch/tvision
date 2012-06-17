/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.
 *
 *
 */

/* ---------------------------------------------------------------------- */
/*      class TInputLine                                                  */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Passive                                                     */
/*        2 = Active                                                      */
/*        3 = Selected                                                    */
/*        4 = Arrows                                                      */
/* ---------------------------------------------------------------------- */

#ifndef TInputLine_defined
#define TInputLine_defined

const unsigned ilValidatorBlocks = 1; // Don't pass the focus if the validator indicates
// the data isn't valid. by SET.

class TInputLine: public TView {
public:
    TInputLine(const TRect& bounds, int aMaxLen);
    ~TInputLine();

    virtual uint32 dataSize();
    virtual void getData(void *rec);
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    void selectAll(Boolean enable);
    virtual void setState(ushort aState, Boolean enable);
    void SetValidator(TValidator *);
    Boolean valid(ushort);
    Boolean insertChar(unsigned val); // Added by SET
    Boolean insertCharEv(TEvent &event);
    void assignPos(int index, unsigned val);
    Boolean pasteFromOSClipboard();
    void copyToOSClipboard();
    void setDataFromStr(void *str);
    const void *getData() { return data; }
    virtual void setData(void *rec);
    void draw();

    // Functions to fine tune the behavior. by SET.
    unsigned setModeOptions(unsigned newOps) {
        unsigned old = modeOptions;
        modeOptions = newOps;
        return old;
    }
    unsigned getModeOptions() {
        return modeOptions;
    }
    static unsigned setDefaultModeOptions(unsigned newOps) {
        unsigned old = defaultModeOptions;
        defaultModeOptions = newOps;
        return old;
    }
    static unsigned getDefaultModeOptions() {
        return defaultModeOptions;
    }

    int curPos;
    int firstPos;
    int selStart;
    int selEnd;

    static char rightArrow;
    static char leftArrow;
    static char orightArrow;
    static char oleftArrow;

protected:
    virtual void resizeData() {}
    TValidator * validator;
    void deleteSelect();
    void makeVisible(); // Added by SET
    Boolean canScroll(int delta);

    // Inline helpers to make the code cleaner
    int insertModeOn();
    int lineIsFull();
    int posIsEnd();

    // IMHO exposing these two is a very bad idea, I added a couple of members to
    // work with them: setDataFromStr & getData. All TV code uses these new
    // members. If we don't hide them then we must compute the string length all
    // the time. SET.
    char *data;
    int maxLen;

    int dataLen;

    // To fine tune the behavior. SET.
    static unsigned defaultModeOptions;
    unsigned modeOptions;

private:
    int mouseDelta(TEvent& event);
    int mousePos(TEvent& event);

#if !defined( NO_STREAM )
    //virtual const char *streamableName() const
    //    { return name; }

protected:

    TInputLineBase(StreamableInit);
    virtual void write(opstream&);
    virtual void *read(ipstream&);
    virtual void writeData(opstream&)=0;
    virtual void *readData(ipstream&)=0;

public:

    //static const char * const name;
    //static TStreamable *build();
#endif // NO_STREAM
};

#if !defined( NO_STREAM )
inline ipstream& operator >> ( ipstream& is, TInputLineBase& cl )
{   return is >> (TStreamable&)cl;}
inline ipstream& operator >> ( ipstream& is, TInputLineBase*& cl )
{   return is >> (void *&)cl;}

inline opstream& operator << ( opstream& os, TInputLineBase& cl )
{   return os << (TStreamable&)cl;}
inline opstream& operator << ( opstream& os, TInputLineBase* cl )
{   return os << (TStreamable *)cl;}
#endif // NO_STREAM

inline
int TInputLine::insertModeOn() {
    return (state & sfCursorIns) == 0;
}

inline
int TInputLine::lineIsFull() {
    return dataLen >= maxLen;
}

inline
int TInputLine::posIsEnd() {
    return curPos >= dataLen;
}

#if !defined( NO_STREAM )
inline ipstream& operator >> ( ipstream& is, TInputLine& cl )
{   return is >> (TStreamable&)cl;}
inline ipstream& operator >> ( ipstream& is, TInputLine*& cl )
{   return is >> (void *&)cl;}

inline opstream& operator << ( opstream& os, TInputLine& cl )
{   return os << (TStreamable&)cl;}
inline opstream& operator << ( opstream& os, TInputLine* cl )
{   return os << (TStreamable *)cl;}
#endif // NO_STREAM

#if 0
#ifndef TInput1Line_defined
#define TInput1Line_defined
// This is based on TVTools idea, but I think is better to implement it
// in this way and not like a macro.
class TInput1Line: public TInputLine {
public:
    TInput1Line(int x, int y, int max) :
    TInputLine(TRect(x,y,x+max+2,y+1), max)) {};
};
#endif
#endif

#endif
