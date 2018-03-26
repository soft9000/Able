#ifndef CommBase_Hpp
#define CommBase_Hpp

#include <Able1.hpp>

using namespace Able1;

namespace stdnet
{

class CommBase
   {
   public:

      virtual bool Send(const ZStr& std) = 0;

      virtual bool Receive(ZStr&) = 0;

      virtual bool Transact(const ZStr& in, ZStr& out) = 0;

      virtual int         GetLastError(void) const = 0;
      virtual const char *GetError(ZStr& sResult, int iCode) const = 0;
   };
}

#endif
