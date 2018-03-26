
#ifndef z_RoutingSlip
#define z_RoutingSlip

#include <Able1.hpp>
using namespace Able1;


class RoutingSlip
   {
   private:
      ZStr _to;
      ZStr _from;
      ZStr _subject;

   public:
      RoutingSlip(void)                         {}
      RoutingSlip(const RoutingSlip& rs)        {*this = rs;}
      virtual ~RoutingSlip(void)                {}

      bool        IsNull(void)                  {if(_to.IsNull() && _from.IsNull() && _subject.IsNull()) return true; return false;}

      void        From(const ZStr& ss)     {_from   = ss;}
      void        To(const ZStr& ss)       {_to     = ss;}
      void        Subject(const ZStr& ss)  {_subject= ss;}

      const char *To(void)           const      {return _to.c_str();       }
      const char *From(void)         const      {return _from.c_str();     }
      const char *Subject(void)      const      {return _subject.c_str();  }

      RoutingSlip& operator=(const RoutingSlip& rs)
                                                {if(this == &rs) return *this; _from = rs._from; _to = rs._to; _subject = rs._subject; return *this;}
   };

#endif

