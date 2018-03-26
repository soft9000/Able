//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uEditParams.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEditParams *frmEditParams;
//---------------------------------------------------------------------------
__fastcall TfrmEditParams::TfrmEditParams(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool __fastcall TfrmEditParams::Query(TaskEntry& ref)
   {
   }
bool __fastcall TfrmEditParams::Assign(const TaskEntry& ref)
   {
   }

