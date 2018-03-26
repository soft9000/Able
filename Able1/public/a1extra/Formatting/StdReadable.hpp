//
// StdReadable is used to parse streams and strings into strings that
// fit into page boundraries and / or gramatical (sentance) conceptions.
//
// 05/07/2005: Class Created, R. Nagy
//
#ifndef StdReadable_hpxx
#define StdReadable_hpxx

#include <Able1.hpp>
using namespace Able1;

struct StdReadable
   {
// This function returns \n\n for a paragraph, else a normalized 
// (no newlines and monospaced) sentance
   static bool getSentance(istream& is, ZStr& sLine)
      {
      bool br = false;
      sLine = "";
      char ch;
      int para = 0;
      while(is)
         {
         is.get(&ch, 1);
         if(!is)
            continue;
         if(ch == '\r')
            continue;   // ignore MSDOS carrage returns (what about mac?)
         if(!sLine.Length())
            {
            // a single newline could mark former formatting ...
            if(ch == '\n')
               {
               para++;
               if(para > 1)
                  {
                  sLine = "\n\n";
                  return true;   // two newlines mark a paragraph 
                  }
               continue;         // else ignore any leading newlines
               }
            }
         para = 0;
         // build the final line ...
         br = true;
         sLine.Append(ch);
         if(ispunct(ch))
            break;
         }
      // Normalize
      sLine.Replace('\n', ' ');
      sLine.Replace("  ", ' ');
      sLine.Strip();
      return br;
      }
      
// This section extracts a segment from a sentance-string
   static ZStr mkSegment(ZStr& sBuf, size_t maxlen)
      {
      sBuf.Strip();
      ZStr sLine = sBuf;
      sLine.Append(' ');
      
      size_t pos_last = size_t(maxlen);
      size_t pos = sLine.Find(' ');
      while(pos < maxlen)
         {
         pos_last = pos;
         pos = sLine.Find(' ');
         }
      ZStr sResult = sLine.subpos(0, pos_last);
      sLine.RemovePos(0, pos_last);
      sLine.Strip();
      sBuf = sLine;
      return sResult;
      }
}; // StdReadable class

