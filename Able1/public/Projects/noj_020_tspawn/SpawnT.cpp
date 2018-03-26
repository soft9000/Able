// 01/14/2007: Written, R. Nagy
//
#include "SpawnT.hpp"

bool SpawnT::Save(Array<SpawnTask>& job)
   {
   File file = Settings();
   ostream& os = file.OpenWrite();
   for(size_t ss = 0L; ss < job.Nelem(); ss++)
      job[ss].Write(os);
   file.Close();
   return file.Exists();
   }

bool SpawnT::Run(Array<SpawnTask>& job, ostream& cout, StdLog& log)
   {
   while(job.Nelem())
      {
      time_t tStart = ::time(NULL);
      time_t tNext  = tStart + 60;
      while(tNext > tStart)
         tStart = ::time(NULL);

      for(size_t ss = 0L; ss < job.Nelem(); ss++)
         {
         enum RunResponse resp = job[ss].RunTick(log, cout, ::time(NULL));
         switch(resp)
            {
            case rr_remove:
               {
               job.Remove(ss);
               ss--;
               stringstream srm;
               srm << "Task " << job[ss].sName << " removed (as requested).";
               ZStr str = PRESTO(srm);
               cout << str;
               log.Log(str);
               if(Save(job) == false)
                  {
                  str = "ERROR: Unable to re-schedule tasks!";
                  cout << str;
                  log.PrintLine(str);
                  return false;
                  }
               }
            continue;
            case rr_error:
               {
               stringstream srm;
               srm << "Task " << job[ss].sName << " reports error.";
               ZStr str = PRESTO(srm);
               cout << str;
               log.Log(str);
               }
            return false;
            case rr_run_rescheduled:
               {
               if(Save(job) == false)
                  {
                  ZStr str = "ERROR: Unable to re-schedule tasks!";
                  cout << str;
                  log.PrintLine(str);
                  return false;
                  }
               }
            continue;

            default:
            case rr_not_time:
               {
               }
            continue;
            }
         }

      }
   return Save(job);
   }
bool SpawnT::Run(void)
   {
   StdLog log;

   File file = Settings();
   if(!file.Exists())
      {
      log.PrintLine("Settings file not found. Did you use -edit?");
      Usage(cout);
      return false;
      }

   // STEP: Load the tasks
   Array<SpawnTask> tasks;
   tasks.AddZombies(25);
   istream& is = file.OpenRead();
   SpawnTask task;
   while(is)
      {
      task.Read(is);
      if(!is)
         continue;
      tasks.Append(task);
      }
   file.Close();
   if(!tasks.Nelem())
      {
      ZStr str = "Task list is empty.";
      log.PrintLine(str);
      cout << str << endl;
      return false;
      }

   return Run(tasks, cout, log);
   }

File SpawnT::Settings(void)
   {
   File file("SPAWNT.TXT");
   return file;
   }

bool SpawnT::CreateSettings(void)
   {
   OidTag oid;
   if(SpawnTask::Write_default(oid) == false)
      return false;
   File file = Settings();
   oid.Write(file.OpenWrite());
   return true;
   }

bool SpawnT::EditSettings(void)
   {
   return Settings().Launch();
   }

void SpawnT::Usage(ostream& cout)
   {
   cout << "SpawnT - " << __DATE__ << endl;
   cout << "======" << endl << endl;
   cout << "   -edit   Create / edit settings" << endl;   
   cout << "   -run    Process settings" << endl;
   }

int SpawnT::Main(int argc, char *argv[], ostream& cout)
   {
   if(argc != 2)
      {
      Usage(cout);
      return 0;
      }

   ZStr str = argv[1];
   str.ToLower();

   if(str == "-edit")
      return int(SpawnT::EditSettings());

   if(str == "-run")
      return int(SpawnT::Run());

   return 0;
   }
bool SpawnT::Test(ostream& os)
   {
   if(SpawnTask::Test(os) == false)
      return false;

   return true;
   }
