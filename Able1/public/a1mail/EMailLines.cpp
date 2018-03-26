// 10/24/1998, Ran through NOTAB, R. Nagy
//

#include <a1mail/EmailLines.hpp>

using namespace BetterMail;

void EMailLines::Assign(const EMailMessage& em)
   {
   stringstream srm;
   em.Export(srm);
   srm << ends;
   sLines = srm.str().c_str();
   }
void EMailLines::Assign(const ZStr& str)
   {
   sLines = str;
   }
bool EMailLines::FirstLine(ZStr& str)
   {
   szLastPos = NULL;
   return NextLine(str);
   }
bool EMailLines::NextLine(ZStr& str)
   {
   size_t szNextPos  = szLastPos ? (szLastPos + 1) : szLastPos;
   size_t szFoundPos = sLines.Find('\n', szNextPos);
   if(szFoundPos == NPOS)
      return false;
   str = sLines.Substr(szNextPos, szFoundPos - szNextPos + 1);
   szLastPos = szFoundPos;
   return true;
   }

