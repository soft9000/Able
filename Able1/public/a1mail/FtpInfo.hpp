// FtpInfo - Names say it all
//
// 12/31/2007: Added FtpUser and FtpFilePair, R. Nagy
//
#ifndef _FTPInfo_Hpp
#define _FTPInfo_Hpp

#include <Able1.hpp>

using namespace Able1;

struct FtpFilePair
   {
      bool      bText;
      ZStr sFileClient;
      ZStr sFileServer;

      FtpFilePair(void) : bText(false) 
         {
         }

      bool IsNull(void)
         {
         if(sFileClient.IsNull() == false)
            return false;
         if(sFileServer.IsNull() == false)
            return false;
         return true;
         }
   };

struct FtpUser
   {
      ZStr sSite;     // FTP == soft9000.com (no "www" (etc.))
      ZStr sUser;
      ZStr sPassword;

      bool IsNull(void)
         {
         if(sSite.IsNull() == false)
            return false;
         if(sUser.IsNull() == false)
            return false;
         if(sPassword.IsNull() == false)
            return false;
         return true;
         }
   };

class FtpInfo : public FtpUser
   {
   protected:
      File pwFile;

   public:
      FtpInfo(void);

   
   // Load / save the pw file   
   bool Load(void);
   bool Save(void) const;

   // change / home the pw file
   virtual bool Load(const File& file);
   virtual bool Home(const Directory& dir);

   ZStr IniName(void)
      {
      ZStr sResult = pwFile.Name();
      return sResult;
      }

   ZStr IniNodeName(void)
      {
      ZStr sResult;
      pwFile.QueryNode(sResult);
      return sResult;
      }
   };



#endif
