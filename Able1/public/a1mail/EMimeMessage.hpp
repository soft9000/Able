
#ifndef EMimeMessage_hpx
#define EMimeMessage_hpx

#include <a1mail/EMailMessage.hpp>

namespace BetterMail {

class BetterMail::EMimeMessage
   {
      static bool  Encode(EMailMessage& msg);
      static bool  Decode(EMailMessage& msg);

      static bool IsSupported(const EMailHeader&);
      static bool IsMultipart(const EMailHeader&);

      static bool IsMime(const File& file);
      static bool LoadMime(const File& file, EMailMessage& result);
      static bool SaveMime(const File& file, EMailMessage& result);

      static       bool  LoadTest(EMailMessage& msg);
   public:
      static ZStr   SampleOutlookPattern(void);
   };

}

#endif

