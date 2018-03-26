// Class DayLog: One log file a day, to keep same from becomming huge.
// Default is NOT to auto-wrap around every year, so as to not loose valuable log info.
//
// 06/18/2001: Class created, R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
//
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
//
#ifndef zDayLog_Hpp
#define zDayLog_Hpp

#include <a1extra/StdLog.hpp>
#include <a1extra/JulianDay.hpp>

class DayLog : public StdLog
   {
   private:
      bool      bAutoWrap;
      int       jdate;
      JulianDay today;
      ZStr sRootName;

   public:
      DayLog(void)                 : bAutoWrap(false)   {Name("jday.txt");}
      DayLog(const ZStr& sfn) : bAutoWrap(false)   {Name(sfn.c_str());}
      virtual ~DayLog(void)           {}

      virtual bool Name(const ZStr& sName);
      virtual bool Write(const ZStr& sMessage);

      bool IsOneYearOnly(void)               {return bAutoWrap;}
      bool OneYearOnly(bool b = true)       {bAutoWrap = b; return true;}
   };


inline
bool DayLog::Name(const ZStr& pszName)
   {
   sRootName = pszName;

   ZStr str;
   jdate = today.Today();
   today.Today(str);
   if(sRootName[0] != '.')
      str.Append('.');
   str.Append(sRootName);

   ZStr str2;
   if(bAutoWrap == false)  // our default, this is.
      {
      str2 = today.LocalYear();
      str2.Append('.');
      }
   str2.Append(str);
   return StdLog::Name(str2);
   }

inline
bool DayLog::Write(const ZStr& psz)
   {
   if(today.Today() != jdate)
      Name(sRootName);
   StdLog::PrintLine(psz);
   return true;
   }

#endif
