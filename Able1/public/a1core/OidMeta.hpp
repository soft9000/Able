// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidMT_Hpp
#define StdOidMT_Hpp

namespace Able1
{
// Used to override teh default delmiters used to pars StdOid definitions
namespace Oid
{
struct OidMeta
   {
   DelimiterSet delim;

   OidMeta(const ZStr& sON = DEFAULT_BLOCKON, const ZStr& sOFF = DEFAULT_BLOCKOFF, const ZStr& sSEP = DEFAULT_SEP, const ZStr& sEQ = DEFAULT_EQ);
   bool Use(const OidTag& oidTag);
   ostream& Write(ostream& os);
   istream& Read(istream& is);
   };
} // namespace Oid
} // namespace Able1

#endif
