#ifndef z_MimeConentIdzz
#define z_MimeConentIdzz

#include <Able1.hpp>
using namespace Able1;

namespace BetterMail {

struct MimeContentId
   {
   // RFC 2045, Page 11 
   enum ContentMajor // AKA "Type"
      {
      maNone,        // discrete-type
      maImage,       // discrete-type
      maText,        // discrete-type
      maApplication, // discrete-type
      maMessage,     // composite-type
      maMultipart,   // composite-type
      //maAudio,
      //maVideo
      } contentMajor;
   enum ContentMinor // AKA "Format"
      {
      miNone,
      miPlain,
      miHtml,
      miGif,
      miJpeg,
      //miMpeg,
      //miMsword,
      //miQuicktime,
      miAlternative  // Content-ID has special semantics in the multipart/alternative media type.  See RFC 2046.
      } contentMinor;


   MimeContentId(void);
   MimeContentId(ContentMajor ma, ContentMinor mi) {contentMajor = ma; contentMinor = mi;}

   bool IsNull(void) const;
   const char *Query(ZStr& sResult);

   static MimeContentId Parse(const File& file);
   static MimeContentId Parse(const ZStr& sMimeContentString);
   static ZStr     Compose(const MimeContentId& refId);
};

inline ostream& operator << (ostream& os, const MimeContentId& ref)
   {
   os << MimeContentId::Compose(ref);
   return os;
   }

}
#endif

