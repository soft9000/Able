#include "EgaColor16.hpp"
#include "Screen.hpp"

namespace ColorTextReader
{
   
struct ColorArea
   {
   Array<ZStr> aLines;
   
   int x, y;
   int cx, cy;
   EgaColor16 clrFore;
   EgaColor16 clrBack;
   ColorArea(void)
      {
      x  = Screen::STARTX(); y = Screen::STARTY();
      cx = Screen::MAXX();  cy = Screen::MAXY();
      clrFore.Color(STD_EGA_YELLOW);
      clrBack.Color(STD_EGA_BLUE);
      }
   void Setup(int xpos, int ypos, int cxx, int cyy, int iCF, int iCB)
      {
      x  = xpos; y = ypos;
      cx = cxx; cy = cyy;
      clrFore.Color(iCF);
      clrBack.Color(iCB);
      }
      
   virtual void Clear(void);
   virtual void Draw(void) = 0;
           void Redraw(void) {Clear(); Draw();}
   };

// Top line
struct TextCommandArea : public ColorArea
   {
   TextCommandArea(void);
   void Draw(void);
   };

// Bottom line
struct TextMessageArea : public ColorArea
   {
   TextMessageArea(void);
   void Draw(void);
   };

// Right hand - 2/3 of the screen
struct TextPageArea : public ColorArea
   {
   TextPageArea(void);
   void Draw(void);
   };

// Left hand - 1/3 of the screen   
struct TextVerseArea : public ColorArea
   {
   TextVerseArea(void);
   void Draw(void);
   };
   
class Reader : public ColorArea
   {
   protected:
      TextCommandArea areaCommand;
      TextMessageArea areaMessage;
      TextVerseArea   areaVerse;
      TextPageArea    areaPage;
   public:
      void Draw(void)
         {
         areaCommand.Draw();
         areaMessage.Draw();
         areaVerse.Draw();
         areaPage.Draw();
         }
      void Clear(void)
         {
         ColorArea::Clear(); // draw our background
         areaCommand.Clear();
         areaMessage.Clear();
         areaVerse.Clear();
         areaPage.Clear();
         }
   };   
}
