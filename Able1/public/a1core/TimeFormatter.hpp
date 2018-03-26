// TimeFormatter: Manage standard time formatting requirements.
//
// 12/30/2007: Created for better RSS Support, R. Nagy
//
 
#ifndef TimeFormatter_hpp
#define TimeFormatter_hpp

// http://asg.web.cmu.edu/rfc/rfc822.html#sec-5

namespace Able1
{
/*  Manage standard time formatting requirements, suitable for RFC usage.
 *
 */
class TimeFormatter
{
private:
      ZStr timeZone;

      static const char *day[7];
      static const char *month[12];

public:

      TimeFormatter(void);

      TimeFormatter(const ZStr& sTimeZone);

      ZStr pad2(int iPos);

      ZStr Format822(const StdDateTime& sdt);

      bool Format822(const StdDateTime& sdt, ZStr& sResult);
};

// Use the default (compiled) time-zone (typically GMT)
bool Format822(const StdDateTime& sdt, ZStr& sResult);
ZStr Format822(const StdDateTime& sdt);

} // namespace

#endif
