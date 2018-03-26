// Color8
// 05/03/2005: Header created to handle same (cognative extraction from my ctoos operating system), R. Nagy
//
#ifndef StdColor_hpx
#define StdColor_hpx

#include <Able1.hpp>
using namespace Able1;

namespace stdscreen
{

// This color encoding scheme will represent 8 colors across a variety of platforms.
// Even if your platform does not have color, you can use this across the Able1 api.
struct Color8
{
bool red, green, blue;

Color8(void) :red(false), green(false), blue(false)
   {
   }
Color8(bool bred, bool bgreen, bool bblue) : red(bred), green(bgreen), blue(bblue)
   {
   }
void Set(bool bred, bool bgreen, bool bblue)
   {
   red   = bred;
   green = bgreen;
   blue  = bblue;
   }
ZStr Encode(void) const
   {
   ZStr sResult;
   if(red)
      sResult.Append("r");
   if(green)
      sResult.Append("g");
   if(blue)
      sResult.Append("b");
   return sResult;
   }
ZStr Decode(const ZStr& code)
   {
   ZStr sResult = code;
   sResult.ToLower();
   red = blue = green = false;
   if(sResult.Find('r') != npos)
      red = true;
   if(sResult.Find('g') != npos)
      green = true;
   if(sResult.Find('b') != npos)
      blue = true;
   }
static Color8 FromString(const ZStr& str)
   {
   Color8 color;
   color.Decode(str);
   return color;
   }
static ZStr ToString(const Color8& color)
   {
   return color.Encode();
   }
};

struct ColorSet
	{
	Color8 foreground;
	Color8 background;
	ColorSet(void)
	   {
	   Reset();
	   }
	void Reset(void)
	   {
	   foreground.red = foreground.green = foreground.blue = true;
	   background.red = background.green = background.blue = false;
	   }
	};


/*
 r g b
 = = =
 + + + white
 - - - black
 + - - red
 - + - green
 - - + blue
 + + - yellow
 - + + lt blue
 + - + lt red
*/

inline Color8 White8(void)
   {
   Color8 result;
   result.Set(true, true, true);
   return result;
   }
inline Color8 Black8(void)
   {
   Color8 result;
   result.Set(false, false, false);
   return result;
   }
inline Color8 Red8(void)
   {
   Color8 result;
   result.Set(true, false, false);
   return result;
   }
inline Color8 Green8(void)
   {
   Color8 result;
   result.Set(false, true, false);
   return result;
   }
inline Color8 Blue8(void)
   {
   Color8 result;
   result.Set(false, false, true);
   return result;
   }
inline Color8 Yellow8(void)
   {
   Color8 result;
   result.Set(true, true, false);
   return result;
   }
inline Color8 LightBlue8(void)
   {
   Color8 result;
   result.Set(false, true, true);
   return result;
   }
inline Color8 LightRed8(void)
   {
   Color8 result;
   result.Set(true, false, true);
   return result;
   }

} // namespace

#endif
