// Class HtmlParser: Designed to read same. This class is the new base for all
// parsing of tagged grammers.
//
// 10/19/2000, Class created tonight while teaching first "java class" in Chicago, R. Nagy
// 10/23/2000, Debugged, tested, and working 100%, R. Nagy
// 09/16/2003, Fixed bugs in HtmlBlock::read() & re-worked internal representation, R. Nagy
//             Also removed HtmlBlock parentage, and mapped to ANSI `bool` usage.
//
// NOTE: The HtmlTag class detects the location of all <> delimited tokens.
// The pattern for the token in the file is called a `key`.
//
// Once tags are detected, the HtmlBlock uses them to extract what is in *between*
// a tagged pair. What is between two tags is known as "body content".
//
// Note that the tags (keys) DO NOT have to match or be paired up to extract a block!
// This means that you can easily get the body content between ANY two tags.
//
// 06/25/2008: Moved into new namespace + signatures normalized. - H27, R. Nagy
//
#ifndef HtmlParser_hpp
#define HtmlParser_hpp

#include "TagReader.Hpp"
#include "HtmlTag.Hpp"
#include "HtmlBlock.hpp"

namespace H27
{
class HtmlParser
{
private:
   ZStr sToken, eToken;

protected:
   // MarkStartStreamPast returns the START position of sKey, but streams past it;
   bool MarkStartStreamPast(istream& is, const ZStr& sKey, long& st1);

   // snarfit copies the range from the stream into the string;
   bool snarfit(istream& is, ZStr& sResult, long spStart, long spEnd);

   // DumpToAppend dumps the present position of the stream to the end of the string until (and including) 'ch'; 
   void DumpToAppend(const char ch, istream& is, ZStr& std);

   // As the name says, this streams to where the next read will return the given char; 
   bool StreamTo(const char ch, istream& is);

public:
   HtmlParser(void);

	bool ExtractTag(istream& is,  HtmlBlock& sResult)
      {
/* TODO 2 -cImport Recipes : This is broken - Need to research what it did, then make it work for EzGourmet uCatConveter.cpp */
      return false;
      }

   // A single tag looks like <HTML> OR </HTML>
	bool ExtractTag(istream& is,        HtmlTag& sResult);
	bool ExtractTag(const ZStr&,   HtmlTag& sResult);

   // In HTML, a block is delimited by a token. e.g: <HTML> </HTML>
	bool ExtractBlock(const ZStr& sKey, const HtmlBlock& sInput, HtmlBlock& sResult);
	bool ExtractBlock(const ZStr& sKey, istream& is,             HtmlBlock& sResult);

   // Same as above, 'cept we will get them ALL; 
	bool ExtractBlocks(const ZStr& sKey, const HtmlBlock& sInput, Array<HtmlBlock>& sResult);

};


// This function is usefull for taking, for example, a "<BR>" block over to an array of strings; 
bool ConvertToStrings(const ZStr& sPat, const ZStr& sBlock, Array<ZStr>& aRes);

// This function will remove *ALL* of the HTML from a string;
ZStr ZapHtml(const ZStr& sBlock, const char ch1 = '<', const char ch2 = '>');
// This function will transalte the single-character codes to their 7-bit equivalent
ZStr HtmlTo7Bit(const ZStr& str);

} // namespace

#endif
