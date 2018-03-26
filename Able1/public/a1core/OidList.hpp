// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidL_Hpp
#define StdOidL_Hpp


namespace Able1
{

namespace Oid
{
// Used to easily search and manage a list of StdOid properties
//
// NOTE: At this point, nested blocks require different delimiters at each
// nesting level. While fine for now, eventually we should use StdOid::Block
// to "peel away" the nesting so as to allow the same tokens to be used
// throughtout the entire block.
//
class OidList
   {
   private:
      ZStr GetUniqueObject(const ZStr sObjName, const ZStr sFieldName, bool bIgnoreCase = true);

   public:
      Array<OidTag> aTags;

      OidList(void)
         {
         }

      OidList(const Array<OidTag>& array) : aTags(array)
         {
         }

      OidList& operator=(const Array<OidTag>& array)
         {
         aTags = array;
         return *this;
         }

      void Empty(void)
         {
         aTags.Empty();
         }

      void Append(const OidTag& oid)
         {
         aTags.Append(oid);
         }

      size_t Nelem(void)
         {
         return aTags.Nelem();
         }

      // Find the first NAMED OBJECT. -1L on not found
      size_t FindFirst(const ZStr sObjName, OidTag& oidTag, bool bIgnoreCase = true);

      // Find the next NAMED OBJECT. -1L on not found
      // NOTE: Enumeration will restart if ssPos == -1L ...
      size_t FindNext(const ZStr sObjName, OidTag& oidTag, size_t ssPos, bool bIgnoreCase = true);

      // Lookup a UNIQUE Object.Field setting in a list.
      // Returns NULL if NF ~OR~ both OBJECT and FIELD are not unique!
      ZStr GetUniqueField(const ZStr& sObjName, const ZStr sFieldName, bool bIgnoreCase = true);
      bool      SetUniqueField(const ZStr& sObjName, const ZStr sFieldName, const ZStr& sValue, bool bIgnoreCase = true);

      // Find a ~UNIQUELY~ NAMED OBJECT.
      // 0 = not found           (oidTag is null)
      // 1 = found ONLY one      (oidTag is populated)
      // 2 = more than one found (oidTag is null)
      int    FindUnique(const ZStr sObjName, OidTag& oidTag, bool bIgnoreCase = true);
   };

} // namespace Oid
} // namespace Able1;

#endif
