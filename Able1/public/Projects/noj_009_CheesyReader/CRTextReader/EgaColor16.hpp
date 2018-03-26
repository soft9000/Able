#ifndef EgaColor16_hpp
#define EgaColor16_hpp

#include <Able1.hpp>
using namespace Able1;

namespace ColorTextReader
{

const int STD_EGA_BLACK        = 0;
const int STD_EGA_BLUE         = 1;
const int STD_EGA_GREEN        = 2;
const int STD_EGA_RED          = 4;
const int STD_EGA_LIGHTBLUE    = 57;
const int STD_EGA_LIGHTGREEN   = 58;
const int STD_EGA_LIGHTRED     = 60;
const int STD_EGA_CYAN         = 3;
const int STD_EGA_LIGHTCYAN    = 59;
const int STD_EGA_MAGENTA      = 5;
const int STD_EGA_LIGHTMAGENTA = 61;
const int STD_EGA_BROWN        = 20;
const int STD_EGA_LIGHTGRAY    = 7;
const int STD_EGA_DARKGRAY     = 56;
const int STD_EGA_YELLOW       = 62;
const int STD_EGA_WHITE        = 63;


struct EgaColor16
{
   int iColor;

   EgaColor16(void) : iColor(STD_EGA_YELLOW) {}

   bool Color(int color)
      {
      switch(iColor)
         {
         case STD_EGA_BLACK:
         case STD_EGA_LIGHTBLUE:
         case STD_EGA_BLUE:
         case STD_EGA_LIGHTGREEN:
         case STD_EGA_GREEN:
         case STD_EGA_WHITE:
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
            iColor = color;
         return true;
         default:
         return false;
         }
      }
      
   bool Color(const ZStr& str)
      {
      ZStr sColor = str;
      sColor.Strip();
      sColor.ToUpper();
      if(sColor == "RED")
         {
         iColor = STD_EGA_RED;
         return true;
         }
      if(sColor == "GREEN")
         {
         iColor = STD_EGA_GREEN;
         return true;
         }
      if(sColor == "BLUE")
         {
         iColor = STD_EGA_BLUE;
         return true;
         }
      if(sColor == "YELLOW")
         {
         iColor = STD_EGA_YELLOW;
         return true;
         }
      if(sColor == "BLACK")
         {
         iColor = STD_EGA_BLACK;
         return true;
         }
      if(sColor == "WHITE")
         {
         iColor = STD_EGA_WHITE;
         return true;
         }
      if(sColor == "LIGHTBLUE")
         {
         iColor = STD_EGA_LIGHTBLUE;
         return true;
         }
      if(sColor == "LIGHTGREEN")
         {
         iColor = STD_EGA_LIGHTGREEN;
         return true;
         }
      if(sColor == "LIGHTRED")
         {
         iColor = STD_EGA_LIGHTRED;
         return true;
         }
      if(sColor == "CYAN")
         {
         iColor = STD_EGA_CYAN;
         return true;
         }
      if(sColor == "LIGHTCYAN")
         {
         iColor = STD_EGA_LIGHTCYAN;
         return true;
         }
      if(sColor == "MAGENTA")
         {
         iColor = STD_EGA_MAGENTA;
         return true;
         }
      if(sColor == "LIGHTMAGENTA")
         {
         iColor = STD_EGA_LIGHTMAGENTA;
         return true;
         }
      if(sColor == "BROWN")
         {
         iColor = STD_EGA_BROWN;
         return true;
         }
      if(sColor == "LIGHTGRAY")
         {
         iColor = STD_EGA_LIGHTGRAY;
         return true;
         }
      if(sColor == "DARKGRAY")
         {
         iColor = STD_EGA_DARKGRAY;
         return true;
         }
      return false;
      }
};

} // namespace
#endif
