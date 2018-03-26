// Class HtmlParser: Designed to read same. This class is the new base for all
// parsing of tagged grammers.
//
// 10/19/2000, Class created tonight while teaching first "java class" in Chicago, R. Nagy
// 10/23/2000, Debugged, tested, and working 100%, R. Nagy
// 09/16/2003, Fixed bugs in HtmlBlock::read() & re-worked internal representation, R. Nagy
//             Also removed HtmlBlock parentage, and mapped to ANSI `bool` usage.
// 06/24/2008, Added ParseTag(), and Attribute array to support htmlEvents, R. Nagy
// 06/25/2008, Moved into new namespace + signatures normalized. - H27, R. Nagy
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
#ifndef HtmlTag_hpp
#define HtmlTag_hpp

#include <Able1.hpp>
using namespace Able1;

namespace H27
{

class HtmlTag;
class HtmlBlock;
class HtmlParser;


class HtmlTag
{
protected:
   long stStart;
   ZStr sKey;            // This the the KEY, without any <> delimiters, but WITH any '/'.
   ZStr sStartTag;       // This is the delimited value", as found (now 'Parsed') in stream

public:
   struct Attribute
      {
      ZStr sTag;
      ZStr sValue;
      static bool Parse(const ZStr& sOneParam, Attribute& result);
      };
      
   Array<Attribute> aAttributes;

   HtmlTag(void);
   HtmlTag(const HtmlTag& hb);
   ~HtmlTag(void);

   ZStr     Key(void)            const;   // KEY is html or /html (no < >)
   ZStr     Token(void)          const;   // TOKEN would be html  (no /)
   long     PosStart(void)       const;
   ZStr     BlockStart(void)     const;

   bool     IsComment(void)      const;   // Unary
   bool     IsUnary(void)        const;   // No '/'-end required - e.g: <br>, <hr>, <!--

   bool     IsTagStart(void)     const;   // Start of a key pairing
   bool     IsTagEnd(void)       const;   // End   of a key pairing
   bool     IsTagStartEnd(void)  const;   // Tag is UNARY, or othewise contains BOTH the start + end-tag markup

   bool     IsNull(void)         const;
   void     NormalizeKey(void);
   HtmlTag& operator=(const HtmlTag& hb);

   static bool ParseTag(const ZStr& sData, HtmlTag& tag);

/* TODO 1 -oNowhere Man -cIdle gossip : Enforce the new Attribute parsing capability - Remove this friendship! */
friend class HtmlParser;
friend class HtmlBlock;
};

} // namespace


#endif
