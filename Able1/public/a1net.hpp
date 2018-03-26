//
// The stdnet namespace contains modernized versions of models designed to
// operate on the Internet. Here you will find Sockets, Protocols, and patterns
// designed for portable operation across unix, linux, windows (WIN32), DOS, 
// and Mac OSX.
//
// 09/15/2006: Namespace created, R. Nagy
// 10/08/2006: Added a more comprehensive URL definition, R. Nagy
//
#ifndef stdnet_hpp
#define stdnet_hpp


#include <Able1.hpp>
using namespace Able1;

namespace stdnet
{
// Seconds for timeout -
const long     SOC_TIMEOUT        = 15L;    
}

#include <a1net/URL.hpp>
#include <a1net/CommBase.hpp>
#include <a1net/Socket.hpp>
#include <a1net/SocketSelect.hpp>
#include <a1net/SocketMonitor.hpp>
#include <a1net/Http.hpp>



#endif
