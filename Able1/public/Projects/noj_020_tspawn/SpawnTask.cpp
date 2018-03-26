// 01/14/2007: Written, R. Nagy
//
#include "SpawnTask.hpp"

SpawnTask::SpawnTask(void) : bOnce(true), bValid(false), sName("none")
   {
   }

bool SpawnTask::IsValid(void)   
   {
   return bValid;
   }

bool SpawnTask::Validate(void)
   {
   SpawnTask st;
   bValid = false;
   OidTag oid;
   if(st.Write(oid) == false)
      return false;
   if(st.Read(oid) == false)
      return false;
   bValid = true;
   return bValid;
   }

bool SpawnTask::Write_default(OidTag& oid)
   {
   oid = OidTag();
   oid.Name("SpawnTask");

   stringstream srm;
   StdDateTime sdt;
   ExportDottedEditable(sdt, srm);
   oid.Create("Run.Time", PRESTO(srm));

   oid.Create("Run.Once", "true");
   oid.Create("Name", "enter your task identifier here");
   oid.Create("File", "c:\\YourProgram.exe");
   oid.Create("File.Parameters", " ");

   oid.Create("Comment", "This file may contain multiple SpawnTask entries.");
   oid.Create("Comment", "Any object can contain multiple comments.");
   return true;
   }

RunResponse SpawnTask::RunTick(StdLog& log, ostream& cout, time_t ttMight)
   {
   StdDateTime sdt(ttMight);

   if(sdt >= sdtTime)
      return RunNow(log, cout);

   return rr_not_time;
   }

RunResponse SpawnTask::RunNow(StdLog& log, ostream& cout)
   {
   if(!file.Exists())
      {
      stringstream srm;
      srm << "ERROR: File " << file.Name() << " not found.";
      ZStr str = PRESTO(srm);
      cout << str;
      log.PrintLine(str);
      return rr_remove;
      }

   stringstream srm;
   srm << file.Name();
   srm << " " << sParams;

   if(::system(srm.str().c_str()) == 0)
      return rr_error;

   if(bOnce)
      return rr_remove;

   sdtTime.NextDay();

   return rr_run_rescheduled;
   }

int SpawnTask::operator==(const SpawnTask& ref)
   {
   if(ref.bOnce != bOnce)
      return 0;
   if(ref.sName != sName)
      return 0;
   if(ref.sParams != sParams)
      return 0;
   if(ref.sdtTime != sdtTime)
      return 0;
   ZStr str = ref.file.Name();
   if(str != file.Name())
      return 0;
   return 1;
   }

int SpawnTask::operator!=(const SpawnTask& ref)
   {
   int iRes = operator==(ref);
   return !iRes;
   }


bool SpawnTask::Read(const OidTag& oid)
   {
   bValid = false;

   ZStr str = oid.Name();
   str.ToLower();
   if(str != "spawntask")
      return false;


   StdDateTime sdt;
   oid.Read("Run.Time", str);
   if(ImportDottedEditable(sdt, str) == false)
      return false;
   sdtTime = sdt;

   if(oid.Read("Run.Once", str) == true)
      {
      bOnce = true;
      str.ToLower();
      if(str == "false")
         bOnce = false;
      }


   if(oid.Read("Name", sName) == false)
      return false;

   if(oid.Read("File", str) == false)
      return false;
   if(file.Name(str) == false)
      return false;

   oid.Read("File.Parameters", sParams);

   bValid = true;

   return bValid;
   }

bool SpawnTask::Write(OidTag& oid)
   {
   oid = OidTag();
   oid.Name("SpawnTask");

   stringstream srm;
   StdDateTime sdt;
   ExportDottedEditable(sdt, srm);
   oid.Create("Run.Time", PRESTO(srm));

   if(bOnce)
      oid.Create("Run.Once", "true");
   else
      oid.Create("Run.Once", "false");

   oid.Create("Name", sName);

   oid.Create("File", file.Name());

   oid.Create("File.Parameters", sParams);

   return true;
   }

istream& SpawnTask::Read(istream& is)
   {
   OidTag oid;
   oid.Read(is);
   Read(oid);
   return is;
   }

ostream& SpawnTask::Write(ostream& os)
   {
   OidTag oid;
   Write(oid);
   oid.Write(os);
   return os;      
   }

bool SpawnTask::Test(ostream& os)
   {
   SpawnTask taskA, taskB;

   if(taskA != taskB)
      {
      os << "Error 1" << endl;
      return false;
      }

   taskA.bOnce = false;
   if(taskA == taskB)
      {
      os << "Error 2" << endl;
      return false;
      }
   taskB = taskA;
   if(taskA != taskB)
      {
      os << "Error 3" << endl;
      return false;
      }

   taskA.file.Name("cmd.exe");
   if(taskA == taskB)
      {
      os << "Error 4" << endl;
      return false;
      }

   if(taskA.Validate() == false)
      {
      os << "Error 5" << endl;
      return false;
      }

   if(taskA.IsValid() == false)
      {
      os << "Error 6" << endl;
      return false;
      }

   taskB = SpawnTask();

   File file;
   taskA.Write(file.OpenWrite());
   file.Close();

   taskB.Read(file.OpenRead());
   file.Close();
   file.Remove();

   if(taskA != taskB)
      {
      os << "Error 7" << endl;
      return false;
      }

   return true;
   }
