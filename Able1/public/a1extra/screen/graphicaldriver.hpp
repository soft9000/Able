// 05/04/2005: Created, R. Nagy
//
#ifndef uigraphicaldriver_hpx
#define uigraphicaldriver_hpx

#include "uidriver.hpp"
using namespace stdscreen;

namespace _drivers
{
// The idea here is to keep this as simple as possible for maximum
// portability across a tui / gui family   
class graphicalbuffer : public stdscreen::uibuffer
   {
   public:
      void cls(const ColorSet& ref);
      bool putch(int x, int y, uichar& ref);
      void querysize(int& x, int& y);
   };
   
class graphicaldriver : public stdscreen::uidriver
   {
   public:
      bool iodisplay(uibuffer *buffer, uiaction *action) = 0;
      uibuffer *create(int x = 80, int y = 25) = 0;
   };
   
} // namespace

#endif   
