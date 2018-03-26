//---------------------------------------------------------------------------

#ifndef uEditParamsH
#define uEditParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>

#include "uTaskEntry.h"

//---------------------------------------------------------------------------
class TfrmEditParams : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TSplitter *Splitter1;
   TPanel *Panel3;
   TMemo *memParamEdit;
   TToolBar *ToolBar1;
   TActionList *ActionList1;
   TStatusBar *StatusBar1;
   TPanel *Panel5;
   TMemo *memExeTemplate;
   TSplitter *Splitter2;
   TPanel *Panel4;
   TPanel *Panel6;
   TButton *btnCloneTemplate;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
   __fastcall TfrmEditParams(TComponent* Owner);

   bool __fastcall Query(TaskEntry& ref);
   bool __fastcall Assign(const TaskEntry& ref);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditParams *frmEditParams;
//---------------------------------------------------------------------------
#endif
