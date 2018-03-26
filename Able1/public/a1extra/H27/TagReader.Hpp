// TagReader.HPP: Classes to handle the parsing and rendering of
// HTML-style (i.e: "<tagged> ... </tagged>") definitions.
//
// 04/15/2000  Created, R. Nagy
// 06/25/2008: Moved into new namespace + signatures normalized. - H27, R. Nagy
//
#ifndef Tag_Reader_Hpp
#define Tag_Reader_Hpp


#include <Able1.hpp>
using namespace Able1;

namespace H27
{

// NOTE: THESE CLASSES WILL NOT YET HANDLE RECURSIVE TAGS.
// (recursed paragraphs, etc).
//
// NOTE: CASE SENSITIVITY NEEDS TO BE REMOVED.
// (<P> .. </p> as a defined tag-pairing will not be recognized (etc)).
//
class GenericTagParser;
class SpecificTagLocator;


class GenericTagParser
{
protected:
   ZStr sTag;
   ZStr sTagContents;

   bool TAG(istream& is, ZStr& sPrefix, ZStr& sToken);

   virtual bool FindTagStart(istream& is);
   virtual bool FindTagEnd(istream& is);

public:
   GenericTagParser(void)                  {}
   virtual ~GenericTagParser(void)         {}

   const char *GetTagKey(ZStr& std)        {std = sTag; return std.c_str();}
   const char *GetTagContents(ZStr& std)   {std = sTagContents; return std.c_str();}

   bool Parse(istream& is);
};


class SpecificTagLocator : public GenericTagParser
{
protected:
   SpecificTagLocator(void)                   {}

   virtual bool FindTagStart(istream& is);

public:
   SpecificTagLocator(const ZStr& sKey)  {sTag = sKey;}
   virtual ~SpecificTagLocator(void)          {}

   void SetTagKey(const ZStr& std)            {sTag = std;}
};



inline 
bool GenericTagParser::TAG(istream& is, ZStr& sPrefix, ZStr& sToken)
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
bool GenericTagParser::FindTagStart(istream& is)
   {
   sTagContents = "";
   sTag         = "";

   ZStr sPrefix, sToken;

   sToken = "/";
   while(sToken[0] == '/')    // *GENERIC HTML TAG BECOMES THE TARGET
      {
      if(TAG(is, sPrefix, sToken) == false)
         return false;
      if(!is)
         return false;
      }

   sTag = sToken;
   return true;
   }
inline
bool GenericTagParser::FindTagEnd(istream& is)
   {
   sTagContents = "";
   ZStr sPrefix, sToken;
   
   // Here is the token that we are looking for;
   ZStr sPat;
   sPat = "/";
   sPat.Append(sTag);
   while(sToken.Find(sPat) == NPOS)
      {
      if(TAG(is, sPrefix, sToken) == false)
         return false;
      if(!is)
         return false;
      sTagContents.Append(sPrefix);
      }
   return true;
   }
inline
bool GenericTagParser::Parse(istream& is)
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
bool SpecificTagLocator::FindTagStart(istream& is)
   {
   ZStr sActual = sTag;
   sTag = "";
   while(sTag != sActual)
      {
      if(GenericTagParser::FindTagStart(is) == false)
         {
         sTag = sActual;
         return false;
         }
      }
   return true;
   }

} // namespace
#endif
