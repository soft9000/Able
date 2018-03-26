// ScreenSaver: Classes to support moving rectangles (etc) about as used in
// a screen-saver (etc).
//
// 07/03/2003: Class created by refactoring old OmniWind BubbleMotion class, R. Nagy
// 12/03/2006: ScreenSaver namespace created, R. Nagy
//
#ifndef BubMot_hpx
#define BubMot_hpx

namespace ScreenSaver
{
class BubbleMotion
   {
   protected:
      int maxrate;
      int minrate;
      int xinc, yinc;
      void Bump(int &X, int &Y);
      void Fixup(int &X, int &Y);
   public:
      enum movement
         {
         North,
         South,
         East,
         West,
         NorthWest,
         NorthEast,
         SouthWest,
         SouthEast,
         none
         } trend;

      BubbleMotion(void);
      // Returns TRUE if there has been a change in movement:
      bool Next(int &X, int &Y, int xWide, int yHigh, int maxX, int maxY);
      void MaxRate(int r)  {maxrate = r;}
      int  MaxRate(void)   {return maxrate;}
      void MinRate(int r)  {minrate = r;}
      int  MinRate(void)   {return minrate;}
   };
}

#endif
