/* TODO 1 -cUrl : Test this feature set. */

#define STRICT
#include <windows.h>
#include <shellapi.h>// shellexecute()

namespace Able1
   {
   bool Url::Launch(void) const
      {
      if(sUrl.IsNull())
         return false;
      if(int(ShellExecute(NULL, "open", sUrl.c_str(), NULL, NULL, SW_SHOWNORMAL)) <= 32)
         return false;
      return true;
      }
   } // Able1


