//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop

#include "uFlasher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.xfm"
TfrmFlasher *frmFlasher;
//---------------------------------------------------------------------------
__fastcall TfrmFlasher::TfrmFlasher(TComponent* Owner)
   : TForm(Owner), pwSS(0L)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmFlasher::Use(const FlashTest& file)
{
pwTest = file;
ZStr str = "Flashing ";
str += file.TestName();
Caption = str.c_str();
}




void __fastcall TfrmFlasher::actNextExecute(TObject *Sender)
{
pwSS++;
if(pwSS >= pwTest.info.Nelem())
   pwSS = 0L;
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmFlasher::actPreviousExecute(TObject *Sender)
{
if(pwSS != 0L)
   pwSS--;
Refresh();
}
//---------------------------------------------------------------------------


void _fastcall TfrmFlasher::Refresh(void)
{
memRecord->Visible = false;
DomainLibrary::FlashRecord rec = pwTest.info[pwSS];
pnlBigName->Caption = rec.sTag.c_str();
memRecord->Text = rec.sValue.c_str();
}
void __fastcall TfrmFlasher::actPeekExecute(TObject *Sender)
{
memRecord->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmFlasher::actRemoveExecute(TObject *Sender)
{
pwTest.info.Remove(pwSS);
if(pwSS >= pwTest.info.Nelem())
   pwSS = 0L;
Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmFlasher::FormClose(TObject *Sender,
      TCloseAction &Action)
{
pwTest.Save();
}
//---------------------------------------------------------------------------

