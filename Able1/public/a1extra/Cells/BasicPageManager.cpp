#include "BasicPageManager.hpp"


BasicPageManager::BasicPageManager(void) : linesPerPage(rangeBottom() / 10) 
   {
   }

bool BasicPageManager::pageSize(int num_lines)
   {
   if(!num_lines)
      return false;
   if(num_lines < rangeTop())
      return false;
   if(num_lines >= rangeBottom())
      return false;
   linesPerPage = num_lines;
   return true;         
   }
int BasicPageManager::pageSet(int page_number)
   {
   int pos = (linesPerPage - 1) * page_number; // Parens always make me feel better...
   return setLine(pos);
   }
int BasicPageManager::pageUp(int num)
   {
   int pos = rangeStat() - (num * linesPerPage) +1;
   return setLine(pos);
   }
int BasicPageManager::pageDown(int num)
   {
   int pos = rangeStat() + (num * linesPerPage) -1;
   return setLine(pos);
   }
// Express where we are in page terms      
int BasicPageManager::pageStat(void) const
   {
   return (rangeStat() / linesPerPage);
   }
int BasicPageManager::pageFirst(void)
   {
   return setFirstLine();
   }
int BasicPageManager::pageLast(void)
   {
   return setLine(this->rangeBottom() - linesPerPage -1);
   }            
   
#ifdef TESTING_CASES
bool BasicPageManager::test(ostream& os) const
   {
   // Step
   BasicPageManager bpm;
   if(bpm.range(0, 100, 0) == false)
      {
      os << "Unable to set the range" << endl;
      return false;
      }
   int iResult = 0;
   bpm.pageSize(5);
   if(bpm.pageSize() != 5)
      {
      os << "Unable to set page size." << endl;
      return false;
      }
   iResult = bpm.pageDown();
   if(iResult != 4)
      {
      os << "Simple page down fails." << endl;
      return false;
      }         
   iResult = bpm.pageUp();
   if(iResult != 0)
      {
      os << "Simple page up fails." << endl;
      return false;
      }
   iResult = bpm.pageDown();  //  4
   iResult = bpm.pageDown();  //  8
   iResult = bpm.pageDown();  // 12
   if(iResult != 12)
      {
      os << "Simple page down fails." << endl;
      return false;
      }         
   // Step      
   iResult = bpm.pageSet(0);
   if(iResult != 0)
      {
      os << "Relative page jump 0 fails." << endl;
      return false;
      }
   iResult = bpm.pageSet(1);
   if(iResult != 4)
      {
      os << "Relative page jump 1 fails." << endl;
      return false;
      }
   iResult = bpm.pageSet(2);
   if(iResult != 8)
      {
      os << "Relative page jump 2 fails." << endl;
      return false;
      }
   iResult = bpm.pageSet(3);
   if(iResult != 12)
      {
      os << "Relative page jump 3 fails." << endl;
      return false;
      }
   iResult = bpm.pageLast();
   if(iResult != 94)
      {
      os << "Last page jump fails." << endl;
      return false;
      }
   iResult = bpm.pageDown();
   if(iResult != 98)
      {
      os << "Last page page down attempt fails." << endl;
      return false;
      }
   iResult = bpm.pageDown();
   if(iResult != -1)
      {
      os << "EOF page down ERROR attempt fails." << endl;
      return false;
      }
   // Step      
   return true;
   }
#endif

