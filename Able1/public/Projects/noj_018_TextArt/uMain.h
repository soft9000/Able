//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
   TStatusBar *StatusBar1;
   TMainMenu *MainMenu1;
   TActionList *ActionList1;
   TPanel *Panel2;
   TPanel *Panel3;
   TPanel *Panel1;
   TPanel *Panel4;
   TSplitter *Splitter1;
   TImage *Image1;
   TPanel *Panel5;
   TSplitter *Splitter2;
   TListBox *ListBox1;
   TPaintBox *PaintBox1;
   TImageList *ImageList1;
   TGroupBox *GroupBox1;
   TSpeedButton *SpeedButton1;
   TSpeedButton *SpeedButton2;
   TGroupBox *GroupBox2;
   TSpeedButton *SpeedButton3;
   TSpeedButton *SpeedButton4;
   TEdit *edWidth;
   TEdit *edHeight;
   TLabel *Label1;
   TLabel *Label2;
   TCheckBox *CheckBox1;
   TColorDialog *ColorDialog1;
   TAction *actRefreshGrid;
   TAction *actRefreshText;
   TMenuItem *Picture1;
   TMenuItem *actRefreshGrid1;
   TMenuItem *actRefreshText1;
   TPopupMenu *popImageTools;
   TPopupMenu *popArtLoader;
   TMenuItem *Tools1;
   TAction *actToolText;
private:	// User declarations
public:		// User declarations
   __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
