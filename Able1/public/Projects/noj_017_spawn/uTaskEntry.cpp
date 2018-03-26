//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTaskEntry.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TaskEntry::TaskEntry(void) : bOnceOnly(true), bHasRun(false), bHasFailed(false)
   {
   sTaskName = "Task Name";
   sComment = "Comment ...";
   }
int TaskEntry::operator==(const TaskEntry& ref) const
   {
   if(bOnceOnly != ref.bOnceOnly)
      return 0;
   if(sTaskName != ref.sTaskName)
      return 0;
   if(sComment != ref.sComment)
      return 0;
   if(oidParams != ref.oidParams)
      return 0;
   if(sdtNext != ref.sdtNext)
      return 0;
   return 1;
   }
bool TaskEntry::IsNull(void) const
   {
   TaskEntry ref;
   return (*this == ref);
   }
ostream& TaskEntry::Write(ostream& os)
   {
   ZStr str;
   str.Append((int)bOnceOnly);
   str.WriteStream(os);

   str = "";
   str.Append((int)bHasRun);
   str.WriteStream(os);

   str = "";
   str.Append((int)bHasFailed);
   str.WriteStream(os);

   sTaskName.WriteStream(os);
   sComment.WriteStream(os);
   sdtNext.Write_bin(os);

   pwFile.Write(os);
   oidParams.WriteStream(os);
   return os;
   }
istream& TaskEntry::Read(istream& is)
   {
   ZStr str;
   str.ReadStream(is);
   bOnceOnly = (bool)str[0];
   str.ReadStream(is);
   bHasRun = (bool)str[0];
   str.ReadStream(is);
   bHasFailed = (bool)str[0];

   sTaskName.ReadStream(is);
   sComment.ReadStream(is);
   sdtNext.Read_bin(is);

   pwFile.Read(is);
   oidParams.ReadStream(is);
   return is;
   }
void TaskEntry::EncodeParams(const Array<ZStr>& aaa)
   {
   oidParams = OidTag();
   Array<ZStr> array = aaa;
   stringstream srm;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      srm << array[ss] << oidParams.SafeSep();
   oidParams.Name(srm.str().c_str());
   }
void TaskEntry::DecodeParams(Array<ZStr>& aParams) const
   {
   aParams = oidParams.Name().slice(oidParams.SafeSep());
   }
bool TaskEntry::ShouldRun(const TaskEntry& entry)
   {
   StdDateTime sdt;

   if(entry.bHasFailed)
      return false;

   if(entry.bOnceOnly == true)
      if(entry.bHasRun == true)
         return false;

   if(sdt >= entry.sdtNext)
      return true;
   return false;
   }
bool TaskEntry::Reschedule(TaskEntry& entry)
   {
   if(entry.bOnceOnly == true)
      return false;
   entry.sdtNext.NextDay();
   return true;
   }
bool TaskEntry::Launch(const TaskEntry& entry, StdLog& log)
   {
   if(entry.pwFile.Exists() == false)
      {
      log.PrintLine(ZStr("Launch Error: File ") + entry.pwFile.Name() + " not found.");
      return false;
      }

   log.PrintLine(ZStr("Launching: ") + entry.sTaskName + "...");
   stringstream srm;
   ZStr str = entry.pwFile.Name();
   Array<ZStr> array;
   entry.DecodeParams(array);
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      str += " ";
      str += array[ss];
      }

   if(::system(str.c_str()) == -1)
      {
      log.PrintLine(ZStr("Failure: ") + entry.sTaskName + " did not launch");
      return false;
      }

   log.PrintLine(ZStr("Success: ") + entry.sTaskName + " launched");
   return true;
   }
size_t TaskEntry::FindNext(Array<TaskEntry>& array)
   {
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(ShouldRun(array[ss]) == true)
         return ss;
      }
   return npos;
   }
bool TaskEntry::Load(const File& fff, Array<TaskEntry>& aResult)
   {
   aResult.Empty();
   File pwFile = fff;
   istream& is = pwFile.OpenRead(File::AT_BINARY);
   if(!is)
      return false;
   aResult.Read(is);
   if(!is)
      return false;
   return true;
   }
bool TaskEntry::Save(const File& fff, const Array<TaskEntry>& aResult)
   {
   File pwFile = fff;
   pwFile.Remove();
   ostream& os = pwFile.OpenWrite(File::AT_BINARY);
   aResult.Write(os);
   return pwFile.Exists();
   }
bool TaskEntry::Manage(Array<TaskEntry>& array, StdLog& log)
   {
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(TaskEntry::ShouldRun(array[ss]) == true)
         {
         if(TaskEntry::Launch(array[ss], log) == true)
            {
            Reschedule(array[ss]);
            array[ss].bHasRun = true;
            array[ss].bHasFailed = false;
            }
         else
            {
            array[ss].bHasRun = false;
            array[ss].bHasFailed = true;
            }
         }
      }
   return true;
   }
