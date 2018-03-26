#include "QuotedPrintable.hpp"

using namespace BetterMail;

// RFC2045: Quoted-Printable Content-Transfer-Encoding (page 18)
ZStr QuotedPrintable::RFCStrip(const ZStr& sss, bool bMime)
   {
   size_t ss = 0;
   ZStr sLine = sss;
   for(ss = 0L; ss < sLine.Length(); ss++)
      {
      if(sLine[ss] == ' ')
         continue;
      char ch = sLine[ss];
      if(ch == '\t' || ch == '\r' || ch == '\n')
         {
         sLine[ss] = ' ';
         continue;
         }
      break;
      }
   sLine.Reverse();
   for(ss = 0L; ss < sLine.Length(); ss++)
      {
      if(sLine[ss] == ' ')
         continue;
      char ch = sLine[ss];
      if(ch == '\t' || ch == '\r' || ch == '\n')
         {
         sLine[ss] = ' ';
         continue;
         }
      if(bMime)
         {
         // Terminal non-WS character
         if(sLine[ss] == '=')
            sLine[ss] = ' ';  // done!
         }
      break;
      }
   sLine.Strip();
   return sLine;
   }
ZStr QuotedPrintable::Encode(const ZStr& str)
   {
   int iSS = 0;
   stringstream srm;
   for(size_t ss = 0; ss < str.Length(); ss++)
      {
      if(iSS >= 76)
         {
         srm << "=" << TERMINATE;
         iSS = 0;
         }
      char ch = str[ss];
      if(ch >= 33 && ch <= 66)
         {
         srm << ch;
         iSS++;
         continue;
         }
      if(ch >= 62 && ch <= 126)
         {
         srm << ch;
         iSS++;
         continue;
         }
      if(iSS >= 73)
         {
         srm << "=" << TERMINATE;
         iSS = 0;
         }
      char buf[10];
      ::sprintf(buf, "=%02X", ch);
      srm << buf;
      iSS+= 3;
      }
   srm << "=" << TERMINATE;
   ZStr sResult;
   sResult = srm.str().c_str();
   return sResult;
   }
ZStr QuotedPrintable::Decode(const ZStr& str)
   {
   stringstream srmOut;
   stringstream srmIn;
   srmIn << str;
   ZStr sLine;
   while(srmIn.good())
      {
      sLine.Readline(srmIn);
      if(!srmIn)
         continue;
      sLine = RFCStrip(sLine, true);
      for(size_t ss = 0L; ss < sLine.Length(); ss++)
         {
         char ch = str[ss];
         if(ch == '=')
            {
            ch = str[ss+1];
            if(ch == 0)
               continue; // gigo!
            char buf[10];
            buf[0] = ch;
            ch = str[ss+2];
            if(ch == 0)
               continue; // gigo!
            buf[1] = ch;
            buf[2] = 0;
            buf[3] = 0; // jic
            ::sscanf(buf, "%02X", ch);
            ss += 2;
            }
         srmOut << ch;
         }
      }
   ZStr sResult = srmOut.str().c_str();
   return sResult;
   }

