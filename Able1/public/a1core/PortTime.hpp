// Class PortTime: Use this when you just want to store a human-readable time.
// 01/08/1997: Class created (Document project, 32bit update), R. Nagy
//    Interfaced same with Node1 and GetFileTime classes.
// 11/02/1999: Added Encode/DecodeDate() and Encode/DecodeTime(), R. Nagy
// 03/29/2001: Fixed operator < and >, R. Nagy
// 12/05/2001: Added Extract(struct tm), R. Nagy
// 11/24/2004: Extracted implementation into it's own file, R. Nagy
//
#ifndef PORT_TIME_HPP
#define PORT_TIME_HPP


namespace Able1
   {

/** PortTime competes with StdDateTime to provide a streamable date / time format.
  *
  */
class PortTime
   {
   protected:
      struct goomey
         {
         int YY;
         int DD;
         int MM;
         int SS;
         int Mn;
         int HH;
         } goo;
   public:
      PortTime(void);
      virtual ~PortTime(void);

      int Day(void)              const;
      int Month(void)            const;
      int Year(void)             const;

      int Hour24(void)           const;
      int Minute(void)           const;
      int Second(void)           const;

      void DateYMD(int yy, int mm, int dd);
      void TimeHMS(int hh, int mm, int ss);

      void EncodeDate(int yy, int mm, int dd);
      // DO NOT USE REFERENCES HERE: Causes problem under C++ Builder 5.x;
      void DecodeDate(int *yy, int *mm, int *dd);

      void EncodeTime(int hh, int mm, int ss);
      // DO NOT USE REFERENCES HERE: Causes problem under C++ Builder 5.x;
      void DecodeTime(int *hh, int *mm, int *ss);

      PortTime& operator = (const PortTime& pt);

      int operator == (const PortTime& pt)   const;

      int operator != (const PortTime& pt)   const;

      int operator > (const PortTime& pt)    const;

      int operator < (const PortTime& pt)    const;

      // Default date format is StdDateTime::sdtMasks::AsMDY()
      const char *Format(ZStr& str, const char *pFmt = 0L) const;

      ostream& Write(ostream& os);
      istream& Read(istream& is);
      time_t Extract(struct tm& rtm);
      time_t Extract(void);
   };

   } // Able1
#endif
