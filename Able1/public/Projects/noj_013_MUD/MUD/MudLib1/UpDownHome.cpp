#include "UpDownHome.hpp"

UpDownHome::UpDownHome(void)
   {
   ProgramId pid;
   dirLocal.Name("UpDownHome");
   pid.Home(dirLocal);
   }

bool UpDownHome::AsLocal(const Url& url, const UpDownHome& ref, UpDownFile& fileResult)
   {
   return false;
   }
