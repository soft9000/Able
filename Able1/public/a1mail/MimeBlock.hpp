
#ifndef z_MimeBlock
#define z_MimeBlock

#include <a1mail/EMail.hpp>
#include <a1mail/MimeContentId.hpp>

namespace BetterMail {

class EMimeMessage;

class MimeBlock
   {
   private:
      ZStr     sContent;
      static MimeBlock Parse(const ZStr& message);
      static Array<ZStr> aPrefix;

   public:
      MimeContentId contentId;

      ZStr     RawContent(void);  // unincoded (mime encoded)
      ZStr     Content(void);
      void          Content(const ZStr& sContent);

      MimeBlock(void);
      MimeBlock(MimeContentId::ContentMajor ma, MimeContentId::ContentMinor mi, const ZStr& str)
         {
         sContent = str;
         contentId = MimeContentId(ma, mi);
         }

      static bool      Decode(const EMailMessage& message, Array<MimeBlock>& mimeBody);
      static bool      Encode(EMailMessage& message, const Array<MimeBlock>& mimeBody);
   };

   }
#endif

