#include <Able1.hpp>
using namespace Able1;

#include "EgaColor16.hpp"

namespace ColorTextReader
{
struct Screen
   {
   static int STARTX(void) {return 0;}
   static int STARTY(void) {return 0;}
   static int MAXX(void)   {return 80;}
   static int MAXY(void)   {return 25;}
   
   virtual bool PutChar(char ch, int x, int y, const EgaColor16& clrFore, const EgaColor16& clrBack) = 0;
   
   enum ViewMode
      {
      viewTextColor
      };
      
   static Screen *Obtain(ViewMode _mode = viewTextColor);
   static void    Release(Screen *);
   };
