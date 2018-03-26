// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// Default Format is
// -----------------
// Object.ID <
// UniqueTag=Value,
// ....
// >
//
// Can also be represented in a linear format (for INI usage, etc.)
// -----------------
// Object.ID {UniqueTag=Value, ... }
//
// How to override - Example
// -----------------
// .ODDOID. {
//    BLOCK.ON = "<",
//    BLOCK.OF   = ">",
//    BLOCK.SEP = ",",
//    BLOCK.EQ = "=="
// }
//
// 01/02/2007: Class created, R. Nagy
// 07/18/2007: Fixed a bug in parse() caused by trying to mess with the grow size fo the string - yikes!
//
#ifndef StdOid_Hpp
#define StdOid_Hpp

namespace Able1
{

class File;
class ZStr;
class Directory;


#define DEFAULT_META_TAG  ZStr(".StdOid.")
/** Objective was to create a updatable, newline-indepentant
  * object naming and object property specification. Purpose is to allow for
  * users to MANAGE a file full of MIXED types with heterogenous properties.
  * Properties that can be quickly read and maintained by ANY program.
  * <br>
  * <b>Over-engineered</b>, it has been moved into it's own namespace. Hope to
  * make it easier to use.
  */
namespace Oid
{
class OidTag;

struct Block
{
   ZStr sPrefix;
   ZStr sPayload;

   /** Seperates PREFIX from SUFFIX. Nested child delimiters ARE preserved. */
   static bool Parse(const ZStr& sBuffer, const ZStr& sStart, const ZStr& sEnd, Array<Block>& aResult);
   static ZStr Compose(const ZStr& sStart, const ZStr& sEnd, const Array<Block>& aResult);
};
 } // namespace Oid

} // namespace Able1


#endif
