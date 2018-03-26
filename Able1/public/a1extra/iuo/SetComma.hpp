// Class SetComma: Scavanged from my old pvPrompter class, this stand-alone
// class is now available for general use.
//
// 06/18/2001: Class created, R. Nagy
// 07/15/2003: Moved under Able1, R. Nagy
//             Got rid of stringstream usage due to bugs in same under thReaded operations.
// 09/06/2003: Changed usage to static, renamed class. R. Nagy
//
#ifndef SetComma_Hpp
#define SetComma_Hpp

#include <Able1.hpp>

using namespace Able1;

class _SetComma
{
private:
   static void _Format(char *buf);

protected:
   static void _Format(ZStr& str);

public:
   static const char *Format(long unsigned uldata, ZStr& buf);
   static ZStr   Format(long unsigned uldata);
};

inline const char *CommaFormat(long unsigned ss, ZStr& str)  // 06/04/2002
   {
   _SetComma::Format(ss, str);
   return str.c_str();
   }

inline
void _SetComma::_Format(ZStr& str)
   {
   char *psz = new char[str.Length() * 2];   // massive room for comma-growth (len%3 + 1 ain't worth the cpu)
   strcpy(psz, str.c_str());
   _Format(psz);
   str = psz;
   delete [] psz;
   }

inline
void _SetComma::_Format(char *buf)
   {
   char hold[30], *pc;
   int i = 0;

   pc = buf;

   ::strrev(pc);

   strcpy(&hold[0], buf);

   while(hold[i])
      {
      if ((i) && (!(i % 3)))
         {
         *buf = ',';
         buf++;
         }
      *buf = hold[i];
      buf++;
      i++;
      }
   *buf = NULL;

   ::strrev(pc);
   } // _Format()

inline
const char *_SetComma::Format(long unsigned uldata, ZStr& str)
   {
   char buf[25];
   ::ltoa(uldata, buf, 10);
   str = buf;
   _Format(str);
   return str.c_str();
   } // Format()

inline
ZStr _SetComma::Format(long unsigned uldata)
   {
   ZStr str;
   Format(uldata, str);
   return str;
   } // Format()

inline
ZStr SetComma(long unsigned lu)
{
return (_SetComma::Format(lu));
}

inline
ZStr SetZerosLeft(long unsigned lu, int len = 6)
{
ZStr sPat = "%0";
if(len < 98)
   {
   char buf[100];
   ZStr s2;
   s2.assign(len);
   sPat.Append(s2);
   sPat.Append("d");
   sprintf(&buf[0], sPat.c_str(), lu);
   sPat = buf;
   }
return sPat;
}
#endif

