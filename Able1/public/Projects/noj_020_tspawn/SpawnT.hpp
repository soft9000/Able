// 01/14/2007: Written, R. Nagy
//
#ifndef SpawnT_hpx
#define SpawnT_hpx

#include "SpawnTask.hpp"


class SpawnT
{
private:
   static bool Run(Array<SpawnTask>& job, ostream& cout, StdLog& log);
   static bool Run(void);
   static bool Save(Array<SpawnTask>& job);

   static File Settings(void);

protected:
   static bool CreateSettings(void);
   static bool EditSettings(void);
   static void Usage(ostream& cout);

public:
   static int  Main(int argc, char *argv[], ostream& cout);
   static bool Test(ostream& os);
};

#endif
