#include <a1net.hpp>
#include <sstream>
using namespace std;

using namespace stdnet;


Http::HttpResponse::HttpResponse(void) : iCode(0)
   {
   }

bool Http::HttpResponse::Parse(const ZStr& sSocketString)
   {
   ZStr sBuf = sSocketString;
   sBuf.Replace("\r\r", "\r");   // Adjust if a "\r\n" was saved as text on DOS -

   iCode = 0;
   aHeaders.Empty();
   sResponse = "";
   size_t szHeader = sBuf.Find("\r\n\r\n");  // 4
   if(szHeader == npos)
      return false;
   sBuf[szHeader] = NULL;
   sBuf.Replace("\r\n", "\n");
   if(sBuf.Split('\n', aHeaders) == false)
      return false;

   szHeader += 4;
   sResponse = sSocketString.Substr(szHeader, NPOS);

   sBuf = aHeaders[0];
   Array<ZStr> array;
   if(sBuf.Split(' ', array) == false)
      return false;

   iCode = array[1].AsInt();
   if(!iCode)
      return false;

   return true;
   }

bool Http::Connect(Socket& soc, const Url& url)
   {
   if(url.Type() != url_http)
      return false;

   if(soc.Connect(url.Site(), 80) == false)
      return false;

   return true;
   }

size_t Http::Size(const Url& url, size_t szDefault)
   {
   Socket soc;

   if(Connect(soc, url) == false)
      return npos;

   stringstream srm;
   srm << "HEAD " << url.Page() << " HTTP/1.0\n\n";

   ZStr sRequest = srm.str().c_str();
   ZStr sResult;

   bool br = soc.Transact(sRequest, sResult);
   soc.Disconnect();
   if(br == false)
     return npos;

   ZStr sPattern = "Content-Length:";
   size_t pos = sResult.Find(sPattern);
   if(pos == npos)
      return szDefault;

   sResult.RemovePos(0, pos + sPattern.Length());
   pos = sResult.Find('\n');
   if(pos == npos)
      return npos;

   sResult.Remove(pos);
   sResult.Strip();

   return (size_t)sResult.AsLong();
   }

bool Http::Download(const Url& url, const File& fff, size_t szDefault)
   {
/*
   size_t pos = Size(url, szDefault);
   if(pos == npos)
      return false;
*/
   stringstream srm;
   srm << "GET " << url.Page() << " HTTP/1.0\n\n";
   ZStr sRequest = srm.str().c_str();

   Socket soc;
   if(Connect(soc, url) == false)
      return npos;

   if(soc.Send(sRequest) == false)
      return false;

   ZStr sResult, sBuffer;
   while(soc.Receive(sBuffer) == true)
      {
      if(sBuffer.IsNull())
         break;
      if(sResult.IsNull())
         {
         HttpResponse resp;
         if(resp.Parse(sBuffer) == true)
            {
            // Only want to examine the headers -
            if(resp.iCode != 200)
               return false;
            // Do not want the headers ...
            sBuffer = resp.sResponse;
            }
         }
      sResult += sBuffer;
      }

   if(sResult.IsNull())
      return false;

   File file = fff;
   ostream& os = file.OpenWrite();
   os << sResult;
   return true;
   }

