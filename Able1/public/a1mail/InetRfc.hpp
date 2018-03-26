// Internet classes. Designed specifically to work with observed and documented RFC's.
// (c) 1998 by R. A. Nagy.
//
// 02/10/1998: Added the bShouldAbort members to support on-demand abortions.
// 02/12/1998: Created and implemented the StatusObject for better status reporting, R. Nagy
// 12/03/1998: Added PacketTimeout() and 'l_timeout` to reduce the 5 .. 8 minutes wait for BAILOUT, R. Nagy
// 01/05/1999: Added t_GetAtMost(,, NELEM) to get <= AN EXACT COUNT from a group, R. Nagy
// 04/30/1999: Added Post(), R. Nagy
// 01/08/2000: Added Set/QueryVerbose(), R. Nagy
// 03/06/2000: Fixed isdotmagic() (re-wrote around a context bug in .RFind(pos)).
//             Also added the 'replace' parameter to same, R. Nagy
// 08/17/2002: Added support for RFC821 HELO protocol, R. Nagy
//             Added support for SMTP Login (i.e: promoted && re-used NNTP logic), R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
// 01/17/2007: Cleaned up Get(TEMP FILE) home()ing logic. Clarified log messages. R. Nagy
//
#ifndef InetRfc_Hpp
#define InetRfc_Hpp

#include <a1mail/RfcObjects.hpp>
#include <a1mail/EmailFilter.hpp>

// FINALLY OBSOLETE
//#include <a1mail/Pop3Batch.hpp>
#include <a1mail/PopX.hpp>

#define USE_COMMENT

namespace BetterMail {

using namespace Able1;

// This defines a way to get articles from a stream. It insures and parses
// CR/LF commands.
class Rfc822Server
   {
   private:
      int         iShowLogon;
      ZStr   sMagicBuffer;     // Exclusively used by isdotmagic()

   protected:
      stdnet::Socket   soc;

      RfcObjectStatus zStat;

      bool  Put(const ZStr& str);
      bool  Get(ZStr& str);
      bool  More(void);

      bool  isdotmagic(ZStr& strL, char terminal_dot_replacement = ' ');

      // Commands are assumed to produce a contiguous response (i.e: NOTE: a 'MORE' is never sent);
      virtual bool  TransactRfcOrDottedResponse(const ZStr& sCmd, ZStr& sResult);

   public:
      Rfc822Server(void);
      virtual ~Rfc822Server(void);

      bool  Transact(const ZStr& stdIn, ZStr& stdOut);

      // CodeLevel returns true is RFC result is same LEVEL (typically 1, 2, 3, 4, or 5)...
      bool  TransactCodeLevel(const ZStr& str, ZStr& sResult, int RFC_code_expected = 200);

      // CodeSpecific returns true is RFC result is exact same code...
      bool  TransactCodeSpecific(const ZStr& str, ZStr& sResult, int RFC_code_expected);

      // Tell the default RefObject to show all of those protocol state messages sent to it's
      // RfcObject::OnVerbose() member;
      void SetVerbose(bool b = true)            {zStat.SetVerbose(b);}
      bool QueryVerbose(void)                   {return zStat.QueryVerbose();}

      // Mostly for end-user debugging of their authentication process.
      void  ShowLogon(void)                     {iShowLogon = 1;}
      void  DontShowLogon(void)                 {iShowLogon = NULL;}
      int   ShouldShowLogon(void)               {return iShowLogon;}

      virtual bool  Connect(HostName&);
      virtual void  Disconnect(HostName&);

      bool  Use(const ExeLog& rLog)
         {
         zStat.Use(rLog);
         return true;
         }
      void  LastError(ZStr& str);

#ifdef USE_COMMENT
      bool  Comment(const char *psz);
      bool  Comment(const ZStr& str);
#endif
   };


class Rfc977NewsGroupServer : public Rfc822Server
   {
   protected:
      bool        br;

   private:
      ZStr   str;
      NewsGroup   pwNewsGroup;

      bool  GetMagicBuffer(NewsGroup& ng, ArticleThunk& at, stringstream& sResult);

   protected:
      ZStr sServer;
      ZStr sGroup;

      // Sometimes you need them from the most resent to the oldest. Other times,
      // the other way 'round makes the most sense. These functions work both ways;      
      bool GetFirstThunk(NewsGroup&, ArticleThunk&, bool bForward = false);
      bool GetNextThunk(NewsGroup&, ArticleThunk&, bool bForward = false);

   public:
      Rfc977NewsGroupServer(void)                          {}
      virtual ~Rfc977NewsGroupServer(void)                 {}

      virtual bool  Connect(HostName& hn)      {return Rfc822Server::Connect(hn);}
      virtual void  Disconnect(HostName& hn)   {Rfc822Server::Disconnect(hn);}

      virtual bool  Connect(UserData&);
      virtual void  Disconnect(UserData&);

      virtual bool  Connect(NewsGroup&);
      virtual void  Disconnect(NewsGroup&);

      // Collect the article thunks
      bool  Get(NewsGroup& ng, Array<ArticleThunk>& rResult, mail_t StatStart = NULL);

      // Get the articles, via a filter. Results are tallied by the objects, themselves;
      // Returns false if process was aborted.
      bool  Get(NewsGroup&, Array<EMailMessage>& raOut, Array<ArticleThunk>& raIn, EMailFilter *pQ = NULL);

      // Get a single article
      bool  Get(NewsGroup&, EMailMessage& rOut, ArticleThunk& rIn);

      virtual bool  Post(const EMailMessage&, ZStr& sError);

 };

class SmtpServer : public Rfc822Server
   {
   protected:
      UserData      ConnectedUser;

   public:
      virtual bool  Connect(HostName& hn, UserData& ud);
      virtual void  Disconnect(HostName& hn);

      virtual bool  Connect(UserData& ud);
      virtual void  Disconnect(UserData&);

      virtual bool  Post(const EMailMessage&, ZStr& sError);
      // virtual bool  Post(const EMailFactory&, ZStr& sError);
   };



class Pop3Server : public Rfc822Server
   {
   protected:
      struct PopId
         {
         size_t szPos;
         PopId(void) : szPos(NPOS) {}
         PopId(size_t sz) : szPos(sz) {}
         };
      bool     Get(const Directory& dirSave, const ZStr& sType, bool bRemoveFromServer = false);

      bool     DeleteArticle(size_t which);
      bool     StatArticles(size_t&);
      bool     GetMagicBuffer(size_t which, ZStr& sResult);
      bool     RemoveFromServer(Array<PopId>& array);

      /* Retired
      bool     RemoveAsDesired(Pop3Batch&);
      bool     RemoveFromServer(EMailMessage&);
      bool     Get(Pop3Batch&);
      */

   public:
      virtual bool  Connect(HostName& hn)            {return Rfc822Server::Connect(hn);}
      virtual void  Disconnect(HostName& hn)         {Rfc822Server::Disconnect(hn);}

      virtual bool  Connect(UserData&);
      virtual void  Disconnect(UserData&);

      static bool   Download(HostName& host, UserData& user, const Directory& dir, ExeLog& sLog, bool bDelete = false, bool bVerbose = false);
      static bool   Download(PopX& popx, ExeLog& sLog);
   };






#ifdef USE_COMMENT
inline bool Rfc822Server::Comment(const char *psz)
   {
   return zStat.StatusMessage(psz);
   }

inline bool Rfc822Server::Comment(const ZStr& str)
   {
   return zStat.StatusMessage(str.c_str());
   }
#endif

}

#endif
