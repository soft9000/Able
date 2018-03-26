#include <Able1.hpp>
using namespace Able1;


using namespace Able1;

#ifdef UNIX
#include <a1core/os/unix/unix_Platform.cpp>
#endif

#ifdef MSDOS
#include <a1core/os/msdos/msdos_Platform.cpp>
#endif

#ifdef WIN32
#include <a1core/os/win32/win32_Platform.cpp>
#endif

