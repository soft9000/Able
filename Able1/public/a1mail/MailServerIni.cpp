#include <a1mail/MailServerIni.Hpp>
using namespace BetterMail;
using namespace ini;

bool MailServerIni::QuerySmtpDefault(IniFile& pwFile, HostName& host, UserData& user)
   {
   return Generic(pwFile, host, user, "SMTP");
   }
bool MailServerIni::Generic(IniFile& pwFile, HostName& host, UserData& user, const ZStr& sToken)
   {
   IniFile ini(pwFile);
   ZStr sKey, sResult;

   sKey = sToken;
   sKey.Append("_SERVER");
   sResult = ini.Get("DEFAULT_HOST", sKey);
   if(sResult.IsNull())
      return false;
   host.Name(sResult.Strip());

   sKey = sToken;
   sKey.Append("_PORT");
   sResult = ini.Get("DEFAULT_HOST", sKey);
   if(sResult.IsNull())
      return false;
   host.Port((unsigned short)::atoi(sResult.c_str()));

   sKey = sToken;
   sKey.Append("_USER");
   sResult = ini.Get("DEFAULT_HOST", sKey);
   if(sResult.IsNull())
      return false;
   if(sResult[0] != '*')
      user.User(sResult.Strip());

   sKey = sToken;
   sKey.Append("_PASS");
   sResult = ini.Get("DEFAULT_HOST", sKey);
   if(sResult.IsNull())
      return false;
   if(sResult[0] != '*')
      user.Pass(sResult.Strip());

   // 08/17/2002, R. Nagy
   sKey = "SMTP_HELO";
   sResult = ini.Get("DEFAULT_HOST", sKey);
   if(sResult.IsNull())
      return false;
   user.Domain(sResult.Strip());

   return true;
   }
bool MailServerIni::GetDefaultAddress(IniFile& pwFile, ZStr& std)
   {
   IniFile ini(pwFile);
   std = ini.Get("USERS", "DEFAULT");
   if(std.IsNull())
      return false;
   return true;
   }
bool MailServerIni::GetAdministratorsAddress(IniFile& pwFile, ZStr& std)
   {
   IniFile ini(pwFile);
   std = ini.Get("USERS", "ADMIN");
   if(std.IsNull())
      return false;
   return true;
   }
bool MailServerIni::QueryPop3Default(IniFile& pwFile, HostName& host, UserData& user)
   {
   return Generic(pwFile, host, user, "POP3");
   }
bool MailServerIni::QueryNntpDefault(IniFile& pwFile, HostName& host, UserData& user)
   {
   return Generic(pwFile, host, user, "NNTP");
   }
bool MailServerIni::CreateDefaultIniFile(IniFile& pwFile)
   {
   bool br = false;
   IniFile ini(pwFile);

   ini.Put("USERS", "ADMIN",     "your_userid@your.isp.com");
   ini.Put("USERS", "DEFAULT",   "list_serverid@your.isp.com");

   ini.Put("DEFAULT_HOST", "SMTP_SERVER", "smtp.your_server.com");
   ini.Put("DEFAULT_HOST", "SMTP_USER",   "* (means none required)");
   ini.Put("DEFAULT_HOST", "SMTP_PASS",   "* (means none required)");
   ini.Put("DEFAULT_HOST", "SMTP_PORT",   "25");
   ini.Put("DEFAULT_HOST", "SMTP_HELO",   "your_domain.com");    // 08/17/2002, R. Nagy

   ini.Put("DEFAULT_HOST", "POP3_SERVER", "popd.your_server.com");
   ini.Put("DEFAULT_HOST", "POP3_USER",   "USER your_name@your_site.com");
   ini.Put("DEFAULT_HOST", "POP3_PASS",   "PASS password");
   ini.Put("DEFAULT_HOST", "POP3_PORT",   "110");

   ini.Put("DEFAULT_HOST", "NNTP_SERVER",  "nntp.your_server.com");
   ini.Put("DEFAULT_HOST", "NNTP_USER",    "your_name@your_site.com");
   ini.Put("DEFAULT_HOST", "NNTP_PASS",    "password");
   ini.Put("DEFAULT_HOST", "NNTP_PORT",    "119");

   br = ini.Save();
   return br;
   }



