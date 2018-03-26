#ifndef EmailMessage_Hpx
#define EmailMessage_Hpx

#include <a1mail/EMailHeader.hpp>
#include <a1mail/MimeBlock.hpp>

namespace BetterMail {

class EMailMessage : public EMailHeader
   {
   private:
      bool   ParseMessageBody(ifstream& is);     // Rfc822 format (BODY ONLY)

   protected:
      ZStr   _text;

      // If you dare to use these, you simply *MUST* make sure that your
      // stream is in BINARY MODE since \r\n is by definition what TERMINATE is!!
      ostream& WriteStream(ostream& os) const; // NATIVE / BINARY
      istream& ReadStream(istream& is);        // NATIVE / BINARY

      bool     rfc_Write(ostream& ofs) const;   // RFC
      bool     rfc_Read(istream& ifs);          // RFC

      bool     rfc_message(istream& ifs);      // BODY ONLY ..?

      ostream&  Write_searchable(ostream& os);

   public:
      EMailMessage(void)                       {}
      EMailMessage(const EMailMessage& em)     {(*this) = em;}
      virtual ~EMailMessage(void)  {}

      bool   IsNull(void)   const;

      bool   ParseMessageBody(const File& file); // Now, only RFC ASCII... but later, who knowns?
      bool   ParseMessageBody(stringstream& is); // Rfc822 format (BODY ONLY)

      bool           HasBody(void) const;
      const char *   Body(void) const                {return _text.c_str();}
      bool           Body(const ZStr& msg)      {_text.Assign(msg); return true;}
      bool           Decode(Array<MimeBlock>& array) {return MimeBlock::Decode(*this, array);}
      bool           Encode(Array<MimeBlock>& array) {return MimeBlock::Encode(*this, array);}

      int            operator==(const EMailMessage& em) const;
      EMailMessage&  operator=(const EMailMessage& em);

      // Streamable (array compatible) format
      ostream& Write(ostream& os) const    {return WriteStream(os);}
      istream& Read(istream& is)           {return ReadStream(is);}

      // Streamable (array compatible) format
      bool Load(const File& file);
      bool Save(const File& file) const;

      // RFC Format - one per file / stream
      bool Import(const File& file);
      bool Export(const File& file) const;
      bool Import(istream& is);
      bool Export(ostream& os ) const;

      static bool EncodeHTML(EMailMessage& ref, const ZStr& sHtmlMessage);

   friend class EMailAND;
   friend class EMailOR;
   friend class EMailFactory;
   friend class EMailModifier;
   friend class Pop3Server;
   friend class SmtpServer;
   friend class EMailAndOrNot;
   friend class EMailFilter;
   friend class EMailAndOrNotExtended;
   friend class MimeBlock;
   friend class EMimeMessage;
   };

}

#endif

