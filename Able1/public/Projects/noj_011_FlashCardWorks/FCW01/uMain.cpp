//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop

#include "uMain.h"
#include "uFlasher.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.xfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
   : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::Refresh(void)
{
lbRecords->Clear();
memRecord->Text = "";
for(size_t ss = 0L; ss < project.aData.Nelem(); ss++)
   {
   DomainLibrary::FlashRecord& rec = project.aData[ss];
   lbRecords->Items->Append(rec.sTag.c_str());
   }
   
Array<File> aFiles;
lbDomains->Clear();
DomainLibrary::Query(aFiles);
ZStr sNode = project.file.QueryNode();
sNode.ToLower();
bool bGot = false;
for(size_t ss = 0L; ss < aFiles.Nelem(); ss++)
   {
   File& file = aFiles[ss];
   
   // Only want domain files
   if(DomainLibrary::IsDomain(file) == false)
      continue;

   ZStr sVal = aFiles[ss].QueryNode();
   sVal.ToLower();
   if(sVal == sNode)
      bGot = true;
   lbDomains->Items->Append(aFiles[ss].QueryNode().c_str());
   }
if(bGot == false)
   {
   sNode = project.file.QueryNode();
   sNode.Append(" *");
   lbDomains->Items->Insert(0, sNode.c_str());
   }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::Load(const File& file)
{
project.aData.Empty();
project.file = file;
project.bDirty = false;
if(file.Exists() == false)
   {
   DomainLibrary::FlashRecord rec;
   rec.sTag = "TAG";
   rec.sValue = "Enter the definition here.";
   project.aData.Append(rec);
   Refresh();
   return;
   }
if(DomainLibrary::Read(project.file, project.aData) == false)
   {
   ShowMessage("Error: Unable to load data.");
   }
Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::actCreateFileExecute(TObject *Sender)
{
AnsiString ans;
if(InputQuery("New Flash Card Domain", "File Name", ans) == false)
   return;
File file;
if(file.Name(ans.c_str()) == false)
   {
   ShowMessage("Error: Invalid file name.");
   return;
   }
if(DomainLibrary::Home(file) == false)
   {
   ShowMessage("Error: Unable to Home() this file!");
   return;
   }
Load(file);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbRecordsClick(TObject *Sender)
{
int iPos = lbRecords->ItemIndex;
if(iPos == -1)
   return;
memRecord->Text = project.aData[iPos].ToString().c_str();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actRecordUpdateExecute(TObject *Sender)
{
DomainLibrary::FlashRecord rec;
ZStr str = memRecord->Lines->GetText();
if(rec.FromString(str) == false)
   {
   rec.sTag = "TAG";
   rec.sValue = str;
   }
int iPos = lbRecords->ItemIndex;
if(iPos == -1)
   return;
project.aData[iPos] = rec;
Refresh();
project.bDirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actSaveFileExecute(TObject *Sender)
{
if(DomainLibrary::Write(project.file, project.aData) == false)
   {
   ShowMessage("Error: Unable to save data!");
   return;
   }
project.bDirty = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actRecordDeleteExecute(TObject *Sender)
{
int iPos = lbRecords->ItemIndex;
if(iPos == -1)
   return;
project.aData.Remove(iPos);
Refresh();
project.bDirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actRecordNewExecute(TObject *Sender)
{
DomainLibrary::FlashRecord rec;
project.aData.Insert(rec, 0);
Refresh();
project.bDirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbDomainsDblClick(TObject *Sender)
{
actOpenSelectedExecute(Sender);   
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actOpenSelectedExecute(TObject *Sender)
{
int iPos = lbDomains->ItemIndex;
if(iPos == -1)
   return;
File file;
AnsiString ans = lbDomains->Items->operator [](iPos);
ZStr str = ans.c_str();

// In-memory file click -
if(str.EndsWith("*") == true)
   return;

if(file.Name(str) == false)
   {
   ShowMessage("Error: Bad file name selected?");
   return;
   }
if(DomainLibrary::Home(file) == false)
   {
   ShowMessage("Error: Bad file name / home");
   return;
   }
Load(file);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
if(project.file.Exists() == false)
   {
   DomainLibrary::FlashRecord rec;
   project.aData.Append(rec);
   project.bDirty = true;
   actSaveFileExecute(Sender);
   }
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actStartFlashExecute(TObject *Sender)
{
FlashTest test = FlashTest::Create(project.aData);
frmFlasher->Use(test);
frmFlasher->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actResumeTestExecute(TObject *Sender)
{
FlashTest test;
test.Read();
frmFlasher->Use(test);
frmFlasher->ShowModal();
}
//---------------------------------------------------------------------------

