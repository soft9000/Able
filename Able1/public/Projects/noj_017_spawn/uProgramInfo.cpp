//---------------------------------------------------------------------------


#pragma hdrstop

#include "uProgramInfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ostream& ProgramInfo::Options::Write(ostream& os)
   {
   ZStr str;
   str.assign((int)bAutoRun);
   str.WriteStream(os);

   str.assign((int)bDayOnly);
   str.WriteStream(os);

   str.assign(iTimerSec);
   str.WriteStream(os);

   str.assign(iPauseMinutes);
   str.WriteStream(os);

   return os;
   }
istream& ProgramInfo::Options::Read(istream& is)
   {
   ZStr str;
   str.ReadStream(is);
   if(str[0] == '1')
      bAutoRun = true;
   else
      bAutoRun = false;

   str.ReadStream(is);
   if(str[0] == '1')
      bDayOnly = true;
   else
      bDayOnly = false;

   str.ReadStream(is);
   iTimerSec = str.AsInt();

   str.ReadStream(is);
   iPauseMinutes = str.AsInt();

   return is;
   }

