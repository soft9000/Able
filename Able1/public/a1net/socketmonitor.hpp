// 09/15/2006: Refactored StdSocket::MonitorConnection() into 
//             nojnet::SocketMonitor class .Still needs to be tested for 
//             possible regression, R. Nagy
//
#ifndef SocketMonitor78_hpx
#define SocketMonitor78_hpx

#include <a1net.hpp>

namespace stdnet 
{

class SocketMonitor
{
protected:
   stdnet::Socket pwSocket;

   void LOG(ostream& cout, const char *pszBuf, int capture);
   void LOG_LINE(const char *pszBuf);
   void LOG_LINE(ostream& cout, const char *pszBuf, int capture);
   int  GETLINE(istream& cin, ostream& cout, char *pszBuf, size_t szBuf, int& capture, int& converse);

public:

   // This monitors an existing connection -
   void MonitorConnection(Socket& soc, ostream& cout, istream& cin);

};


}

#endif
