#include <Able1.hpp>
using namespace Able1;

const Able1::ZStr sToken("!@#@~$^");

namespace Able1
   {

// Encoded EVERYthing -
ZStr Html::EncodeAll(const ZStr& sLine)
   {
   stringstream srm;
   for(int ss = 0; ss < sLine.Length(); ss++)
      {
      char ch = sLine[ss];
      srm << "&#" << (int)ch << ";";
      }
   ZStr str = srm.str().c_str();
   return str;
   }

// Allows for imbedded HTML tags -
ZStr Html::EncodeText(const ZStr& sss)
   {
   ZStr sLine = sss;
   bool bSkip = false;
   stringstream srm;
   for(int ss = 0; ss < sLine.Length(); ss++)
      {
      char ch = sLine[ss];
      switch(ch)
         {
         case('\r'):
         case('\n'):
         case('\t'):
            srm << ch;
         continue;
         case ('<'):
            bSkip = true;
         break;
         case ('>'):
            bSkip = false;
            srm << ">";
         continue;
         default:
         break;
         }
      if(bSkip == true)
         {
         srm << ch;
         continue;
         }
      srm << "&#" << (int)ch << ";";
      }
   ZStr str = srm.str().c_str();
   return str;
   }

// Allows for imbedded HTML tags -
ZStr Html::ToParagraphs(const ZStr& sss)
   {
   int iNewlines = 0;
   ZStr sLine = sss;
   bool bSkip = false;
   bool bFirst = true;
   bool bLastWasNewline = false;
   stringstream srm;
   for(int ss = 0; ss < sLine.Length(); ss++)
      {
      char ch = sLine[ss];
      if(ch == '\r' || ch == ' ' || ch == '\t')
         {
         srm << ch;  // ignore it - could throw off our newline counting -
         continue;
         }
      switch(ch)
         {
         case ('<'):
            bSkip = true;
         break;
         case ('>'):
            bSkip = false;
            srm << ">";
         continue;
         default:
         break;
         }
      if(bSkip == false && ch == '\n')
         {
         iNewlines++;
         if(bFirst)
            {
            srm << "<p>";
            iNewlines = 0;
            bFirst = false;
            }
         if(iNewlines == 2)
            {
            iNewlines = 0;
            srm << "</p><p>";
            }
         bLastWasNewline = true;
         srm << ch;
         continue;
         }
      if(bSkip == false)
         bLastWasNewline = false;   // newlines in HTML are a passthru!
      srm << ch;
      continue;
      }
   if(bLastWasNewline)
      srm << "</p>";
   ZStr str = srm.str().c_str();
   return str;
   }

ZStr Html::RemoveHtml(const ZStr& sLine)
   {
   return TagRemove(sLine);
   }

ZStr Html::LowerTags(const ZStr& sLine)
   {
   bool blc = false;
   ZStr str = sLine;
   for(size_t ss = 0L; ss < str.Length(); ss++)
      {
      char ch = str[ss];
      if(ch == '<')
         {
         blc = true;
         continue;
         }
      if(ch == '>')
         {
         blc = false;
         continue;
         }
      if(blc)
         str[ss] = ::tolower(ch);
      }
   return str;
   }

ZStr Html::GetBody(const ZStr& sLine)
   {
   ZStr str = LowerTags(sLine);
   size_t pos = str.Find("<body");
   if(pos == npos)
      return sLine;

   pos += 4;
   while(++pos < str.Length())
      {
      if(str[pos] == '>')
         {
         str = str.RemovePos(pos+1, npos);
         break;
         }
      }

   pos = str.Find("</body");
   if(pos != npos)
      str.Remove(pos);

   return str;
   }

size_t Paragraph::Longest(const Array<ZStr>& array)
   {
   ZStr ref;
   array.At(0, ref);
   size_t ssTot = ref.Length();
   for(size_t ss = 1L; ss < array.Nelem(); ss++)
      {
      array.At(ss, ref);
      ssTot = ssTot > ref.Length()? ssTot : ref.Length();
      }
   return ssTot;
   }
   
size_t Paragraph::Shortest(const Array<ZStr>& array)
   {
   ZStr ref;
   array.At(0, ref);
   size_t ssTot = ref.Length();
   for(size_t ss = 1L; ss < array.Nelem(); ss++)
      {
      array.At(ss, ref);
      ssTot = ssTot < ref.Length()? ssTot : ref.Length();
      }
   return ssTot;
   }
   
size_t Paragraph::Size(const Array<ZStr>& array, bool bUseNewline)
   {
   size_t ssTot = 0L;
   ZStr ref;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      array.At(ss, ref);
      ssTot += ref.Length();
      if(bUseNewline == false)
         ssTot -= ref.Tally("\n");
      }
   return ssTot;
   }

   
ZStr Paragraph::Normalize(const ZStr& sLine)
   {
   //re-use "\usr\code\cpp\WordWrap\WordWrap.cpp"
   //re-use "\usr\code\cpp\Paragraph\Paragraph.cpp"
   ZStr sText = sLine;
   sText.Replace("\r\n", "\n");
   sText.Replace("\n\r", "\n");
   sText.Replace("\r", "\n");

   while(sText.Find(" \n") != npos)
      sText.Replace(" \n", "\n");
   while(sText.Find("\n ") != npos)
      sText.Replace("\n ", "\n");

   if(sText.Length() && sText[sText.Length()-1] != '\n')
      sText.Append('\n');

   sText.Replace("\n", sToken);
   sText.MkWhite();
   sText.Replace(sToken, "\n");
   return sText;
   }
ZStr Paragraph::Normalize(const Array<ZStr>& aLines)
   {
   ZStr sResult;
   for(size_t ss = 0L; ss < aLines.Nelem(); ss++)
      {
      if(ss && (sResult[sResult.Length() - 1] != '\n'))
         sResult += "\n";
      ZStr sLine;
      aLines.At(ss, sLine);
      sResult += sLine;
      }
   return sResult;   
   }
Array<ZStr> Paragraph::Flow(const Array<ZStr>& aLines)
   {
   ZStr sResult = Normalize(aLines);
   return List(sResult);
   }
ZStr Paragraph::WordWrap(const ZStr& sLine, int iLineWidth)
   {
   ZStr sText = Normalize(sLine);

   sText.Replace("\n\n", sToken);
   sText.Replace("\n", " ");
   sText.Replace(sToken, "\n");

   size_t ssBreak = npos;
   size_t ssCount = 0L;
   
   ZStr sResult;
   for(int ss = NULL; ss < sText.Length(); ss++)
      {
      switch(sText[ss])
         {
         case '\n':
            {
            // process a paragraph
            sResult += sText.Subpos(0, ss);
            sResult += "\n"; // the SECOND newline restored ...
            sResult.RemovePos(0, ss);
            // restart
            ssBreak = npos;
            ss = -1;
            ssCount = 0L;
            }
         continue;

         case ' ':
            {
            // mark a place to break
            ssBreak = ss;
            }
         break;

         default:
         break;
         }

      // everything else ...
      if(ssCount >= iLineWidth)  // ">=" not "==" ... think maintainence ...
         {
         if(ssBreak == npos)
            ssBreak = ss;
            
         int delta = 0;   
         if(sText[ssBreak] == ' ')
            delta = 1;
            
         sResult += sText.Subpos(0, ssBreak);
         sResult += "\n";
         sText.RemovePos(0, ssBreak + delta);
         // restart
         ssBreak = npos;
         ss = -1;
         ssCount = 0L;
         }
      else
         ssCount++;

      }
   sResult.Replace(" \n", "\n");
   return sResult;
   }
Array<ZStr> Paragraph::List(const ZStr& sLine)
   {
   ZStr sText = Normalize(sLine);
   Array<ZStr> ary;
   ary.AddZombies(100);
   size_t result  = NULL;
   size_t ssStart = NULL;

   size_t whence = sText.Find('\n');
   while(whence != NPOS)
      {
      size_t tmp = whence - ssStart;
      if(result < tmp)
         result = tmp;
      ZStr sLine;
      sText.CopyPos(sLine, ssStart, whence + 1);
      ary[ary.Nelem()] = sLine;
      ssStart = whence + 1;
      whence = sText.Find('\n', ssStart);
      }
   return ary;
   }

Array<ZStr> Paragraph::List(const ZStr& sLine, int iLen)
   {
   ZStr sText = Normalize(sLine);
   ZStr sBest = WordWrap(sLine, iLen);
   return List(sBest);
   }

bool PipeArray::Parse(Array<ZStr>& ary, const ZStr& str, char ch)
   {
   ZStr sch(ch);
   return Parse(ary, str, sch);
   }

bool PipeArray::Parse(Array<ZStr>& ary, const ZStr& str, const ZStr& sch)
   {
   if(str.IsNull() || sch.IsNull())
      return true;   // gigo
   if(sch.IsNull())
      return false;  // gigo
   ZStr ssr = str;
   ary.Empty();
   size_t whence = ssr.Find(sch);
   while(whence != NPOS)
      {
      ary[ary.Nelem()] = ssr.Substr(0, whence);
      ssr.RemovePos(0, whence + sch.Length());
      whence = ssr.Find(sch);
      }
   if(ssr.Length())
      ary[ary.Nelem()] = ssr;
   if(ary.Nelem())
      return true;
   return false;
   }

bool PipeArray::Gen(Array<ZStr>& ary, ZStr& str, char ch)
   {
   stringstream srm;
   for(size_t ss = NULL; ss < ary.Nelem(); ss++)
      srm << ary[ss] << ch;
   str = PRESTO(srm);
   if(str.Length())
      return true;
   return false;
   }


bool ValueParser::ReadPastTag(istream& is,  TagBlock& tvRes, char chOn, char chOff)
   {
   tvRes = TagBlock();
   if(!is)
      return false;

   ZStr rex;  // REX buffer -
   int iLevel = 0;
   while(is)
      {
      char ch = is.get();
      if(!is)
         continue;
      if(ch == chOn)
         {
         if(iLevel == 0)
            {
            tvRes.sPrefix = rex;
            rex = "";
            }
         iLevel++;
         continue; // ignore the start / stop chars
         }

      if(ch == chOff)
         {
         iLevel--;
         if(iLevel == 0)
            {
            tvRes.sTag = rex;
            rex = "";
            return true;
            }
         continue; // ignore the start / stop chars
         }

      rex.Append(ch);
      }
      return !(tvRes.IsNull());
   }

bool ValueParser::PrettyWrite(ostream& os, const ZStr& strI)
   {
   bool br = false;
   if(strI.IsNull() == false)
      {
      os << strI;
      ZStr str = strI;
      str.Strip();
      if(str.EndsWith("\n") == false)
         os << endl;
      br = true;
      }
   return br;
   }

bool ValueParser::Write(ostream& os, const TagBlock& tvRes, char chOn, char chOff, char chCloser)
   {
   PrettyWrite(os, tvRes.sPrefix);

   bool bTagged = !(tvRes.sTag.IsNull());

   if(bTagged)
      {
      os << tvRes.sPrefix << endl;
      os << chOn << tvRes.sTag << chOff << endl;
      }

   PrettyWrite(os, tvRes.sValue);

   if(bTagged)
      {
      os << chOn << chCloser << tvRes.sTag << chOff << endl;
      }
   return !(os.fail());
   }

bool ValueParser::Read(istream& is, Array<TagBlock>& array, char chOn, char chOff, char chCloser)
   {
   bool br = false;
   TagBlock tb;
   while(Read(is, tb, chOn, chOff, chCloser) == true)
      {
      br = true;
      array.Append(tb);
      }
   return br;
   }

bool ValueParser::Read(const ZStr& str, Array<TagBlock>& array, char chOn, char chOff, char chCloser)
   {
   stringstream srm;
   srm << str << endl;
   srm.seekg(ios::beg);
   return Read(srm, array, chOn, chOff, chCloser);
   }

bool ValueParser::Read(istream& is, TagBlock& tvRes, char chOn, char chOff, char chCloser)
   {
   TagBlock tbEasy;

   // Read the "header" (comment + tag START)
   if(ReadPastTag(is, tbEasy, chOn, chOff) == false)
      return false;

   tvRes = tbEasy;

   // Calculate the CLOSING condition
   ZStr sLast = tbEasy.sTag;
   sLast.Prepend(chCloser);

   while(1)
      {
      if(ReadPastTag(is, tbEasy, chOn, chOff) == false)
         return false;

      tvRes.sValue += tbEasy.sPrefix;

      if(sLast == tbEasy.sTag)
         {
         return true;
         }
      else
         {
         tvRes.sValue.Append(chOn);
         tvRes.sValue.Append(tbEasy.sTag);
         tvRes.sValue.Append(chOff);
         }
      }
   return !(tvRes.IsNull());
   }

/* First pass - Nice - Untested - Prefer above -
bool ValueParser::ReadOne(istream& is, TagBlock& tvRes, char chOn, char chOff, char chCloser)
   {
   tvRes = TagBlock();
   if(!is)
      return false;

   ZStr rex;  // REX allows us to buffer while we use sTag for a mode switch -
   int iLevel = 0;
   while(is)
      {
      char ch = is.get();
      if(ch == chOn)
         {
         iLevel++;
         continue; // ignore the start / stop chars
         }

      if(ch == chOff)
         {
         iLevel--;

         // The "initialization level" is where all action occurs
         if(iLevel == 0)
            {
            // STEP: IS FIRST TAG?
            if(tvRes.sTag.IsNull())
               {
               // FIRST TAG
               tvRes.sTag = rex;
               rex = "";
               continue;
               }

            // STEP: IS COMPLETED?
            // (CHECK FOR COMPLETION BEFORE WE READ ANOTHER)
            if(rex[0] == chCloser)
               {
               // LAST TAG?
               if(rex.Find(tvRes.sTag) != npos)
                  {
                  // STEP: - NORMAL END OF PROCEDURE - CLEAN IT UP -
                  tvRes.sPrefix.Strip();  // JIC we only had a newline (etc.)
                  return true;            // WE ARE DONE!
                  }

               // STEP: INCLUDE ODD TAGS IN PAYLOAD -
               // IF we are at L0 and this is NOT the block terminator, then
               // we need to re-code & include it!
               stringstream srm;
               srm << chOn << rex.c_str() << chOff;
               tvRes.sValue.Append(srm.str().c_str());
               rex = "";
               }
            }
         continue; // ignore the start / stop chars
         }

      if(!iLevel)
         {
         // In between TAG levels, we are either 
         // building the PREFIX or the PAYLOAD
         if(tvRes.sTag.IsNull())
            tvRes.sPrefix.Append(ch);  // JUST FOUND THE TAG - CONTINUE
         else
            tvRes.sValue.Append(ch);   // ALREADY FOUND THE TAG - BUILD THE VALUE
         continue;
         }

      // IN A LEVEL - Build the REX (i.e. ignore the reserved start / stop characters)
      rex.Append(ch);
      }

   // STEP: Closing comments Assign(ed? Anything??
   return !(tvRes.IsNull());
   }
*/


} // namespace
