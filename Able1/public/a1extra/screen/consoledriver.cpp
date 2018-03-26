// 05/04/2005: Created, R. Nagy
//
#include "consoledriver.hpp"

using namespace _drivers;

#ifdef WIN32
#include "..\win32\win32_consoledriver.cpp"
#endif

#ifdef UNIX
#include "..\unix\unix_consoledriver.cpp"
#endif

#ifdef DOS
#include "..\msdos\msdos_consoledriver.cpp"
#endif
