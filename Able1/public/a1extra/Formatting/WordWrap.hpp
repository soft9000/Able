// TextFormatting: A place for simple text formatting tools.
//
// 08/10/2003: WordWrap Class Created. Competes with SimpleTextFlow (not part of Able1), R. Nagy
// 01/08/2005: Ported WordWrap over to Able1::TextFormatting, R. Nagy
//    Members renamed. Added a more conveniant interface.
//    Re-worked internal normalization functions for public re-use.
// 01/08/2005: Created the Words Class, R. Nagy
// 01/08/2005: Created the LinearMarkup Class, R. Nagy
// 12/26/2005: Split classes out - One class per file / header set, R. Nagy
//    Added a few new Wrapping functions, R. Nagy
// 05/01/2006: Changed a few legacy int-s to size_t-s, R. Nagy
//
//
#ifndef noj_word_wrap_hpp
#define noj_word_wrap_hpp

#include <Able1.hpp>

namespace TextFormatting
{
using namespace Able1;


class WordWrap
{
public:
   // This function demands a simple (unix) formatted string.
   static ZStr  WrapNormalized(const ZStr& str, int cx = 0, int margin = 0, int maxLen = 55);

public:
   enum TextType
      {
      tt_dos,
      tt_unix,
      tt_other
      };

   // This function accepts text with any type of ASCII newline termination - DOS, UNIX, or Mac
   static Array<ZStr> Wrap(const ZStr& str, int cx = 0, int margin = 0, int maxLen = 55);

   // This functions takes anything - returns the format that you request -
   static ZStr  Wrap(const ZStr& str, TextType tt, int cx = 0, int margin = 0, int maxLen = 55);

   // This functions takes anything - returns SimpleString format -
   static ZStr  WrapUnix(const ZStr& str, int cx = 0, int margin = 0, int maxLen = 55);

   // This functions takes anything - returns DosString format -
   static ZStr  WrapDos(const ZStr& str, int cx = 0, int margin = 0, int maxLen = 55);

   // Convert conflicting newline conventions to a simple (unix normal) format. Returns the encoded pattern found.
   static TextType  AsSimpleString(ZStr& str);
   static ZStr AsSimpleString(const ZStr& str)
      {
      ZStr sResult = str;
      AsSimpleString(sResult);
      return sResult;
      }

   // Convert normalized (unix) newlines to Windows/DOS (\r\n) format
   static void      AsDosString(ZStr& str);
   static ZStr AsDosString(const ZStr& str)
      {
      ZStr sResult = str;
      AsDosString(sResult);
      return sResult;
      }

};


}

#endif
