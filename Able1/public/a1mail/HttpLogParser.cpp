#include <a1mail/HttpLogParser.Hpp>

ZStr HttpLogEntry::FileName(void) const
   {
   ZStr str = sRequest;
   size_t whence = str.Find(' ');
   str.RemovePos(0, whence+1); 
   whence = str.Rfind(' ');      // well, why not?
   str.Remove(whence);
   return str;
   }
bool HttpLogEntry::QueryDate(StdDateTime& sdt) const
   {
   // strftime 
   // strptime(sDateTime.c_str(), "%d/%b/%Y:%T", &rtm);
   char buf[100];
   int iDat    = 0;
   int iYear   = 0;
   int iHour   = 0;
   int iMun    = 0;
   int iSec    = 0;

   ZStr str = sDateTime.c_str();
   str.Replace('[', ' ');
   str.Replace(']', ' ');
   str.Replace(':', ' ');
   str.Replace('/', ' ');
   int iFields = ::sscanf(str.c_str(), " %2d %s %4d %d %d %d ", &iDat, buf, &iYear, &iHour, &iMun, &iSec);
   if(iFields != 6)
      return false;
   ZStr sMonth = buf;
   sMonth.ToLower();
   int iMonth = 0;
   if(sMonth.Find("jan") == 0L)
      {
      iMonth = 1;
      goto trer_NEXT;
      }
   if(sMonth.Find("feb") == 0L)
      {
      iMonth = 2;
      goto trer_NEXT;
      }
   if(sMonth.Find("mar") == 0L)
      {
      iMonth = 3;
      goto trer_NEXT;
      }
   if(sMonth.Find("apr") == 0L)
      {
      iMonth = 4;
      goto trer_NEXT;
      }
   if(sMonth.Find("may") == 0L)
      {
      iMonth = 5;
      goto trer_NEXT;
      }
   if(sMonth.Find("jun") == 0L)
      {
      iMonth = 6;
      goto trer_NEXT;
      }
   if(sMonth.Find("jul") == 0L)
      {
      iMonth = 7;
      goto trer_NEXT;
      }
   if(sMonth.Find("aug") == 0L)
      {
      iMonth = 8;
      goto trer_NEXT;
      }
   if(sMonth.Find("sep") == 0L)
      {
      iMonth = 9;
      goto trer_NEXT;
      }
   if(sMonth.Find("oct") == 0L)
      {
      iMonth = 10;
      goto trer_NEXT;
      }
   if(sMonth.Find("nov") == 0L)
      {
      iMonth = 11;
      goto trer_NEXT;
      }
   if(sMonth.Find("dec") == 0L)
      {
      iMonth = 12;
      goto trer_NEXT;
      }
   if(!iMonth)
      return false;

   trer_NEXT:

   ZStr sError;
   sdt.EncodeDate(iYear, iMonth, iDat, sError);
   sdt.EncodeTime(iHour, iMun, iSec);
   return !(sError.IsNull());
   }
bool HttpLogEntry::Parameters(ZStr& str, char ch) const
   {
   size_t whence = sRequest.Rfind(ch);
   if(whence == NPOS)
      return false;
   str = sRequest.Substr(whence, NPOS);
   return true;
   }
// Attempts to remove odd characters and other common problems. 
// false if unexpected data / format is encountered.
bool HttpLogEntry::Normalize(void)
   {
   sRequest.MkWhite();
   sRequest.Strip();
   while(sRequest.Replace("  ", " "))
      ;
   return true;
   }
int HttpLogEntry::operator==(const HttpLogEntry& ref) const
   {
   return (sRequest == ref.sRequest);
   }
int HttpLogEntry::operator!=(const HttpLogEntry& ref) const
   {
   return (sRequest != ref.sRequest);
   }
int HttpLogEntry::operator>(const HttpLogEntry& ref) const
   {
   return (sRequest > ref.sRequest);
   }
istream& HttpLogEntry::log_import(istream& is)
   {
   ZStr str;
   str.Readline(is);
   if(!is)
      return is;
   
   stringstream srm;
   srm << str << ends;
   srm.seekg(0, ios::beg);

   srm >> sRemoteHost;
   srm >> sRemoteLogname;
   srm >> sRemoveUser;
   sDateTime.Readline(srm, '"');
   sDateTime.RemovePattern("\"");
   sRequest.Readline(srm, '\"');
   sRequest.RemovePattern("\"");
   srm >> sResultCode;
   srm >> sBytesSent;
   return is;
   }
ostream& HttpLogEntry::log_export(ostream& os)
   {
   os << sRemoteHost       << ' ';
   os << sRemoteLogname    << ' ';
   os << sRemoveUser       << ' ';
   os << sDateTime         << " \"";
   os << sRequest          << "\" ";
   os << sResultCode       << ' ';
   os << sBytesSent        << endl;
   return os;
   }

istream& HttpLogEntry::Read(istream& is)
   {
   Array<StreamZStr> ary;
   ary.Read(is);
   sRemoteHost       = ary[0];
   sRemoteLogname    = ary[1];
   sRemoveUser       = ary[2];
   sDateTime         = ary[3];
   sRequest          = ary[4];
   sResultCode       = ary[5];
   sBytesSent        = ary[6];
   return is;
   }
ostream& HttpLogEntry::Write(ostream& os) 
   {
   Array<StreamZStr> ary;
   ary.AddZombies(7);
   ary[ary.Nelem()] = sRemoteHost;
   ary[ary.Nelem()] = sRemoteLogname;
   ary[ary.Nelem()] = sRemoveUser;
   ary[ary.Nelem()] = sDateTime;
   ary[ary.Nelem()] = sRequest;
   ary[ary.Nelem()] = sResultCode;
   ary[ary.Nelem()] = sBytesSent;
   return ary.Write(os);
   }

istream& HttpLog::log_import(istream& is)
   {
   HttpLogEntry line;
   while(is)
      {
      line.log_import(is);
      if(is)
         aLines[aLines.Nelem()] = line;
      }
   return is;
   }
ostream& HttpLog::log_export(ostream& os)
   {
   HttpLogEntry line;
   for(size_t ss = 0L; ss < aLines.Nelem(); ss++)
      line.log_export(os);
   return os;
   }

bool HttpLog::Normalize(void)
   {
   if(bNormalized == true)
      return bNormalized;
   bool br = true;
   for(size_t ss = 0L; ss < aLines.Nelem(); ss++)
      {
      if(aLines[ss].Normalize() == false)
         br = false;
      }
   bNormalized = br;
   return br;
   }
istream& HttpLog::Read(istream& is)
   {
   aLines.Read(is);
   return is;
   }
ostream& HttpLog::Write(ostream& os) 
   {
   aLines.Write(os);
   return os;
   }

bool HttpLogParser::Import(HttpLog& hLog, File& file)
   {
   sError = "";
   if(file.Exists() == false)
      {
      sError = "File not found.";
      return false;
      }

   hLog.aLines.AddZombies(NumLines(file));      // this is first open attempt

   istream& is = file.OpenRead();
   if(!is)
      {
      sError = "File is empty";
      return false;
      }

   hLog.log_import(is);
   file.Close();
   return true;
   }
bool HttpLogParser::Export( HttpLog& hLog, File& file)
   {
   bool br = true;
   sError = "";
   ostream& os = file.OpenWrite();
   if(!os)
      {
      sError = "File creation error";
      br = false;
      }
   hLog.log_export(os);
   if(!os)
      {
      sError = "File exportation error";
      br = false;
      }
   file.Close();
   return br;
   }
