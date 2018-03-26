#include <a1mail/MailboxProcessor.hpp>
#include <a1mail/INetRFC.hpp>

using namespace BetterMail;


bool MailboxProcessor::SendAll(MailboxRed& mbox, HostName& host, UserData& user, ExeLog& log)
   {
   int ss = 0;
   do {
      ss = SneakySend(mbox, host, user, log);
      } while(ss == 88);
   return (bool)ss;
   }
int MailboxProcessor::SneakySend(MailboxRed& mbox, HostName& host, UserData& user, ExeLog& log)
   {
   int br = false;
   const int iMaxMessages = 999;
   SmtpServer server;
   br = server.Connect(host, user);
   if(br == false)
      {
      stringstream srm;
      srm << "Unable to connect to host " << host.Name() << " as " << user.User();
      log.Log(PRESTO(srm));
      return (int)false;
      }
   Array<File> array;
   mbox.outbox.Query(array);
   ZStr sError;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(ss == iMaxMessages)
         {
         // Get another session, please -
         br = 88;
         break;
         }
      stringstream srm;
      EMailMessage emm;
      if(emm.Import(array[ss]) == false)
         continue;
      srm << "Posting " << emm.To() << " from " << emm.From();
      br = server.Post(emm, sError);
      if(br == false)
         {
         srm << " unable to post " << array[ss].Name() << " to " << host.Name();
         log.Log(PRESTO(srm));
         log.Log(sError);
         // 2008/05/26 - Observed (Verizon) after posting 1000 messages:
         // ! ERROR: Server reports too many messages in this connection
         // (421)
         br = 88;
         break;
         }

      srm << " success.";
      br = mbox.outbox.MoveToProcessed(array[ss]);
      if(br == false)
         {
         stringstream srm;
         srm << " Unable to MOVE " << array[ss].Name() << " to processing folder!";
         log.Log(PRESTO(srm));
         continue;
         }

      log.Log(PRESTO(srm));
      br = true;
      }

   server.Disconnect(user);
   server.Disconnect(host);

   return br;
   }
bool MailboxProcessor::ReceiveAll(MailboxRed& mbox, HostName& host, UserData& user, ExeLog& log)
   {
   Directory dir;
   mbox.inbox.Query(dir);
   if(Pop3Server::Download(host, user, dir, log, true) == false)
      return false;
   return true;
   }
bool MailboxProcessor::ProcessInbox(MailboxRed& mbox, MessageProcessor& proc, ExeLog& log)
   {
   bool br = false;
   Array<File> array;
   mbox.inbox.Query(array);

   if(!array.Nelem())
      return true;   // nothing to do, all is well -

   ZStr sError;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      enum ProcState _state;
      _state = proc.OnProcess(array[ss], log);
      switch(_state)
         {
         case (ProcMoveOut):
            {
            br = mbox.inbox.MoveToProcessed(array[ss]);
            if(br == false)
               {
               stringstream srm;
               srm << "Unable to move " << array[ss].Name() << " to ProcMoveOut location!";
               log.Log(PRESTO(srm));
               }
            else
               {
               stringstream srm;
               srm << "Moved " << array[ss].Name() << " to ProcMoveOut location.";
               log.Log(PRESTO(srm));
               }
            }
         break;
         case (ProcDeadLetter):
            {
            br = mbox.inbox.MoveToUnProcessed(array[ss]);
            if(br == false)
               {
               stringstream srm;
               srm << "Unable to move " << array[ss].Name() << " to ProcDeadLetter location!";
               log.Log(PRESTO(srm));
               }
            else
               {
               stringstream srm;
               srm << "Moved " << array[ss].Name() << " to ProcDeadLetter location.";
               log.Log(PRESTO(srm));
               }
            }
         break;
         default:
         case (ProcLeaveAlone):
            {
            stringstream srm;
            srm << "ProcLeaveAlone: " << array[ss].Name() << " ...";
            log.Log(PRESTO(srm));
            br = true;
            }
         break;
         }
      }
   return br;
   }

   
