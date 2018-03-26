#include "MailboxRed.hpp"

using namespace BetterMail;

MailboxRed::MailboxRed(void)
{
HomeDefault();
}

bool MailboxRed::Move2Sub(const Directory& dirBase, const File& fff, const ZStr& sSub)
   {
   File file = fff;
   if(file.Exists() == false)
      return false;

   stringstream srm;
   StdDateTime sdt;
   srm << sSub;
   srm << ".";
   srm << sdt.Year();
   srm << ".";
   srm << sdt.Month();
   srm << ".";
   srm << sdt.DayOfMonth();
   ZStr sName = srm.str().c_str();
   Directory dir;
   if(dir.Name(sName) == false)
      return false;
   if(dirBase.Home(dir) == false)
      return false;
   if(dir.Exists() == false)
      if(dir.CreateDirectoryTree() == false)
         return false;

   File file2 = file;
   if(dir.Home(file2) == false)
      return false;
   while(file2.Exists())
      file2.MkUniqueName(dirBase);

   if(file.CopyTo(file2) == false)
      return false;
   if(file.Remove() == false)
      return false;
   return file2.Exists();
   }

bool MailboxRed::SaveTo(const Directory& ddd, EMailMessage& mail, const ZStr& sSuffix)
   {
   Directory dirBase = ddd;
   if(dirBase.Exists() == false)
      if(dirBase.CreateDirectoryTree() == false)
         return false;

   File file = EMailFactory::MkLocalName(dirBase, mail, sSuffix);
   if(file.IsNull())
      return false;

   unsigned iss = 0;
   unsigned loopy = 0;
   ZStr sNode = file.QueryNode();
   while(file.Exists() == true)
      {
      // Try some prefixed numbers -
      stringstream srm;
      srm << iss++ << '.' << sNode;

      if(file.Name(PRESTO(srm)) == false)
         return false;

      if(dirBase.Home(file) == false)
         return false;

      if(iss == 0)
         {
         // Bump the numbering system out a level ...
         loopy++;
         stringstream srm;
         srm << 0 << "." << sNode;
         sNode = PRESTO(srm);
         if(loopy == 0)
            return false;  // it is now officially absurd -
         }
      }
   return mail.Export(file);
   }
bool MailboxRed::SaveTo(const Directory& ddd, EMailMessage& mail)
   {
   return SaveTo(ddd, mail, ".eml");
   }
bool MailboxRed::MoveToProcessed(const Directory& dirBase, const File& mail)
   {
   return Move2Sub(dirBase, mail, "Processed");
   }
bool MailboxRed::MoveToUnProcessed(const Directory& dirBase, const File& mail)
   {
   return Move2Sub(dirBase, mail, "UnProcessed");
   }
bool MailboxRed::Home(const Directory& dir)    // Set the home directory
   {
   ZStr str = dir.Name();
   if(inbox.pwFolder.Name(str + PathChar() + "inbox") == false)
      return false;
   if(outbox.pwFolder.Name(str + PathChar() + "outbox") == false)
      return false;
   pwFolder = dir;
   return true;
   }
bool MailboxRed::HomeDefault(void)   // Default location -
   {
   ProgramId pid;
   Directory dir;
   pid.GetProgram(dir);
   ZStr sName = dir.Name();
   sName.Append(PathChar());
   sName.Append("MailboxRed");
   dir.Name(sName);
   return Home(dir);
   }
bool MailboxRed::HomeGlobal(void)   // Production location -
   {
   Directory dir;
   // Hardcode okay - We can upgrade this when we need
   // to (multi-box LAN processing, etc.)
   if(dir.Name("C:\\MailboxRed") == false)
      return false;
   if(dir.Exists() == false && dir.Create() == false)
      return false;
   return Home(dir);
   }
void MailboxRed::QueryIni(Array<File>& aAccounts)
   {
   aAccounts.Empty();
   Array<File> aFiles;
   pwFolder.Query(aFiles);
   aAccounts.AddZombies(aFiles.Nelem());
   ZStr str;
   for(size_t ss = 0L; ss < aFiles.Nelem(); ss++)
      {
      str = aFiles[ss].QueryNode(str);
      str.ToLower();
      if(str.EndsWith(".ini"))
         aAccounts.Append(aFiles[ss]);
      }
   }

bool MailboxRed::QueryProcessed(const MailboxRed& ref, Directory& dir)
   {
   dir.Name("Processed");
   ref.pwFolder.Home(dir);
   return true;
   }
bool MailboxRed::QueryUnProcessed(const MailboxRed& ref, Directory& dir)
   {
   dir.Name("UnProcessed");
   ref.pwFolder.Home(dir);
   return true;
   }

