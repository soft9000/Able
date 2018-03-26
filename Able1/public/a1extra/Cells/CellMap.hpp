//---------------------------------------------------------------------------

#ifndef CellMap_hpp
#define CellMap_hpp
//---------------------------------------------------------------------------

#include <Cells/CellLocation.hpp>

namespace Cells
{
// A CellMap is all of the cells layed out in a cartesian plain,
// with the origin (0, 0) in the upper right (CRT default). No offset
// origin, or page support. The basis for many linear array management
// classes.
class CellMap
{
protected:
   size_t calcit(CellLocation& ref);    // raw result. undefined on error.
   bool   normalize(CellLocation& ref); // true if it was normalized.
   struct keep
      {
      unsigned x;
      unsigned y;
      keep(void) : x(undefined), y(undefined) {}
      } matDimension;
public:
   CellMap(unsigned x, unsigned y);       // Mat dimensions
   CellMap(CellLocation ref);             // Mat dimensions

   unsigned       CellCount(void);        // Number of cells
   CellLocation   MatSize(void);          // Mat dimensions
   bool           MatResize(CellLocation);// Mat dimensions

   CellLocation   Query(size_t);             // Array position to cell
   size_t         Query(CellLocation&);      // Cell position to array. WILL NORMALIZE!
   bool           Normalize(CellLocation&);  // Normalize as required. True if it had to.
};

} // namespace Cells
#endif
