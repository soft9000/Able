//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSPAWN.h"
#include "uAboutBox.h"
#include <core/StdOid.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSpawn *frmSpawn;
//---------------------------------------------------------------------------
__fastcall TfrmSpawn::TfrmSpawn(TComponent* Owner)
   : TForm(Owner), pwSS(-1L)
{
}
//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::actTaskPickExecute(TObject *Sender)
{
if(opnDlgTask->Execute() == true)
   {
   lstParams->Clear();
   edProgram->Text = opnDlgTask->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actParamNewExecute(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
lstParams->Items->Add("New Param");
}

//---------------------------------------------------------------------------

bool __fastcall TfrmSpawn::EditParams(TaskEntry& task)
{
bool br = false;
int iPos = lstParams->ItemIndex;
if(iPos == -1)
   return false;
AnsiString ans = lstParams->Items->Strings[iPos];
if(InputQuery("Parameter", "Edit parameter", ans) == true)
   {
   lstParams->Items->Strings[iPos] = ans;
   br = true;
   }
return br;
}

//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actParamEditExecute(TObject *Sender)
{
int iPos = lstParams->ItemIndex;
if(iPos != -1)
   {
   if(btnRefresh->Enabled == false)
      btnRefresh->Enabled = true;
   TaskEntry task;
   Query(task);
   if(EditParams(task) == true)
      Assign(task);
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::actTaskNewExecute(TObject *Sender)
{
Timer1->Enabled = false;
LockUI(false);
TaskEntry task;
task.sTaskName += " Set";
program.aTasks.Append(task);
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actAboutExecute(TObject *Sender)
{
frmAboutBox->Show();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSpawn::Query(TaskEntry& entry)
{
   entry = pwTask;
   if(ckOnce->Checked  == true)
      entry.bOnceOnly = true;
   else
      entry.bOnceOnly = false;

   if(ckOkay->Checked  == true)
      {
      entry.bHasRun = false;
      entry.bHasFailed = false;
      }
   else
      {
      entry.bHasRun = true;
      entry.bHasFailed = true;
      }

   entry.pwFile.Name(edProgram->Text.c_str());
   entry.sTaskName = edTaskName->Text.c_str();
   entry.sComment  = memComments->Text.c_str();

   unsigned short i1, i2, i3, i4;
   dtpDate->Date.DecodeDate(&i1, &i2, &i3);
   entry.sdtNext.EncodeDate(i1, i2, i3);

   dtpTime->Time.DecodeTime(&i1, &i2, &i3, &i4);
   entry.sdtNext.EncodeTime(i1, i2, i3);

   Array<ZStr> array;
   for(int ss = 0; ss < lstParams->Count; ss++)
      array.Append(lstParams->Items->Strings[ss].c_str());
   entry.EncodeParams(array);
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSpawn::Assign(const TaskEntry& entry)
{
if(entry.bOnceOnly == true)
   {
   ckOnce->Checked  = true;
   ckDaily->Checked = false;
   }
else
   {
   ckOnce->Checked  = false;
   ckDaily->Checked = true;
   }

if(entry.bHasFailed == true)
   {
   ckOkay->Checked  = false;
   ckError->Checked = true;
   }
else
   {
   ckOkay->Checked  = true;
   ckError->Checked = false;
   }

if(entry.IsNull())
   {
   edProgram->Text = "";
   edTaskName->Text = "";
   memComments->Text = "";
   }
else
   {
   edProgram->Text = entry.pwFile.Name();
   edTaskName->Text = entry.sTaskName.c_str();
   memComments->Text = entry.sComment.c_str();
   }
unsigned i1, i2, i3;
i1 = i2 = i3 = 0;

// dtpDate
entry.sdtNext.DecodeDate(i1, i2, i3);
TDateTime *pFoo = new TDateTime((unsigned short)i1, (unsigned short)i2, (unsigned short)i3);
dtpDate->Date = *pFoo;
delete pFoo;

// dtpTime
entry.sdtNext.DecodeTime(i1, i2, i3);
pFoo = new TDateTime((unsigned short)i1, (unsigned short)i2, (unsigned short)i3, 0);
dtpTime->Time = *pFoo;
delete pFoo;

// lstParams
lstParams->Items->Clear();
Array<ZStr> array;
entry.DecodeParams(array);
for(size_t ss = 0L; ss < array.Nelem(); ss++)
   lstParams->Items->Add(array[ss].c_str());

pwTask = entry;
return true;
}

void __fastcall TfrmSpawn::Refresh(void)
{
lbTasks->Items->Clear();
AnsiString ans;
for(size_t ss = 0L; ss < program.aTasks.Nelem(); ss++)
   {
   if(program.aTasks[ss].bHasFailed == true)
      ans = "(!) - ";
   else
      ans = "(+) - ";
   ans += program.aTasks[ss].sTaskName.c_str();
   lbTasks->Items->Add(ans);
   }
if(pwSS != -1L)
   lbTasks->ItemIndex = pwSS;

// Update the caption
if(Timer1->Enabled == false)
   SetTitle("(Paused)");
else
   SetTitle("(Running)");

// Update the log view -
fileListBox->Update();
}

void __fastcall TfrmSpawn::actTaskDeleteExecute(TObject *Sender)
{
int iPos = lbTasks->ItemIndex;
if(iPos == -1)
   return;
Timer1->Enabled = false;
if(pwSS == iPos)
   {
   TaskEntry task;
   Assign(task);
   }
program.aTasks.Remove(iPos);
pwSS = -1L;
if(!program.aTasks.Nelem())
   {
   TaskEntry task;
   Assign(task);
   LockUI(true);
   }
Refresh();

if(!iPos)
   {
   if(lbTasks->Items->Count)
      lbTasks->ItemIndex = iPos;
   return;
   }
if(iPos > lbTasks->Items->Count)
   iPos--;
lbTasks->ItemIndex = iPos;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actTaskCloneExecute(TObject *Sender)
{
int iPos = lbTasks->ItemIndex;
if(iPos == -1)
   return;
Timer1->Enabled = false;
TaskEntry task = program.aTasks[iPos];
program.aTasks.Append(task);
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::lbTasksClick(TObject *Sender)
{
int iPos = lbTasks->ItemIndex;
if(iPos == -1)
   return;
TaskEntry entry;
// Get the GUI record is ever opened for editing
if(pwSS != -1L)
   {
   if(btnRefresh->Enabled == true)
      {
      Query(entry);
      program.aTasks[pwSS] = entry;
      }
   }
// Assign the selection
pwSS = iPos;
entry = program.aTasks[pwSS];
Assign(entry);

btnRefresh->Enabled = false;

Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actParamDeleteExecute(TObject *Sender)
{
int iPos = lstParams->ItemIndex;
if(iPos != -1)
   {
   if(btnRefresh->Enabled == false)
      btnRefresh->Enabled = true;
   lstParams->Items->Delete(iPos);
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::LockUI(bool bLocked)
{
if(bLocked)
   {
   // Lock down the editable portions of the UI -
   edProgram->Enabled = false;
   edTaskName->Enabled = false;
   memComments->Enabled = false;
   lstParams->Enabled = false;

   dtpDate->Enabled = false;
   dtpTime->Enabled = false;

   btnCreate->Enabled = false;
   btnEdit->Enabled = false;
   btnDelete->Enabled = false;
   btnFindTask->Enabled = false;
   btnRefresh->Enabled = false;

   ckDaily->Enabled = false;
   ckOnce->Enabled = false;
   }
else
   {
   edProgram->Enabled = true;
   edTaskName->Enabled = true;
   memComments->Enabled = true;
   lstParams->Enabled = true;

   dtpDate->Enabled = true;
   dtpTime->Enabled = true;

   btnCreate->Enabled = true;
   btnEdit->Enabled = true;
   btnDelete->Enabled = true;
   btnFindTask->Enabled = true;
   btnRefresh->Enabled = true;

   ckDaily->Enabled = true;
   ckOnce->Enabled = true;
   }
}
void __fastcall TfrmSpawn::FormCreate(TObject *Sender)
{
Refresh();
if(program.aTasks.Nelem() == 0L)
   LockUI(true);
dirListBox->Directory = program.pwLog.pwFile.QueryParent().c_str();

ZStr str;
str.assign(program.options.iTimerSec);
edTimerSec->Text = str.c_str();

str.assign(program.options.iPauseMinutes);
edPauseMinutes->Text = str.c_str();

ckAutoRunEnabled->Checked = program.options.bAutoRun;
ckTodayOnly->Checked = program.options.bDayOnly;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::FormDestroy(TObject *Sender)
{
// Get the last one -
lbTasksClick(Sender);

// Fill out the entire set of program options -
ZStr str = edTimerSec->Text.c_str();
program.options.iTimerSec = str.AsInt();

str = edPauseMinutes->Text.c_str();
program.options.iPauseMinutes = str.AsInt();

program.options.bAutoRun = ckAutoRunEnabled->Checked;
program.options.bDayOnly = ckTodayOnly->Checked;

// And save EVERYthing -
if(program.Save() == false)
   ShowMessage("Error: Unable to save task list!");
}
//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::actTaskRefreshExecute(TObject *Sender)
{
lbTasksClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::fileListBoxChange(TObject *Sender)
{
AnsiString ans = edPwLogFile->Text;
ZStr str = ans.c_str();
if(str.Find('*') != npos)
   return;  // Mask - setup - yikes -

if(ans.IsEmpty() == false)
   {
   File file;
   if(file.Name(ans.c_str()) == false)
      {
      ShowMessage(AnsiString("Error: Invalid file name - ") + ans);
      return;
      }
   ZStr str;
   File::LoadText(file, str);
   str.Replace("\r\n", "\n");
   str.Replace("\n", "\r\n");
   memLog->Text = str.c_str();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actLogSelDeleteExecute(TObject *Sender)
{
ZStr str = edPwLogFile->Text.c_str();

if(str.IsNull() == false)
   {
   File file;
   if(file.Name(str) == false)
      {
      ShowMessage(AnsiString("Error: Invalid file name - ") + str.c_str());
      return;
      }
   int iRes = MessageDlg(AnsiString("Okay to remove ") + file.QueryNode(str) + "?",
            mtInformation, TMsgDlgButtons() << mbOK, 0);
   if(iRes == mrOk)
      {
      if(file.Remove() == false)
         ShowMessage("Unable to remove file.");
      }
   }
   fileListBox->Update();
   memLog->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actLogSelRefreshExecute(TObject *Sender)
{
   fileListBox->Update();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::Timer1Timer(TObject *Sender)
{
   if(TaskEntry::Manage(program.aTasks, program.pwLog) == false)
      StatusBar1->SimpleText = "WARNING: Unable to manage task list!";
   Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TfrmSpawn::SetTitle(const ZStr& msg)
{
ZStr sToken = " - ";
ZStr str = Caption.c_str();
str.Remove(str.Find(sToken));
str.Append(sToken);
str.Append(msg);
Caption = str.c_str();
}

//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::actTimerStartExecute(TObject *Sender)
{
ZStr str = edTimerSec->Text.c_str();
int interval = str.AsInt() * 1000;
Timer1->Interval = interval;
Timer1->Enabled = true;
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::actTimerStopExecute(TObject *Sender)
{
Timer1->Enabled = false;
Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TfrmSpawn::edTaskNameChange(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::edProgramChange(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::memCommentsChange(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::dtpTimeChange(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::dtpDateChange(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::ckDailyClick(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::ckOnceClick(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmSpawn::ckOkayClick(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpawn::ckErrorClick(TObject *Sender)
{
if(btnRefresh->Enabled == false)
   btnRefresh->Enabled = true;
}
//---------------------------------------------------------------------------

