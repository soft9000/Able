//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("uSpawn.cpp", frmSpawn);
USEFORM("uAboutBox.cpp", frmAboutBox);
USEFORM("uEditParams.cpp", frmEditParams);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TfrmSpawn), &frmSpawn);
       Application->CreateForm(__classid(TfrmAboutBox), &frmAboutBox);
       Application->CreateForm(__classid(TfrmEditParams), &frmEditParams);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   catch (...)
   {
       try
       {
          throw Exception("");
       }
       catch (Exception &exception)
       {
          Application->ShowException(&exception);
       }
   }
   return 0;
}
//---------------------------------------------------------------------------
