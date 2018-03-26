// The BasicPageManager allows a "frame" (page) to be imposed upon a line enumeration.
// In general, the page manager returns the line number, not the page, of each operation.
//
// 08/17/2004: Class created, R. Nagy
// 08/18/2004: Lightly tested. Basic functionality assured, but more on the way, R. Nagy
//
#ifndef BasicLineManager_hppx
#define BasicLineManager_hppx

#include "BasicLineManager.hpp"

// GUI pagination is a strange beastie for a number of reasons. First of all, users 
// expect to see the last item on the page become the first line on a new page.
// So beware - this class always honors the user's expectations. In other words, 
// starting at the top and doing two page downs is equivalent to going to page 2 
// (the zero-based third page).
//
class BasicPageManager : public BasicLineManager
{
private:
   int linesPerPage;
public:
   BasicPageManager(void);

   bool pageSize(int num_lines);                      // Set number of lines per page
   int  pageSize(void) const {return linesPerPage;}   // Get number of lines per page
   
   int  pageSet(int page_number);// Set page (absolute). Zero based.
   int  pageStat(void) const;    // Query where we are in page terms

   int  pageUp(int num = 1);     // Page up (relative)
   int  pageDown(int num = 1);   // Page down (relative)

   int  pageFirst(void);         // Go to the first page
   int  pageLast(void);          // Go to the last page
   
#ifdef TESTING_CASES
   bool test(ostream& os) const;
#endif

};

#endif
