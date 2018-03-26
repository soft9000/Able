#include <Able1.hpp>
using namespace std;

namespace Able1
   {
ostream& operator<<(ostream& os, const StdDateTime& sdt) 
   {
   StdDateTime tmp = sdt;
   os << ' ' << time_t(tmp) << ' ';
   return os;
   }
istream& operator>>(istream& is, StdDateTime& sdt)
   {
   char ch;
   time_t tt = NULL;
   is.read(&ch, 1);
   is.read((char *)&tt, sizeof(time_t));
   is.read(&ch, 1);
   sdt = tt;
   return is;
   }
StdDateTime::StdDateTime(void)
   {
   time_t tt = time(NULL);
   ::memcpy(&ttm, localtime(&tt), sizeof(struct tm));
   user_assigned = 0;
   }
StdDateTime::StdDateTime(const StdDateTime& ss)
   {
   *this = ss;
   }
StdDateTime::StdDateTime(time_t tt)
   {
   struct tm *pt = localtime(&tt);
   if(pt)
      {
      ::memcpy(&ttm, pt, sizeof(struct tm));
      user_assigned = 1;
      }
   else
      {
      time_t tt = time(NULL);
      ::memcpy(&ttm, localtime(&tt), sizeof(struct tm));
      user_assigned = 0;
      }
   }
StdDateTime::~StdDateTime(void)
   {
   }
bool StdDateTime::IsSameDate(const StdDateTime& sdt) const
   {
   if( (ttm.tm_mday  == sdt.ttm.tm_mday) &&
       (ttm.tm_mon   == sdt.ttm.tm_mon) &&
       (ttm.tm_year  == sdt.ttm.tm_year) )
       return true;
   return false;       
   }
StdDateTime& StdDateTime::operator=(time_t tt)
   {
   user_assigned = 1;
   StdDateTime sdt(tt);
   *this = sdt;
   return *this;
   }
StdDateTime& StdDateTime::operator+=(int sec)
   {
   user_assigned = 1;
   time_t ttime = (time_t) *this;
   ttime += sec;
   ::memcpy((char *)&ttm, (char *)localtime(&ttime), sizeof(struct tm));
   return *this;
   }
bool StdDateTime::EncodeMMDDYYYY(const ZStr& str, ZStr& sError)
   {
   int mm, dd, yy;
   mm = dd = yy = 0;
   if(::sscanf(str.c_str(), "%d/%d/%d", &mm, &dd, &yy) != 3)
      {
      sError = "Unsupported date format.";
      return false;
      }
   return EncodeDate(yy, mm, dd, sError);
   }
bool StdDateTime::EncodeMMDDYY(const ZStr& str, ZStr& sError)
   {
   int mm, dd, yy;
   mm = dd = yy = 0;
   if(::sscanf(str.c_str(), "%d/%d/%d", &mm, &dd, &yy) != 3)
      {
      sError = "Unsupported date format.";
      return false;
      }
   if(yy < 70)
      yy += 2000;
   else
      yy += 1900;
   return EncodeDate(yy, mm, dd, sError);
   }
bool StdDateTime::EncodeHHMMSS(const ZStr& str, ZStr& sError)
   {
   sError = "Unsupported time format.";
   int hh, mm, ss;
   hh = mm = ss = 0;
   if(::sscanf(str.c_str(), "%d:%d:%d", &hh, &mm, &ss) != 3)
      return false;
   if(EncodeTime(hh, mm, ss) == false)
      return false;
   sError = "";
   return true;      
   }
StdDateTime& StdDateTime::operator-=(int sec)
   {
   user_assigned = 1;
   time_t ttime = (time_t) *this;
   ttime -= sec;
   ::memcpy((char *)&ttm, (char *)localtime(&ttime), sizeof(struct tm));
   return *this;
   }
StdDateTime& StdDateTime::operator=(const StdDateTime& ss)
   {
   if(this == &ss)
      return *this;	
   ::memcpy(&ttm, &ss.ttm, sizeof(struct tm));
   user_assigned = ss.user_assigned;
   return *this;
   }
StdDateTime& StdDateTime::operator=(struct tm& keep)
   {
   user_assigned = 1;
   ::memcpy((char *)&ttm, (char *)&keep, sizeof(struct tm));
   ::mktime(&ttm);      // normalize it.
   return *this;
   }
int StdDateTime::operator==(const StdDateTime& sdt) const
   {
   StdDateTime sampB = sdt;
   StdDateTime sampA = (*this);
   time_t tA = time_t(sampA);
   time_t tB = time_t(sampB);
   return (tA == tB);
   }
int StdDateTime::operator!=(const StdDateTime& sdt) const
   {
   StdDateTime sampB = sdt;
   StdDateTime sampA = (*this);
   time_t tA = time_t(sampA);
   time_t tB = time_t(sampB);
   return (tA != tB);
   }
int StdDateTime::operator>(const StdDateTime& sdt) const
   {
   StdDateTime sampB = sdt;
   StdDateTime sampA = (*this);
   time_t tA = time_t(sampA);
   time_t tB = time_t(sampB);
   return (tA > tB);
   }
int StdDateTime::operator<(const StdDateTime& sdt) const
   {
   StdDateTime sampB = sdt;
   StdDateTime sampA = (*this);
   time_t tA = time_t(sampA);
   time_t tB = time_t(sampB);
   return (tA < tB);
   }
int StdDateTime::operator>=(const StdDateTime& sdt) const
   {
   int ires = (*this == sdt);
   if(ires)
      return ires;
   return (*this > sdt);
   }
int StdDateTime::operator<=(const StdDateTime& sdt) const
   {
   int ires = (*this == sdt);
   if(ires)
      return ires;
   return (*this < sdt);
   }
StdDateTime::operator time_t(void)
   {
   /*
   The mktime function converts the supplied time structure
   (possibly incomplete) pointed to into a fully defined structure
   with normalized values and then converts it to a time_t calendar
   time value.
   */
   return ::mktime(&ttm);
   }
bool StdDateTime::DecodeDate(unsigned *yy, unsigned *mm, unsigned *dd) const
   {
   *yy = (ttm.tm_year + 1900);
   *mm = (ttm.tm_mon +1);
   *dd = ttm.tm_mday;
   return true;
   }
bool StdDateTime::DecodeDate(unsigned &yy, unsigned &mm, unsigned &dd) const
   {
   yy = (ttm.tm_year + 1900);
   mm = (ttm.tm_mon +1);
   dd = ttm.tm_mday;
   return true;
   }
bool StdDateTime::EncodeDate(unsigned yy, unsigned mm, unsigned dd) 
   {
   ZStr sError; 
   return EncodeDate(yy, mm, dd, sError);
   }
bool StdDateTime::EncodeDate(unsigned yy, unsigned mm, unsigned dd, ZStr& sError)
   {
   StdDateTime sdt;  // trying to fix ::mktime() problem - still no workee!
   sdt.Hack();       // (ibid!)

   if(yy < 1970)
      {
      sError = "Year is less than 1970";
      return false;
      }
   sdt.ttm.tm_year = yy   - 1900;
   if(!mm)
      {
      sError = "Month is ZERO.";
      return false;
      }
   if(mm > 12)
      {
      sError = "Month is greater than 12";
      return false;
      }
   sdt.ttm.tm_mon  = mm -1;
   if(!dd)
      {
      sError = "Day is ZERO.";
      return false;
      }
   if(dd > 31)
      {
      sError = "Day of month is greater than 31";
      return false;
      }
   sdt.ttm.tm_mday = dd;

   time_t tt = ::mktime(&sdt.ttm);
   if(tt == -1L)
      {
      sError = "mktime() failure!";
      return false;
      }
   *this = StdDateTime(tt);

   user_assigned = 1;
   return true;
   }
bool StdDateTime::EncodeTime(unsigned hh, unsigned mm, unsigned ss)
   {
   ttm.tm_hour = hh;
   ttm.tm_min = mm;
   ttm.tm_sec = ss;


   time_t tt = ::mktime(&ttm);
   if(tt == -1L)
      return false;

   *this = StdDateTime(tt);

   user_assigned = 1;
   return true;
   }
bool StdDateTime::DecodeTime(unsigned *hh, unsigned *mm, unsigned *ss) const
   {
   *hh = ttm.tm_hour; *mm = ttm.tm_min; *ss = ttm.tm_sec;
   return true;
   }
bool StdDateTime::DecodeTime(unsigned &hh, unsigned &mm, unsigned &ss) const
   {
   hh = ttm.tm_hour; mm = ttm.tm_min; ss = ttm.tm_sec;
   return true;
   }
ostream& StdDateTime::Write(ostream& os) const
   {
   return write_text(os);
   }
istream& StdDateTime::Read(istream& is)
   {
   char ch;
   is.get(ch);
   is.unget();
   if(ch == '+')
      return read_bin(is);    // Convert the older format -
   return read_text(is);
   }
ostream& StdDateTime::write_bin(ostream& os) const
   {
   os.write("+2", 2);
   os.write((const char *)&ttm, sizeof(struct tm));
   os.write((char *)&user_assigned, sizeof(int));
   return os;
   }
istream& StdDateTime::read_bin(istream& is)
   {
   char version[5];
   is.read((char *)&version, 2);
   is.read((char *)&ttm, sizeof(struct tm));
   if(version[1] == '1')
      user_assigned = 0;
   else
      is.read((char *)&user_assigned, sizeof(int));
   return is;
   }
ostream& StdDateTime::write_text(ostream& os) const
   {
   os << ExportDottedEditable(*this);
   return os;
   }
istream& StdDateTime::read_text(istream& is)
   {
   ZStr str;
   str.Readline(is, '$');
   str.Append('$');
   ImportDottedEditable(*this, str);
   return is;
   }
int StdDateTime::DaysInMonth(void) const 
   {
   return Able1::DaysInMonth(*this);
   }
ZStr StdDateTime::MonthName(void) const   
   {
   return Able1::MonthName(*this);
   }

ZStr AsHMS(time_t total_seconds, const char *pszMask)
   {
   StdDateTime sdt(total_seconds);
   unsigned h, m, s;
   sdt.DecodeTime(&h, &m, &s);
   char buf[80];
   ::sprintf(buf, pszMask, h, m, s);
   ZStr str = buf;
   return str;
   }

ZStr AsMDY(time_t total_seconds, const char *pszMask)
   {
   StdDateTime sdt(total_seconds);
   unsigned y, m, d;
   sdt.DecodeDate(&y, &m, &d);
   char buf[80];
   ::sprintf(buf, pszMask, m, d, y);
   ZStr str = buf;
   return str;
   }

ZStr AsMDYHMS(time_t total_seconds, const char *pszMask)
   {
   StdDateTime sdt(total_seconds);
   unsigned y, m, d, h, min, s;
   sdt.DecodeDate(&y, &m, &d);
   sdt.DecodeTime(&h, &min, &s);
   char buf[80];
   ::sprintf(buf, pszMask, m, d, y, h, min, s);
   ZStr str = buf;
   return str;
   }   

ZStr ExportDottedEditable(const StdDateTime& sdt)
   {
   ZStr sResult;
   stringstream srm;
   if(ExportDottedEditable(sdt, srm) == true)
      sResult = PRESTO(srm);
   return sResult;
   }

bool ExportDottedEditable(const StdDateTime& sdt, ostream& os)
   {
   unsigned int a, b, c;
   if(sdt.DecodeDate(&a, &b, &c) == false)
      return false;
   unsigned int d, e, f;
   if(sdt.DecodeTime(&d, &e, &f) == false)
      return false;
   os << "Date[" << a << "." << b << "." << c << "]+";
   os << "Time[" << d << "." << e << "." << f << "]$";
   return true;
   }

bool ImportDottedEditable(StdDateTime& sdt, istream& is)
   {
   ZStr str;
   str.Readline(is, '$');
   if(!is)
      return false;
   return ImportDottedEditable(sdt, str);
   }

bool ImportDottedEditable(StdDateTime& sdt, const ZStr& sss)
   {
   ZStr str = sss;
   int a, b, c, d, e, f;
   str.ToUpper();
   if(::sscanf(str.c_str(), "DATE[%d.%d.%d]+TIME[%d.%d.%d]", &a, &b, &c, &d, &e, &f) != 6)
      return false;
   if(sdt.EncodeDate(a, b, c, str) == false)
      return false;
   if(sdt.EncodeTime(d, e, f) == false)
      return false;
   return true;
   }

   bool IsLeapYear(unsigned uYear)
   {
      if((uYear % 4) == 0)
         {
         // A leap year is divisible by 4 ...
         if (uYear % 100 == 0)
            {
            // ... unless it's divisible by 100 in which case it isn't ...
            if (uYear % 400 == 0)
               // ... unless it's divisible by 400!
               return true;
            else
               return false;
            }
      return true;
      }
   return false;
   }

int DaysInMonth(const StdDateTime& sdt)
   {
   return DaysInMonth(sdt.Month(), sdt.Year());
   }

int DaysInMonth(int mon, unsigned year)
   {
   switch(mon)
      {
      case 1:  // January
      case 3:  // March
      case 5:  // May
      case 7:  // July
      case 8:  // August
      case 10: // October
      case 12: // December
         return 31;
      case 4:  // April
      case 6:  // June
      case 9:  // September
      case 11: // November
         return 30;
      case 2:  // Feb
         {
         int iPos = 0;
         IsLeapYear(year) ? iPos = 29 : iPos = 28;
         return iPos;
         }
      default:
         return 0;
      }
   }


ZStr MonthName(const StdDateTime& sdt)
   {
   return MonthName((unsigned)sdt.Month());
   }

ZStr MonthName(int mon)
   {
   ZStr sName;
   switch(mon)
      {
      case 1:
         sName = "January";
      break;
      case 2:
         sName = "February";
      break;
      case 3:
         sName = "March";
      break;
      case 4:
         sName = "April";
      break;
      case 5:
         sName = "May";
      break;
      case 6:
         sName = "June";
      break;
      case 7:
         sName = "July";
      break;
      case 8:
         sName = "August";
      break;
      case 9:
         sName = "September";
      break;
      case 10:
         sName = "October";
      break;
      case 11:
         sName = "November";
      break;
      case 12:
         sName = "December";
      break;
      default:
         sName = "Islandic Month of Nod";
      break;
      }
   return sName;
   }

   
 } // Able1
