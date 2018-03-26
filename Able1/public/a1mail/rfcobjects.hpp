// Classes to encapsulate the status and data for RFC object transferrals.
//
// 02/12/1998: Classes removed from InetRfc, R. Nagy
// 01/08/1999: Added OnVerbose() to track all of those (potentially interesting) messages, R. Nagy
// 03/10/2001: Added MkWhite() after UserData.User() assignment. Have discoverd email systems permit all types of nasties therein, R. Nagy
// 08/17/2002: Added support for LocalHost on Host class to support SMTP HELO protocol, R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
//
#ifndef RfcObjects_Hpx
#define RfcObjects_Hpx

#include <a1net/Socket.hpp>
using namespace stdnet;

#include <a1mail/EMailFactory.hpp>

namespace BetterMail
{

// This function translates a buffer (any buffer) over to RFC newlines
extern const char *MkRFC(ZStr& sResult);

class HostName;
class UserData;
class ArticleThunk;
class NewsGroup;
class RfcStatusCode;
class RfcObjectStatus;
class Rfc822Server;

// Extern
class EMailFilter;

typedef unsigned long mail_t;


struct ServerType
{
   int server_type_code;

   static int none(void)    {return 0;}
   static int smtp(void)    {return 1;}
   static int ftp(void)     {return 2;}
   static int pop3(void)    {return 3;}
   static int nntp(void)    {return 4;}

   ServerType(void) {server_type_code = none();}

   ZStr Query(void);
};


class HostName
   {
   protected:
      ZStr   sError;
      u_short     port;
      ZStr   sHost;

   public:
      HostName(void)                               : port(NULL)   {}
      HostName(const ZStr& std, u_short p)    : port(p)      {sHost = std;}
      HostName(const HostName& h)                     {(*this) = h;}
      ~HostName(void)                                 {}

      void        Name(const ZStr& str)          {sHost = str;}
      void        Port(u_short p)                     {port = p;}
      const char *Name(void)                  const   {return sHost.c_str();}
      u_short     Port(void)                  const   {return port;}

      // Now featured in dialogs;
      const char *QueryPort(ZStr& str)           {str.Assign((int)port); return str.c_str();}
      void        SetPort(const ZStr& str)       {port = (int) str.AsInt();}

      void        SetError(const ZStr& s)        {sError = s;}
      ZStr   GetError(ZStr s)               {s = sError; return s;}

      int         operator==(const HostName& n)       {return (sHost == n.sHost);}
      HostName&   operator=(const HostName& n)        {if(this == &n) return *this; sHost = n.sHost; port = n.port; sError = n.sError; return *this;}
      ostream&    Write(ostream& os)                  {os << port << " ";  sHost.WriteStream(os); return os;}
      istream&    Read(istream& os)                   {os >> port;         sHost.ReadStream(os);  return os;}

      static int PortSMTP(void)                       {return 25;}
      static int PortPOP(void)                        {return 110;}
      static int PortNNTP(void)                       {return 119;}
      static int PortFTP(void)                        {return 21;}
   };

class UserData
   {
   protected:
      ZStr   sError;
      ZStr   sUserId;
      ZStr   sPassword;
      ZStr   sLocalHost;

      ZStr   AuthNNTP(Rfc822Server& server);
      ZStr   AuthESMTP(Rfc822Server& server);
      ZStr   AuthPOP3(Rfc822Server& server);

      ZStr   sAuthCodes;     // run-time only, please...
      ServerType  stAuth;         // (ibid)

   public:
      UserData(void)                                  {}
      UserData(const UserData& n)                     {(*this) = n;}
      UserData(const ZStr& U, const ZStr& P){User(U); Pass(P);}
      UserData(const ZStr& U, const ZStr& P, const ZStr& D){User(U); Pass(P); Domain(D);}

      void        SetError(const ZStr& s)        {sError = s;}
      ZStr   GetError(ZStr s)               {s = sError; return s;}

      // Added support for ESMTP AUTH requirements on server
      void        SetUserAuthorization(const ZStr& str, ServerType& st)   {sAuthCodes = str; stAuth = st;}
      ZStr   Authorize(Rfc822Server& server);

      // Added support for LocalHost to suport SMTP HELO protocol:
      void        Domain(const ZStr& std)        {sLocalHost = std;}
      const char *Domain(void)         const          {return sLocalHost.c_str();}

      const char *User(void)           const          {return sUserId.c_str();}
      const char *Pass(void)           const          {return sPassword.c_str();}

      void        User(const ZStr& std)          {sUserId   = std; sUserId.MkWhite();}
      void        Pass(const ZStr& std)          {sPassword = std;}

      int         operator==(const UserData& n)       {return ((sUserId == n.sUserId) && (sPassword == n.sPassword));}
      UserData&   operator=(const UserData& h)        {if(this == &h) return *this; sLocalHost = h.sLocalHost; sUserId = h.sUserId; sPassword = h.sPassword; sError = h.sError; return *this;}
      ostream&    Write(ostream& os)                  {sUserId.WriteStream(os); sPassword.WriteStream(os); sLocalHost.WriteStream(os); return os;}
      istream&    Read(istream& os)                   {sUserId.ReadStream(os);  sPassword.ReadStream(os);  sLocalHost.ReadStream(os);  return os;}

   };

class RfcStatusCode
   {
   protected:
      int         iCode;
      ZStr   sMessage;
   public:
      RfcStatusCode(void);
      RfcStatusCode(const RfcStatusCode&);
      virtual ~RfcStatusCode(void);

      bool Assign(const ZStr& std);

      int         Code(void)     const;
      const char *Message(void)  const;

      RfcStatusCode& operator=(const RfcStatusCode&);
   };

// The article thunk is a strange beastie: It can hold either the NEWNEWS "<message-id>" result
// or the numeric 'STAT/NEXT' id: Of course, both can be used with an ARTICLE-type command.
// -All we need to know is if the Number() is non-zero, to know what type is stored.
class ArticleThunk
   {
   private:
      mail_t      StatStart;     // used to "walk" a list of articles in a news-group server
      
   protected:
      ZStr   sError;
      mail_t      number;
      ZStr   sArticleName;
      bool        downloaded;    // true if the article was downloaded

   public:
      ArticleThunk(void)                     : number(NULL), downloaded(false) {}
      ArticleThunk(const ArticleThunk& at)   : number(NULL), downloaded(false) {*this = at;}
      virtual ~ArticleThunk(void)                           {}

      void        Error(const ZStr& err){sError = err;}
      const char* Error(void)        const   {return sError.c_str();}

      bool Assign(ZStr& std);
      
      // THIS IS FOR "CALLING OUT" AN ARTICLE THAT IS GIVING US A UNIQUE DEBUG OPPORTUNITY;
      void DebugAssign(mail_t mt)            {number = mt;}

      bool ArticleDownloaded(void)   const   {return downloaded;}
      void ArticleDownloaded(bool b)         {downloaded = b;}

      const char *MessageId(void)    const   {return sArticleName.c_str();}
      mail_t        Number(void)     const   {return number;}

      ArticleThunk&
         operator= (const ArticleThunk& at);
      int
         operator==(const ArticleThunk& at)  {return(sArticleName == at.sArticleName);}

      ostream& Write(ostream& os);
      istream& Read(istream& is);

   friend class Rfc977NewsGroupServer;
   };

class NewsGroup
   {
   protected:
      char canpost;
      int  okay;
      mail_t m_count;
      mail_t m_greater_than;
      mail_t m_less_than;

      mail_t m_session_count;
      mail_t m_ttotal_count;
      mail_t m_HighestRead;
      mail_t m_LowestRead;

      ZStr sGroup;

      void Reset(void);

   public:
      NewsGroup(void)                                 {Reset();}
      NewsGroup(const NewsGroup& n)                   {Reset();(*this) = n;}
      NewsGroup(const ZStr& which)               {Reset();Name(which);}

      long spNEXT;    // used for find first / next.

      void        SearchNewSetup(const EMailFilter& rFilter);

      bool        AssignFromLIST(ZStr& std);
      bool        AssignFromEntry(ZStr& std);

      // NOTE: Start and End represent a range. Nelem represents an actual count.
      // Due to article withdrawls and pruning, the deltas are almost certainly not
      // the same.
      mail_t        Nelem(void)           const         {return m_count;}
      mail_t        HighestNumber(void)   const         {return m_greater_than;}
      mail_t        LowestNumber(void)    const         {return m_less_than;}

      // The following group of counters is maintained by this event;
      void          LastArticleRead(ArticleThunk& at);
      mail_t        SessionYield(void) const            {return m_session_count;}
      mail_t        GroupYield(void) const              {return m_ttotal_count;}
      mail_t        HighestRead(void) const             {return m_HighestRead;}
      mail_t        LowestRead(void) const              {return m_LowestRead;}

      void        Name(const ZStr& std);
      const char *Name(void)              const         {return sGroup.c_str();}

      // DATA will always be different, but the NAMES must always match, => we only cmp the later;
      int         operator==(const NewsGroup& n)      {return (sGroup == n.sGroup);}

      // Complete data assignment, of course;
      NewsGroup&  operator=(const NewsGroup& n);

      ostream&    Write(ostream& os);
      istream&    Read(istream& os);
   };

class LowLevelSocketStatusProbe : public ExeLog
{
   protected:
      RfcObjectStatus *pStatusLog;

   public:
      LowLevelSocketStatusProbe(RfcObjectStatus *pl);
      virtual ~LowLevelSocketStatusProbe(void);
      ZStr Format(ostream& os, const ZStr& psz, int LogCapture = 1);
      ZStr Log(ostream& os, const ZStr& psz, int LogCapture = 1);
};

class RfcObjectStatus
   {
   protected:
      ExeLog log;

   public:
      enum CommentType
           {
           ctDEFAULT,
           ctDEBUG,
           ctDRIVER,
           ctABORT,
           ctERROR
           };
      RfcObjectStatus(void)                      {}
      virtual ~RfcObjectStatus(void)             {}

      void Use(const ExeLog& rcLog)              {log = rcLog;}
      void Query(ExeLog& rcLog)                  {rcLog = log;}

      //ExeLog *GetProbe(void)                  {return (new DayLog);} // LowLevelSocketStatusProbe(this));}

      virtual bool StatusMessage(const char *psz, CommentType = ctDEFAULT);
              bool StatusMessage(const ZStr std, CommentType = ctDEFAULT) {return StatusMessage(std.c_str());}

      // Activation / deactivation of the search process;
      virtual void OnActivation(void);
      virtual void OnDeActivation(void);
      virtual void OnTermination(void);

      // Local resource errors;
      virtual void OnDirectoryNotFound(const ZStr& sDirectoryName);

      // What to say when the user aborts the process;
      virtual void OnUserAbortProcessed(void);

      // Monitor connections;
      virtual void OnConnect(const HostName& host);
      virtual void OnConnect(const NewsGroup& group);
      virtual void OnConnectFailed(const HostName& host);
      virtual void OnConnectFailed(const NewsGroup& group);

      // Monitor retrevial of the list of available news-groups;
      virtual void OnGetNewListStart(void);
      virtual void OnGetNewListPacket(size_t block, ZStr& sPacket);
      virtual void OnGetNewListPacketAbort(void);
      virtual void OnGetNewListCompleted(void);

      // Monitor the loading of the selected news-groups;
      virtual void OnNewsGroupLoadStart(void);
      virtual void OnNewsGroupLoadItem(const ZStr& std);
      virtual void OnNewsGroupLoadCompleted(Array<NewsGroup>& rResult);

      // Monitor the actual downloading of articles to your machine;
      virtual void OnNewsGroupDownloadStart(Array<NewsGroup>& ngA);
      virtual void OnNewsGroupDownloadStart(NewsGroup& ng);
      virtual void OnNewsGroupDownloadStartError(NewsGroup& ng);
      virtual void OnNewsGroupDownloadCompleted(Array<NewsGroup>& ngA);
      virtual void OnNewsGroupDownloadCompleted(NewsGroup& ng);

      // Monitor as a QUALIFIED search is taking place;
      virtual void OnQualificationStart(const NewsGroup& ng, const EMailFilter& emf);
      virtual void OnQualifiedNone(const NewsGroup& ng, const EMailFilter& flt);
      virtual void OnArticleMatched(const NewsGroup& ng, const EMailMessage& Em, const EMailFilter& emf);
      virtual void OnArticleMatched(const NewsGroup& ng, const EMailMessage& Em);
      virtual void OnArticleRejected(const NewsGroup& ng, const EMailMessage& Em, const EMailFilter& emf);
      virtual void OnArticleRejected(const NewsGroup& ng, const EMailMessage& Em);

      // Monitor what happens when QUALIFIED articles are being saved to local resources;
      virtual void OnQualifiedSaveStart(const NewsGroup& ng, Array<EMailMessage> rOut, const EMailFilter& flt);
      virtual void OnQualifiedSaveCompleted(const NewsGroup& ng, Array<EMailMessage> rOut, const EMailFilter& flt);
      virtual void OnBadFileName(const EMailMessage& em);
      virtual void OnRenamedFileName(const EMailMessage& em);
      virtual void OnDuplicateFileName(const EMailMessage& em);
      virtual void OnArticleSaveFailure(const EMailMessage& em);
      virtual void OnArticleSaved(const EMailMessage& em);

      // Monitor object / object collections as-they-aggregate;
      virtual void OnNewsGroups(const Array<NewsGroup>& rGroups);
      virtual void OnNewsGroupObject(const NewsGroup& ng, const ArticleThunk& aT, mail_t StatStart, int retries);
      virtual void OnLocalObject(const NewsGroup& ng, const EMailMessage& Em);    // (local search)
      virtual void OnNewsGroupObject(const NewsGroup& ng, const EMailMessage& Em, const ArticleThunk aT);
      virtual void OnNewsGroupObjects(const NewsGroup& rGroup, Array<EMailMessage>& rOut, const EMailFilter& flt);
      virtual void OnNewsGroupObjects(const NewsGroup& group, Array<ArticleThunk>& thunks);
      virtual void OnNewsGroupObjectsMissing(const NewsGroup& group, Array<ArticleThunk>& thunks);

      // Monitor low-level article STAT-status;
      virtual void OnGroupStatStart(const NewsGroup& ng, mail_t StatStart);
//    virtual void OnGroupStatError(const NewsGroup& ng, const char *psz);
      virtual void OnArticleStat(const NewsGroup& ng, size_t block, int retries);
      virtual void OnError(const NewsGroup& group, ArticleThunk& thunks);
      virtual void OnError(const NewsGroup& group, RfcStatusCode& RfcCode);
      virtual void OnTimeoutDeath(const NewsGroup& group, ArticleThunk& thunk, int packet_retry_times);
//    virtual void OnWithdrawn(const NewsGroup& group, ArticleThunk& thunk, int RfcCode, const ZStr& sBuffer);

      // Monitor low-level buffer retries and bail-outs;
      virtual void OnBadArticleBuffer(const NewsGroup& ng, ArticleThunk& aThunk, EMailMessage& em);
      virtual void OnBufferError(const NewsGroup& ng, ArticleThunk& aT, ZStr& stdOut);
      virtual void OnBufferError(const NewsGroup& ng, ZStr& stdOut);
      virtual void OnSocketError(Socket& soc);


      virtual bool ShouldAbort(void)          {return false;}

      // There are legacy. Used mostly by the servers in InetRfc. Maybe we'll phase them out,
      // or phase out the redundant ones from (above);
      virtual void Got(const HostName&)             {}
      virtual void Got(const UserData&)             {}
      virtual void Got(NewsGroup&)            {}
      virtual void Got(ArticleThunk&)         {}
      virtual void Got(EMailMessage&)                {}

      virtual void OnError(const EMailMessage& group, RfcStatusCode& RfcCode);
      virtual void OnError(const EMailMessage& group, const ZStr& RfcCode);

      // Added 01/08/1999
      void SetVerbose(bool b = true)          {if(b) log.Enable(); else log.Disable();}
      bool QueryVerbose(void)                 {return log.Enabled();}
      virtual void OnVerbose(const ZStr& VerboseMessage);
   };

}

#endif
