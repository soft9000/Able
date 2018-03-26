//---------------------------------------------------------------------------

#ifndef uFlashTestH
#define uFlashTestH
//---------------------------------------------------------------------------

#include "uDomainLibrary.h"

class FlashTest
   {
   public:
      File file;
      Array<DomainLibrary::FlashRecord> info;

      FlashTest(void)
         {
         file = DomainLibrary::DefaultTest();
         }

      StdString TestName(void)
         {
         StdString str;
         str += file.QueryNode();
         return str;
         }

      // Create a file using the default test name - If you want other
      // name, just use Write(below) with ANY other file name
      static FlashTest Create(Array<DomainLibrary::FlashRecord>& set)
         {
         FlashTest res;
         res.info = set;
         return res;
         }

      bool Save(void)
         {
         return WriteTest(file);
         }

      // Convert file name on write -
      bool WriteTest(const File& fff)
         {
         File pwf = fff;
         if(DomainLibrary::IsTest(pwf) == false)
            {
            if(pwf.Name(pwf.Name() + DomainLibrary::sTestFileType) == false)
               return false;
            if(DomainLibrary::Home(pwf) == false)
               return false;
            }
         if(DomainLibrary::Write(pwf, info) == false)
            return false;
         file = pwf;
         return file.Exists();
         }

      // Read w/o file name conversion -
      bool Read(void)
         {
         return Read(file);
         }

      // Read w/o file name conversion -
      bool Read(const File& fff)
         {
         if(DomainLibrary::IsTest(fff) == false)
            {
            if(DomainLibrary::IsDomain(fff) == false)
               return false;
            }
         if(DomainLibrary::Read(fff, info) == false)
            return false;
         file = fff;
         return true;
         }
   };

#endif
