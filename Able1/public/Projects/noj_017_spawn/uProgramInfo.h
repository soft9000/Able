//---------------------------------------------------------------------------

#ifndef uProgramInfoH
#define uProgramInfoH
//---------------------------------------------------------------------------

#include "uTaskEntry.h"

#include <FastJob.hpp>
#include <extra/StdLog.hpp>
using namespace FastJob;

struct ProgramInfo
   {
   StdLog pwLog;
   File   pwTaskFile;
   File   pwOptionsFile;
   Directory dirLogs;
   Array<TaskEntry> aTasks;

   struct Options
      {
      bool bAutoRun;
      bool bDayOnly;
      int  iTimerSec;
      int  iPauseMinutes;
      Options(void) : bAutoRun(false), bDayOnly(false), iTimerSec(7), iPauseMinutes(10)
         {
         }
      ostream& write(ostream& os);
      istream& read(istream& is);

      } options;

   ProgramInfo(void)
      {
      ProgramId pid;

      pwTaskFile.Name("Tasks.DAT");
      pid.Home(pwTaskFile);
      if(pwTaskFile.Exists() == true)
         TaskEntry::Load(pwTaskFile, aTasks);

      pwOptionsFile.Name("Options.DAT");
      pid.Home(pwOptionsFile);
      if(pwOptionsFile.Exists() == true)
         {
         options.read(pwOptionsFile.OpenRead(File::AT_BINARY));
         pwOptionsFile.Close();
         }

      dirLogs.Name("LOGS");
      pid.Home(dirLogs);
      if(dirLogs.Exists() == false)
         dirLogs.Create();

      StdDateTime sdt;
      stringstream srm;
      srm << sdt.Year() << "_" << sdt.JulianDay() << ".LOG";
      pwLog.pwFile.Name(srm.str().c_str());
      dirLogs.Home(pwLog.pwFile);
      }

   bool Save(void)
      {
      options.write(pwOptionsFile.OpenWrite(File::AT_BINARY));
      pwOptionsFile.Close();
      return TaskEntry::Save(pwTaskFile, aTasks);
      }

   ~ProgramInfo(void)
      {
      Save();
      }
   };


#endif
