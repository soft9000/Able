// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidC_Hpp
#define StdOidC_Hpp


namespace Able1
{

namespace Oid
{
// Newline independant - Definable parsing tokens - Mixed record types -
// Human Editable - Default Format is "ObjectName {TAG=VALUE; TAG=VALUE; ...}"
//
// NOTE: At this point, nested blocks require different delimiters at each
// nesting level. While fine for now, eventually we should use StdOid::Block
// to "peel away" the nesting so as to allow the same tokens to be used
// throughtout the entire block.
//
class OidController
   {
   public:
      static bool Load(const File& file, OidList& aResult, ZStr& sError);
      static istream&  Read(istream& is, OidList& oidList, ZStr& sError);
      static istream&  Read(istream& is, OidList& oidList, const OidMeta& oid, ZStr& sError);

      static bool Save(const File& file, const OidList& oidList);
      static ostream&  Write(ostream& os, const OidList& oidList);
      static ostream&  Write(ostream& os, const OidList& oidList, const OidMeta& oid);

      // Looks for a set of OBJECT NAMES in a list. True if any are found.
      static bool ListObject(const ZStr sObjName, const OidList& oidList, OidList& aResult, bool bIgnoreCase = true);

      static bool Test(void);
   };


} // namespace Oid
} // namespace Able1

#endif
