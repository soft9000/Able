// Class StdLogger: Class to allow for the creation of a fully-qualified log-file. Need to keep the log
// files from floatin' round! Also needed to get access to the Format() for GUI / non-stream based logging.
//
// 01/17/1998: StdLog class created, R. Nagy.
// 01/21/1998: Broke-out StdLogger to return formatted string (Better for GUI, etc), R. Nagy
//             Added the Print/PrintLine(os, psz, 1) idea form the StdSocket LOG capability.
// 09/19/2003: Ported StdLogger over to Able1/extra/StdLog.hpp, R. Nagy
//             Added a few functions & changed poor constructor init logic.
// 10/15/2003: Lightly modernized the interface (i.e. use File for assignements of same), R. Nagy
//             New! Every executable has their own log (default)
// 06/15/2003: Updated for legacy usage, R. Nagy
// 12/04/2004: Added operator=, operator+=, Disable(), Enable(), _append() and
//             changed all const char * return values to ZStr, R. Nagy
// 08/04/2005: Added LogFormat, R. Nagy
// 09/15/2006: Added IsLogging(void) const, R. Nagy
// 01/11/2006: Moved LogFormat() from namespace (inline) to class smf. Updated external dependancies, R. Nagy
// 01/26/2007: Day logging RT file name assertion added. Is now the default, R. Nagy
//             Added ability to SetTimeFormat(), as well as better enforcement of a universal dt format.
//             Also added newline detection / Splitting.
// ============
// 12/29/2007: * RESOLVED *
//             Ready for inclusionary reWrite - Const usage *must* be part of the final signature!
// ============
//
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
// 06/29/2008: THIS CLASS IS NOW OBSOLETE - USE EXELOG, INSTEAD!
//
#ifndef zStdLogger_Hpp
#define zStdLogger_Hpp

#include <Able1.hpp>

using namespace Able1;

const ZStr LFU_PATTERN = "%m/%d/%Y %H:%M:%S - ";

// The StdLog class is about formatting, homing, and managing the writing
// of a log file.
//
// The default convention places a log file next to the name of the exe,
// with the date appended with a ".log" suffix.
//
// Writing to same can be enabled and disabled.
//
class StdLog
   {
   private:
      File         pwFile;
      bool         bEnabled;
      ZStr    sStrftime;
      virtual void _init(void);

   protected:
      bool         bCalcName;
      bool         _CalcName(File& file);
      virtual bool _append(const ZStr& sLine, bool bNewline);

   public:
      //! Constructors place log in Home(). Logging is ENABLED by default.
      //! param bCalcDayFileName allows you to override the automatic date / time suffix usage
      StdLog(const char *str);
      StdLog(bool bCalcDayFileName = true);
      StdLog(const File&, bool bCalcDayFileName = true);
      StdLog(const ZStr& str, bool bCalcDayFileName = true);

      virtual ~StdLog(void);

      bool         Home(void);     // Default name. Default location.
      bool         Home(Directory& dir);  // New location -
      bool         Edit(void);
      bool         EditHome(void);

      bool         Enabled(void) {return bEnabled;}
      void         Enable(void);   // The default: Enable printing to the log file - debug, etc...
      void         Disable(void);  // The option:  Disable printing to the log file - format only
      bool         IsLogging(void) const;

      bool         Delete(void);   // Remove the ACTUAL log file

      // Manage the BASE NAME to use for the file log. (CalcName determines
      // the ultimate file name used.)
      ZStr    Name(void) const;
      bool         Name(const ZStr& str);
      bool         Name(const File& file);
      // bool      Assign(const File& file); REDUNDANT - Use Name() -
      bool         Query(File& file) const;

      // No matter what name is assigned to pwFile, the actual name will be
      // calculated each time a log is written to. Use CalcName() to override
      // this default: t = calc on, f = calc off
      void         SetCalcName(bool bCalcDayFileName);
      bool         QueryCalcName(void);
      bool         CalcName(File& file);

      bool         SetTimeFormat(const ZStr& rFmt = LFU_PATTERN);

      virtual ZStr Format(const ZStr& cstr);
      virtual ZStr Print(const ZStr& cstr);
      virtual ZStr PrintLine(const ZStr& cstr);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);

      // "SET THE LOG FILE CONTENT TO"
      StdLog operator=(const ZStr& str)
         {
         Delete();
         PrintLine(str);
         return *this;
         }
      // "ADD TO THE LINE CONTENT"
      StdLog operator+(const ZStr& str)
         {
         Print(str);
         return *this;
         }
      // "ADD TO THE LOG FILE"
      StdLog operator+=(const ZStr& str)
         {
         PrintLine(str);
         return *this;
         }

      // Show us the format applied to a string
      static ZStr LogFormat(const ZStr& msg, const ZStr& sStrftime = LFU_PATTERN);

      // A little expensive, but very much apreciated - Default file logging - Required by most -
      static bool Log(const ZStr& msg, const ZStr& sStrftime = LFU_PATTERN);

      };



#endif
