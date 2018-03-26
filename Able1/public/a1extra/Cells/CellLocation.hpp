#ifndef CellLocation_Hpp
#define CellLocation_Hpp

#include <Able1.hpp>


namespace Cells
{
using namespace Able1;

const unsigned undefined = -1;

// Minimum cell locaitons is (0,0).
// Default cell location is (undefined, undefined).
struct CellLocation
{
protected:
   unsigned x;
   unsigned y;
public:
   CellLocation(void)   : x(undefined), y(undefined)  {}
   CellLocation(unsigned x, unsigned y)               {X(x); Y(y);}

   bool X(unsigned i)  {x = i; return true;}
   bool Y(unsigned i)  {y = i; return true;}
   unsigned X(void)    {return x;}
   unsigned Y(void)    {return y;}

   int operator==(const CellLocation& ref) {if((x == ref.x) && (y == ref.y)) return 1; return 0;}
};

} // Namespace

#endif

