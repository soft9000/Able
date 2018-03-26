#include "Able1.hpp"

using namespace Able1;

ZStr Able1::LOG_PATTERN = "%m/%d/%Y %H:%M:%S - "; // Default, as used by logging - (ExeLog, etc)

void ExeLog::_init(void)
   {
   sStrftime = LOG_PATTERN;
   SetLogging();
   Home();
   }

ExeLog::ExeLog(bool bCalc) : bCalcName(bCalc)
   {
   _init();
   }

ExeLog::ExeLog(const File& file, bool bCalc) : bCalcName(bCalc)
   {
   _init(); // just in case we as more than that...
   pwFile = file;
   }

ExeLog::~ExeLog(void)
   {
   }

bool ExeLog::SetTimeFormat(const ZStr& rFmt)
   {
   sStrftime = rFmt;
   return true;
   }
   
bool ExeLog::_CalcName(File& file)
   {
   file = pwFile;
   return true;
   }

bool ExeLog::Home(void)
   {
   // Every executable has their own log - this is the default
   ProgramId pid;
   File file;
   pid.GetProgram(file);
   ZStr str = file.Name();
   str += ".log";
   pwFile.Name(str);
   return true;
   }

bool ExeLog::Home(Directory& dir)
   {
   // Rename the internal pwFile ONLY - NOT any external file -
   if(dir.Exists())
      dir.Home(pwFile);
   return false;
   }

void ExeLog::SetLogging(bool bLog)
   {
   bEnabled = bLog;
   }
   
bool ExeLog::GetLogging(void) const
   {
   return bEnabled;
   }

ZStr ExeLog::Format(const ZStr& cstr)
   {
   return (LogFormat(cstr, sStrftime));
   }

bool ExeLog::_append(const ZStr& sLine, bool bNewline)
   {
   if(bEnabled)
      {
      File file;
      if(_CalcName(file) == false)
         return false;
      ostream& os = file.OpenAppend();
      if(!os)
         return false;
      if(bNewline == false)
         {
         os << sLine;
         }
      else
         {
         Array<ZStr> array;
         if(sLine.Split('\n', array) == false)
            return false;
         for(size_t ss = 0L; ss < array.Nelem(); ss++)
            {
            array[ss].MkWhite();
            array[ss].Strip();
            os << LogFormat(array[ss], sStrftime);
            os << endl;
            }
         }
      file.Close();
      }
   return true;
   }

ZStr ExeLog::Log(const ZStr& cstr)
   {
   ZStr sLine = cstr;
   if(_append(sLine, true) == false)
      sLine = "";
   return sLine;
   }

bool ExeLog::Delete(void)
   {
   File file;
   _CalcName(file);
   return file.Remove();
   }

ZStr ExeLog::LogFormat(const ZStr& msg, const ZStr& sStrftime)
   {
   size_t   iMax = sStrftime.Length() * 5;
   char     *psz = new char[iMax];

   // Concoct the time prefix in the requested format
   time_t   pwTime;
   tm         *ptm;
   time(&pwTime);
   ptm = localtime(&pwTime);
   strftime(psz, iMax-1, sStrftime.c_str(), ptm);

   // Encode Result
   ZStr sResult;
   stringstream srm;
   srm << psz << msg;
   srm << ends;
   sResult = PRESTO(srm);

   return sResult;
   }
bool ExeLog::WriteLog(const ZStr& msg, const ZStr& sStrftime)
   {
   ExeLog dLog;
   dLog.SetTimeFormat(sStrftime);
   ZStr str = dLog.Log(msg);
   if(str.IsNull())
      return false;
   return true;
   }

ostream& ExeLog::Write(ostream& os)
   {
   pwFile.Write(os);
   return os;
   }

istream& ExeLog::Read(istream& is)
   {
   pwFile.Read(is);
   return is;
   }

