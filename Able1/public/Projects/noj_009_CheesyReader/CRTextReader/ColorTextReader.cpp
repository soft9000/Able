#include "ColorTextReader.hpp"

using namespace ColorTextReader;

void ColorArea::Clear(void)
{
Screen *pScreen = Screen::Obtain();
if(pScreen)
   {
   for(int yy = y; yy < y + cy; yy++)
      {
      for(int xx = x; xx < x + cx; xx++)
         pScreen->PutChar(' ', xx, yy, clrFore, clrBack);
      }
   }
}

TextCommandArea::TextCommandArea(void)
{
Setup(Screen::STARTX(), 
      Screen::STARTY(), 
      Screen::MAXX(), 
      1, 
      STD_EGA_WHITE, 
      STD_EGA_GREEN);
}
TextMessageArea::TextMessageArea(void)
{
Setup(Screen::STARTX(), 
      Screen::MAXY(), 
      Screen::MAXX(), 
      1, 
      STD_EGA_RED, 
      STD_EGA_BLUE);
}
TextPageArea::TextPageArea(void)
{
Setup(Screen::STARTX() + (Screen::MAXX() / 3) * 2, 
      Screen::STARTY() + 1, 
      Screen::MAXX(),
      Screen::MAXY() - 1, 
      STD_EGA_BLACK, 
      STD_EGA_WHITE);
}
TextVerseArea::TextVerseArea(void)
{
Setup(Screen::STARTX(),    
      Screen::STARTY() + 1, 
      Screen::MAXX() / 3,  
      Screen::MAXY() - 1, 
      STD_EGA_WHITE, 
      STD_EGA_BLACK);
}


void TextCommandArea::Draw(void)
{
// TODO: Draw, 'pardner...
}

void TextMessageArea::Draw(void)
{
// TODO: Draw, 'pardner...
}

void TextVerseArea::Draw(void)
{
// TODO: Draw, 'pardner...
}

void TextPageArea::Draw(void)
{
// TODO: Draw, 'pardner...
}

