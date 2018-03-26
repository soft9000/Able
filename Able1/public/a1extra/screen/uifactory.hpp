// 05/04/2005: Created, R. Nagy
//
#ifndef uifactory_hpx
#define uifactory_hpx

#include <Able1.hpp>
using namespace Able1;

#include "consoledriver.hpp"
#include "graphicaldriver.hpp"

namespace stdscreen
{
class uifactory
   {
   // Create a driver - x and y are requests - use querysize to see the actuals
   static uidriver *create(const ZStr& sDriverName);
   static void dispose(uidriver *);
   };
} // namespace
#endif
