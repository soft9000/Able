#include "FileConversion.hpp"

using namespace FileConversion;

bool TextReader::ReadFirst(Array<ZStr>& aResult, LinearType type)
   {
   delete pReader;
   pReader = 0L;

   switch(type)
      {
      case ltCsv:
         {
         pReader = new CsvLine();
         }
      break;

      case ltTab:
         {
         pReader = new TabbedLine();
         }
      break;

      case ltSdf: 
      // At some point we will auto-detect the parameters 
      // required for this one - but not now -
      default:
      break;
      }

   if(pReader)
      {
      if(pwFile.Exists() == false)
         {
         delete pReader;
         sLastError = ZStr("Not found: ") + pwFile.Name();
         return false;
         }
      // At some point we should use the binary mode so 
      // as to make Linux <-> Win32 transitions easier -
      if(!pwFile.OpenRead())
         {
         delete pReader;
         sLastError = ZStr("Cannot Read: ") + pwFile.Name();
         return false;
         }
      }

   return ReadNext(aResult);
   }
bool TextReader::ReadNext(Array<ZStr>& aResult)
   {
   if(!pReader)
      {
      sLastError = "Unsupported LinearType Reader.";
      return false;
      }
   istream& is = pwFile.Resume();
   bool br = pReader->Readline(is, aResult);
   if(br == false)
      {
      sLastError = pReader->sLastError;
      pwFile.Close();
      delete pReader;
      pReader = 0L;
      }
   return br;
   }

bool TextReader::Recall(size_t zbRecordId, const File& fff, Array<ZStr>& aResult, LinearType type)
   {
   bool br = false;

   File file = fff;

   TextReader Reader(file);

   br = Reader.ReadFirst(aResult, type);
   if(br == false)
      return br;

   size_t pwRec = 0L;
   if(zbRecordId)
      {
      while(pwRec != zbRecordId)
         {
         br = Reader.ReadNext(aResult);
         if(br == false)
            break;
         pwRec++;
         }
      }
   return br;
   }
