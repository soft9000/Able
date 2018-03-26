#include <a1mail/EMailFactory.hpp>
#include <a1mail/EMailLines.hpp>

void _CleanFileName(ZStr& str, bool bAllowPathChars = false)
{
str.MkWhite();
str.Strip();
for(size_t ss = NULL; ss < str.Length(); ss++)
   {
   switch(str[ss])
      {
      case '\\':
         if(bAllowPathChars == true)
            continue;
      case ':':
         if((bAllowPathChars == true) && ss == 1)
            continue;
      case '<':
      case '>':
      case '*':
      case '?':
      case '/':
      case '\"':
         str[ss] = '_';
      default:
         continue;
      }
   }
}


using namespace BetterMail;

bool EMailFactory::IsEMailFactoryFile(const File& file)
   {
   EMailHeader msgResult;
   bool br = msgResult.Load(file);
   if(br == false)
      br = msgResult.Import(file);
   return br;
   }

bool EMailFactory::Load(const File& fff, EMailMessage& msgResult)
   {
   return msgResult.Load(fff);
   }

bool EMailFactory::Save(const File& fff, EMailMessage& msgResult)
   {
   return msgResult.Save(fff);
   }

bool EMailFactory::Export(const File& fff, EMailMessage& msgResult)       // binary format
   {
   return msgResult.Export(fff);
   }

bool EMailFactory::Import(const File& fff, EMailMessage& msgResult)       // binary format
   {
   return msgResult.Import(fff);
   }


bool EMailFactory::Import(const File &fff, EMailHeader& header)
   {
   File file = fff;
   if(!file.Exists())
      return false;

   bool br = header.rfc_Read(file.OpenRead(File::AT_BINARY));

   // No matter what the result is, this is what we were asked to Read;
   // header.SetLocalName(file.Name());
   return br;
   }

bool EMailFactory::Export(const File& fff, EMailHeader& header)
   {
   return header.Export(fff);
   }
bool EMailFactory::RemoveTerminalDot(EMailMessage& emb)
   {
   ZStr str = emb.Body();
   size_t pos = str.Rfind("\r\n.");
   if(pos == str.Length() - 4)
      {
      str.Remove(pos);
      emb.Body(str);
      return true;
      }
   return false;
   }
void EMailFactory::EncodeDots(EMailMessage& emb)
   {
   ZStr str = emb.Body();
   if(str.Replace("\r\n.\r\n", "\r\n..\r\n"))
      emb.Body(str);
   }
void EMailFactory::DecodeDots(EMailMessage& emb)
   {
   ZStr str = emb.Body();
   if(str.Replace("\r\n..\r\n", "\r\n.\r\n"))
      emb.Body(str);
   }
bool EMailFactory::MkLogicalName(File& file, const EMailHeader& emh, const ZStr& sExtension, bool TryMessageID)
   {
   ZStr str;

   if(TryMessageID)
      {
      str = emh.MessageID();      // THIS IS OUR LEGACY. USED TO BE THE DEFAULT.
      str.MkWhite();              // OBSERVED
      str.Strip();
      }

   // If there is NO message id (i.e. if it is outgoing email)
   if(str.IsNull() || (str.Length() <= 2))
      {
      // If there is a single recipient, then try to use that as the root name
      str = emh.To();
      if(str.Find(';') != NPOS || str.Find(',') != NPOS)
         str = emh.Subject(); // else go with the subject -

      // If neither single user subject (very unusual!)
      if(str.IsNull() || str.IsSpace())
         {
         ZStr scmp;
         str = "Posted on ";
         scmp = emh.Date();
         if(scmp.IsNull())
            str.Append("unknown date");
         else
            str.Append(scmp);
         str.Append(" from ");
         scmp = emh.From();
         if(scmp.IsNull())
            {
            // This may look nuts, but it happens!
            scmp = emh.InternetPath();
            if(scmp.IsNull() || scmp.IsSpace())
               str.Append("unknown source");
            else
               str.Append(scmp);
            }
         else
            str.Append(scmp);
         }
      }

   _CleanFileName(str);

   if(str.EndsWith(sExtension) == false)
      str.Append(sExtension);

   // Validate the NEW file name -
   Directory dir;
   file.Query(dir);
   if(file.Name(str) == false)
      return false;
   dir.Home(file);
   return true;
   }

// Like MkLocalName, but favors the string provided (emh.Subject(), etc.)
File EMailFactory::MkLocalName(const Directory& dir, const ZStr& sNodeRoot, const ZStr& sExtension)
   {
   ZStr sFileRoot = sNodeRoot;
   sFileRoot += sExtension;
   _CleanFileName(sFileRoot);

   File file;
   dir.Home(file);

   if(sFileRoot.IsNull())
      {
      file.MkUniqueName(dir, sExtension); // Failsafe works with the extension -
      return file;
      }

   if(file.Name(dir, sFileRoot) == false)
      {
      file.MkUniqueName(dir, sExtension); // Failsafe works with the extension -
      return file;
      }

   // NO HEADER TO INSPECT
   // Rule here is that if what we have alReady exists, then we use a number series -
   return File::MkGenerationName(dir, file);
   }

File EMailFactory::MkLocalName(const Directory& dir, EMailHeader& em, const ZStr& sExtension)
   {
   File file;
   dir.Home(file);
   // First try to make a meaningfull name from the message header -
   // Try the recipient if only one - else the subject - first -
   if(MkLogicalName(file, em, sExtension, false) == false)
      {
      // Next, try using that nasty 'ol message id -
      if(MkLogicalName(file, em, sExtension, true) == false)
         {
         // Finally, try the file's own posix-based ability -
         dir.Home(file);
         if(file.MkUniqueName(dir, sExtension) == true)
            return file;
         }
      }

   // MkLogicalName gave us a unique name - or not - Go with what we have ...

   // Does what we have alReady exist?
   unsigned iCount = 0;
   File filePre = file; // the base name
   while(file.Exists())
      {
      // STEP: We have a file with that name - Is it the same message?
      EMailHeader emh;
      bool br = emh.Load(file);
      if(br == false)
         br = emh.Import(file);
      if(br == true)
         {
         // IF the header is the same, then the content is the same .... SO
         // IF the header is the same, then the file name should be the same, too -
         if(em == emh)
            return file;
         }

      // STEP: Not the same message - Lets keep going with the standard prefixes -
      iCount++;
      if(!iCount) // wrap - not likley - but all the same - could happen - some day -
         {
         dir.Home(file);
         file.MkUniqueName(dir, sExtension); // Failsafe works with the extension -
         return file;
         }
      stringstream srm;
      srm << iCount << "." << filePre.QueryNode();
      file.Name(PRESTO(srm));
      dir.Home(file);
      }
   return file;
   }
bool EMailFactory::IsAddressSeparator(char ch)
   {
   switch(ch)
      {
      case '<':
      case '>':
      case ' ':
      case '\t':
      case '\n':
      case '\r':
      case ',':
      case ';':   // Microsoft does this...
         return true;
      }
   return false;
   }
bool EMailFactory::AbsEmailAddress(ZStr& str)
   {
   // It happens that people have newlines and other unspeakable
   // nasties in their email addresses. Our job is simply to make
   // the best guess here;
   str.MkWhite();

   // Okay: Now we can assume a somewhat tangendental reality;
   size_t whence = str.Find('@');
   if(whence == NPOS)
      return false;

   size_t start = whence;
   while(start)
      {
      if(IsAddressSeparator(str[start]) == true)
         {
         start++;
         break;
         }
      start--;
      }
   str = &str[start];   // save start point

   size_t end = str.Find('@');
   while(end < str.Length())
      {
      if(IsAddressSeparator(str[end]) == true)
         {
         str.Remove(end);     // terminate (atypical)
         break;
         }
      end++;
      }
   return true;
   }
bool EMailFactory::FormatAsAddress(ZStr& str)
   {
   ZStr sHold = str;
   if(AbsEmailAddress(str) == false)
      {
      str = sHold;
      return false;
      }
   if(str.Find('<') == NPOS)     // maintenance
      {
      str.Prepend('<');
      str.Append('>');
      }
   return true;
   }
bool EMailFactory::ContainsAbsEmailAddress(const ZStr& sIn)
   {
   ZStr sOut = sIn;
   return AbsEmailAddress(sOut);
   }
bool EMailFactory::AbsEmailAddress(const ZStr& sIn, ZStr& sOut)
   {
   sOut = sIn;
   return AbsEmailAddress(sOut);
   /*
   sOut = "";
   ZStr str = sIn;
   str.MkWhite();
   str.Strip();
   size_t which = str.Rfind(' ');
   if(which != NPOS)
      {
      str = &str[which+1];
      str.Strip();
      }

   sOut = str;
   if(sOut.Find('@') == NPOS)
      return false;
   if(sOut.Find('.') == NPOS)
      return false;

   return true;
   */
   }

bool EMailFactory::List(const EMailMessage& email, Array<ZStr>& aLines)
   {
   aLines.Empty();
   EMailLines eml;
   eml.Assign(email);
   ZStr str;
   bool br = eml.FirstLine(str);
   while(br)
      {
      aLines.Append(str);
      br = eml.NextLine(str);
      }
   return true;
   }
bool EMailFactory::ListBody(const EMailMessage& email, Array<ZStr>& aLines)
   {
   aLines.Empty();
   EMailLines eml;
   eml.Assign(email.Body());
   ZStr str;
   bool br = eml.FirstLine(str);
   while(br)
      {
      aLines.Append(str);
      br = eml.NextLine(str);
      }
   return true;
   }

bool EMailFactory::OmniLoad(const File& file, EMailHeader& emx)
   {
   EMailHeader emh;
   if(emh.Load(file) == false && emh.Import(file) == false)
      return false;
   emx = emh;
   return true;
   }
bool EMailFactory::OmniLoad(const File& file, EMailMessage& emx)
   {
   EMailMessage emh;
   if(emh.Load(file) == false && emh.Import(file) == false)
      return false;
   emx = emh;
   return true;
   }

