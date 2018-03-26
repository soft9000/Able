// TextFormatting: A place for simple text formatting tools.
//
// 08/10/2003: WordWrap Class Created. Competes with SimpleTextFlow (not part of Able1), R. Nagy
// 01/08/2005: Ported WordWrap over to Able1::TextFormatting, R. Nagy
//    Members renamed. Added a more conveniant interface.
//    Re-worked internal normalization functions for public re-use.
// 01/08/2005: Created the Words Class, R. Nagy
// 01/08/2005: Created the LinearMarkup Class, R. Nagy
// 12/26/2005: Split classes out - One class per file / header set, R. Nagy
//
#ifndef noj_words_formatting_hpp
#define noj_words_formatting_hpp

#include <Able1.hpp>

namespace TextFormatting
{
using namespace Able1;

class Words
{
public:
   // Formats the block into a series of "record" (sentance) format(s).
   static Array<ZStr> AsSentances(const ZStr& sWords);

   // Formats the string as a SINGLE flowing block of text (paragraph)
   static Array<ZStr> AsParagraph(const ZStr& sWords, int cx = 0, int margin = 0, int maxLen = 55);

   // Formats the string as SEVERAL flowing blocks of paragraph delimited (\n\n) blocks (page)
   static Array<ZStr> AsPage(const ZStr& sWords, int cx = 0, int margin = 0, int maxLen = 55);

   // Formats the array into an unformatted block (no newlines) of single-spaced words.
   static ZStr AsBlock(const Array<ZStr>& array);
};

}

#endif
