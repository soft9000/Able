//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QActnList.hpp>
#include <QExtCtrls.hpp>
#include <QImgList.hpp>
#include <QMenus.hpp>
#include <QTypes.hpp>

#include <FastJob.hpp>
#include <QButtons.hpp>
using namespace FastJob;

#include "uDomainLibrary.h"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TSplitter *Splitter1;
   TPanel *Panel2;
   TPanel *Panel3;
   TSplitter *Splitter2;
   TPanel *Panel4;
   TPanel *Panel5;
   TListBox *lbDomains;
   TListBox *lbRecords;
   TMemo *memRecord;
   TPanel *Panel6;
   TPanel *Panel7;
   TMainMenu *MainMenu1;
   TActionList *ActionList1;
   TImageList *ImageList1;
   TAction *actCreateFile;
   TMenuItem *File1;
   TMenuItem *actCreateFile1;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn3;
   TAction *actRecordUpdate;
   TAction *actRecordDelete;
   TAction *actRecordNew;
   TMenuItem *Record1;
   TMenuItem *New1;
   TMenuItem *Update1;
   TMenuItem *Delete1;
   TAction *actSaveFile;
   TMenuItem *actSaveFile1;
   TAction *actOpenSelected;
   TMenuItem *OpenSelected1;
   TAction *actStartFlash;
   TMenuItem *Testing1;
   TMenuItem *TestNow1;
   TAction *actResumeTest;
   TMenuItem *ResumeTest1;
   TBitBtn *BitBtn1;
   void __fastcall actCreateFileExecute(TObject *Sender);
   void __fastcall lbRecordsClick(TObject *Sender);
   void __fastcall actRecordUpdateExecute(TObject *Sender);
   void __fastcall actSaveFileExecute(TObject *Sender);
   void __fastcall actRecordDeleteExecute(TObject *Sender);
   void __fastcall actRecordNewExecute(TObject *Sender);
   void __fastcall lbDomainsDblClick(TObject *Sender);
   void __fastcall actOpenSelectedExecute(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall actStartFlashExecute(TObject *Sender);
   void __fastcall actResumeTestExecute(TObject *Sender);
private:	// User declarations
   struct pwSet
      {
      bool bDirty;
      File file;
      Array<DomainLibrary::FlashRecord> aData;
      pwSet(void) : bDirty(false)
         {
         file = DomainLibrary::DefaultDomain();
         }
      } project;

public:		// User declarations
   __fastcall TfrmMain(TComponent* Owner);
   void __fastcall Load(const File& file);
   void __fastcall Refresh(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
