// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidQRY_Hpp
#define StdOidQRY_Hpp


namespace Able1
{
namespace Oid
{
// A handy wrapper to support the parsing and use of command-line objects.
// See OidParamQuery for an example.
class OidSender
   {
   private:
      OidSender(void) {};

   protected:
      OidTag oidRef;

   public:
      OidSender(const ZStr sObjectName1) {oidRef.Name(sObjectName1);}

      // ("CLIENT") Returns true if the string is the name of YOUR query
      bool IsObject(const ZStr& sCmdLineName);

      // ("CLIENT") Set-up the instance for a response.
      // Assignment. Returns true if the OidTag is YOUR query
      bool Use(const OidTag& oidTag);

      // ("SERVER") Sends a named object + property list. No response.
      static bool Submit(const File& fileClient, const OidTag& oidResult);
   };
} // namespace Oid
} // namespace Able1

#endif
