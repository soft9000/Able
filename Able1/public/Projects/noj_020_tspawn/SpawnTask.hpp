// 01/14/2007: Written and tested, R. Nagy
//
#ifndef SpawnTask_hpx
#define SpawnTask_hpx

#include <Able1.hpp>
#include <Extra/StdLog.hpp>


using namespace Able1;

enum RunResponse
   {
   rr_not_time,
   rr_run_rescheduled,
   rr_remove,
   rr_error
   };

class SpawnTask 
{
   protected:
      bool              bValid;

   public:
      bool              bOnce;
      ZStr         sName;
      ZStr         sParams;

      StdDateTime       sdtTime;

      File              file;

      SpawnTask(void);

      bool IsValid(void); 

      bool Validate(void);

      int operator==(const SpawnTask& ref);
      int operator!=(const SpawnTask& ref);

      RunResponse RunTick(StdLog& log, ostream& cout, time_t ttMight);

      RunResponse RunNow(StdLog& log, ostream& cout);

      bool Read(const OidTag& oid);
      bool Write(OidTag& oid);

      istream& Read(istream& is);
      ostream& Write(ostream& os);

      static bool Write_default(OidTag& oid);

      static bool Test(ostream& os);
};


#endif
