// 05/04/2005: Created, R. Nagy
//
#ifndef uidriver_hpx
#define uidriver_hpx

#include "uichar.hpp"

namespace stdscreen
{
// The idea here is to keep this as simple as possible for maximum
// portability across a tui / gui family - Also to allow for doubble
// buffering so as to make for smoother screen transitions.

class uibuffer
   {
   public:
      virtual void cls(const ColorSet& ref) = 0;
      virtual bool putch(int x, int y, uichar& ref) = 0;
      virtual void querysize(int& x, int& y) = 0;
   };

class uiaction
   {
   public:
      virtual bool process(void);
   };
   
class uidriver
   {
   public:
      virtual bool iodisplay(uibuffer *buffer, uiaction *action) = 0;
      virtual uibuffer *create(int x = 80, int y = 25) = 0;
   };
   
} // namespace

#endif   
