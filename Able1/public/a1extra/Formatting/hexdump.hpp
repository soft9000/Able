//
// 11/30/2003: Changed hexdump to stop showing the NULL terminator, R. Nagy
//

#ifndef _hex_dumper1_
#define _hex_dumper1_

#include <Able1.hpp>

using namespace Able1;

inline
void hexdump(const ZStr& str, ostream& os)
   {
   size_t which, ss2, ss1;
   which = ss2 = ss1 = NULL;
   char *pbuf = new char[100];
   for(ss1 = NULL; (ss1 * 16) < str.Length(); ss1++)
      {
      ::sprintf(pbuf, "%04d: ", ss1 * 16);
      os << pbuf;
      for(ss2 = NULL; ss2 < 16; ss2++)
         {
         which = (ss1 * 16) + ss2;
         if(which <= str.Length())
            ::sprintf(pbuf, " %02x", str[which]);
         else
            ::strcpy(pbuf, "   ");
         os << pbuf;
         }
      ::strcpy(pbuf, ":   ");
      os << pbuf;
      for(ss2 = NULL; ss2 < 16; ss2++)
         {
         which = (ss1 * 16) + ss2;
         if(which <= str.Length())
            {
            byte_t bb = str[which];
            if((bb >= ' ') && (bb <= '~'))
               ::sprintf(pbuf, "%c", bb);
            else
               ::strcpy(pbuf, ".");
            }
         else
            ::strcpy(pbuf, " ");
         os << pbuf;
         }
      os << endl;
      }
   delete [] pbuf;
   }

inline
const char *hexdump(const ZStr& str, ZStr& sResult)
   {
   stringstream srm;
   hexdump(str, srm);
   sResult = PRESTO(srm);
   return sResult.c_str();
   }

#endif
