#include <Able1.hpp>
using namespace Able1;

bool PicketFile::Recall(const File& fff, ZStr& sResult, const ZStr& sTokenSep, size_t ssPos)
   {
   File file = fff;
   istream& is = file.OpenRead();
   size_t which = 0L;
   ZStr sLine;
   while(is)
      {
      sLine.Readline(is, sTokenSep);
      if(!is)
         return false;
      sResult = sLine;
      sLine.MkWhite();
      sLine.Strip();
      if(which == ssPos)   // 08/14/2007, R. Nagy (removed loop while record content was NULL)
         return true;
      else
         which++;
      }
   return false;
   }

bool PicketFile::Recall(const File& file, ZStr& sResult, const ZStr& sToken)
   {
   return Recall(file, sResult, sToken, 0L);
   }

bool PicketFile::Write(const File& file, Array<ZStr>& aResult, const ZStr& sTokenSep)
   {
   File f2 = file;
   ostream& os = f2.OpenWrite(File::AT_BINARY);
   bool br = Write(os, aResult, sTokenSep);
   f2.Close();
   return br;
   }
bool PicketFile::Write(ZStr& sOutput, Array<ZStr>& aResult, const ZStr& sTokenSep)
   {
   stringstream srm;
   bool br = Write(srm, aResult, sTokenSep);
   sOutput = PRESTO(srm);
   return br;
   }
bool PicketFile::Write(ostream& os, Array<ZStr>& aResult, const ZStr& sTokenSep)
   {
   for(size_t ss = 0L; ss < aResult.Nelem(); ss++)
      os << sTokenSep << aResult[ss];
   os << sTokenSep;
   return true;
   }

bool PicketFile::Read(const File& file, Array<ZStr>& aResult, const ZStr& sTokenSep)
   {
   File f2 = file;
   istream& is = f2.OpenRead();
   bool br = Read(is, aResult, sTokenSep);
   f2.Close();
   return br;
   }
bool PicketFile::Read(const ZStr& sData, Array<ZStr>& aResult, const ZStr& sToken)
   {
   sData.Split(sToken, aResult);
   if(aResult.Nelem())
      return true;
   return false;
   }
bool PicketFile::Read(istream& is, Array<ZStr>& aResults, const ZStr& sToken)
   {
   aResults.Empty();
   ZStr sLine;
   while(is)
      {
      sLine.Readline(is, sToken);
      if(!is)
         continue;
      aResults.Append(sLine);
      }
   if(aResults.Nelem())
      return true;
   return false;
   }
