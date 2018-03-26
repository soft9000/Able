// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidTest_Hpx
#define StdOidTest_Hpx



namespace Able1
{

namespace Oid
{
// The official parameter query
class OidParamTest : public OidSender
   {
   public:
      OidParamTest(void);

      // ("CLIENT") Responds to the USE()d query
      bool Respond(const OidTag& oidTag);

      // ("SERVER") Requests a response to a named object + property list
      static bool Query(const File& fileClient, OidTag& oidResult, int iSec);
   };
} // namespace Oid
} // namespace Able1

#endif
