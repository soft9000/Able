// Class StdDateTime: Place to hang all of the STANDARD (portable) date-and-time
// conversions and conventions.
//
// 1999/05/10: Class created, R. Nagy
// 2001/05/09: Growing into a replacement for TDate amd TTime, R. Nagy
// 2001/12/05: Added IsNull() and expanded support for user_Assign(ed to recent operators, R. Nagy
// 2003/10/30: Added EncodeMMDDYY(const ZStr& str) and EncodeHHMMSS(...), R. Nagy
// 2003/11/03: Added IsSameDate(), R. Nagy
// 2004/04/26: Added Import / ExportDottedEditable(), R. Nagy
// 2006/10/11: Updated EncodeDate() and EncodeTime() to preserve any complementing date / time aspect, R. Nagy
// 2006/10/14: Changed Read() and Write() to use an ASCII format by default. Legacy(binary) format detected and converted on read as required, R. Nagy
// 2006/12/06: Added operators >= and <= to support S.P.A.W.N, R. Nagy
// 2007/01/22: Added Second()s, R. Nagy
// 2007/12/30: Added const to appropriate members, R. Nagy
//             Added Hack(), R. Nagy
// 2008/02/01: Added DaysInMonth(...) and MonthName(...), R. Nagy
//             Fixed problem in EncodeDate() / EncodeTime() - ::mktime() failure now returns false, R. Nagy
//

#ifndef StdDateTime_Hpp
#define StdDateTime_Hpp

// SEE ALSO
// #include <a1core/PortTime.hpp>

/** StdDateTime competes with PortTime to provide a streamable date / time format.
  *
  */
namespace Able1
   {

class StdDateTime
{
private:
   int user_assigned;
   StdDateTime(bool);         // bogus!
   StdDateTime(char);         // bogus!
   StdDateTime(short);        // bogus!
   StdDateTime(int);          // archaic!
   StdDateTime(unsigned);     // archaic!

protected:
   // Maybe some day we'll find a reason to make this more
   // efficient, but there is no reason to do so, now;
   struct tm ttm;

public:
   StdDateTime(void);
   StdDateTime(const StdDateTime& ss);
   StdDateTime(time_t tt);
   virtual ~StdDateTime(void);

   void Hack(void)               {*this = StdDateTime(::time(NULL));};

   int  IsDefaultTime(void)      {return (!user_assigned);}
   bool IsNull(void) const       {return (!user_assigned);}

   virtual StdDateTime& operator=(const StdDateTime& ss);

   StdDateTime& operator=(struct tm& keep);
   StdDateTime& operator=(time_t tt);

   operator time_t(void);

   int          operator==(const StdDateTime& sdt) const;
   int          operator!=(const StdDateTime& sdt) const;
   StdDateTime& operator+=(int sec);
   StdDateTime& operator-=(int sec);
   int          operator>(const StdDateTime& sdt) const;
   int          operator<(const StdDateTime& sdt) const;
   int          operator>=(const StdDateTime& sdt) const;
   int          operator<=(const StdDateTime& sdt) const;

   bool         IsSameDate(const StdDateTime& sdt) const;

   // Year is fully qualified, though year before 1970 is not supported;
   bool EncodeDate(unsigned yy, unsigned mm, unsigned dd, ZStr& sError);
   bool EncodeDate(unsigned yy, unsigned mm, unsigned dd);
   bool DecodeDate(unsigned *yy, unsigned *mm, unsigned *dd) const;
   bool DecodeDate(unsigned &yy, unsigned &mm, unsigned &dd) const;

   bool EncodeJulian(unsigned yy, unsigned jDay)
      {
      if(yy < 1900)
         return false;
      struct tm ttm2;
      ::memset(&ttm2, 0, sizeof(struct tm));
      ttm2.tm_yday = jDay;
      if(jDay)
         ttm2.tm_yday--;
      ttm2.tm_year = yy - 1900;
      *this = ttm2;
      return true;
      }

   // Hour is in military time;
   bool EncodeTime(unsigned hh, unsigned mm, unsigned ss);
   bool DecodeTime(unsigned *hh, unsigned *mm, unsigned *ss) const;
   bool DecodeTime(unsigned &hh, unsigned &mm, unsigned &ss) const;

   bool EncodeMMDDYY(const ZStr& str, ZStr& sError);
   bool EncodeMMDDYYYY(const ZStr& str, ZStr& sError);
   // Hour is in military time;
   bool EncodeHHMMSS(const ZStr& str, ZStr& sError);

   int  IsDaylightSavingsTime(void) const       {return ttm.tm_isdst;}
   int  DayOfWeek(void)             const       {return ttm.tm_wday +1;}      // (Sunday is the first day of the week)
   int  JulianDay(void)                         {return ttm.tm_yday +1;}      // (January 1st is the first day of the year)
   int  Month(void)      const {return (ttm.tm_mon +1);}      // months since January - [0,11]
   int  DayOfMonth(void) const {return ttm.tm_mday;}          // day of the month - [1,31]
   int  Year(void)       const {return (ttm.tm_year + 1900);} // years since 1900   
   int  Hour(void)       const {return ttm.tm_hour;}          // hours since midnight - [0,23]
   int  Minute(void)     const {return ttm.tm_min;}           // minutes after the hour - [0,59]
   int  Second(void)     const {return ttm.tm_sec;}           // seconds after the minute - [0,59]

   void AddYear(void)    {ttm.tm_year += 1;}
   void NextDay(void)    {operator+=(86400);}
   void PreviousDay(void){operator-=(86400);}
   int DaysInMonth(void) const;
   ZStr MonthName(void) const;

   ostream& write_bin(ostream& os) const;
   istream& read_bin(istream& is);

   ostream& write_text(ostream& os) const;
   istream& read_text(istream& is);

   ostream& Write(ostream& os) const;
   istream& Read(istream& is);
};

struct sdtMasks
   {
   static const char *AsHMS(void) {return "%02d:%02d:%02d";}
   static const char *AsMDY(void) {return "%02d/%02d/%02d";}
   static const char *AsMDYHMS(void) {return "%02d/%02d/%02d %02d:%02d:%02d";}
   };

ZStr AsHMS(time_t total_seconds, const char *pszMask = sdtMasks::AsHMS());
ZStr AsMDY(time_t total_seconds, const char *pszMask = sdtMasks::AsMDY());
ZStr AsMDYHMS(time_t total_seconds, const char *pszMask = sdtMasks::AsMDYHMS());

ostream& operator<<(ostream& os, const StdDateTime& sdt);
istream& operator>>(istream& is, StdDateTime& sdt);

bool ExportDottedEditable(const StdDateTime& std, ostream& os);
bool ImportDottedEditable(StdDateTime& std, istream& is);

ZStr   ExportDottedEditable(const StdDateTime& sdt);
bool        ImportDottedEditable(StdDateTime& sdt, const ZStr& str);
bool        IsLeapYear(unsigned uYear);

int DaysInMonth(const StdDateTime& sdt);
int DaysInMonth(int mon, unsigned year);

ZStr MonthName(const StdDateTime& sdt);
ZStr MonthName(int mon);

// Move out - later!
//int StdDateTime::DaysInMonth(void) const;
//ZStr StdDateTime::MonthName(void) const;

   } // Able1
   
#endif


