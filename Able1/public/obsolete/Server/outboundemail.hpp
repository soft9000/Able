// 11/12/1998, Created OutboundEMail to support PostJOB1, R. Nagy
// 11/16/1998, Added FileVersion support, R. Nagy
// 05/17/1999, Now MUST use "Load()" and "Save()": Moved Read() and Write() into "protected", R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
// 06/17/2004: Added Load and Save for file objects, R. Nagy
//
#ifndef zOutBoundEmail_Hpp
#define zOutBoundEmail_Hpp
#include <obsolete/Server/Email.hpp>
#include <Extra/FileVersion.hpp>

using namespace Able1;

class EmailHeader : public FileVersion
{
public:
   EmailHeader(void) {ProductName("OBEM"); VersionName("OutBoundEmail"); VersionNumber(1.1);}
};

class OutBoundEmail
   {
   protected:
      EmailHeader header;
      EMail       email;

      ostream& Write(ostream& os)             {header.Write(os); return email.Write(os);}
      istream& Read(istream& is)              {header.Read(is);  return email.Read(is);}

   public:
      OutBoundEmail(void)                    {}
      OutBoundEmail(const OutBoundEmail& em) {*this = em;}
      virtual ~OutBoundEmail(void)           {}

      bool Load(const ZStr& sArticle);
      bool Save(const ZStr& sArticle);
      bool Load(File& file);
      bool Save(File& file);

      operator EMail&(void)                  {return email;}
      operator const EMail&(void) const      {return email;}

      bool        IsOutBoundEmailFile(const ZStr& pszfn);

      const char *From(void)         const   {return email._from.c_str();     }
      const char *To(void)           const   {return email._to.c_str();       }
      const char *Date(void)         const   {return email._date.c_str();     }
      const char *Subject(void)      const   {return email._subject.c_str();  }
      const char *Newsgroups(void)   const   {return email._newsg.c_str();    }

      bool        From(const       ZStr& psz) {email._from   = psz; return true;}
      bool        To(const         ZStr& psz) {email._to     = psz; return true;}
      bool        Date(const       ZStr& psz) {email._date   = psz; return true;}
      bool        Subject(const    ZStr& psz) {email._subject= psz; return true;}
      bool        Newsgroups(const ZStr& psz) {email._newsg  = psz; return true;}

      bool  Message(File& file);

      void  Message(const ZStr& psz)    {email.Message(psz.c_str());}
      const char *Message(void)      const   {return email.Message();}

      OutBoundEmail& operator=(const OutBoundEmail& em);
                                             
   friend class SmtpServer;
   };

inline bool OutBoundEmail::Message(File& file)
   {
   bool br = false;
   if(IsTextFile(file) == false)
      return br;
   br = email.MessagePayload(file);
   file.Close();
   return br;
   }

inline bool OutBoundEmail::Load(const ZStr& sArticle)
   {
   File file(sArticle);
   return Load(file);
   }

inline bool OutBoundEmail::Load(File& file)
   {
   istream& is =  file.OpenRead(File::AT_BINARY);
   if(!is)
      return false;
   bool br = false;
   if(Read(is))
      br = true;
   file.Close();
   return br;
   }

inline bool OutBoundEmail::Save(const ZStr& sArticle)
   {
   File file(sArticle);
   return Save(file);
   }

inline bool OutBoundEmail::Save(File& file)
   {
   file.Remove();
   Write(file.OpenWrite(File::AT_BINARY));
   file.Close();
   return file.Exists();
   }

#endif
