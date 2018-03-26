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
#ifndef HtmlBlock_hpp
#define HtmlBlock_hpp

#include <Able1.hpp>
using namespace Able1;

namespace H27
{

class HtmlTag;
class HtmlBlock;
class HtmlParser;


class HtmlBlock
{
protected:
   HtmlTag   tagStart;
   HtmlTag   tagEnd;

   ZStr sBodyContent;    // This is what was between the s/e keys.

   long posBodyStart;    // Where the payload starts
   long posBodyLength;   // Where the payload ends

   void _init(void)
      {
      posBodyStart  = 0L;
      posBodyLength = 0L;
      }

public:
   HtmlBlock(void)                    {_init();}
   HtmlBlock(const HtmlBlock& hb)     {*this = hb;}
   virtual ~HtmlBlock(void)           {}

   const char *Key(void)         const{return tagStart.sKey.c_str();}
   const char *blockContents(void)    {return sBodyContent.c_str();}

   bool read(istream& is, const HtmlTag& s, const HtmlTag& e)
      {
      if(s.PosStart() == e.PosStart())
         return false;
      if(s.PosStart() > e.PosStart())
         return read(is, e, s);
      HtmlBlock blanker;
      *this = blanker;
      posBodyLength = ((long)e.PosStart() - (long)s.PosStart() - s.sStartTag.Length() - 1);
      posBodyStart = s.PosStart() + e.sStartTag.Length();
      is.seekg(posBodyStart);
      sBodyContent.Read(is, (size_t)posBodyLength);
      tagStart        = s;
      tagEnd          = e;
      return true;
      }
   bool IsNull(void)
      {
      bool br = sBodyContent.IsNull();
      if(br == false)
         return false;
      return true;
      }
   HtmlBlock& operator=(const HtmlBlock& hb)
      {
      if(this == &hb)
         return *this;
      tagStart     = hb.tagStart;
      tagEnd       = hb.tagEnd;
      sBodyContent = hb.sBodyContent;
      posBodyStart = hb.posBodyStart;
      posBodyLength= hb.posBodyLength;
      return *this;
      }

friend class HtmlParser;
};

} // namespace

#endif
