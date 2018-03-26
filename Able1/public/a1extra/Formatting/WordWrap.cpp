#include <a1extra/Formatting/WordWrap.hpp>

using namespace TextFormatting;


WordWrap::TextType WordWrap::AsSimpleString(ZStr& str)
   {
   char ZZ_NEWLINE  = char(0xfe);

   TextType iFlag = tt_unix;
   if(str.Find("\r\n") != NPOS)
      {
      iFlag = tt_dos;  // Probable: Map back to MS-DOS style newlines
      str.Replace("\r\n", ZZ_NEWLINE);
      }
   // Expected (unix) mapping:
   str.Replace('\n', ZZ_NEWLINE);
   if(str.Find('\r') != NPOS)
      {
      iFlag = tt_other;  // Unexpected (TANDY / ERROR) mapping
      str.Replace('\r', ZZ_NEWLINE);
      }
   str.Replace(ZZ_NEWLINE, '\n');
   int ict = str.Replace(" \n", '\n');
   while(ict)
      ict = str.Replace(" \n", '\n');
   return iFlag;
   }


void  WordWrap::AsDosString(ZStr& str)
   {
   str.Replace('\n', "\r\n");
   }


Array<ZStr>  WordWrap::Wrap(const ZStr& str, int cx, int margin, int max)
   {
   ZStr sResult = str;
   AsSimpleString(sResult);
   sResult = WrapNormalized(str, cx, margin, max);
   Array<ZStr> array;
   sResult.Split('\n', array);
   return array;  // bad form?
   }


ZStr  WordWrap::Wrap(const ZStr& str, TextType tt, int cx, int margin, int maxLen)
   {
   ZStr sContent = str;
   AsSimpleString(sContent);
   sContent = WrapNormalized(sContent, cx, margin, maxLen);
   if(tt != tt_unix)
      AsDosString(sContent);
   return sContent;
   }


ZStr  WordWrap::WrapUnix(const ZStr& str, int cx, int margin, int maxLen)
   {
   return Wrap(str, tt_unix, cx, margin, maxLen);
   }


ZStr  WordWrap::WrapDos(const ZStr& str, int cx, int margin, int maxLen)
   {
   return Wrap(str, tt_dos, cx, margin, maxLen);
   }


ZStr  WordWrap::WrapNormalized(const ZStr& str, int cx, int margin, int max)
   {
   ZStr sQuote = str;
   if(cx < max)
      cx = max;

   if(cx < margin)
      margin = cx / 4;

   int ignoring_leading_newlines_and_spaces = 1;

   size_t last_sp = -1L;
   for(size_t ss = NULL, offset = NULL; ss < (int)sQuote.Length(); ss++, offset++)
      {
      switch(sQuote[ss])
         {
         case '\n':
            {
            // If multiple '\n' sequence, then just pass-it-thru;
            if(sQuote[ss+1] == '\n')
               ignoring_leading_newlines_and_spaces = 1;

            if(ignoring_leading_newlines_and_spaces)
               {
               offset  = NULL;   // Position 0 on pwLine
               last_sp = -1L;    // NO SPACE ON pwLine
               continue;
               }

            size_t underflow = cx - margin;
            // Is there an UNDERflow?
            if(ss && (offset < underflow))
               {
               // Map the '\n' over to a space. Moving onward without
               // changing our offset now makes us a candidate for an
               // OVERflow conditon (DESIRED);
               sQuote[ss] = ' ';
               last_sp = ss-1;
               }
            else
               {
               // No need to re-format anything.
               // Move on toward to the next line;
               offset  = NULL;   // Position 0 on pwLine
               last_sp = -1L;    // NO SPACE ON pwLine
               }
            }
         continue;

         case ' ':
         case '\t':
            last_sp = ss;
         continue;

         default:
            {
            ignoring_leading_newlines_and_spaces = 0;

            if(offset > cx)
               {
               if(last_sp && (last_sp != -1L))
                  {
                  // BREAK TYPE ONE (TYPICAL)
                  // ========================
                  if(sQuote[ss+1] == '\n')
                     continue;

                  // Break the line at the last white-space;
                  sQuote.Insert(last_sp+1, '\n');
                  // re-start parsing AFTER the last '\n' (IMPORTANT FOR UNDERFLOW DETECTION);
                  ss = sQuote.Find('\n', last_sp); // MAINTENANCE: USE THIS METHOD. DO NOT RISK A FUTURE UNDERFLOW TO SAVE A FEW PICA-SECONDS!
                  ss++;
                  }
               else
                  {
                  // BREAK TYPE TWO (ATYPICAL)
                  // =========================
                  // Too strange a format calls for too strange a result;
                  // (i.e: precision break-up of a long series of "===="'s (etc);
                  sQuote.Insert(ss, '\n');
                  }
               offset  = NULL;   // Position 0 on pwLine
               last_sp = -1L;    // NO SPACE ON pwLine
               }
            }
         continue;
         }
      }
   return sQuote;
}




