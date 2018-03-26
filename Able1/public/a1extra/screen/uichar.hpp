// 05/04/2005: Created, R. Nagy
//
#ifndef uichar_hpx
#define uichar_hpx

#include "stdcolor.hpp"

namespace stdscreen
{
// All chars have attributes
struct uichar
   {
   int code;
   ColorSet color;
   };
}
#endif
