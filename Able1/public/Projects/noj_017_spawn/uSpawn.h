//---------------------------------------------------------------------------

#ifndef SPAWNH
#define SPAWNH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ToolWin.hpp>
#include <FileCtrl.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>

#include "uProgramInfo.h"

//---------------------------------------------------------------------------
class TfrmSpawn : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TTabSheet *TabSheet2;
   TPanel *pnlZed;
   TSplitter *Splitter1;
   TPanel *Panel1;
   TToolBar *tbTasks;
   TPanel *Panel2;
   TImage *Image1;
   TGroupBox *GroupBox1;
   TRadioButton *ckOnce;
   TRadioButton *ckDaily;
   TGroupBox *GroupBox2;
   TDateTimePicker *dtpDate;
   TDateTimePicker *dtpTime;
   TGroupBox *GroupBox3;
   TLabel *Label1;
   TLabel *Label2;
   TButton *btnFindTask;
   TListBox *lstParams;
   TButton *btnCreate;
   TButton *btnDelete;
   TStatusBar *StatusBar1;
   TActionList *ActionList1;
   TTimer *Timer1;
   TToolBar *tbMain;
   TPanel *Panel3;
   TPanel *Panel4;
   TSplitter *Splitter2;
   TPanel *Panel5;
   TFileListBox *fileListBox;
   TMemo *memLog;
   TAction *actTaskPick;
   TAction *actParamNew;
   TAction *actParamEdit;
   TAction *actParamDelete;
   TPopupMenu *popParam;
   TImageList *imgLstMain;
   TToolButton *ToolButton1;
   TToolButton *ToolButton2;
   TToolButton *ToolButton3;
   TToolButton *ToolButton4;
   TToolButton *ToolButton5;
   TToolButton *ToolButton6;
   TMenuItem *New1;
   TMenuItem *Edit1;
   TMenuItem *Delete1;
   TAction *actTaskClone;
   TToolButton *ToolButton7;
   TEdit *edProgram;
   TEdit *edPwLogFile;
   TOpenDialog *opnDlgTask;
   TButton *btnEdit;
   TTabSheet *Settings;
   TPanel *Panel6;
   TAction *actTaskNew;
   TAction *actTaskDelete;
   TPopupMenu *popTask;
   TMenuItem *actTaskNew1;
   TMenuItem *actTaskDelete1;
   TMenuItem *Clone1;
   TEdit *edTaskName;
   TLabel *Label3;
   TMemo *memComments;
   TToolButton *ToolButton8;
   TToolButton *ToolButton9;
   TAction *actAbout;
   TAction *actVisit;
   TToolButton *ToolButton10;
   TToolButton *ToolButton11;
   TButton *btnRefresh;
   TAction *actTaskRefresh;
   TDirectoryListBox *dirListBox;
   TPopupMenu *popLogList;
   TAction *actLogSelDelete;
   TMenuItem *Delete2;
   TAction *actLogSelRefresh;
   TToolBar *ToolBar1;
   TToolButton *ToolButton12;
   TToolButton *ToolButton13;
   TToolButton *ToolButton14;
   TToolButton *ToolButton15;
   TToolButton *ToolButton16;
   TListBox *lbTasks;
   TAction *actTimerStart;
   TAction *actTimerStop;
   TToolButton *ToolButton17;
   TToolButton *ToolButton18;
   TToolButton *ToolButton19;
   TToolButton *ToolButton20;
   TToolButton *ToolButton21;
   TGroupBox *GroupBox4;
   TCheckBox *ckAutoRunEnabled;
   TEdit *edPauseMinutes;
   TLabel *Label5;
   TCheckBox *ckTodayOnly;
   TGroupBox *GroupBox5;
   TEdit *edTimerSec;
   TLabel *Label4;
   TGroupBox *GroupBox6;
   TRadioButton *ckOkay;
   TRadioButton *ckError;
   void __fastcall actTaskPickExecute(TObject *Sender);
   void __fastcall actParamNewExecute(TObject *Sender);
   void __fastcall actParamEditExecute(TObject *Sender);
   void __fastcall actTaskNewExecute(TObject *Sender);
   void __fastcall actAboutExecute(TObject *Sender);
   void __fastcall actTaskDeleteExecute(TObject *Sender);
   void __fastcall actTaskCloneExecute(TObject *Sender);
   void __fastcall lbTasksClick(TObject *Sender);
   void __fastcall actParamDeleteExecute(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall actTaskRefreshExecute(TObject *Sender);
   void __fastcall fileListBoxChange(TObject *Sender);
   void __fastcall actLogSelDeleteExecute(TObject *Sender);
   void __fastcall actLogSelRefreshExecute(TObject *Sender);
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall actTimerStartExecute(TObject *Sender);
   void __fastcall actTimerStopExecute(TObject *Sender);
   void __fastcall edTaskNameChange(TObject *Sender);
   void __fastcall edProgramChange(TObject *Sender);
   void __fastcall memCommentsChange(TObject *Sender);
   void __fastcall dtpTimeChange(TObject *Sender);
   void __fastcall dtpDateChange(TObject *Sender);
   void __fastcall ckDailyClick(TObject *Sender);
   void __fastcall ckOnceClick(TObject *Sender);
   void __fastcall ckOkayClick(TObject *Sender);
   void __fastcall ckErrorClick(TObject *Sender);
private:	// User declarations
   int pwSS;
   TaskEntry pwTask;    // save the state of those things that are not stored in the GUI -
   ProgramInfo program;

   void __fastcall Refresh(void);
   void __fastcall LockUI(bool bLocked);
   void __fastcall SetTitle(const StdString& msg);

public:		// User declarations
   __fastcall TfrmSpawn(TComponent* Owner);
   bool __fastcall Query(TaskEntry& entry);
   bool __fastcall EditParams(TaskEntry& task);
   bool __fastcall Assign(const TaskEntry& entry);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSpawn *frmSpawn;
//---------------------------------------------------------------------------
#endif
