#include "hotswap.hpp"

bool MoveFile(const ZStr& sFileFrom, const ZStr& sFileTo)
   {
   File fFrom;
   if(fFrom.Name(sFileFrom) == false)
      return false;
   File fTo;
   if(fTo.Name(sFileTo) == false)
      return false;
   if(fFrom.CopyTo(fTo) == true)
      return fFrom.Remove();
   return false;
   }


const char *HotSwap::_result_name(ZStr& str)
   {
   str = sFileName;
   str.Append(".HOT");
   return str.c_str();
   }
const char *HotSwap::_old_name(ZStr& str)
   {
   str = sFileName;
   str.Append(".OLD");
   return str.c_str();
   }
void HotSwap::ResultClear(void)
   {
   ZStr str;
   ::unlink(_result_name(str));
   ofstream ofs(str.c_str(), ios::out);
   }
void HotSwap::ResultSave(const ZStr& sBuffer)
   {
   ZStr str;
   ofstream ofs(_result_name(str), ios::out | ios::app);
   ofs << sBuffer.c_str();
   ofs << endl;
   }
void HotSwap::ResultAssertFinal(bool changed)
   {
   ZStr str;
   if(changed == true)
      {
      ::unlink(_old_name(str));
      MoveFile(sFileName.c_str(), str.c_str());
      MoveFile(_result_name(str), sFileName.c_str());
      }
   else
      {
      ::unlink(_old_name(str));
      ::unlink(_result_name(str));
      }
   }
void HotSwap::EvHit(const ZStr& sBuffer, size_t offset)
   {
   }
void HotSwap::EvHitFixup(const ZStr& sBuffer, size_t offset)
   {
   }
void HotSwap::EvDisplayError(const char *psz, ostream& os)
   {
   os << psz;
   os << endl;
   }
void HotSwap::EvFileName(const char *psz)
   {
   sFileName = psz;
   }
bool HotSwap::EvProgressMeter(size_t lines, ostream& os)
   {
   os << ".";
   return true;
   }
HotSwap::HotSwap(void)
   {
   }
HotSwap::~HotSwap(void)
   {
   }
bool HotSwap::Open(const ZStr& pszFileName)
   {
   ifstream ifs(pszFileName.c_str(), ios::in);
   if(ifs)
      {
      EvFileName(pszFileName.c_str());
      return true;
      }
   return false;
   }
const char *HotSwap::FileName(void)
   {
   return sFileName.c_str();
   }
size_t HotSwap::List(const ZStr& str, const ZStr& sReplacement, ostream& os)
   {
   return _exec(str, sReplacement, os, false);
   }
size_t HotSwap::Exec(const ZStr& str, const ZStr& sReplacement, ostream& os)
   {
   return _exec(str, sReplacement, os, true);
   }
size_t HotSwap::_replace_all(ZStr& sBuffer, const ZStr& str, const ZStr& replace)
   {
   size_t numHits = NULL;
   size_t ssHit   = sBuffer.Find(str);
   while(ssHit != NPOS)
      {
      numHits++;
      EvHit(sBuffer, ssHit);

      sBuffer.RemovePos(ssHit, ssHit + str.Length());
      sBuffer.Insert(ssHit, replace.c_str());

      EvHitFixup(sBuffer, ssHit);

      ssHit = sBuffer.Find(str.c_str(), ssHit + replace.Length());
      }
   return numHits;
   }
size_t HotSwap::_exec(const ZStr& str, const ZStr& sResult, ostream& os, bool saveit)
   {
   size_t sz_nelem = NULL;
   size_t total    = NULL;
   ifstream ifs(sFileName.c_str(), ios::in);
   if(!ifs)
      {
      EvDisplayError("Unable to open file.", os);
      return NULL;
      }

   if(saveit == true)
      ResultClear();

   ZStr sBuffer;
   while(ifs)
      {
      sBuffer = "";
      sBuffer.Readline(ifs);
      if(ifs)
         {
         size_t sz = sBuffer.Find(str);
         if(sz != NPOS)
            sz_nelem += _replace_all(sBuffer, str, sResult);

         if(saveit == true)
            ResultSave(sBuffer);

         EvProgressMeter(++total, os);
         }
      else
         {
         if(sBuffer.IsNull() == false)
            {
            // Hummmm ..... ?
            if(saveit == true)
               ResultSave(sBuffer);
            }
         }

      }

   ifs.close();
   if(saveit == true)
      {
      bool bChanged = false;
      if(sz_nelem)
         bChanged = true;
      ResultAssertFinal(bChanged);
      }
   return sz_nelem;
   }
