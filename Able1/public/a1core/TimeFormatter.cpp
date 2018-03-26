#include <Able1.hpp>
using namespace Able1;

const char *TimeFormatter::day[7] = {
   "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"
   };

const char *TimeFormatter::month[12] = {
   "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
   };


// Use the default (compiled) time-zone (typically GMT)
bool Format822(const StdDateTime& sdt, ZStr& sResult)
   {
   TimeFormatter fmt;
   return fmt.Format822(sdt, sResult);
   }

// Use the default (compiled) time-zone (typically GMT)
ZStr Format822(const StdDateTime& sdt)
   {
   TimeFormatter fmt;
   return fmt.Format822(sdt);
   }

TimeFormatter::TimeFormatter(void)
   {
   timeZone = "GMT";
   }

TimeFormatter::TimeFormatter(const ZStr& sTZ)
   {
   timeZone = sTZ;
   }

ZStr TimeFormatter::pad2(int iPos)
   {
   stringstream srm;
   if(iPos < 10)
      srm << "0";
   srm << iPos;
   ZStr str = srm.str().c_str();
   return str;
   }

ZStr TimeFormatter::Format822(const StdDateTime& sdt)
   {
   ZStr sResult;
   if(Format822(sdt, sResult) == false)
      sResult = "";
   return sResult;
   }

bool TimeFormatter::Format822(const StdDateTime& sdt, ZStr& sResult)
   {
   int iPos = 0;
   
   // STEP: Name of the week day
   iPos = sdt.DayOfWeek();
   if(iPos > 7)
      return false;

   stringstream srm;
   srm << day[iPos] << ", ";

   // STEP: Zero-padded numerical day in the month
   srm << pad2(sdt.DayOfMonth()) << " ";

   // STEP: Name of the month
   iPos = sdt.Month() + 1;
   if(iPos > 12)
      return false;

   srm << month[iPos] << " ";

   // STEP: Year
   srm << sdt.Year() << " ";

   // STEP: Zero-padded numerical day in the month
   srm << pad2(sdt.Hour()) << ":";
   srm << pad2(sdt.Minute()) << ":";
   srm << pad2(sdt.Second()) << " ";
   
   // STEP: Arbitraty time zone
   srm << timeZone;

   // STEP: Final result
   sResult = srm.str().c_str();
   return true;
   }
