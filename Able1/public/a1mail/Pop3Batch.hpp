 THIS CLASS IS OFFICIALLY OBSOLETE!

#ifndef Pop3Pathc_Hpx
#define Pop3Pathc_Hpx

#include <a1mail/RfcObjects.hpp>

namespace BetterMail
{
// Pop3Batch allows us to save a collection into a single file. While fine for
// fully automated / robotic message processing, using a Mailbox (like MailboxRed)
// allows email to be stored in a more user-maintainable format.

// Unlike news-group postings, articles in a POP3 account can be deleted PERMINATELY.
// For this reason, special care is given to these articles to insure that if the
// session terminates abnormally that we can recover WITHOUT DATA LOASS. The Pop3Batch
// is the "wrapper" that we use to ensure that data is either (1) on the server,
// or (2) on the local hard drive. WORST CASE is that items are duplicated during
// disaster recovery, but hey, that is why we have the "EMailMessage::operator=()" !
class Pop3Batch
   {
   private:
      bool                 bShouldDelete;
      size_t               ssNext;

      bool     SaveRecoveryFile(void);
      bool     ShouldRecover(void);
      bool     LoadRecoveryFile(void);

      bool     Append(EMailMessage&);
      EMailMessage *  Recall(EMailMessage *pem = NULL);

      void     Error(const ZStr& std);

      time_t   error_file_time;
      time_t   email_file_time;

      ZStr   sOutputDirectory;

   public:  // 06/16/2004, R. Nagy
      Array<StreamZStr>  rErrorArray;
      Array<EMailMessage>  rArray;

   public:
      Pop3Batch(void);
      virtual ~Pop3Batch(void);

      // EMailMessage saved via array.
      // Errors "     "    "  .
      // Returns NPOS on error, else number of items saved;
      size_t   SaveArrays(void);
      bool     LoadArray(Array<EMailMessage>& rArray);
      bool     LoadArray(Array<StreamZStr>& rArray);
      bool     ReplaceArray(Array<EMailMessage>& rArray);
      bool     ReplaceArray(Array<StreamZStr>& rArray);
      bool     HaveArraysChanged(void);

      // Each EMailMessage saved using "SaveBin" under a temp name.
      // Errors saved in "LoadArray" format (above).
      // Returns NPOS on error, else number of items saved;
      size_t   Save(void);

      // Each EMailMessage saved using "Dump" under a temp name.
      // Errors saved in "LoadArray" format (above).
      // Returns NPOS on error, else number of items saved;
      size_t   Dump(const ZStr& sExtension = ".TXT");

      // Like the above, but overrides and replaces the output directory for
      // the entire instance ...
      size_t   Export(Directory& dir, const ZStr& sExtension = ".TXT");

      // After files are downloaded and BEFORE they are removed from the server,
      // a "hardened" copy of the EMailMessage items is saved. To stop the automatic
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

// Extract a user's electronic mail from a PopServer -
struct PopX
   {
   bool      bDelete;
   Directory dir;
   BetterMail::HostName host;
   BetterMail::UserData user;

   PopX(bDelFromAcct = false) : bDelete(bDelFromAcct)
      {
      host.Port(HostName::PortPOP());
      }

   ostream& Write(ostream& os)
      {
      ZStr str;
      if(bDelete)
         str = "1";
      else
         str = 0;
      str.WriteStream(os);
      host.Write(os);
      user.Write(os);
      dir.Write(os);
      return os;
      }
   istream& Read(istream& is)
      {
      ZStr str;
      str.ReadStream(is);
      if(str == "1")
         bDelete = true;
      else
         bDelete = false;
      host.Read(is);
      user.Read(is);
      dir.Read(is);
      return is;
      }
   };

}

#endif


 
