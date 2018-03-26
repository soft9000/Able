#include "../../../../protected/WinCon/WinCon01.hpp"

#include "Screen.hpp"
using namespace ColorTextReader;

struct Win32Screen : public Screen
{
   WinCon01 console;
   bool PutChar(char ch, int x, int y, const EgaColor16& clrFore, const EgaColor16& clrBack);
   
   WORD Translate(EgaColor16 clrFore, enum WinCon01::Plane plane)
      {
      switch(clrFore.iColor)
         {
         case STD_EGA_BLACK:
            {
            return console.BLACK(plane);
            }
         break;   
         case STD_EGA_LIGHTBLUE:
         case STD_EGA_BLUE:
            {
            return console.BLUE(plane);
            }
         break;   
         case STD_EGA_LIGHTGREEN:
         case STD_EGA_GREEN:
            {
            return console.GREEN(plane);
            }
         break;   
         case STD_EGA_WHITE:
            {
            return console.WHITE(plane);
            }
         break;   
         case STD_EGA_CYAN:
         case STD_EGA_LIGHTCYAN:
         case STD_EGA_MAGENTA:
         case STD_EGA_LIGHTMAGENTA:
         case STD_EGA_BROWN:
         case STD_EGA_LIGHTGRAY:
         case STD_EGA_DARKGRAY:
         case STD_EGA_YELLOW:
         case STD_EGA_LIGHTRED:
         case STD_EGA_RED:
         default:
            {
            return console.RED(plane);
            }
         break;   
         }
      }
};

Win32Screen screen;

bool Win32Screen::PutChar(char ch, int x, int y, const EgaColor16& clrFore, const EgaColor16& clrBack)
   {
   WORD attrib = 0L;
   attrib  = Translate(clrFore, WinCon01::Plane::FORE);
   attrib |= Translate(clrBack, WinCon01::Plane::BACK);
   return console.Put(x, y, ch, attrib);
   }
   
Screen *Screen::Obtain(ViewMode _mode)
   {
   return &screen;
   }
   
void Screen::Release(Screen *pScreen)
   {
   }
