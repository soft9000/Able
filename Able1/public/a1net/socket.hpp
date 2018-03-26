// Class nojnet::Socket: Tired of all of the #ifdef garbage? 
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
// 09/15/2006: Refactored SocketSelect into Socket,    R. Nagy 
//
#ifndef zSocket78_Hpp
#define zSocket78_Hpp

// NOTE: Borland uses the older version of windows sockets. Be sure to globally define
// _WINSOCKAPI_ to turn it off!

#include <Able1.hpp>
using namespace Able1;

#include <a1net/URL.hpp>
#include <a1net/CommBase.hpp>
#include <winsock2.h>

// msdn.microsoft.com recv() doc SAYS that they define it in winsock2.h - But they do not -
#ifndef MSG_WAITALL
//#define MSG_WAITALL 0x8 - // Modern (2005) = Constant from MS SDK - STILL DOES NOT WORK!
#define MSG_WAITALL 0       // Classic - WINSOCK, WINSOCK2, and now WS2_36 !
#endif

// A micro-smurff extension (winsoc2) -
#define SOC_BUFFER_SZ  SO_MAX_MSG_SIZE

namespace stdnet
{

   class Socket : public CommBase
      {
      private:
         long     timeout_ai;    // This value is adjusted upward to accomidate service slowdowns, etc..
         int      connected;     // Please don't make the user worry about an "IsConnected()", okay?
         SOCKET   port;          // -the purpose of this class is to hide the gory details from the user,
         fd_set   fdset;         // no? -Enough to tell them that we're connected, or no, from the API result.

      public:
         ExeLog    pwLog;

         Socket(void);
         virtual ~Socket(void);

         bool IsConnected(void);

         bool Connect(const ZStr& sHostName, u_short service_port = IPPORT_ECHO, int af_which = AF_INET);
         void Disconnect(void);

         bool Send(const ZStr& str);
         bool Receive(ZStr&);
         bool Transact(const ZStr& in, ZStr& out);

         const char *GetError(ZStr& sResult, int iCode) const;
         int         GetLastError(void) const;

         // This is useful for management by external routines;
         operator SOCKET(void)      {return port;}
      };
}

#endif
