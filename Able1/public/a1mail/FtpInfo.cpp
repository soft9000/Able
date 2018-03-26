#include "FtpInfo.hpp"

#define _FTP_FILE_ "FTPINFO.INI"


#include <a1extra/ini/IniFile.hpp>


FtpInfo::FtpInfo(void)
{
   pwFile.Name(_FTP_FILE_);

   sUser     = "user";
   sSite     = "site";
   sPassword = "password";

   ProgramId pid;
   pid.Home(pwFile);
}

bool FtpInfo::Home(const Directory& dir)
{
   return dir.Home(pwFile);
}

bool FtpInfo::Load(void)
{
   return Load(pwFile);
}

bool FtpInfo::Load(const File& file)
{
   pwFile = file;
   ini::IniFile iIni(pwFile);
   if(iIni.Load() == false)
      return false;

   sUser = iIni.Get("FTP_HOST", "USER");
   if(sUser.IsNull())
      return false;

   sSite = iIni.Get("FTP_HOST", "SITE");
   if(sSite.IsNull())
      return false;

   sPassword = iIni.Get("FTP_HOST", "PASSWORD");
   if(sPassword.IsNull())
      return false;

   return true;
}


bool FtpInfo::Save(void) const
{
   ini::IniFile iIni(pwFile);
   if(iIni.Load() == true)
      {
      if(iIni.Put("FTP_HOST", "USER", sUser) == false)
         return false;

      if(iIni.Put("FTP_HOST", "SITE", sSite) == false)
         return false;

      if(iIni.Put("FTP_HOST", "PASSWORD", sPassword) == false)
         return false;
      }
   else
      {
      if(iIni.Put("FTP_HOST", "USER", sUser) == false)
         return false;

      if(iIni.Put("FTP_HOST", "SITE", sSite) == false)
         return false;

      if(iIni.Put("FTP_HOST", "PASSWORD", sPassword) == false)
         return false;
      }
   return iIni.Save();
}
