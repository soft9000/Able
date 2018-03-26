// 10/10/2003: Classes created, R. Nagy
//
#ifndef _Http_Log_Parser
#define _Http_Log_Parser

#include <Able1.hpp>

/*
The Common Logfile Format

    remotehost rfc931 authuser [date] "request" status bytes

   remotehost
      Remote hostname (DNS hostname or IP address if not available.) 
   rfc931
      The remote logname of the user (if available). 
   authuser
      The authenticated username (if available). 
   [date]
      Date and time of the request, delimited by brackets. Always present.
   "request"
      The exact client request line, delimited by quotes. Use Normalize() to standardize it.
   status
      HTTP status code result.
   bytes
      Resulting content-length transferred. 
*/

using namespace Able1;

class HttpLogEntry
{
public:
   ZStr sRemoteHost;
   ZStr sRemoteLogname;
   ZStr sRemoveUser;
   ZStr sDateTime;
   ZStr sRequest;
   ZStr sResultCode;
   ZStr sBytesSent;

   // Convert to our standard date and time format
   bool        QueryDate(StdDateTime&) const;
   // The web page or file name requested
   ZStr   FileName(void)          const;
   // Attempts to remove odd characters and other common problems. False if unexpected data / format is encountered.
   bool        Normalize(void);
   // Returns the parameters up to and including the parameter char        
   bool        Parameters(ZStr& str, char ch = '?') const;
   // The RFC (hundreds based) result code
   int         ResultCode(void)  const      {return sResultCode.AsInt();}

   int operator==(const HttpLogEntry& ref) const;
   int operator!=(const HttpLogEntry& ref) const;
   int operator>(const HttpLogEntry& ref)  const;

   istream& log_import(istream& is);       // HTTP (common) format
   ostream& log_export(ostream& os);       // HTTP (common) format

   istream& Read(istream& is);         // proprietary format
   ostream& Write(ostream& os) ;       // proprietary format
};

class HttpLog
{
public:
   Array<HttpLogEntry> aLines;

   HttpLog(void) : bNormalized(false)  {}

   bool bNormalized;                   // Normalization occurs only when required
   bool Normalize(void);               // Asserts bNormalized only when 100% pass.

   istream& log_import(istream& is);       // HTTP (common) format
   ostream& log_export(ostream& os);       // HTTP (common) format

   istream& Read(istream& is);         // proprietary format
   ostream& Write(ostream& os);        // proprietary format
};

class HttpLogParser
{
public:
   ZStr sError;

   bool Import(HttpLog&, File& fileIn);
   bool Export(HttpLog&, File& fileOut);
};


inline
long unsigned NumLines(File& file)
   {
   ZStr str;
   long unsigned count = 0L;
   istream& is = file.OpenRead();
   while(is)
      {
      str.Readline(is);
      count++;
      }
   file.Close();
   return count;
   }

#endif
