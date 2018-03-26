#include <Able1.hpp>
using namespace Able1;

#ifdef UNIX
#include <a1core/os/unix/unix_FileSystem.cpp>
#endif

#ifdef MSDOS
#include <a1core/os/msdos/msdos_FileSystem.cpp>
#endif

#ifdef WIN32
#include <a1core/os/win32/win32_FileSystem.cpp>
#endif

