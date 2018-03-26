#include <a1extra/Formatting/WordWrap.hpp>
#include <a1extra/Formatting/LinearMarkup.hpp>

using namespace TextFormatting;


ZStr LinearMarkup::AsGmlPage(const ZStr& str)
   {
   ZStr sResult = WordWrap::AsSimpleString(str);
   sResult.Replace("\n", "<br>");
   return sResult;
   }
ZStr LinearMarkup::AsGmlPage(Array<ZStr>& array)
   {
   ZStr sResult;
      {
   stringstream srm;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      srm << array[ss] << " ";
   sResult = PRESTO(srm);
      }
   sResult.Replace("  ", ' ');
   return AsGmlPage(sResult);
   }
ZStr LinearMarkup::RemoveHtmlTags(const ZStr& sGmlLine)
   {
   bool bSkip = false;
   ZStr sResult;
   for(size_t ss = 0L; ss < sGmlLine.Length(); ss++)
      {
      switch(sGmlLine[ss])
         {
         case '<':
            bSkip = true;
         continue;
         case '>':
            bSkip = false;
         continue;
         default:
            if(bSkip == false)
               sResult.Append(sGmlLine[ss]);
         break;
         }
      }
   sResult.Replace("  ", ' ');
   return sResult;
   }
ZStr LinearMarkup::AsTextPage(const ZStr& sGmlLine)
   {
   ZStr sResult = sGmlLine;
   sResult.Strip();
   sResult.Replace("  ", ' ');
   sResult.Replace("\n", "<br>");
   return RemoveHtmlTags(sResult);
   }


