// TextFormatting: A place for simple text formatting tools.
//
// 08/10/2003: WordWrap Class Created. Competes with SimpleTextFlow (not part of Able1), R. Nagy
// 01/08/2005: Ported WordWrap over to Able1::TextFormatting, R. Nagy
//    Members renamed. Added a more conveniant interface.
//    Re-worked internal normalization functions for public re-use.
// 01/08/2005: Created the Words Class, R. Nagy
// 01/08/2005: Created the LinearMarkup Class, R. Nagy
//
#ifndef noj_markup_formatting_hpp
#define noj_markup_formatting_hpp

#include <Able1.hpp>

namespace TextFormatting
{
using namespace Able1;

// LinearMarkup exresses words in an HTML subset by removing all carrage control codes.
// Both the convert to, and the remove from, capability is supported.
class LinearMarkup
{
public:
   static ZStr AsGmlPage(const ZStr& str);
   static ZStr AsGmlPage(Array<ZStr>& array);
   
   static ZStr AsTextPage(const ZStr& sGmlLine);
   static ZStr RemoveHtmlTags(const ZStr& sGmlLine);
};

}

#endif
