// The BasicLineManager manages an enumerated list range. It is handy for doing
// things like keeping reack of the lines in a file, listbox, or other containers
// where the exact number of lines are known and relatively static.
//
// 08/17/2004: Class created, tested and verified, R. Nagy
//
#ifndef BasicLineManager_Hppx
#define BasicLineManager_Hppx

#include <Able1.hpp>

using namespace Able1;

class BasicLineManager
{
public:
   struct view_stat {
      int top;
      int bottom;
      int pos;
      // The default is for 100 items, range 0 - 99. Start at the top.
      view_stat() : top(0), bottom(100), pos(0) {}
   };

   bool range(int top, int bottom, int pos);   // Establish the range
   int  rangeStat(void) const;   // Return the current physical postion. Always valid in this class.
   int  rangeBottom(void) const; // Return the original EOF (N+1) value.
   int  rangeTop(void) const;    // Return the original top value.

   bool isEnd(void) const;       // Logical: Being at the bottom (EOF) is a VALID state. Use this to quickly test for it.

   int  setLine(int pos);            // Go to an absolute line postion. Accepts bottom.
   int  setLineUp(int nelem = 1);    // Go to a relative line position.
   int  setLineDown(int nelem = 1);  // Go to a relative line position. Can position to bottom (i.e - at the eof).

   int  setLastLine(void);           // Logical: The last line is the line BEFORE the end (bottom).
   int  setFirstLine(void);          // Logical: Same as the Top.

   bool operator=(view_stat& vs);
      
   operator view_stat() const
      {
      view_stat res = line;
      return res;
      }      
   
#ifdef TESTING_CASES
   bool test(ostream& os) const;
#endif

private:
   view_stat line;
};


#endif
