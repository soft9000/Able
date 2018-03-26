
#ifndef z_EMailLines78
#define z_EMailLines78

#include <a1mail/EMail.hpp>

namespace BetterMail
{

class EMailLines
   {
   ZStr sLines;
   size_t    szLastPos;

   public:
      EMailLines(void) : szLastPos(NULL)  {}
      virtual ~EMailLines(void)           {}

      void Assign(const EMailMessage& em);
      void Assign(const ZStr& str);

      bool FirstLine(ZStr& str); 
      bool NextLine(ZStr& str); 
   };

}

#endif

