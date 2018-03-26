#include "Taco.hpp"

using namespace Taco;

#define CHAR_UNDEF char(0xfe)

bool Job::Load(const Directory& dirSource, const LanguageInfo& lang, Job& job)
   {
   // DEFAULT loads the file type(s) for the default language.
   return false;
   }

bool Job::Save(const Job& job)
   {
   // DEFAULT loads the file type(s) for the default language.
   return false;
   }

bool Job::CodeToTaco(Job& job)
   {
   // Processed the files over to the .taco data file in the TACO sub-folder for the SOURCE
   return false;
   }

bool Job::TacoToCode(Job& job)
   {
   // Processed the files over to the .taco data file in the TACO sub-folder for the SOURCE
   return false;
   }

bool Job::HeaderFunList(Job& job)
   {
   for(size_t ss = 0L; ss < job.aFiles.Nelem(); ss++)
      {
      Extract(job.aFiles[ss], job, job.aDoc);
      }
   return true;
   }

ZStr Job::ExtractDeffBlock(istream& is, const Job& job)
   {
   int iComment = 0;

   stringstream srm;
   int iLevel = -1;
   char ch = 0;
   while(is)
      {
      is >> ch;

      // STEP: Comment On Logic
      if(ch == '/')
         {
         is >> ch;
         if(ch == '/')
            {
            // line comment on
            iComment = 1;
            continue;
            }
         if(ch == '*')
            {
            // block comment on
            iComment = 2;
            continue;
            }
         }

      // STEP: Comment Off Logic
      if(ch == '\n' && iComment == 1)
         {
         // line comment off
         iComment = 0;
         continue;
         }

      if(ch == '*')
         {
         is >> ch;
         if(ch == '/' && iComment == 1)
            {
            // block comment off
            iComment = 0;
            continue;
            }
         }
      
      // STEP: Comment Logic
      if(iComment)
         continue;

      // STEP: Level Block Detection
      if(ch == job.lang.chBlockStart)
         {
         if(iLevel == -1)
            iLevel = 0;

         iLevel++;

         if(iLevel == 1)
            srm << CHAR_UNDEF;
         continue;
         }

      if(ch == job.lang.chBlockEnd)
         {
         iLevel--;

         if(iLevel == 1)
            srm << endl;
         continue;
         }

      // STEP: Level Block Skipping
      if(iLevel == -1)
         continue;

      if(iLevel == 1)
         {
         if(ch == job.lang.chStatememt)
            ch = CHAR_UNDEF;
         srm << ch;
         continue;
         }

      if(iLevel == 0)
         break;
      }
      ZStr str = srm.str().c_str();
      return str;
   }

void Job::Extract(const File& fff, const Job& job, Array<Entry>& aResult)
   {
   int iLevel = 0;
   ZStr sNamespace, sObject, sMember, sWord;

   File file = fff;
   istream& is = file.OpenRead();
   char ch = 0;
   while(is)
      {
      if(sObject.IsNull() == false)
         {
         sWord = ExtractDeffBlock(is, job);
         Array<ZStr> array;
         sWord.Split(CHAR_UNDEF, array);
         for(size_t ss = 0L; ss < array.Nelem(); ss++)
            {
            Entry ent;
            ent.bFound = true;
            ent.sName = "/";
            ent.sName += sNamespace;
            ent.sName += "/";
            ent.sName += sObject;
            ent.sName += "/";
            ent.sName += array[ss];
            aResult.Append(ent);
            }
         sObject = ZStr();
         }
      else
         {
         sWord.ReadLine(is);
         if(!is)
            continue;
         if(sWord == job.lang.sKeyUsing)
            {
            sWord.ReadLine(is);
            // HEADER FILES - JUNK IT!
            continue;
            }
         if(sWord == job.lang.sKeyNamespace)
            {
            sWord.ReadLine(is);
            sNamespace = sWord;
            continue;
            }
         if(sWord == job.lang.sKeyClass)
            {
            sWord.ReadLine(is);
            sObject = sWord;
            continue;
            }
         if(sWord == job.lang.sKeyStruct)
            {
            sWord.ReadLine(is);
            sObject = sWord;
            continue;
            }
         if(sObject.IsNull())
            continue;
         }
      
      }
   }
