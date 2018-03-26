// Class HostAccouints: Eliminating hard-code in an easy to re-use manner.
//
// 10/26/1999: Class created, R. Nagy
// 09/02/2000: Added EmailedDatabase and re-wrote for same, R. Nagy
// 03/13/2005: Converting (in-place - no port!) to Able1, R. Nagy
// 11/25/2006: Reamed and updated for public inclusion as MailServerIni, R. Nagy
//
#ifndef MailServerIni_hpx
#define MailServerIni_hpx

#include <a1mail/rfcobjects.hpp>
#include <a1extra/Ini/IniFile.hpp>
using namespace ini;

namespace BetterMail
{
// MailServerIni data are maintained in an INI file.
class MailServerIni
{
protected:
   static bool Generic(IniFile& pwIni, HostName& host, UserData& user, const ZStr& sToken);
   static bool CreateDefaultIniFile(IniFile& pwIni);

public:
   // In order to minimize disk access times, these assume that an IniFile has been cached!
   static bool QuerySmtpDefault(IniFile& pwIni, HostName& hn, UserData& ud);
   static bool QueryNntpDefault(IniFile& pwIni, HostName& hn, UserData& ud);
   static bool QueryPop3Default(IniFile& pwIni, HostName& hn, UserData& ud);
   static bool GetAdministratorsAddress(IniFile& pwIni, ZStr& str);
   static bool GetDefaultAddress(IniFile& pwIni, ZStr& sAddress);

   static void DefaultName(IniFile& pwIni)
      {
      pwIni.pwFile.Name("HOST.INI");
      }

   // Locate an IniFile in a folder.
   static bool Load(IniFile& pwIni, const Directory& dir)
      {
      if(dir.Home(pwIni.pwFile) == false)
         return false;
      return pwIni.Load();
      }
   // Creates & loads it up with the defaults
   static bool Create(IniFile& pwIni, const Directory& dir)
      {
      if(dir.Home(pwIni.pwFile) == false)
         return false;

      if(CreateDefaultIniFile(pwIni) == false)
         return false;
      return pwIni.Load();
      }
};

}

#endif

