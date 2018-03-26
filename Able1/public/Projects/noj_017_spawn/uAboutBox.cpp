//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uAboutBox.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TfrmAboutBox *frmAboutBox;
//--------------------------------------------------------------------- 
__fastcall TfrmAboutBox::TfrmAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmAboutBox::OKButtonClick(TObject *Sender)
{
Hide();   
}
//---------------------------------------------------------------------------

