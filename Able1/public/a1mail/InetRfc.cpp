#include <a1mail/InetRfc.hpp>
using namespace BetterMail;

#include <cstdio>             // sscanf()



/*
RFC 977
=======
The first digit of the response broadly indicates the success, failure, or progress of the previous 
command.

1xx   Informative message 
2xx   Command ok
3xx   Command ok so far, send the rest of it. 
4xx   Command was correct, but couldn't be performed for some reason.
5xx   Command unimplemented, or incorrect, or a serious program error occurred.

The next digit in the code indicates the function response category. 

x0x   Connection, setup, and miscellaneous messages
x1x   Newsgroup selection
x2x   Article selection
x3x   Distribution functions
x4x   Posting
x8x   Nonstandard (private implementation) extensions
x9x   Debugging output

The exact response codes that should be expected from each command are detailed in the description of
that command.
*/

#define BEGIN  {
#define END    }

const char *MORE_STRING = "\r\n";

Rfc822Server::Rfc822Server(void) : iShowLogon(NULL)
   {
   }
Rfc822Server::~Rfc822Server(void)
   {
   }
/*
void  Rfc822Server::PacketTimeout(long l)
   {
   l_timeout = l;
   }
long  Rfc822Server::PacketTimeout(void)
   {
   return l_timeout;
   }
*/   
bool  Rfc822Server::isdotmagic(ZStr& strL, char replace)
   {
   // If the string is empty, then we have a problem;
   if(!strL.Length())
      return false;
   /*
Text is sent only after a numeric status response line has been sent that indicates that text will
follow. Text is sent as a series of successive lines of textual matter, each terminated with CR-LF
pair. A single line containing only a period (.) is sent to indicate the end of the text (i.e., the
server will send a CR-LF pair at the end of the last line of text, a period, and another CR-LF pair).

If the text contained a period as the first character of the text line in the original, that first
period is doubled. Therefore, the client must examine the first character of each line received, and
for those beginning with a period, determine either that this is the end of the text or whether to
collapse the doubled period to a single one.

The intention is that text messages will usually be displayed on the user's terminal whereas
command/status responses will be interpreted by the client program before any possible display
is done.
   */
   if(strL.Length() < 2)
      return false;

   if((strL[0] == '.') && (strL[1] == '\r'))
      {
      // Remove the darn thing;
      strL[0] = replace;
      return true;      // What else could it be?
      }

   // *******
   // WARNING
   // *******
   // From here on out, there is a five (5) byte terminaiton sequence, no matter 
   // where it is found. It would fine to simply;
   /*
   long sp = strL.Find("\r\n.\r\n");
   if(sp != npos)
      {
      // Remove the darn thing;
      strL[sp+2] = replace;
      return true;
      }
   */
   // but, the problem IS that when we have an article wint an ILLEGAL 
   // (non-doubled) period-newline sequence, a routine would detect it as a
   // "terminal" (a common problem with email content, but not with NNTP 
   // servers (etc)). 
   //
   // On an interesting vector, I have discovered that the only *ABSOLUTELY* 
   // affermitave way to detect a terminal sequence (due to transmission errors, 
   // transmission padding, etc) is to permit a subsequent time-out after this 
   // routine returns true, but that's neither RFC nor implemented. Indeed, as
   // our news-Reader and list server base worked this way for a season, this
   // procedure is tried-and-true... But it wastes significant time at the
   // moment.
   //
   // OUR COMPROMISE is, as it was, to only check the trailing five bytes.
   // We'll assume that modern modem technologies are handling the transmission 
   // errors enough to allow for this: Note that this approach "rareifies" the 
   // ILLEGAL imbedding of a terminal, as well as honors the letter of the RFC's;
   //
   if(strL.Length() < 5)
      return false;

   ZStr sck = &strL[strL.Length() - 5];
   if(sck.Find("\r\n.\r\n") != npos)
      {
      // Remove the darn thing;
      strL[strL.Length()-3] = replace;
      return true;
      }

   return false;
   }
bool Rfc822Server::Put(const ZStr& str)
   {
   return soc.Send(str);
   }
bool Rfc822Server::Get(ZStr& str)
   {
   // If it's a "MORE", then adjust the time-out to keep us from waiting
   // till we freak-out;
   //if(str[0] == '\r')
   //   return soc.Receive(str);
   // Else. doittoit
   return soc.Receive(str);
   }
bool Rfc822Server::More(void)
   {
   return soc.Send(MORE_STRING);
   }
bool Rfc822Server::TransactCodeLevel(const ZStr& str, ZStr& sResult, int RFC_code)
   {
   if(Transact(str, sResult) == false)
      return false;
   RfcStatusCode RfcCode;
   if(RfcCode.Assign(sResult) == false)
      return false;
   if((RfcCode.Code() / 100) != RFC_code)
      return false;
   return true;
   }
bool Rfc822Server::TransactCodeSpecific(const ZStr& str, ZStr& sResult, int RFC_code)
   {
   if(Transact(str, sResult) == false)
      return false;
   RfcStatusCode RfcCode;
   if(RfcCode.Assign(sResult) == false)
      return false;
   if(RfcCode.Code() != RFC_code)
      return false;
   return true;
   }
bool Rfc822Server::Transact(const ZStr& stdIn, ZStr& stdOut)
   {
   return soc.Transact(stdIn, stdOut);
   }
bool Rfc822Server::Connect(HostName& host)
   {
   // connect the nntp host;
   if(soc.Connect(host.Name(), host.Port()) == false)
      {
      zStat.OnConnectFailed(host);
      zStat.StatusMessage(soc.GetLastError());
      return false;
      }
   zStat.OnConnect(host);
   
   ZStr str;
   // get the sign-on banner;
   int i = 0;
   while(soc.Receive(str) == false)
      {
      if(i++ == 10)
         {
         zStat.OnSocketError(soc);
         return false;
         }
      }
   return true;
   }
void Rfc822Server::Disconnect(HostName&)
   {
   soc.Disconnect();
   }
void Rfc822Server::LastError(ZStr& str)
   {
   str = soc.GetLastError();
   }
bool Rfc977NewsGroupServer::Connect(UserData& ud)
   {
   // *****
   // See if "login" is required for NNTP:
   // *****
   // (This works fine with FTP strings like "user rnagy", "pass xxxxxxxx" (literally!));
   ServerType st;
   st.server_type_code = st.nntp();
   ud.SetUserAuthorization("", st);
   ZStr str;
   str = ud.Authorize(*this);

   // Inform of slave status;
   bool br = false;
   if(str.IsNull() == true)
      {
      str = "SLAVE\r\n";
      br = soc.Transact(str, str);
      if(br == true)
         zStat.Got(ud);
      }
   return br;
   }
void  Rfc977NewsGroupServer::Disconnect(UserData&)
   {
   // Stop the news server;
   str = "QUIT\r\n";
   soc.Transact(str, str);
   // No "logout" required for NNTP.
   }
bool  Rfc977NewsGroupServer::Connect(NewsGroup& group)
   {
   br = false;

   str = "GROUP ";
   str.Append(group.Name());
   str.Append("\r\n");
   if(soc.Transact(str, str) == true)
      {
      switch(str[0])
         {
         case '2':
         case '1':
            br = group.AssignFromEntry(str);
         break;

         default:
         break;
         };
      }
   // Assign what we have assigned;
   if(br == true)
      {
      pwNewsGroup = group;
      zStat.Got(group);
      }
   else
      {
      NewsGroup ng;
      pwNewsGroup = ng;
      }
   return br;
   }
void  Rfc977NewsGroupServer::Disconnect(NewsGroup& ng)
   {
   }
bool  Rfc977NewsGroupServer::Get(NewsGroup& ng, Array<ArticleThunk>& rResult, mail_t StatStart)
   {
   ArticleThunk aT;
   // Carefull! If GetFirstThunk changes, the we need to change the following to match;
   aT.StatStart = StatStart;
   bool br = GetNextThunk(ng, aT);
   while(br == true)
      {
      rResult[rResult.Nelem()] = aT;
      br = GetNextThunk(ng, aT);
      }
   if(!rResult.Nelem())
      return false;
   return true;
   }
bool  Rfc977NewsGroupServer::GetFirstThunk(NewsGroup& ng, ArticleThunk& aT, bool bForward)
   {
   // WE NEED TO TRAP FOR
   // WSAECONRESET
   // AT THE SOCKET LEVEL!
   // <<<WIP>>>
   BEGIN
   // Zero out the result;
   ArticleThunk at2;
   aT = at2;
   END
   if(bForward == true)
      {
      aT.StatStart = (ng.LowestRead() > ng.LowestNumber()) ? ng.LowestRead() : ng.LowestNumber();

      // If we've seen 'em all, then we've no more to see (c++?);
      if(aT.StatStart >= ng.HighestNumber())
         return false;
      }
   else
      aT.StatStart = ng.HighestNumber();     // Searching BACKWARDS from here (inclusive)

   zStat.OnGroupStatStart(ng, aT.StatStart);

   return GetNextThunk(ng, aT, bForward);
   }
bool  Rfc977NewsGroupServer::GetNextThunk(NewsGroup& ng, ArticleThunk& aT, bool bForward)
   {
   if(!(pwNewsGroup == ng))
      if(Connect(ng) == false)         // "AssignFromEntry"
         return false;

   // AFTER a possible Connect() ("AssignFromEntry()"),
   // if there are none to get, then we've got em all!
   if(!ng.Nelem())
      return false;

   ZStr stdIn, stdOut;
   int retries = NULL;

   ZStr std2;
   int running    = 1;
   // This is a count of how many time we will "ignore" a "garbage filled", or non RFC-compliant, response.
   int too_much   = NULL;
   while(running)
      {
      if(zStat.ShouldAbort() == true)
         {
         zStat.OnUserAbortProcessed();
         return false;
         }

      // Are we done?
      if(aT.StatStart < ng.LowestNumber())
         return false;

      // Are we done?
      if(aT.StatStart > ng.HighestNumber())
         return false;

      // We are not using the CP here. Instead, we count back/forwards from the last know article
      // number;
      stdIn = "";
      stdIn << "STAT " << aT.StatStart << "\r\n";
#ifdef DEBUG
      zStat.OnArticleStat(ng, aT.StatStart, retries);
#endif

      stdOut = "^";
      size_t times = 6;
      while(times-- && (soc.Transact(stdIn, stdOut) == false))
         ;
      if(!times)
         {
         // <<WIP>>>: This is where we should try a re-connect;
         return false;
         }

      // Nothing back. Dung happened;
      if(stdOut[0] == '^')
         {
         // <<WIP>>>: This is where we should try a re-connect;
         return false;
         }

      RfcStatusCode RfcCode;
      if(RfcCode.Assign(stdOut) == true)
         {
         switch(stdOut[0])
            {
            case '2':
            //    2xx - Command ok
               // Either got garbage back, or we're legally done;
               if(aT.Assign(stdOut) == true)
                  {
                  retries = NULL;
                  zStat.Got(aT);
                  zStat.OnNewsGroupObject(ng, aT, aT.StatStart, retries);
                  if(bForward)
                     aT.StatStart++;
                  else
                     aT.StatStart--;
                  return true;
                  }
            case '4':
            //    4xx - Command was correct, but couldn't be performed for some reason.
               // An error of this type is either an article withdrawn, the end of the
               // enumeration, or a concidental positioning of an ASCII character at
               // the [0] position (I've seen it happen!). Either way, we'll count it as
               // the same error and re-try;
               // Observed: "483 NEWNEWS temporarily disabled due to load" in both slave and non-slave modes.
               // Observed: "423 Bad article number"
               if(RfcCode.Code() != 423)
                  {
                  zStat.OnError(ng, RfcCode);
                  return false;
                  }

            case '1':
            //    1xx - Informative message
            case '3':
            //    3xx - Command ok so far, send the rest of it.
            default:
               retries = NULL;
               if(bForward)
                  aT.StatStart++;
               else
                  aT.StatStart--;
            continue;
            case '5':
            //    5xx - Command unimplemented, or incorrect, or a serious program error occurred.
            // "oficially" give-up on this dog;
               zStat.OnError(ng, RfcCode);
               retries = NULL;
               
               // Check our too-much count;
               too_much++;
               if(too_much > 25)
                  return false;

               // Go to the next one, if we can;
               if(bForward)
                  aT.StatStart++;
               else
                  aT.StatStart--;
            continue;
            }
         }
      else
         {
         retries++;
         if(retries > 10)
            {
            // "oficially" give-up on this dog;
            zStat.OnBufferError(ng, stdOut);
            retries = NULL;

            // Check our too-much count;
            too_much++;
            if(too_much > 25)
               return false;

            // Go to the next one, if we can;
            if(bForward)
               aT.StatStart++;
            else
               aT.StatStart--;
            continue;
            }
         }
      } // ewhile
   return true;
   }
bool Rfc977NewsGroupServer::Get(NewsGroup& ng, Array<EMailMessage>& rResult, Array<ArticleThunk>& rIn, EMailFilter *pQ)
   {
   // Keep the thrashing to a minimum;
   if(rResult.NumZombies() < rIn.Nelem())
      rResult.AddZombies(rIn.Nelem());

   // Collect the beasties;
   // ng.get_failed = ng.get_success = NULL;
   for(size_t which = NULL; which < rIn.Nelem(); which++)
      {
      if(zStat.ShouldAbort() == true)
         {
         zStat.OnUserAbortProcessed();
         return false;
         }

      EMailMessage Em;

      ArticleThunk& aT  = rIn[which];

      if(Get(ng, Em, aT) == true)
         {
         //ng.get_success++;
         if(pQ)
            {
            if(pQ->Qualifies(Em) == true)
               {
               rResult[rResult.Nelem()] = Em;
               zStat.OnArticleMatched(ng, Em, *pQ);
               }
            else
               zStat.OnArticleRejected(ng, Em, *pQ);
            }
         else
            {
            zStat.OnArticleMatched(ng, Em);
            rResult[rResult.Nelem()] = Em;
            }
         }
      else
         {
         zStat.OnArticleRejected(ng, Em);
         //ng.get_failed++;
         }
      } // for
   return true;
   }
bool  Rfc977NewsGroupServer::Get(NewsGroup& ng, EMailMessage& em, ArticleThunk& aThunk)
   {
   BEGIN
   // Blank out any previous result;
   EMailMessage    em2;
   em     = em2;
   END

   stringstream is;
   // This sets-up aThunk.ArticleDownloaded() as required;
   br = GetMagicBuffer(ng, aThunk, is);
   if(br == false)
      {
      zStat.OnError(ng, aThunk);
      return br;
      }

   is.seekg(0, ios::beg);
   br = em.Parse(is);
   if(br == false)
     {
     zStat.OnBadArticleBuffer(ng, aThunk, em);
     return br;
     }

   ng.LastArticleRead(aThunk);
   zStat.OnNewsGroupObject(ng, em, aThunk);

   return true;
   }
bool Rfc977NewsGroupServer::Post(const EMailMessage& email, ZStr& sError)
   {
   EMailMessage em = email;
   bool br = false;
   sError = "POST: ";


   ZStr str, stc;

   str = "post\r\n";
   br = soc.Transact(str, stc);
   if(!br)
      {
      sError.Append("No response to POST request.");
      return br;
      }

   RfcStatusCode RfcCode;
   if(RfcCode.Assign(stc) == true)
      if(RfcCode.Code() != 340)
         {
         sError.Append(stc);
         return false;
         }

   stc.Assign(em.Newsgroups());
   if(!stc.IsNull())
      {
      str.Assign("Newsgroups: ");
      str.Append(stc);
      str.Append("\r\n");
      br = soc.Send(str);
      if(!br)
         {
         sError.Append("Send(Newsgroups:) failed.");
         return br;
         }
      }


   stc.Assign(em.From());
   if(!stc.IsNull())
      {
      str.Assign("From: ");
      str.Append(stc);
      str.Append("\r\n");
      br = soc.Send(str);
      if(!br)
         {
         sError.Append("Send(From:) failed.");
         return br;
         }
      }


   stc.Assign(em.Subject());
   if(!stc.IsNull())
      {
      str.Assign("Subject: ");
      str.Append(stc);
      str.Append("\r\n");
      br = soc.Send(str);
      if(!br)
         {
         sError.Append("Send(Subject:) failed.");
         return br;
         }
      }

   if(soc.Send("\r\n") == false)
      {
      sError.Append("Send(MESSAGE_TEXT_START) failed.");
      return false;
      }

   Array<ZStr> aLines;
   br = EMailFactory::ListBody(em, aLines);
   for(size_t ss = 0L; ss < aLines.Nelem(); ss++)
      {
      br = soc.Send(aLines[ss]);
      if(!br)
         {
         sError.Append("Send(MESSAGE_TEXT) failed.");
         return br;
         }
      }
   aLines.Free();

   str = "\r\n.\r\n";
   br = soc.Transact(str, stc);
   if(!br)
      {
      sError.Append("Article \"dot\" termination failed. Article might not have been posted by server.");
      return br;
      }

   if(RfcCode.Assign(stc) == true)
      if(RfcCode.Code() != 240)
         {
         sError.Append(stc);
         return false;
         }

   sError = "";
   return br;
   }

// NOTE: 'MORE' is never used. Commands are assumed to produce a contiguous response;
bool  Rfc822Server::TransactRfcOrDottedResponse(const ZStr& sCmd, ZStr& sResult)
   {
   bool br = soc.Transact(sCmd, sResult);
   if(br)
      {
      // If we have an RfcStatusCode, then we are done, too;
      RfcStatusCode RfcCode;
      if(RfcCode.Assign(sResult) == true)
         {
         switch(sResult[0])
            {
            case '1': //    1xx - Informative message
               break;
            case '2': //    2xx - Command ok (Either got garbage back, or we're legally done);
            case '3': //    3xx - Command ok so far, send the rest of it.
            case '4': //    4xx - Command was correct, but couldn't be performed for some reason.
            case '5': //    5xx - Command unimplemented, or incorrect, or a serious program error occurred.
            default:
               return true;
            }
         }
      }
   while(br && (isdotmagic(sResult) == false))
      {
      ZStr sBuf;
      br = soc.Receive(sBuf);
      sResult.Append(sBuf);
      }
   return br;
   }

bool  Rfc977NewsGroupServer::GetMagicBuffer(NewsGroup& ng, ArticleThunk& at, stringstream& sResult)
   {
   // The default;
   at.ArticleDownloaded(false);

   if(!(pwNewsGroup == ng))
      if(Connect(ng) == false)
         return false;

   // Call out the EXACT article that we are looking for (preference to  thunk's number)
   str = "";
   if(at.Number())
      str << "ARTICLE " << at.Number()    << "\r\n";
   else
      str << "ARTICLE " << at.MessageId() << "\r\n";

   int first_one               = 1;
   int put_packet_retry_times  = 0;
   int get_packet_retry_times  = 0;
   while(zStat.ShouldAbort() == false)
      {
      // ********
      // * STEP *
      // EXTRACT THE PACKET FROM THE SOCKET (includes rational timeout-handling)

      // A time-out on SEND is actually very common, since the socket driver might very well
      // TIMEOUT on us under Windows: NNTP activity seems to fail to be noticed as "activity"!
      // Maybe this behavior could be avoided by paying attention to some type of a KEEPALIVE
      // socket-level protocol? Who knows! -As mail_t as we have the ArticleThunk.Id(), and can
      // resume a download from THAT point, this isn't a very large problem...
      if(Put(str) == false)
         {
#ifdef MOO_MOO_CHECK
         SocketTraceOn();
#endif
         switch(put_packet_retry_times)
            {
            case 0:
            case 1:
             put_packet_retry_times++;
             continue;
            default:
               {
               zStat.OnTimeoutDeath(ng, at, put_packet_retry_times);
               return false;
               }
            }
         }

      // ********
      // * STEP *
      // GET the response.
      if(zStat.ShouldAbort() == true)
         continue;

      bool br = Rfc822Server::Get(str);
      if(br == false)
         {
#ifdef MOO_MOO_CHECK
         SocketTraceOn();
#endif
         // This is an elegant way to make sure we that we are not "hung"
         // on a "more", while waiting to download an existing article:
         // WE JUST ASK FOR THE WHOLE DARN THING OVER AGAIN if a threshold
         // of "get_packet_retry_times" has not yet expired;
         switch(get_packet_retry_times)
            {
            // SEND OKAY, THEN RECEIVE PACKET ERROR / TIME OUT, LOGIC;
            // =======================================================
            case 0:     // second time
            case 1:     // third time
            case 2:     // fourth time
               // Always assume that time-out is a more serious error. Ask for the
               // article again, by name. -This is to keep us from getting "hung"
               // on an unexpected "more";
               if(!first_one)
                  {
                  // Junk the present article && ask for it over again, by name;
                  str = "";
                  if(at.Number())
                     str << "ARTICLE " << at.Number() << "\r\n";
                  else
                     str << "ARTICLE " << at.MessageId() << "\r\n";
                  sResult.seekp(0, ios::beg);
                  }
               get_packet_retry_times++;
               continue;
            default:
               {
               zStat.OnTimeoutDeath(ng, at, get_packet_retry_times);
               return false;
               }
            }
         }  // ewhile(FLASE)

      // ********
      // * STEP *
      // Packet received okay, check the NNTP codes.
      get_packet_retry_times = 0;

      // Check the return code on the first_one;
      if(first_one)
         {
         switch(str[0])
            {
            case '2':         // article found...
               {
               at.Error("");

               // First packet will have the NNTP result line in it. We need to remove it;
               long sp = str.Find('\n');
               if(size_t(sp) != npos)
                  str.RemovePos(0, sp);
               }
            break;
            case '4':
            // An error of this type is either an article withdrawn, the end of the
            // enumeration, or a concidental positioning of an ASCII character at
            // the [0] position (I've seen it happen!). Either way, we'll count it as
            // the same error and re-try;
            // Observed: "483 NEWNEWS temporarily disabled due to load" in both slave and non-slave modes.
            // Observed: "423 Bad article number"
            case '5':
            default:
               {
               RfcStatusCode RfcCode;
               if(RfcCode.Assign(str) == true)
                  {
                  zStat.OnError(ng, RfcCode);
                  return false;
                  }
               sResult << str.c_str();
               sResult << ends;
               at.Error(str);
               zStat.OnBufferError(ng, at, str);
               return false;
               }
            }
         }  // first_one

      // ********
      // * STEP *
      // Looks official, build the article, block-by-block;
      br = isdotmagic(str);
      first_one = 0;
      sResult << str.c_str();
      if(br == true)
         break;            // We're done! (normal exit point)

      str = MORE_STRING;   // "MORE"
      }
   sResult << ends;

   if(zStat.ShouldAbort() == true)
     {
     zStat.OnUserAbortProcessed();
     return false;
     }

   at.ArticleDownloaded(true);
#ifdef MOO_MOO_CHECK
   SocketTraceOff();
#endif
   return true;
   }

bool SmtpServer::Connect(HostName& hn, UserData& ud)
   {
   // Added on 08/17/2002, R. Nagy
   bool bUseHelo = true;
   ZStr str;
   ud.SetError(str);
   hn.SetError(str);
   ZStr sx = ud.Domain();
   if(sx.IsNull())
      {
      bUseHelo = false;
      //str = "LocalError: SMTP HELO protocol requires a domain name [RFC821].";
      //ud.SetError(str);
      //hn.SetError(str);
      //return false;
      }

   if(Rfc822Server::Connect(hn) == false)
      {
      Socket soc;
      str = soc.GetLastError();
      str.Prepend("Socket: Cannot connect to HOST: ");
      ud.SetError(str);
      hn.SetError(str);
      return false;
      }

   // 08/17/2002, R. Nagy
   if(bUseHelo == false)
      return true;

/*****
   ZStr sHelp;
   if(Transact("HELP\r\n", sHelp) == false)
      {
      ud.SetError(sHelp);
      hn.SetError(sHelp);
      return false;
      }
*****/

   // Some servers (like outgoing.verizon.net) support EHLO...
   str = ud.Domain();
   str.Prepend("EHLO ");
   str.Append("\r\n");
   ZStr sResult;
   ServerType st;
   st.server_type_code = st.smtp();
   if(TransactCodeLevel(str, sResult, 2) == false)
      {
      ud.SetUserAuthorization("", st);
      str = ud.Domain();
      str.Prepend("HELO ");
      str.Append("\r\n");
      ZStr sResult;
      if(TransactCodeLevel(str, sResult, 2) == false)
         {
         ud.SetError(sResult);
         hn.SetError(sResult);
         return false;
         }
      }
   else
      {
      // Store the supported authorazition encoding types -
      size_t whence = sResult.Find("AUTH ");
      if(whence != NPOS)
         {
         ZStr sResult2 = &sResult[whence];
         whence = sResult.Find('\r');
         if(whence != NPOS) 
            sResult2.Remove(whence);
         ud.SetUserAuthorization(sResult2, st);
         }
      }
   /*
   RFC 1869 prohibits all extensions except (1) extensions defined by the IETF 
   and (2) extensions beginning with the letter X. However, some servers use 
   private extensions that do not begin with the letter X. In any case, clients 
   must be prepared for unrecognized extensions; the IETF may define new extensions 
   at any time. Extensions generally apply to a single connection. If the client 
   reconnects to the same host a minute later, it may find a completely different 
   list of extensions. 

   Extensions are supposed to be interpreted without regard to case. In practice 
   extensions are always sent in uppercase. I don't know if there are clients that 
   have trouble with lowercase.

               Extension name index
               The following list shows all the extensions that I've seen from SMTP servers. 
               ----------------------------------------------------------------------------
               8BITMIME 
               ATRN 
               AUTH 
               AUTH=LOGIN 
               BINARYMIME 
               CHUNKING 
               DSN 
               ENHANCEDSTATUSCODES 
               ENHANGEDSTATUSCODES [sic] 
               ETRN 
               EXPN 
               HELP 
               ONEX 
               PIPELINING 
               RSET 
               SAML 
               SEND 
               SIZE 
               SOML 
               TIME 
               TLS 
               TURN 
               VERB 
               VRFY 
               X-EXPS 
               X-EXPS=LOGIN 
               X-LINK2STATE 
               X-RCPTLIMIT 
               X-TURNME 
               XADR 
               XAUD 
               XDSN 
               XEXCH50 
               XGEN 
               XONE 
               XQUE 
               XREMOTEQUEUE 
               XSTA 
               XTRN 
               XUSR 
               XVRB    
    
   */
   if(Connect(ud) == false)
      {
      Disconnect(hn);
      return false;
      }
   return true;
   }
void SmtpServer::Disconnect(HostName& hn)
   {
   ZStr sResult; 
   Transact("QUIT\r\n", sResult); 
   Rfc822Server::Disconnect(hn);
   }
bool SmtpServer::Connect(UserData& ud)
   {
   // 08/17/2002, R. Nagy 
   ZStr str;
   str = ud.Authorize(*this);
   if(str.IsNull())
      {
      ConnectedUser = ud;
      return true;
      }
   return false;
   }
void SmtpServer::Disconnect(UserData&)
   {
   }
   /*
bool SmtpServer::Post(const EMailFactory& obm, ZStr& sError)
   {
   EMailMessage emOut;
   emOut = obm;
   emOut._to      = obm.email.To();
   emOut._from    = obm.email.From();
   return Post(emOut, sError);
   }
   */
bool SmtpServer::Post(const EMailMessage& email, ZStr& sError)
   {
   ZStr str, sResult;
   str = "MAIL FROM:<";
   str.Append(email.From());//ConnectedUser.User());
   str.Append(">\r\n");
   if(Transact(str, sResult) == false)
      return false;
   RfcStatusCode RfcCode;
   if(RfcCode.Assign(sResult) == false)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }
   if(RfcCode.Code() != 250)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }

   str = email.To();
   str.Prepend("RCPT TO:<");
   str.Append(">\r\n");
   if(Transact(str, sResult) == false)
      return false;
   if(RfcCode.Assign(sResult) == false)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }
   if(RfcCode.Code() != 250)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }

   str = "DATA";
   str.Append("\r\n");
   if(Transact(str, sResult) == false)
      return false;

   if(RfcCode.Assign(sResult) == false)
      {
      zStat.OnError(email, RfcCode);
      Transact("\r\n.\r\n", sResult);
      zStat.OnError(email, sResult);
      return false;
      }
   if(RfcCode.Code() != 354)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }

   Array<ZStr> aLines;
   bool br = EMailFactory::List(email, aLines);
   for(size_t ss = 0L; ss < aLines.Nelem(); ss++)
      {
      br = Put(aLines[ss]);
      if(br == false)
         {
         zStat.OnError(email, "Send-data failed.");
         // WARNING: Conversation is now in an unknown state!
         // We assume that the connection has been lost, else
         // we need to terminate (as above).
         return false;
         }
      };

   if(Transact("\r\n.\r\n", sResult) == false)
      return false;
   if(RfcCode.Assign(sResult) == false)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }
   if(RfcCode.Code() != 250)
      {
      zStat.OnError(email, RfcCode);
      return false;
      }   
   return true;
   }
bool Pop3Server::Connect(UserData& ud)
   {
   // 08/17/2002: We must keep the Kaled race pure...
   ServerType st;
   st.server_type_code = st.pop3();
   ud.SetUserAuthorization("", st);
   ZStr str;
   str = ud.Authorize(*this);
   if(str.IsNull())
      return true;
   return false;
   }
void Pop3Server::Disconnect(UserData& ud)
   {
   ZStr sError;
   Transact("QUIT\r\n", sError);
   }


bool Pop3Server::RemoveFromServer(Array<PopId>& array)
   {
   PopId def;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(array[ss].szPos == def.szPos)
         continue;   // gigo
      if(DeleteArticle(array[ss].szPos) == false)
         return false;
      }
   return true;
   }

bool Pop3Server::Get(const Directory& dirSave, const ZStr& sType, bool bRemoveFromServer)
   {
   ZStr str;

   // STEP
   // ****
   // Set up our download location
   if(dirSave.Exists() == false && dirSave.Create() == false)
      {
      stringstream srm;
      srm << "Error: Unable to create " << dirSave.Name();
      zStat.OnVerbose(PRESTO(srm));
      return false;
      }

   // STEP
   // ****
   // Prime the loop with the number of articles avaialble NOW
   size_t szStat;
   if(StatArticles(szStat) == false)
      return false;
   if(!szStat)
      return true;

   // STEP
   // ****
   // DOWNLOAD EVERY ARTICLE IN THE MAILBOX.
   // DELETE EVERYTHING EXTRACTED FROM THE HOST IF REQUESTED.
   Array<PopId> array;
   for(size_t ss = NULL; ss < szStat; ss++)
      {
      BEGIN
      stringstream srm;
      srm << "Attempting buffer capture for article " << ss;
      srm << ends;
      zStat.OnVerbose(PRESTO(srm));
      END

      bool br = GetMagicBuffer(ss+1, str);
      if(br == false)
         {
         stringstream srm;
         srm << "ERROR: Unable to download article #";
         srm << ss+1;
         srm << " from HOST.";
         srm << ends;
         zStat.OnVerbose(PRESTO(srm));
         if(bRemoveFromServer)
            {
            stringstream srm2;
            if(RemoveFromServer(array))
               srm2 << "CLEANUP: Removed " << array.Nelem() << " downloaded articles from host...";
            else
               srm2 << "CLEANUP: UNABLE TO REMOVE downloaded articles from host!";
            zStat.OnVerbose(PRESTO(srm2));
            }
         return false;
         }

      zStat.OnVerbose("Article buffer captured.");

      // STEP:
      // *****
      // Save the message buffer to a TEMP file for RFC822 parse / rename (next)
      File fileTEMP;
      if(dirSave.Home(fileTEMP) == false)
         zStat.OnVerbose("WARNING: Unexpected Home(temp) error!");
      fileTEMP.MkUniqueName(dirSave, sType);
      BEGIN
      stringstream srm;
      srm << "Temporarily saving buffer as `" << fileTEMP.Name() << "`...";
      srm << ends;
      zStat.OnVerbose(PRESTO(srm));
      END
      str.Write(fileTEMP.OpenWrite(File::AT_BINARY));
      fileTEMP.Close();
      str = "";

      // STEP:
      // *****
      // Rename the file - from the RFC822 portions of the HEADER
      EMailHeader emh;
      if(EMailFactory::Import(fileTEMP, emh) == true)
         {
         // 02/11/2007 - Server was timing out - Rename is a lot faster than parse!
         // Since we ARE using the RFC as the default i/o format, all we
         // need to do is to RENAME it.
         // 01/10/2008: Changed to MkLocalSubjectName (was MkLocanName())
         File fileLocal = EMailFactory::MkLocalName(dirSave, emh.Subject(), sType);
         if(fileTEMP.Rename(fileLocal) == false)
            {
            stringstream srm;
            srm << "WARNING: MkLocalName(" << fileTEMP.Name() << ") FAILED.";
            zStat.OnVerbose(PRESTO(srm));
            }
         else
            {
            stringstream srm;
            srm << "Buffer renamed to `" << fileTEMP.Name() << "`.";
            srm << ends;
            zStat.OnVerbose(PRESTO(srm));
            }
         }
      else
         {
         stringstream srm;
         srm << "WARNING: RFC822 EMailHeader.Import(" << fileTEMP.Name() << ") FAILED.";
         zStat.OnVerbose(PRESTO(srm));
         }

      // email._pop3_server_id = ss+1;
      array.Append(PopId(ss+1));
      } // efor

      // STEP
      // ****
      // FILES SECURED ON CLIENT:
      // We are free to delete the items from the server, if that's what
      // the user requested (default);
      if(bRemoveFromServer)
         {
         stringstream srm;
         srm << "CLEANUP: " << array.Nelem() << " articles ";
         if(RemoveFromServer(array))
            srm << " removed from host.";
         else
            srm << " UNABLE TO BE COMPLETELY REMOVED from host!";
         zStat.OnVerbose(PRESTO(srm));
         }
      return true;
   }
bool Pop3Server::GetMagicBuffer(size_t which, ZStr& sResult)
   {
   EMailMessage email;
   ZStr str;
   BEGIN
   stringstream srm;
   srm << "RETR ";
   srm << which;
   srm << "\r\n";
   srm << ends;
   str = PRESTO(srm).c_str();
   END

   zStat.OnVerbose("RETR start.");
   bool br = Transact(str, str);
   if(br == false)
      {
      str.Prepend("Error: RETR command returned: ");
      zStat.OnError(email, str);
      return br;
      }
   zStat.OnVerbose("RETR completed.");

   size_t sz = str.Find("+OK ");
   if(sz == NPOS)
      {
      str.Prepend("Error: Unknown RETR response: ");
      zStat.OnError(email, str);
      return false;
      }
   zStat.OnVerbose("RETR result okay.");

   // OBSERVED: Some times, on Windows98 ONLY (no joke)
   // RETR returns the entire message, while same code
   // and server combination did not do so on Windows2000!
   sz = str.Find("\r\n");
   if(sz != NPOS)
	  str.RemovePos(0, sz+2);      // Chomp the RETR message
   sResult = str; 
   if(isdotmagic(sResult) == true)
      {
      zStat.OnVerbose("Server returned the ENTIRE message on RETR!");
      }
   else
      {
      zStat.OnVerbose("Attempting Get(1).");
      if(Rfc822Server::Get(str) == false)
         {
         zStat.OnError(email, "Error: Get(1) failed.");
         return false;
         }
      zStat.OnVerbose("Get(1) okay.");
      sResult.Append(str); 
      while(isdotmagic(sResult) == false)
         {
         zStat.OnVerbose("No dot magic: Attempting Get(2).");
         str = "\r";     // Be sure to select a shorter time-out (see Get())
         if(Rfc822Server::Get(str) == false)
            {
            stringstream srm;
            srm << "Error: Get(2) failed. Results follow;"            << endl;
            srm << "/RESULTS[" << sResult << "]RESULTS\\"             << endl << endl;
            srm << "/ERRORRESULTS[" << str << "]ERRORRESULTS\\"       << endl;
            zStat.OnError(email, PRESTO(srm));
            return false;
            }
         zStat.OnVerbose("Get(2) okay.");
         sResult.Append(str);
         }
      }


   zStat.OnVerbose("Properly terminated message buffer successfully retrieved from host.");
   return true;
   }
bool Pop3Server::DeleteArticle(size_t which)
   {
   ZStr str;
   BEGIN
   stringstream srm;
   srm << "DELE ";
   srm << which;
   srm << "\r\n";
   srm << ends;
   str = PRESTO(srm).c_str();
   END

   zStat.OnVerbose("DELE start.");
   bool br = Transact(str, str);
   if(br == false)
      {
      EMailMessage email;
      str.Prepend("Error: DELE command returned: ");
      zStat.OnError(email, str);
      return br;
      }
   zStat.OnVerbose("DELE command returned.");

   size_t sz = str.Find("+OK");
   if(sz == NPOS)
      {
      EMailMessage email;
      str.Prepend("Error: Unknown DELE response: ");
      zStat.OnError(email, str);
      return false;
      }
   zStat.OnVerbose("DELE command successful.");

   return true;
   }
bool Pop3Server::StatArticles(size_t& sz)
   {
   ZStr str;
   zStat.OnVerbose("STAT start.");
   bool br = Transact("STAT\r\n", str);
   if(br == false)
      {
      EMailMessage email;
      str.Prepend("Error: STAT command returned: ");
      zStat.OnError(email, str);
      return false;
      }
   zStat.OnVerbose("STAT command completed.");

   sz = str.Find("+OK ");
   if(sz == NPOS)
      {
      EMailMessage email;
      str.Prepend("Error: Unknown STAT response: ");
      zStat.OnError(email, str);
      return false;
      }
   zStat.OnVerbose("STAT command okay.");

   str.RemovePos(0, 4);
   sz = str.Find(' ');
   if(sz == NPOS)
      {
      EMailMessage email;
      str.Prepend("Error: Unknown STAT response: ");
      zStat.OnError(email, str);
      return false;
      }

   zStat.OnVerbose("STAT command successful.");
   str = str.Substr(0, sz);
   sz = atoi(str.c_str());

   return true;
   }
bool Pop3Server::Download(PopX& popx, ExeLog& sLog)
   {
   return Download(popx.host, popx.user, popx.dir, sLog, popx.bDelete, popx.bVerbose);
   }
bool Pop3Server::Download(HostName& host, UserData& user, const Directory& dir, ExeLog& sLog, bool bDelete, bool bVerbose)
   {
   bool br = false;
   Pop3Server server;
   server.Use(sLog);
   server.SetVerbose(bVerbose);
   br = server.Connect(host);
   if(br == false)
      {
      stringstream srm;
      srm << "Unable to connect to host " << host.Name();
      sLog.Log(PRESTO(srm));
      return false;
      }
   br = server.Connect(user);
   if(br == false)
      {
      stringstream srm;
      srm << "Unable to connect to host " << host.Name() << " as " << user.User();
      sLog.Log(PRESTO(srm));
      return false;
      }

   br = server.Get(dir, ".EML", bDelete);
   if(br == false)
      {
      // TODO: Setup automatic recovery (etc?)
      }

   server.Disconnect(user);
   server.Disconnect(host);

   return br;
   }

