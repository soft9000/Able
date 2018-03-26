
#ifndef z_EMailLines
#define z_EMailLines

#include <Able1.hpp>
using namespace Able1;

class EMail;

class EMailLines
   {
   ZStr sLines;
   size_t    szLastPos;

   public:
      EMailLines(void) : szLastPos(NULL)  {}
      virtual ~EMailLines(void)           {}

      void Assign(const EMail& em);

      bool FirstLine(ZStr& std); 
      bool NextLine(ZStr& std); 
   };



#endif

