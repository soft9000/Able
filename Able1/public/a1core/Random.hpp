// 02/16/2007: Updated RandRange to call Rnd(exact same implementation), R. Nagy
//             Updated Rnd() to perform basic range and santiy chackeing, R. Nagy
// 02/17/2007: Added Randomize(), R. Nagy
//
#ifndef RandomStd_hpx
#define RandomStd_hpx

namespace Able1 {

#define Max(a, b) (a > b) ? a : b;
#define Min(a, b) (a < b) ? a : b;

struct Random
   {
// Select a pseudo random number between `min` and `max` (inclusive)
   static void Randomize(void);
   static void Randomize(unsigned ui);
   static int RandRange(int min, int max);
   static int Rnd(int min, int max);
   static int Rnd(int max=1000);
   static bool TF(void);
   };
}
#endif

 
