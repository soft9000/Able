// 02/16/2007: Updated RandRange to call Rnd(exact same implementation), R. Nagy
//             Updated Rnd() to perform basic range and santiy chackeing, R. Nagy
#include <Able1.hpp>
using namespace Able1;

void Random::Randomize(void)
   {
   srand((unsigned int)time(NULL));
   }
void Random::Randomize(unsigned ui)
   {
   srand(ui);
   }
int Random::RandRange(int min, int max)
   {
   return Rnd(min, max);
   }

int Random::Rnd(int min, int max)
   {
   if(min == max)
      return max;
   if(min > max)
      swap(min, max);
   return ((::rand() % (int)(((max)+1) - (min))) + (min));
   }

int Random::Rnd(int max)
   {
   if(!max)
      max = 1;
   srand((unsigned int)time(NULL));
   return ((rand() >> 3) % max);
   }

bool Random::TF(void)
   {
   bool iSeed = false;
   if(!iSeed)
      {
      srand((unsigned int)time(NULL));
      iSeed = true;
      }
   int iRand = rand();
   if(iRand % 2)
      return true;
   return false;
   }


