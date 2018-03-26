//---------------------------------------------------------------------------

#ifndef uTaskEntryH
#define uTaskEntryH
//---------------------------------------------------------------------------

#include <extra/stdlog.hpp>

struct TaskEntry
{
   bool      bOnceOnly;    // Should only run a single time
   bool      bHasRun;      // Has run okay (system() call worked)
   bool      bHasFailed;   // Did not run okay (system() call failed)

   File      pwFile;
   StdString sTaskName;
   StdString sComment;
   OidTag    oidParams;
   StdDateTime sdtNext;

   TaskEntry(void);

   bool IsNull(void) const;
   bool IsOid(void)  const  {return oidParams.HasBody();}

   void EncodeParams(const Array<StdString>& array);
   void DecodeParams(Array<StdString>& aParams) const;

   int operator==(const TaskEntry& ref) const;

   ostream& write(ostream& os);
   istream& read(istream& is);

   static bool ShouldRun(const TaskEntry& entry);
   static bool Launch(const TaskEntry& entry, StdLog& log);
   static bool Reschedule(TaskEntry& entry);
   static bool Manage(Array<TaskEntry>& array, StdLog& log);

   static size_t FindNext(Array<TaskEntry>& array);
   static bool Load(const File& file, Array<TaskEntry>& aResult);
   static bool Save(const File& file, const Array<TaskEntry>& aResult);
};

#endif
