
#include <core/Screensaver.hpp>


using namespace ScreenSaver;

BubbleMotion::BubbleMotion(void)
{
   srand(time(NULL));
   xinc = yinc = 1;
   maxrate = 3;
   minrate = 1;
   trend = none;     // bugfix 09/14/03, R. Nagy
}

void BubbleMotion::Fixup(int& Left, int& Top)
{
   if(minrate < maxrate)
      {
      xinc = yinc = 0;
      while(xinc < minrate)
         xinc = rand() % maxrate;
      while(yinc < minrate)
         yinc = rand() % maxrate;
      }
   else
      xinc = yinc = maxrate;     // gigo

   int foo = int(trend);
   while(foo == int(trend))
      foo = rand() % 8;
   trend = movement(foo);
   Bump(Left, Top);
   Bump(Left, Top);
}

void BubbleMotion::Bump(int& Left, int& Top)
{
switch(trend)
   {
   case North:
      {
      Top  -= yinc;
      //Left -= xinc;
      }
   break;
   case South:
      {
      Top  += yinc;
      //Left -= xinc;
      }
   break;
   case East:
      {
      //Top  -= yinc;
      Left += xinc;
      }
   break;
   case West:
      {
      //Top  -= yinc;
      Left -= xinc;
      }
   break;
   case NorthWest:
      {
      Top  -= yinc;
      Left -= xinc;
      }
   break;
   case SouthEast:
      {
      Top  += yinc;
      Left += xinc;
      }
   break;
   case NorthEast:
      {
      Top  -= yinc;
      Left += xinc;
      }
   break;
   case SouthWest:
      {
      Top  += yinc;
      Left -= xinc;
      }
   break;
   }
}


bool BubbleMotion::Next(int &Left, int &Top, int Width, int Height, int maxX, int maxY)
{
bool br = false;
if(trend == none)
   trend = NorthWest;
if(Top + Height > maxY)
   {
   Top = maxY - Height;
   Fixup(Left, Top);
   br = true;
   }
if(Left + Width > maxX)
   {
   Left = maxX - Width;
   Fixup(Left, Top);
   br = true;
   }
if(Left <= 0)
   {
   Left = 1;
   Fixup(Left, Top);
   br = true;
   }
if(Top <= 0)
   {
   Top = 1;
   Fixup(Left, Top);
   br = true;
   }
Bump(Left, Top);
return br;
}

