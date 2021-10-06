/*---------------------------------------------------------------------*/
/*                                                                     */
/*   Turbo Vision Forms Demo main source file.                         */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/* This Turbo Vision application uses forms to enter and edit data     */
/* in a collection. Two data files, PHONENUM.F16 and PARTS.F16, are    */
/* provided and can be loaded using this application's File|Open menu. */
/* (PHONENUM.F32 and PARTS.F32 are used for the 32 bit version of      */
/*  TVFORMS)                                                           */
/*                                                                     */
/* The .F16 or .F32 files were created by GENFORMS.MAK, which compiles */
/* and runs GENFORM.CPP. You can create additional data files by       */
/* copying and modifying GENPARTS.H or GENPHONE.H and then             */
/* incorporating your new header into GENFORM.CPP.                     */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_TChDirDialog
#define Uses_TFileDialog
#define Uses_MsgBox
#define Uses_TDisplay
#define Uses_TScreen
#define Uses_TEditor
#define Uses_TMemo
#define Uses_TStreamableClass
#include <tvision/tv.h>
__link( RResourceCollection )
__link( RButton )
__link( RCheckBoxes )
__link( RInputLine )
__link( RLabel )
__link( RMenuBar )
__link( RRadioButtons )
__link( RFrame )
__link( REditor )
__link( RMemo )

#if !defined( __STRING_H )
#include  <string.h>
#endif // __STRING_H

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif // __STDLIB_H

static short winNumber = 0;


const char *fileToRead = "bible.cpp";
const int maxLineLength_ = maxViewWidth + 1;
const int maxLines = 100;
char *lines[maxLines];
int lineCount = 0;

void readFile(const char *fileName)
{
	FILE *fp = fopen(fileToRead, "r");

    if (fp == NULL) {
        perror("Failed: ");
        exit(1);
    }

    char buffer[maxLineLength_+1];

    int i = 0;
    while (fgets(buffer, maxLineLength_ - 1, fp)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\r")] = 0;
        buffer[strcspn(buffer, "\n")] = 0;

        lines[i] = (char *) malloc(maxLineLength_ * sizeof(char *));
        strcpy(lines[i], buffer);
        i++;

        if (i >= maxLines) {
            break;
        }
    }
    fclose(fp);    
}
class TInterior: public TView
{
public:
    TInterior(const TRect& bounds);
    virtual void draw();
};

TInterior::TInterior(const TRect& bounds): TView(bounds)
{
    growMode = gfGrowHiX | gfGrowHiY;
    options = options | ofFramed;
}

void TInterior::draw() {

    ushort color = getColor(0x0301);
    for (int i = 0; i < size.y; i++) {


        TDrawBuffer b;
        b.moveChar(0, ' ', color, size.x);
        if (lines[i]) {
            char s[maxLineLength_];
            strncpy(s, lines[i], size.x);
            s[size.x] = EOS;
            b.moveStr(0, s, color);
        }
        writeLine(0, i, size.x, 1, b);
        // writeStr(0, i, lines[i], 1);
    }
    // const char *hstr = "Hello World!";
    // ushort color = getColor(0x0301);
    // TView::draw();
    // TDrawBuffer b;
    // b.moveStr(0, hstr, color);
    // writeLine(4, 2, 12, 1, b);
}

class TDemoWindow: public TWindow
{
public:
    TDemoWindow( const TRect& r, const char *aTitle, short aNumber);
};

TDemoWindow::TDemoWindow( const TRect& bounds, const char *aTitle, short aNumber):
            TWindow(bounds, aTitle, aNumber),
            TWindowInit( &TDemoWindow::initFrame)
{
    TRect r = getClipRect();
    r.grow(-1, -1);
    insert(new TInterior(r));
}

class TBibleApp : public TApplication
{
public:
    TBibleApp();
    static TMenuBar *initMenuBar( TRect r);
    static TDeskTop *initDeskTop( TRect r);
    static TStatusLine *initStatusLine( TRect r);
    void handleEvent( TEvent& event );
    void myNewWindow();
};
// TBibleApp
void TBibleApp::myNewWindow()
{
    TRect r(0, 0, 26, 7);
    r.move(53, 16);
    TDemoWindow *window = new TDemoWindow(
        r, "Demo window", ++winNumber);
    
    deskTop->insert(window);
}

const int cmMyNewWin = 444;

void TBibleApp::handleEvent( TEvent& event )
{
    TApplication::handleEvent(event);
    if (event.what == evCommand) {
        switch(event.message.command)
        {
            case cmMyNewWin:
                myNewWindow();
                break;
            default:
                return;
        }
        clearEvent(event);
    }
}

TBibleApp::TBibleApp() :
    TProgInit(&TBibleApp::initStatusLine,
              &TBibleApp::initMenuBar,
              &TBibleApp::initDeskTop),
    TApplication()
{
}

TMenuBar *TBibleApp::initMenuBar( TRect r) {
    return NULL;
}

TStatusLine *TBibleApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;
        return (new TStatusLine( r,
      *new TStatusDef( 0, 50 ) +
        *new TStatusItem( "~F1~ My Win", kbF1, cmMyNewWin ) +
        *new TStatusItem( "~Alt-X~ Exitas", kbAltX, cmQuit ) +
        *new TStatusItem( "Howdy", kbF1, cmHelp )
        )
    );
}

TDeskTop *TBibleApp::initDeskTop( TRect r) {
    // r.a.y--;
    // r.b.y--;

    // TRect r(0, 0, 26, 7);
    // r.move(53, 16);
    TDemoWindow *window = new TDemoWindow(
        r, "Demo window", ++winNumber);

    // return window;
    return new TDeskTop(r);
}

int main()
{
    readFile(fileToRead);

    TBibleApp *bibleApp = new TBibleApp;

    bibleApp->run();

    TObject::destroy(bibleApp);

    return 0;
}
