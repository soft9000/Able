// Here is a little ditty that I wrote to help you encode and decode 
// julian dates. This source code will work wherever a C++ compiler
// is available. You can download it simply by cutting and pasting it
// from your web-browser into your editor, but please note;
//
// Permission is hereby granted to freely use and / or modify this code 
// as long as this message block remains intact. 
// 
// This source code is free. It is provided "as is". USE AT YOUR OWN RISK.
// 
// More free stuff awaits you at "The Quote For Today".
// Come check us out at http://www.TheQuoteForToday.com 
//
// 02/26/2001: Functions created, R. Nagy
// 06/18/2001: Renamed to JulianDay.HPP for class development.
// 09/23/2003: Ported to Able1, R. Nagy
//
#ifndef z_Julianday_hpp
#define z_Julianday_hpp

#include <Able1.hpp>
#include <ctime>

using namespace Able1;

class JulianDay
{
   protected:
      int days[12];
   public:
      JulianDay(void);
      
      int  LocalYear(void);

      int  IsLeapYear(int year);

      int  Today(void);
      const char *Today(ZStr& str);

      int  Decode(const time_t& ttime);
      int  Decode(const struct tm& tmtime);

      void Decode(int jdate, int &mm, int &dd, int is_leap_year = 1);
      int  Encode(int mm, int dd);
};



inline
JulianDay::JulianDay(void)
   {
   int d[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
   ::memcpy((void *)&days, (void *)&d, (sizeof(int))*12);
   }

inline
int JulianDay::IsLeapYear(int year)
   {
   return (year / 4);
   }

inline
void JulianDay::Decode(int jdate, int &mm, int &dd, int is_leap_year)
{
   dd = mm = 0;
   if(jdate > 366)
      return;
   if(jdate <= 0)
      return;

   if(is_leap_year && (jdate >= 60))
      {
      for(size_t ss = 2; ss < 12; ss++)
         days[ss] = (days[ss] + 1);
      }
   for(size_t ss = NULL; ss < 12; ss++)
     {
     if(jdate < days[ss])
        {
        mm = ss;
        dd = jdate - days[(ss - 1)];
        return;
        }
     }
}

inline
int JulianDay::Encode(int mm, int dd)
{
    if(mm < 1 )
      return -1;
    if(mm > 12)
      return -1;
    if(dd < 1)
      return -1;
    if(dd > 31)
      return -1;
    return (days[mm-1] + dd);
}

inline
int JulianDay::Decode(const struct tm& rtm)
{
   return (rtm.tm_yday +1);    /* days since January 1 - [0,365] */
}


inline
int JulianDay::LocalYear(void)
{
   time_t ttime = time(NULL);
   struct tm *pTm = localtime(&ttime);
   if(!pTm)
      return -1;
   return (pTm->tm_year + 1900);    /* years since 1900 */
}

inline
int JulianDay::Decode(const time_t& ttime)
{
   struct tm *pTm = localtime(&ttime);
   if(!pTm)
      return -1;
   return Decode(*pTm);
}

inline
int JulianDay::Today(void)
{
   time_t tt = time(NULL);
   if(!tt)
      return -1;
   return Decode(tt);
}

inline
const char *JulianDay::Today(ZStr& str)
{   
   int ii = Today();
   if(ii == -1)
      str = "";
   else
      str = ii;
   return str.c_str();
}
#endif
