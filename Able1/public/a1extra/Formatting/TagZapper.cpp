#include <a1extra/Formatting/TagZapper.hpp>

ZStr TagZapper::_ZapHtml(const ZStr& sBlock, const char ch1, const char ch2)
   {
   bool bSkip = false;
   ZStr sResult;
   for(size_t ss = NULL; ss < sBlock.Length(); ss++)
      {
      if(sBlock[ss] == ch1)
         {
         bSkip = true;
         continue;
         }
      if(sBlock[ss] == ch2)
         {
         bSkip = false;
         continue;
         }
      if(bSkip == false)
         {
         sResult.Append(sBlock[ss]);
         continue;
         }
      }
   return sResult;
   }

ZStr TagZapper::HtmlTo7Bit(const ZStr& str)
   {
   /* TODO 1 -oYo -cHTML :
   Need to finally create *the definitive* set of HTML character codes
   for 8-bit (ONLY). Only do symbolic. Will do the decimal encodings
   later */
   return _ZapHtml(str, '&', ';');      // <<<WIP>>>
   }

ZStr TagZapper::ZapHtml(const ZStr& sBlock, const char ch1, const char ch2)
   {
   ZStr sResult = _ZapHtml(sBlock, ch1, ch2);
   sResult.MkWhite();
   sResult = HtmlTo7Bit(sResult);
   return sResult;
   }
