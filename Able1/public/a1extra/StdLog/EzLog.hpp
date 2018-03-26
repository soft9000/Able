
//! EzLog demonstrates how to easily create a Able1 tool. this tool allows
//! simple messages to be time-stamped and added / listed to either the `pwd`, or
//! to an .ezlog file in the parent's tree or in the default program (".EXE") folder.
//!
//! This 'noj is very useful when you are generating comments on an entire TREE of 
//! files, folder and / or directories.
//! 
//! NOTE THAT LOG FILE USAGE IS OPTOMISTIC - NO LOG FILE CONTENTION LOGIC IS USED AT THIS TIME!
//!
//! See the ReadMe.txt, or EzLog::Usage() for more information.
//!
//
// 2008/10/17 Updated signature + updated to work wiht Able1. Still needs to be re-written, R. Nagy
//

#ifndef EzLog_Hpp
#define EzLog_Hpp

#include <a1extra/StdLog.hpp>

class EzLog
{
protected:
   File pwFile;
   
public:

   EzLog(void);

   void SetDefault(void);                    // Set the log to ".ezlog" in the main program folder
   bool SetDefaultLog(Directory& dir);       // Sets the log to a file called ".ezlog" in the folder
   bool SetDerivedLog(File& file);           // Derive a fle name by appending ".ezlog" to the file+path
   void LocateDefaultLog(void);              // Searches up folder parentage looking for a log file, else uses the default -

   bool ShowLog(ostream& os);                // Word-wrap and display the log file

   bool WriteLog(const ZStr& message);  // Obvio -
   bool WriteLog(const ZStr& message, ZStr& sResult);// ibid -
   
   static bool ShowLog(const File& file, ostream& os);         // First try the HTML version, else the testual -
   static bool ShowHtmlLog(const File& file);                  // Display the log file in HTML format - TRUE if LAUNCHED
   static bool ShowTextLog(const File& file, ostream& os);     // Display the log file in word-wrapoed text format -
   static const char *LogDefaultName(ZStr& str);          // Get the default name
   
   static bool HasDefaultLog(Directory& dir);

   static void Usage(ostream& os);                             // Command-line usage
   static bool Main(Array<ZStr>& array, ostream& os);     // Command-line operations
   static bool Main(int argc, char *argv[], ostream& os);      // Command-line 'stuffing
};

#endif
