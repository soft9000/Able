// Class StdLogger: Class to allow for the creation of a fully-qualified log-file. Need to keep the log
// files from floatin' round! Also needed to get access to the Format() for GUI / non-stream based logging.
//
// 01/17/1998: StdLog class created, R. Nagy.
// 01/21/1998: Broke-out StdLogger to return formatted string (Better for GUI, etc), R. Nagy
//             Added the Print/PrintLine(os, psz, 1) idea form the StdSocket LOG capability.
// 09/19/2003: Ported StdLogger over to Able1/extra/StdLog.hpp, R. Nagy
//             Added a few functions & changed poor constructor init logic.
//
#ifndef zStdLogger_Hpp
#define zStdLogger_Hpp

#include <Able1.hpp>

using namespace Able1;

const char *DEFAULT_LOG_NAME = "StdNojLog2.Log";

class StdLog
   {
   protected:
      ZStr   sLogFileName;
      ZStr   sLine;

   public:
      StdLog(void)  : sLogFileName(DEFAULT_LOG_NAME)              {}
      StdLog(const ZStr& rLogFile) : sLogFileName(rLogFile)  {}
      virtual ~StdLog(void)                                       {}

      virtual bool Name(const ZStr& cstrName);
      const char * Name(void)   const     {return sLogFileName.c_str();}

      bool Assign(const File& file);
      bool Query(File& file);

      bool Delete(void);

      const char *Format(const ZStr& cstr);

      const char *Print(const ZStr& cstr);
      const char *PrintLine(const ZStr& cstr);

      virtual const char *Print(ostream& os, const ZStr& psz, int LogCapture = 1);
      virtual const char *PrintLine(ostream& os, const ZStr& psz, int LogCapture = 1);

      ostream& Write(ostream& os)
         {
         sLogFileName.WriteStream(os);
         return os;
         }
      istream& Read(istream& is)
         {
         sLogFileName.ReadStream(is);
         return is;
         }
      };


#endif
