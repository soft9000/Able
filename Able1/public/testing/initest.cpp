// 2006/08/29: Updating, R. Nagy
//
#include <io.h>     // for unlink()

#include "inistrm.hpp"

const char IFILE[] = "test.ini";

using namespace ini;


void main(void)
  {
  IniSection  *pSection,  *pSection2;

  // First, we create a dummy INI file, add sections, and then save it;
  unlink(IFILE);

  IniFile *pFile = new IniFile(ZStr(IFILE));
  if(pFile->Exists() == false)
     {
     pSection = new IniSection(ZStr("[TEST]"));
     pSection->AddData(ZStr("Option1A"), ZStr("is FALSE"));
     pSection->AddData(ZStr("Option1B"), ZStr("is Usually FALSE"));

     pSection2 = new IniSection(ZStr("[TESTAGAIN]"));
     pSection2->AddData(ZStr("Option2A"), ZStr("is TRUE"));
     pSection2->AddData(ZStr("Option2B"), ZStr("is Usually TRUE"));

     pFile->AddSection(*pSection);
     pFile->AddSection(*pSection2);

     pFile->Write();
     delete pFile;
     }

  // Next, we Read it && Write it out again;
  pFile = new IniFile(ZStr(IFILE));
  pFile->Read();
  pFile->Write();
  delete pFile;

  // Finally, we Read it, add a section, and Write it;
  pFile = new IniFile(ZStr(IFILE));
  pFile->Read();
  pSection = new IniSection(ZStr("[TESTAGAIN2]"));
  pSection->AddData(ZStr("TESTaGaInA"), ZStr(" A1234"));
  pSection->AddData(ZStr("TESTaGaInB "), ZStr("B1234"));
  pSection->AddData(ZStr("TESTaGaInC"), ZStr(" C1234"));
  pSection->AddData(ZStr("TESTaGaInD "), ZStr("D1234"));
  pSection->AddData(ZStr("TESTaGaInE"), ZStr(" E1234"));
  pSection->AddData(ZStr("TESTaGaInF "), ZStr("F1234"));
  pFile->AddSection(*pSection);
  pFile->Write();
  delete pFile;

  // Next, we Read it && Write it out again;
  pFile = new IniFile(ZStr(IFILE));
  pFile->Read();
  pFile->Write();
  delete pFile;


  // Next, we Read it && Write it out again;
  ZStr sResult;
  pFile = new IniFile(ZStr(IFILE));
  pFile->Read();
  cout << endl << "FIND:" << pFile->Find(sResult, "TEST", "Option1A") << endl << endl;
  cout <<  "UPDATE: "        << pFile->Update("TEST", "Option1A", "HAS CHANGED") << endl << endl;
  cout << "FIND: "           << pFile->Find(sResult, "TEST", "Option1A") << endl << endl;

  pFile->Update("TESTAGAIN2", "TESTaGaInD ", "Also changed");
  pFile->Delete("TESTAGAIN2", "TESTaGaInB ");
  cout << "Should be 0: " << pFile->Update("TESTAGAIN2", "TESTaGaInB ", "Also changed") << endl;

  pFile->Write();
  delete pFile;

  }
