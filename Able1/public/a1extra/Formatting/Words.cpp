#include <a1extra/Formatting/WordWrap.hpp>
#include <a1extra/Formatting/Words.hpp>

using namespace TextFormatting;

// Formats the string as a flowing block of text (paragraph)
Array<ZStr> Words::AsParagraph(const ZStr& sBlock, int cx, int margin, int maxLen)
   {
   ZStr str = sBlock;
   WordWrap::AsSimpleString(str);
   str.Replace("\n", ' ');
   return WordWrap::Wrap(str, cx, margin, maxLen);
   }

// Formats the string as a flowing block of text (paragraph)
Array<ZStr> Words::AsPage(const ZStr& sBlock, int cx, int margin, int maxLen)
   {
   ZStr str = sBlock;
   WordWrap::AsSimpleString(str);
   str.Replace("\n\n", (char)0xfe);
   str.Replace("\n", ' ');
   Array<ZStr> sArray;
   str.Split((char)0xfe, sArray);
   Array<ZStr> array;
   array.AddZombies(500);
   for(size_t ss = 0L; ss < sArray.Nelem(); ss++)
      {
      array.Append(AsParagraph(sArray[ss]));
      array.Append("\n\n");
      }
   return array;
   }

// Formats the block into a "record" (sentance) format.
Array<ZStr> Words::AsSentances(const ZStr& sBlock)
   {
   ZStr str = sBlock;
   str.Replace('\r', ' ');
   str.Replace('\n', ' ');
   str.Replace("  ", ' ');
   size_t last_ss = 0L;
   ZStr sLine;
   Array<ZStr> array;
   size_t ss = 0L;

   str.Replace("...", '.');
   str.Replace("??", '?');
   str.Replace("!!", '!');

   for(ss = 0L; ss < str.Length(); ss++)
      {
      switch(str[ss])
         {
         case '?':
         case ':':
         case '!':
         case ';':
         case '.':
            {
            sLine = str.Subpos(last_ss, ss + 1);
            sLine.Strip();
            array.Append(sLine);
            last_ss = ss + 1;
            }
         break;
         default:
         break;
         }
      }
   if(last_ss != ss)
      array.Append(str.Subpos(last_ss, NPOS));
   return array;
   }

ZStr Words::AsBlock(const Array<ZStr>& array)
   {
   ZStr str;
   stringstream srm;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      array.At(ss, str);
      srm << str;
      srm << '\n';
      }
   str = WordWrap::AsSimpleString(PRESTO(srm));
   str.Replace('\n', ' ');
   return str;
   }


