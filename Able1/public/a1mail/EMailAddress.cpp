#include "EMailAddress.hpp"

bool EMailAddress::IsNull(void) const
   {
   if(sUserName.IsNull() == false)
      return false;
   if(sHostAccount.IsNull() == false)
      return false;
   return true;
   }

bool EMailAddress::Parse(const ZStr& sss)
   {
   (*this) = EMailAddress();
   if(sss.Find('@') == npos)
      return false;

   ZStr str = sss;
   str.MkWhite();
   size_t pos = str.Find(": ");
   if(pos != npos)
      str.Remove(pos + 1);
   pos = str.Find("<");
   if(pos != npos)
      {
      sHostAccount = str.Subpos(pos + 1, npos);
      sHostAccount.Remove(sHostAccount.Find('>'));
      str.Remove(pos - 1);
      sUserName = str;
      }
   else
      {
      str.Strip();
      pos = str.Rfind(' ');
      if(pos != npos)
         {
         sHostAccount = str.Subpos(pos + 1, npos);
         str.Remove(pos);
         sUserName = str;
         }
      else
         sHostAccount = str;
      }
   sUserName.RemovePattern('"');
   sUserName.Strip();
   return true;
   }

ZStr EMailAddress::Compose(void)
   {
   ZStr sResult;
   if(IsNull())
      return sResult;
   sResult = sUserName;
   sResult += " <";
   sResult.Append(sHostAccount);
   sResult.Append(">");
   return sResult;
   }

bool EMailAddress::Parse(const ZStr& sLine, Array<EMailAddress>& aResult, char chSep)
   {
   aResult.Empty();
   Array<ZStr> array;
   if(sLine.Split(chSep, array) == false)
      return false;
   aResult.AddZombies(array.Nelem());
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(aResult[ss].Parse(array[ss]) == false)
         return false;
      }
   return true;
   }

