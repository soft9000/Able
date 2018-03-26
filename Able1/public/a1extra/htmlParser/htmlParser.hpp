// Class htmlParser: Designed to Read same. This class is the new base for all
// parsing of tagged grammers.
//
// 10/19/2000, Class created tonight while teaching first "java class" in Chicago, R. Nagy
// 10/23/2000, Debugged, tested, and working 100%, R. Nagy
// 09/16/2003, Fixed bugs in htmlBlock::Read() & re-worked internal representation, R. Nagy
//             Also removed htmlBlock parentage, and mapped to ANSI `bool` usage.
//
// NOTE: The htmlTag class detects the location of all <> delimited tokens.
// The pattern for the token in the file is called a `key`. 
//
// Once tags are detected, the htmlBlock uses them to extract what is in *between* 
// a tagged pair. What is between two tags is known as "body content".
//
// Note that the tags (keys) DO NOT have to match or be paired up to extract a block!
// This means that you can easily get the body content between ANY two tags.
//
#ifndef html_Block
#define html_Block

#include "TagReader.Hpp"

class htmlTag;
class htmlBlock;
class htmlParser;


class htmlTag
{
protected:
   long stStart;
   ZStr sKey;            // This the the KEY, without any delimiters.
   ZStr sStartTag;       // This is the delimited "start key", as found in stream

public:
   htmlTag(void) : stStart(0L)             {}
   htmlTag(const htmlTag& hb)              {*this = hb;}
   virtual ~htmlTag(void)                  {}

   const char *key(void)         const     {return sKey.c_str();}
   long   posStart(void)    const     {return stStart;}
   const char *blockStart(void)  const     {return sStartTag.c_str();}

   void NormalizeKey(void)                 {sKey.ToLower();}

   bool IsNull(void)
      {
      bool br = false;
      if(stStart == (long)0L)
         br = sStartTag.IsNull();
      if(br == false)
         return false;
      return true;
      }

   htmlTag& operator=(const htmlTag& hb)
      {
      if(this == &hb)
         return *this;
      stStart      = hb.stStart;
      sKey         = hb.sKey;
      sStartTag    = hb.sStartTag;
      return *this;
      }
friend class htmlParser;
friend class htmlBlock;
};


class htmlBlock
{
protected:
   htmlTag   tagStart;
   htmlTag   tagEnd;

   ZStr sBodyContent;    // This is what was between the s/e keys.

   long posBodyStart;    // Where the payload starts
   long posBodyLength;   // Where the payload ends

   void _init(void)
      {
      posBodyStart  = 0L;
      posBodyLength = 0L;
      }

public:
   htmlBlock(void)                    {_init();}
   htmlBlock(const htmlBlock& hb)     {*this = hb;}
   virtual ~htmlBlock(void)           {}

   const char *key(void)         const{return tagStart.sKey.c_str();}
   const char *blockContents(void)    {return sBodyContent.c_str();}   

   bool Read(istream& is, const htmlTag& s, const htmlTag& e)
      {
      if(s.posStart() == e.posStart())
         return false;
      if(s.posStart() > e.posStart())
         return Read(is, e, s);
      htmlBlock blanker;
      *this = blanker;
      posBodyLength = ((long)e.posStart() - (long)s.posStart() - s.sStartTag.Length() - 1);
      posBodyStart = s.posStart() + e.sStartTag.Length();
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
   htmlBlock& operator=(const htmlBlock& hb)
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

friend class htmlParser;
};


class htmlParser
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

   // As the name says, this streams to where the next Read will return the given char; 
   bool StreamTo(const char ch, istream& is);

public:
   htmlParser(void);

	bool ExtractTag(istream& is,  htmlBlock& sResult)
      {
/* TODO 2 -cImport Recipes : This is broken - Need to research what it did, then make it work for EzGourmet uCatConveter.cpp */
      return false;
      }

   // A single tag looks like <HTML> OR </HTML>
	bool ExtractTag(istream& is,        htmlTag& sResult);
	bool ExtractTag(const ZStr&,   htmlTag& sResult);

   // In HTML, a block is delimited by a token. e.g: <HTML> </HTML>
	bool ExtractBlock(const ZStr& sKey, const htmlBlock& sInput, htmlBlock& sResult);
	bool ExtractBlock(const ZStr& sKey, istream& is,             htmlBlock& sResult);

   // Same as above, 'cept we will get them ALL; 
	bool ExtractBlocks(const ZStr& sKey, const htmlBlock& sInput, Array<htmlBlock>& sResult);

};


// This function is usefull for taking, for example, a "<BR>" block over to an array of strings; 
bool ConvertToStrings(const ZStr& sPat, const ZStr& sBlock, Array<ZStr>& aRes);

// This function will remove *ALL* of the HTML from a string;
ZStr ZapHtml(const ZStr& sBlock, const char ch1 = '<', const char ch2 = '>');
// This function will transalte the single-character codes to their 7-bit equivalent
ZStr HtmlTo7Bit(const ZStr& str);

#endif
