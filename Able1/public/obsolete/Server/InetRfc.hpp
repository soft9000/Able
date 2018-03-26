// Internet classes. Designed specifically to work with observed and documented RFC's.
// (c) 1998 by R. A. Nagy.
//
// 02/10/1998: Added the bShouldAbort members to support on-demand abortions.
// 02/12/1998: Created and implemented the StatusObject for better status reporting, R. Nagy
// 12/03/1998: Added PacketTimeout() and 'l_timeout` to reduce the 5 .. 8 minutes wait for BAILOUT, R. Nagy
// 01/05/1999: Added t_GetAtMost(,, NELEM) to get <= AN EXACT COUNT from a group, R. Nagy
// 04/30/1999: Added Post(), R. Nagy
// 01/08/2000: Added Set/QueryVerbose(), R. Nagy
// 03/06/2000: Fixed isdotmagic() (re-wrote around a context bug in .rfind(pos)).
//             Also added the 'replace' parameter to same, R. Nagy
// 08/17/2002: Added support for RFC821 HELO protocol, R. Nagy
//             Added support for SMTP Login (i.e: promoted && re-used NNTP logic), R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
//
#ifndef InetRfc_Hpp
#define InetRfc_Hpp

#include <obsolete/Server/RfcObjects.hpp>
#include <obsolete/Server/EmailFilter.hpp>

#define USE_COMMENT

using namespace Able1;

// This defines a way to get articles from a stream. It insures and parses
// CR/LF commands.
class Rfc822Server
   {
   private:
      long        l_timeout;
      int         iShowLogon;
      ZStr   sMagicBuffer;     // Exclusively used by isdotmagic()

   protected:
      StdSocket   soc;

      RfcObjectStatus *pStat;
/*
      void  PacketTimeout(long l);     // Packet
      long  PacketTimeout(void);
*/
      bool  Put(const ZStr& std);
      bool  Get(ZStr& std);
      bool  More(void);

      bool  isdotmagic(ZStr& strL, char terminal_dot_replacement = ' ');

      // Commands are assumed to produce a contiguous response (i.e: NOTE: a 'MORE' is never sent);
      virtual bool  TransactRfcOrDottedResponse(const ZStr& sCmd, ZStr& sResult);

   public:
      Rfc822Server(void);
      virtual ~Rfc822Server(void);

      bool  Transact(const ZStr& stdIn, ZStr& stdOut);

      // CodeLevel returns true is RFC result is same LEVEL (typically 1, 2, 3, 4, or 5)...
      bool  TransactCodeLevel(const ZStr& std, ZStr& sResult, int RFC_code_expected = 200);

      // CodeSpecific returns true is RFC result is exact same code...
      bool  TransactCodeSpecific(const ZStr& std, ZStr& sResult, int RFC_code_expected);

      // Tell the default RefObject to show all of those protocol state messages sent to it's
      // RfcObject::OnVerbose() member;
      void SetVerbose(bool b = true)            {pStat->SetVerbose(b);}
      bool QueryVerbose(void)                   {return pStat->QueryVerbose();}

      // Mostly for end-user debugging of their authentication process.
      void  ShowLogon(void)                     {iShowLogon = 1;}
      void  DontShowLogon(void)                 {iShowLogon = NULL;}
      int   ShouldShowLogon(void)               {return iShowLogon;}

      virtual bool  Connect(HostName&);
      virtual void  Disconnect(HostName&);

      bool  Use(RfcObjectStatus *pLog);      // OWNERSHIP TRANSFERS IN: (do not delete pointer)
      bool  Use(const StdLog& rLog);

      bool  SocketLogFileName(const char *pszLogFile);
      void  SocketLogFileName(void);

      void  SocketTraceOn(void);
      void  SocketTraceOn(StdLog *pTrace);// OWNERSHIP TRANSFERS IN: (do not delete pointer)
      void  SocketTraceOff(void);

      void  LastError(ZStr& std);
      virtual void  MonitorConnection(ostream& os, istream& is);

#ifdef USE_COMMENT
      bool  Comment(const char *psz);
      bool  Comment(const ZStr& std);
#endif
   };


class Rfc977NewsGroupServer : public Rfc822Server
   {
   protected:
      bool        br;

   private:
      ZStr   std;
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
      bool  Get(NewsGroup&, Array<EMail>& raOut, Array<ArticleThunk>& raIn, EMailFilter *pQ = NULL);

      // Get a single article
      bool  Get(NewsGroup&, EMail& rOut, ArticleThunk& rIn);

      virtual bool  Post(const EMail&, ZStr& sError);

      virtual void  MonitorConnection(ostream& os, istream& is)
         {
         Rfc822Server::MonitorConnection(os, is);
         }
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

      virtual bool  Post(const EMail&, ZStr& sError);
      virtual bool  Post(const OutBoundEmail&, ZStr& sError);
   };


// Unlike news-group postings, articles in a POP3 account can be deleted PERMINATELY.
// For this reason, special care is given to these articles to insure that if the
// session terminates abnormally, we can recover WITHOUT DATA LOASS. The Pop3Batch
// is the "wrapper" that we use to ensure that data is either (1) on the server,
// or (2) on the local hard drive. WORST CASE is that items are duplicated during
// disaster recovery, but, hey, that's why God created the "EMail::operator=()" !
class Pop3Batch
   {
   private:
      bool                 bShouldDelete;
      size_t               ssNext;

      bool     SaveRecoveryFile(void);
      bool     ShouldRecover(void);
      bool     LoadRecoveryFile(void);

      bool     Append(EMail&);
      EMail *  Recall(EMail *pem = NULL);

      void     Error(const ZStr& std);

      time_t   error_file_time;
      time_t   email_file_time;

      ZStr   sOutputDirectory;

   public:  // 06/16/2004, R. Nagy
      Array<StreamZStr>  rErrorArray;
      Array<EMail>         rArray;
   
   public:
      Pop3Batch(void);
      virtual ~Pop3Batch(void);

      // EMail saved via array.
      // Errors "     "    "  .
      // Returns NPOS on error, else number of items saved;
      size_t   SaveArrays(void);
      bool     LoadArray(Array<EMail>& rArray);
      bool     LoadArray(Array<StreamZStr>& rArray);
      bool     ReplaceArray(Array<EMail>& rArray);
      bool     ReplaceArray(Array<StreamZStr>& rArray);
      bool     HaveArraysChanged(void);

      // Each EMail saved using "SaveBin" under a temp name.
      // Errors saved in "LoadArray" format (above).
      // Returns NPOS on error, else number of items saved;
      size_t   Save(void);

      // Each EMail saved using "Dump" under a temp name.
      // Errors saved in "LoadArray" format (above).
      // Returns NPOS on error, else number of items saved;
      size_t   Dump(const ZStr& sExtension = ".TXT");

      // Like the above, but overrides and replaces the output directory for
      // the entire instance ...
      size_t   Export(Directory& dir, const ZStr& sExtension = ".TXT");

      // After files are downloaded and BEFORE they are removed from the server,
      // a "hardened" copy of the EMail items is saved. To stop the automatic
      // recovery of the SAVED file, you *MUST* call the following member AFTER
      // you have successfully copied the files from your BATCH instance into 
      // another storage facility;
      void     BatchCompleted(void);
      size_t   NumInBatch(void)                             {return rArray.Nelem();}
      size_t   Nelem(void)                                  {return rArray.Nelem();}

      bool     AutoRemoveHostArticles(void);
      void     AutoRemoveHostArticles(bool b)               {bShouldDelete = b;}


      bool HadErrors(void);
      void RecallErrors(ZStr& sCrLfErrorList);

   friend class Pop3Server;
   };

class Pop3Server : public Rfc822Server
   {
   protected:
      bool     DeleteArticle(size_t which);
      bool     StatArticles(size_t&);
      bool     GetMagicBuffer(size_t which, ZStr& sResult);

   public:
      virtual bool  Connect(HostName& hn)            {return Rfc822Server::Connect(hn);}
      virtual void  Disconnect(HostName& hn)         {Rfc822Server::Disconnect(hn);}

      virtual bool  Connect(UserData&);
      virtual void  Disconnect(UserData&);

      virtual bool  Get(Pop3Batch&);
      virtual bool  RemoveFromServer(EMail&);
   };






#ifdef USE_COMMENT
inline bool Rfc822Server::Comment(const char *psz)
   {
   return pStat->StatusMessage(psz);
   }

inline bool Rfc822Server::Comment(const ZStr& std)
   {
   return pStat->StatusMessage(std.c_str());
   }
#endif

#endif
