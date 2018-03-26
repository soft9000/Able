#ifndef MailboxProcessor_hpp
#define MailboxProcessor_hpp
// 2008/05/26: Added SneakySend(): Verizon only allows us 1000 messages and our connection is poor, R. Nagy
//

#include <a1mail/INetRFC.hpp>
#include <a1mail/MailboxRed.hpp>

namespace BetterMail
   {
enum ProcState
   {
   ProcMoveOut,
   ProcLeaveAlone,
   ProcDeadLetter
   };

struct MessageProcessor
   {
   virtual ProcState OnProcess(const File& file, ExeLog& log) = 0;
   };

   
class MailboxProcessor
   {
   private:
      static int  SneakySend(MailboxRed& mbox, HostName& host, UserData& user, ExeLog& log);
   public:
      static bool SendAll(MailboxRed& mbox, HostName& host, UserData& hostUser, ExeLog& log);
      static bool ReceiveAll(MailboxRed& mbox, HostName& host, UserData& hostUser, ExeLog& log);
      static bool ProcessInbox(MailboxRed& mbox, MessageProcessor& proc, ExeLog& log);
   };

   }
#endif
