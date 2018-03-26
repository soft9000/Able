#ifndef QuotedPrintable_hpx
#define QuotedPrintable_hpx

#include "EMail.hpp"

namespace BetterMail
{
// RFC2045: Quoted-Printable Content-Transfer-Encoding (page 18)
struct QuotedPrintable {
   static ZStr RFCStrip(const ZStr& sss, bool bMime = false);
   static ZStr Encode(const ZStr& str);
   static ZStr Decode(const ZStr& str);
};

}

#endif

