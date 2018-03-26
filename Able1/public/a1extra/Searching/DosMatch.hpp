// Class DosMatch: Expand DOS-type wildcard characters to match patterns in strings.
// NOTE: The name might say `DOS`, but the implementation is PLATFORM INDEPENDANT!!
// ====  Use where ever C++ is sold!!
//
// Class created 12/18/1999, R. Nagy
// 12/27/1999: Added test cases to intercept a few bugs that came up in EzSearch, R. Nagy.
//             Dumped the silly "Bool" usage, as it broke Borland (sigh).
// 08/09/2005: Ported over to Able1, R. Nagy
//
#ifndef DosMatch_Hpp
#define DosMatch_Hpp


#include <Able1.hpp>
using namespace Able1;


// Note: ?  matches any SINGLE character ('?' == '1', but '?' != '123') except NULL: '?' != ""
//       *  matches any pattern                                         except NULL: '*' != ""
//
// Match chars and patterns can be arbitrarily combined to create masks, eg:
//       "*.EXE", "T?.*", "F*.*", "D*.??M", (etc.): (See test program for more information).
//
// See the test cases for a good demonstration of what this class is capeable of doing for you.
//

class DosMatch
{
protected:
   size_t      MatchMaskChars(const ZStr& sString, const ZStr& sMask);
   const char *MaskPortion(const ZStr& sString, ZStr& sMask);
public:
   bool        Match(const ZStr& sPattern, const ZStr& sString);
   bool        HasWildcard(const ZStr&);
};

#endif
