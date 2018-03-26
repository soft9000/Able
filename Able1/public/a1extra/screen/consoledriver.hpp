// 05/04/2005: Created, R. Nagy
//
#ifndef uiconsoledriver_hpx
#define uiconsoledriver_hpx

#include "uidriver.hpp"
using namespace stdscreen;

namespace _drivers
{
// The idea here is to keep this as simple as possible for maximum
// portability across a tui / gui family   
class consolebuffer : public stdscreen::uibuffer
   {
   public:
      void cls(const ColorSet& ref);
      bool putch(int x, int y, uichar& ref);
      void querysize(int& x, int& y);
   };
} // namespace

#endif   
