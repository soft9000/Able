#ifndef EMailAddress_hpx
#define EMailAddress_hpx

#include <Able1.hpp>
using namespace Able1;

class EMailAddress
{
   // Examples;
   //    "From: Rusty Alderson <cessna@phoenix.net>"  (classic RFC)
   //    "Rusty Alderson\tcessna@phoenix.net"         (whitespace separated)
   ZStr sUserName;
   ZStr sHostAccount;

   bool      IsNull(void) const;
   bool      Parse(const ZStr& sss);
   ZStr Compose(void);

   static bool Parse(const ZStr& sLine, Array<EMailAddress>& aResult, char chSep = ';');
};


#endif
