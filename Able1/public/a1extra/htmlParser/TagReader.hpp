// TagReader.HPP: Classes to handle the parsing and rendering of
// HTML-style (i.e: "<tagged> ... </tagged>") definitions.
//
// 04/15/2000  Created, R. Nagy
// 
#ifndef Tag_Reader_Hpp
#define Tag_Reader_Hpp


#include <Able1.hpp>
using namespace Able1;


// NOTE: THESE CLASSES WILL NOT YET HANDLE RECURSIVE TAGS.
// (recursed paragraphs, etc).
//
// NOTE: CASE SENSITIVITY NEEDS TO BE REMOVED.
// (<P> .. </p> as a defined tag-pairing will not be recognized (etc)).
//
class HTML_GenericTagParser;
class HTML_SpecificTagLocator;


class HTML_GenericTagParser
{
protected:
   ZStr sTag;
   ZStr sTagContents;

   bool HTML_TAG(istream& is, ZStr& sPrefix, ZStr& sToken);

   virtual bool FindTagStart(istream& is);
   virtual bool FindTagEnd(istream& is);

public:
   HTML_GenericTagParser(void)                  {}
   virtual ~HTML_GenericTagParser(void)         {}

   const char *GetTagKey(ZStr& std)        {std = sTag; return std.c_str();}
   const char *GetTagContents(ZStr& std)   {std = sTagContents; return std.c_str();}

   bool Parse(istream& is);
};


class HTML_SpecificTagLocator : public HTML_GenericTagParser
{
protected:
   HTML_SpecificTagLocator(void)                   {}

   virtual bool FindTagStart(istream& is);

public:
   HTML_SpecificTagLocator(const ZStr& sKey)  {sTag = sKey;}
   virtual ~HTML_SpecificTagLocator(void)          {}

   void SetTagKey(const ZStr& std)            {sTag = std;}
};



inline 
bool HTML_GenericTagParser::HTML_TAG(istream& is, ZStr& sPrefix, ZStr& sToken)
   {
   long sp = is.tellg();

   sPrefix = "";
   sToken  = "";
   sPrefix.Readline(is, '<');
   if(!is)
      {
      is.seekg(sp);
      return false;
      }
   sToken.Readline(is, '>');
   if(!is)
      {
      is.seekg(sp);
      return false;
      }
   return true;
   }
inline
bool HTML_GenericTagParser::FindTagStart(istream& is)
   {
   sTagContents = "";
   sTag         = "";

   ZStr sPrefix, sToken;

   sToken = "/";
   while(sToken[0] == '/')    // *GENERIC HTML TAG BECOMES THE TARGET
      {
      if(HTML_TAG(is, sPrefix, sToken) == false)
         return false;
      if(!is)
         return false;
      }

   sTag = sToken;
   return true;
   }
inline
bool HTML_GenericTagParser::FindTagEnd(istream& is)
   {
   sTagContents = "";
   ZStr sPrefix, sToken;
   
   // Here is the token that we are looking for;
   ZStr sPat;
   sPat = "/";
   sPat.Append(sTag);
   while(sToken.Find(sPat) == NPOS)
      {
      if(HTML_TAG(is, sPrefix, sToken) == false)
         return false;
      if(!is)
         return false;
      sTagContents.Append(sPrefix);
      }
   return true;
   }
inline
bool HTML_GenericTagParser::Parse(istream& is)
   {
   if(FindTagStart(is) == false)
      return false;
   if(FindTagEnd(is) == false)
      return false;
   if(!is)
      return false;
   return true;
   }
inline
bool HTML_SpecificTagLocator::FindTagStart(istream& is)
   {
   ZStr sActual = sTag;
   sTag = "";
   while(sTag != sActual)
      {
      if(HTML_GenericTagParser::FindTagStart(is) == false)
         {
         sTag = sActual;
         return false;
         }
      }
   return true;
   }

#endif
