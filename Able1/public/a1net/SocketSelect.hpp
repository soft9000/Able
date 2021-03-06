// Class nojnet::SocketSelect: Tired of all of the #ifdef garbage? 
// Then here is a wrapper that you can use no matter whose "standard" sockets 
// you are running!
//
// While the model has been designed for portability, what I have to share at 
// the moment remains a decidely WIN32 implementation - Apologies - But there 
// are only so many free hours in the day - (regression testing is always the 
// issue ...!)
//
// *** but ***
// Try libwww - Not too sexy - It has a huge learning curve - but it works
// okay.
//
// *** note ***
// Windows developers will need to include a reference to ws2_32.lib in 
// their project (replaces the old wsock32.lib) to make the link work -
//
// 12/22/1997: Class created, R. A. Nagy (WinSock2 Version)
// 12/24/1997: Added select(TIMEOUT) to IO to keep from blocking-forever, R. Nagy.
//             Added MonitorConnection(), R. Nagy.
// 01/21/1998: Added the Trace facility, R. Nagy.
// 01/31/1998: Implemented the timeout_ai, R. Nagy.
// 12/03/1998: Added timeout value to ::Transact(),   R. Nagy.
// 09/23/2003: Ported to Able1, R. Nagy
// 09/24/2003: Changed SOC_TIMEOUT from 100L to 15L,  R. Nagy
// 09/15/2006: Coined the nojnet namespace            R. Nagy
//             Refactored StdSocket into SocketSelect R. Nagy 
//
#ifndef zSocketSelect_Hpp
#define zSocketSelect_Hpp

// NOTE: Borland uses the older version of windows sockets. Be sure to globally define
// _WINSOCKAPI_ to turn it off!

#include <a1net.hpp>
#ifdef WIN32
#include <winsock2.h>
#endif

namespace stdnet
{

   class SocketSelect
      {
      private:
         long     timeout_ai;    // This value is adjusted upward to accomidate service slowdowns, etc..
         int      connected;     // Please don't make the user worry about an "IsConnected()", okay?
         SOCKET   port;          // -the purpose of this class is to hide the gory details from the user,
         fd_set   fdset;         // no? -Enough to tell them that we're connected, or no, from the API result.

      protected:
         fd_set *OneFd(void);

      public:
         ZStr sLastError;
         ExeLog    pwLog;

         SocketSelect(void);
         ~SocketSelect(void);

         bool IsConnected(void);

         // Notice that we default to INTERNET connections (AF_INET);
         bool Connect(const ZStr& sHostName, u_short service_port = IPPORT_ECHO, int af_which = AF_INET);
         void Disconnect(void);

         bool Send(const ZStr& std, long timeout = SOC_TIMEOUT);
         bool Receive(ZStr&, size_t sz_largest_expected_from_service = SOC_BUFFER_SZ, long timeout = SOC_TIMEOUT);

         // Response will only contain what is available on-the-socket (i.e: might not be the ENTIRE host response (a polling / latency thing));
         bool Transact(const ZStr& in, ZStr& out, long timeout = SOC_TIMEOUT);

         // Response will contain `delim`, and perhaps a little more (depending on host response);
         bool TransactResponseContaining(const ZStr& stdIn, ZStr& stdOut, const char delim = '\n', long l_timeout = SOC_TIMEOUT);

         const char *GetLastError(void);
         int         GetLastErrorCode(void);

         // This is useful for multiple operations on many sockets (i.e. select() that uses a passle of SocketSelects);
         operator SOCKET(void)      {return port;}
      };
}

#endif
