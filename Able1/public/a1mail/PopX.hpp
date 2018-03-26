#ifndef PopX_Hpx
#define PopX_Hpx
// 01/11/2008: Added bVerbose, R. Nagy

#include <a1mail/RfcObjects.hpp>

namespace BetterMail
{

// Extract a user's electronic mail from a PopServer -
struct PopX
   {
   bool      bVerbose;
   bool      bDelete;
   Directory dir;
   BetterMail::HostName host;
   BetterMail::UserData user;

   PopX(bool bDelFromAcct = false, bool bLogVerbose = false) : bDelete(bDelFromAcct), bVerbose(bLogVerbose)
      {
      host.Port(HostName::PortPOP());
      }

   ostream& Write(ostream& os)
      {
      ZStr str;
      if(bDelete)
         str = "1";
      else
         str = 0;
      str.WriteStream(os);
      host.Write(os);
      user.Write(os);
      dir.Write(os);
      return os;
      }
   istream& Read(istream& is)
      {
      ZStr str;
      str.ReadStream(is);
      if(str == "1")
         bDelete = true;
      else
         bDelete = false;
      host.Read(is);
      user.Read(is);
      dir.Read(is);
      return is;
      }
   };

}

#endif



