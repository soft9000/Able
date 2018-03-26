// 10/24/1998, Ran through NOTAB, R. Nagy
//

#include <obsolete/Server/Email.hpp>


void EMailLines::Assign(const EMail& em)
   {
   stringstream srm;
   em.Dump(srm);
   srm << ends;
   sLines = PRESTO(srm).c_str();
   }
bool EMailLines::FirstLine(ZStr& std)
   {
   szLastPos = NULL;
   return NextLine(std);
   }
bool EMailLines::NextLine(ZStr& std)
   {
   size_t szNextPos  = szLastPos ? (szLastPos + 1) : szLastPos;
   size_t szFoundPos = sLines.Find('\n', szNextPos);
   if(szFoundPos == NPOS)
      return false;
   std = sLines.Substr(szNextPos, szFoundPos - szNextPos + 1);
   szLastPos = szFoundPos;
   return true;
   }

