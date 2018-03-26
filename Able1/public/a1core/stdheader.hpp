#ifndef xxstd_header_hpp
#define xxstd_header_hpp

#include <iostream>
#include <cstring>           // memcpy()
#include <fstream>
#include <ctime>
#include <algorithm>         // for swap()
#include <cassert>
#include <cstdio>            // sprintf
#include <cctype>            // toupper()/tolower()
#include <cstddef>           // size_t
#include <cstdlib>           // mbstowcs, wcstombs
#include <sstream>           // 01/03/2007 - Finally - a universally worthy string stream!
#include <ctime>             // time_t
#include <string>
//#include <vector>            // for Array<T>

#ifdef MSDOS
#include <unistd.h>  // unlink(DJGPP)
#endif

#include <sys/stat.h>

#ifdef UNIX
#include <unistd.h>  // unlink
#else
#include <io.h>      // unlink
#endif

#endif
