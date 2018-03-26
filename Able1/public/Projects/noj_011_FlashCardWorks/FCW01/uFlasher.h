//---------------------------------------------------------------------------

#ifndef uFlasherH
#define uFlasherH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#include <QExtCtrls.hpp>

#include "uFlashTest.h"
#include <QActnList.hpp>
#include <QImgList.hpp>

//---------------------------------------------------------------------------
class TfrmFlasher : public TForm
{
__published:	// IDE-managed Components
   TPanel *pnlBigName;
   TSplitter *Splitter1;
   TPanel *Panel2;
   TToolBar *ToolBar1;
   TToolButton *ToolButton1;
   TToolButton *ToolButton2;
   TToolButton *ToolButton3;
   TToolButton *ToolButton4;
   TToolButton *ToolButton5;
   TToolButton *ToolButton6;
   TToolButton *ToolButton7;
   TPanel *Panel3;
   TMemo *memRecord;
   TActionList *ActionList1;
   TImageList *ImageList1;
   TAction *actRemove;
   TAction *actPrevious;
   TAction *actNext;
   TToolButton *ToolButton8;
   TAction *actPeek;
   void __fastcall actNextExecute(TObject *Sender);
   void __fastcall actPreviousExecute(TObject *Sender);
   void __fastcall actPeekExecute(TObject *Sender);
   void __fastcall actRemoveExecute(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   size_t pwSS;
   FlashTest pwTest;
   void _fastcall Refresh(void);
public:		// User declarations
   __fastcall TfrmFlasher(TComponent* Owner);

   void __fastcall Use(const FlashTest& file);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFlasher *frmFlasher;
//---------------------------------------------------------------------------
#endif
