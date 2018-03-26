#ifndef entry_hpp
#define entry_hpp

#include <Able1.hpp>
using namespace Able1;

namespace Taco
{
struct Entry
{
   bool bFound;
   ZStr sName;
   ZStr sDescription;

   Entry(void) : bFound(false)
      {
      }
};


}

#endif
