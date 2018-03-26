#include <a1extra/StdLog.hpp>
#include <cstdio>         // unlink()
#include <ctime>


void StdLog::_init(void)
   {
   sStrftime = LFU_PATTERN;
   Enable();
   Home();
   }

StdLog::StdLog(bool bCalc) : bCalcName(bCalc)
   {
   _init();
   }

StdLog::StdLog(const char *str) : bCalcName(true)
   {
   _init();
   pwFile.Name(str);
   }

StdLog::StdLog(const ZStr& str, bool bCalc) : bCalcName(bCalc)
   {
   _init();
   pwFile.Name(str);
   }

StdLog::StdLog(const File& file, bool bCalc) : bCalcName(bCalc)
   {
   _init(); // just in case we as more than that...
   Name(file);
   }

StdLog::~StdLog(void)
   {
   }

bool StdLog::SetTimeFormat(const ZStr& rFmt)
   {
   sStrftime = rFmt;
   return true;
   }


ZStr    StdLog::Name(void) const
   {
   return pwFile.Name();
   }

bool StdLog::Name(const ZStr& str)
   {
   File file;
   file.Name(str);
   return Name(file);
   }

bool StdLog::Name(const File& file)
   {
   pwFile = file;
   return true;
   }

void StdLog::SetCalcName(bool bCalc)
   {
   bCalcName = bCalc;
   }

bool StdLog::QueryCalcName(void)
   {
   return bCalcName;
   }
   
bool StdLog::CalcName(File& file)
   {
   return _CalcName(file);
   }
   
bool StdLog::_CalcName(File& file)
   {
   if(bCalcName)
      {
      ZStr str, sName, sType, sDate;
         {
      stringstream srm;
      StdDateTime sdt;
      srm << "_" << sdt.Year() << "_";
      int day = sdt.Month();
      if(day < 10)
         srm << '0'; // make it sortable -
      srm << day << "_" << sdt.DayOfMonth();
      sDate = PRESTO(srm);
         }

      pwFile.QueryNode(str);
      if(str.Find(sDate) == npos)
         {
         sName = str = pwFile.Name();
         sType = ".log";
         str.ToLower();
         if(str.EndsWith(sType) == true)
            sName.Remove(sName.Rfind(sType));

         stringstream srm;
         srm << sName << sDate << sType;
         return file.Name(PRESTO(srm));
         }
      }
   file = pwFile;
   return true;
   }

bool StdLog::Edit(void)
   {
   File file;
   if(CalcName(file))
      return file.Launch();
   return false;
   }

bool StdLog::EditHome(void)
   {
   File file;
   if(CalcName(file))
      {
      Directory dir;
      file.Query(dir);
      if(dir.Exists())
         return dir.Launch();
      }
   return false;
   }

bool StdLog::Home(void)
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

bool StdLog::Home(Directory& dir)
   {
   // Rename the internal pwFile ONLY - NOT any external file -
   if(dir.Exists())
      {
      ZStr sBuf;
      File file;
      Query(file);
      file.QueryNode(sBuf);
      ZStr str = ZStr(dir.Name()) + ZStr(PathChar()) + sBuf;
      return pwFile.Name(str);
      }
   return false;
   }

void StdLog::Disable(void)
   {
   bEnabled = false;
   }

void StdLog::Enable(void)
   {
   bEnabled = true;
   }
   
bool StdLog::IsLogging(void) const
   {
   return bEnabled;
   }

bool StdLog::Query(File& file) const
   {
   file = pwFile;
   return true;
   }

ZStr StdLog::Format(const ZStr& cstr)
   {
   return (LogFormat(cstr, sStrftime));
   }

bool StdLog::_append(const ZStr& sLine, bool bNewline)
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

ZStr StdLog::Print(const ZStr& cstr)
   {
   ZStr sLine = cstr;
   if(_append(sLine, false) == false)
      sLine = "";
   return sLine;
   }

ZStr StdLog::PrintLine(const ZStr& cstr)
   {
   ZStr sLine = cstr;
   if(_append(sLine, true) == false)
      sLine = "";
   return sLine;
   }

bool StdLog::Delete(void)
   {
   File file;
   _CalcName(file);
   return file.Remove();
   }

ZStr StdLog::LogFormat(const ZStr& msg, const ZStr& sStrftime)
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
bool StdLog::Log(const ZStr& msg, const ZStr& sStrftime)
   {
   StdLog dLog;
   dLog.SetTimeFormat(sStrftime);
   ZStr str = dLog.PrintLine(msg);
   if(str.IsNull())
      return false;
   return true;
   }

ostream& StdLog::Write(ostream& os)
   {
   pwFile.Write(os);
   return os;
   }

istream& StdLog::Read(istream& is)
   {
   pwFile.Read(is);
   return is;
   }

