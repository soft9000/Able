// Class StdLogger: Class to allow for the creation of a fully-qualified log-file. Need to keep the log
// files from floatin' round! Also needed to get access to the Format() for GUI / non-stream based logging.
//
// 06/29/2008: Feature set extracted from StdLog.
//
#ifndef aExeLogger_Hpp
#define aExeLogger_Hpp


namespace Able1
{

/** The ExeLog class is about formatting, homing, and mnaging the writing
  * of a log file.
  * <br>
  * The default convention places a log file next to the name of the exe,
  * with the date appended with a ".log" suffix.
  * <br>
  * Writing to same can be enabled and disabled.
  */
class ExeLog
   {
   private:
      bool         bEnabled;
      ZStr         sStrftime;
      virtual void _init(void);

   protected:
      File         pwFile;
      bool         bCalcName;
      bool         Home(void);
      bool         Home(Directory& dir);

      virtual bool _CalcName(File& file);
      virtual bool _append(const ZStr& sLine, bool bNewline);

   public:
      //! Constructors place log in Home(). Logging is ENABLED by default.
      //! param bCalcDayFileName allows you to override the automatic date / time suffix usage
      ExeLog(bool bCalcDayFileName = true);
      ExeLog(const File&, bool bCalcDayFileName = true);

      virtual ~ExeLog(void);

      void         SetLogging(bool bEnabled = true);
      bool         GetLogging(void) const;

      bool         Set(const File& file);
      bool         Get(File& file) const;
      bool         Delete(void);

      bool         SetTimeFormat(const ZStr& rFmt = LOG_PATTERN);

      bool         Enabled(void)                {return bEnabled;}
      void         Enable(bool bWrite = true)   {bEnabled = bWrite;}
      void         Disable(void)                {bEnabled = false;}

      /** Often it is handy to get the strings, only - Good for GUI (etc.) */
      virtual ZStr Format(const ZStr& cstr);
      virtual ZStr Log(const ZStr& cstr);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);

      /** Show us the format applied to a string */
      static ZStr LogFormat(const ZStr& msg, const ZStr& sStrftime = LOG_PATTERN);

      /** A little expensive, but very much apreciated - Default file logging - Required by most - */
      static bool WriteLog(const ZStr& msg, const ZStr& sStrftime = LOG_PATTERN);
      };
}

#endif
