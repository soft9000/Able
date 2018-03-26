//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

#include "uProjectData.h"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TSplitter *Splitter1;
   TPanel *Panel3;
   TListBox *ListBox1;
   TPanel *Panel4;
   TSplitter *Splitter2;
   TStaticText *StaticText1;
   TStaticText *StaticText2;
   TStaticText *StaticText3;
   TLabel *lblSite;
   TLabel *lblFolder;
   TLabel *lblFiles;
   TToolBar *ToolBar1;
   TStatusBar *StatusBar1;
   TToolButton *ToolButton1;
   TToolButton *ToolButton2;
   TToolButton *ToolButton3;
   TToolButton *ToolButton4;
   TActionList *ActionList1;
   TToolBar *ToolBar2;
   TToolButton *ToolButton7;
   TToolButton *ToolButton8;
   TToolButton *ToolButton9;
   TToolButton *ToolButton10;
   TToolBar *ToolBar3;
   TToolButton *ToolButton11;
   TToolButton *ToolButton12;
   TToolButton *ToolButton13;
   TToolButton *ToolButton14;
   TToolButton *ToolButton15;
   TToolButton *ToolButton16;
   TAction *actSiteInfoCreate;
   TAction *actSiteInfoDelete;
   TAction *actSiteInfoEdit;
   TAction *actCheckSite;
   TAction *actProcessSite;
   TToolButton *ToolButton17;
   TToolButton *ToolButton18;
   TAction *actEditIrcaTemplate;
   TToolButton *ToolButton5;
   TToolButton *ToolButton6;
   TMemo *memReport;
   void __fastcall FormCreate(TObject *Sender);
private:	// User declarations

   ProjectData project;

public:		// User declarations
   __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
