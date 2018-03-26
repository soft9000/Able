#include <Able1.hpp>
using namespace Able1;

#ifndef stdnet_url_hpx
#define stdnet_url_hpx

namespace stdnet
{
   // URL syntax is Protocol://<user>:<password>@<host>:<port>/<url-path>
   struct URL
   {
      ZStr sError;

      enum RfcProtocol
         {
         none,
         ftp,       // File Transfer Protocol
         http,      // Hypertext Transfer Protocol
         gopher,    // The Gopher Protocol
         mailto,    // Electronic mail address
         news,      // USENET news
         nntp,      // USENET news using NNTP access
         telnet,    // Reference to interactive sessions
         wais,      // Wide Area Information Servers
         file,      // Host-specific file names
         prospero   // Prospero Directory Service
         } protocol;// This is required

      ZStr sServer; // This is required
      ZStr sPath;   // Technically optional, but used frequently.

      // The Specific portion tailors the URL to an access instance -
      struct Specific
         {
         int       iPort;
         ZStr sUserId;
         ZStr sPassword;  // RFC1738: "... there is no way to specify a password without specifying a user name."


         Specific(void) : iPort(0) 
            {
            }

         bool IsNull(void);
         } opt;

      URL(void);

      int  operator==(const URL& url) const;
      int  operator!=(const URL& url) const;
      int  operator> (const URL& url) const;
      int  operator< (const URL& url) const;

      bool IsNull(void) const;
      void Reset(void);

      // RFC1738: Special User, Password, and Path characters must be encoded (sic)
      bool Encode(void) {return false;}   // Not supported yet
      bool Decode(void) {return false;}   // Not supported yet

      static bool Encode(ZStr& sEncoded, const URL& upResult);  // Factorize
      static bool Decode(const ZStr& sEncoded, URL& upResult);  // Serialize
      static bool Test(URL& url, ostream& cout);                     // Resize ;-)
   };

}

#endif
