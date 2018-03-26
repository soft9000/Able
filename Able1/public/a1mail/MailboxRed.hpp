#ifndef MailboxRed_hpx
#define MailboxRed_hpx

#include <a1mail/EMail.hpp>
namespace BetterMail
{
// This is just a mail box manager. No send / receive operaitons supported
// =====
// WHY GENERATE A UNIQUE EMAIL FOR EACH USER?
// So we can add user-specified PREMIUM features some day!
//
// Pop3Batch allows us to save a collection into a single file. While fine for
// fully automated / robotic message processing, using a Mailbox (like MailboxRed)
// allows email to be stored in a more user-maintainable format.
//
// Default structure is:
// =======
// {ExeDir}/MailboxRed
//       Location of all ini files (e.g. MailServerIni) and log files
// {ExeDir}/MailboxRed/inbox
//       Location of the inbox (downloaded - POP) items - Can be forced elsewhere
// {ExeDir}/MailboxRed/outbox
//       Location of the outbox (SMTP) items - Can be forced elsewhere
// {ExeDir}/MailboxRed/{in}|{out}box/{Un}Processed.yyyy.mm.dd
//       Optional locations of workflown items (robotic processing result archives)
//
// NOTE: Directories are only created when required
// NOTE: While we can force either the inbox or the outbox to be anywhere else,
// the home directory always contains the accounts - use Home to manage that,
// then force any overrides
//
class MailboxRed
   {
   private:
      Directory pwFolder;

   public:
      static bool MoveToProcessed(const Directory& dirBase, const File& mail);
      static bool MoveToUnProcessed(const Directory& dirBase, const File& mail);
      static bool SaveTo(const Directory& dirBase, EMailMessage& mail);
      static bool SaveTo(const Directory& dirBase, EMailMessage& mail, const ZStr& sSuffix);
      static bool Move2Sub(const Directory& dirBase, const File& file, const ZStr& sSub);

      MailboxRed(void);

      class anon {
         protected:
            Directory pwFolder;

         public:
            // Active -
            void Query(Array<File>& aFiles)           {pwFolder.Query(aFiles);}
            void Query(Directory& dir)                {dir = pwFolder;}
            void Set(const Directory& dir)            {pwFolder = dir;}
            bool SaveTo(EMailMessage& mail)           {return MailboxRed::SaveTo(pwFolder, mail);}
            bool SaveTo(EMailMessage& mail, const ZStr& sSuffix)
                                                      {return MailboxRed::SaveTo(pwFolder, mail, sSuffix);}

            // Archive -
            bool MoveToProcessed(const File& mail)    {return MailboxRed::MoveToProcessed(pwFolder, mail);}
            bool MoveToUnProcessed(const File& mail)  {return MailboxRed::MoveToUnProcessed(pwFolder, mail);}

            friend class MailboxRed;
         } inbox, outbox;

      static bool QueryProcessed(const MailboxRed& ref, Directory& dirBase);
      static bool QueryUnProcessed(const MailboxRed& ref, Directory& dirBase);
      
      // NOTE: The ini fles, inbox, and the outbox are normally located
      // underneath a single home directory. Default is under the EXE
      // folder. In production we need to use a UNIFIED SINGLE location.
      bool Home(const Directory& dir); // User-defined location
      bool HomeDefault(void);          // Default location -
      bool HomeGlobal(void);           // Production location -

      // Overide the Home for the configuration files
      void SetIni(const Directory& dir)       {pwFolder = dir;}
      void QueryIni(Array<File>& aAccounts);

      // Overide the Home for the inbox and / or outbox
      void SetInbox(const Directory& dir)     {inbox.Set(dir);}
      void SetOutbox(const Directory& dir)    {outbox.Set(dir);}

      friend struct inbox;
      friend struct outbox;
   };
}
#endif

