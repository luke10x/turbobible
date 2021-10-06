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


class TBibleApp : public TApplication
{
public:
    TBibleApp();
    static TStatusLine *initStatusLine( TRect r);
};

// TBibleApp
TBibleApp::TBibleApp() :
    TProgInit(&TBibleApp::initStatusLine,
              &TBibleApp::initMenuBar,
              &TBibleApp::initDeskTop),
    TApplication()
{
}


TStatusLine *TBibleApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;
        return (new TStatusLine( r,
      *new TStatusDef( 0, 50 ) +
        *new TStatusItem( "~F1~ Help", kbF1, cmHelp ) +
        *new TStatusItem( "~Alt-X~ Exitas", kbAltX, cmQuit ) +
        *new TStatusItem( "Howdy", kbF1, cmHelp )
        )
    );
}

int main()
{
    TBibleApp *bibleApp = new TBibleApp;

    bibleApp->run();

    TObject::destroy(bibleApp);

    return 0;
}
