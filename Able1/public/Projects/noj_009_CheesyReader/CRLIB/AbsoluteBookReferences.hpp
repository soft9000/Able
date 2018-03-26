// AbsoluteBookReferences: The interfaces might be cheesy, but the 
// reference that they track and maintain are absolute. While references 
// might hop around the pages, the remain absolute anchor points within the
// book itself.
//
// 04/16/2005 - Class created, R. Nagy
//
#ifndef AbsoluteBookReferences_hpp
#define AbsoluteBookReferences_hpp

#include <Able1.hpp>
#include <extra/StdReadable.hpp>

using namespace Able1;

namespace AbsoluteBookReferences
   {
   // A Line is just that - but it also is uniquely numbered
   struct Line
      {
      int         lineId;     // starts at 1 - the absolute line location - unique within any book
      ZStr   sSentance;  // the payload
      
      Line(void) : lineId(0) {}
      
      enum lineType
         {
         ty_null, ty_paragraph, ty_line
         };
         
      lineType Type(void)
         {
         if(lineId == 0)
            return ty_null;      // valid lines start with 1 -
         if(sSentance.IsNull())
            return ty_null;
         if(sSentance == "\n\n")
            return ty_paragraph;
         return ty_line;            
         }
         
      bool IsNull(void)
         {
         if(Type() == ty_null)
            return true;
         return false;            
         }
      static ZStr mkSegment(Line& refLine, size_t maxlen)
         {
         return StdReadable::mkSegment(refLine.sSentance, maxlen);
         }
      };

   // a Quote has start and end points - even if they are the same
   struct Quote
      {
      Line lrStart;
      Line lrEnd;
      
      // comments, categories - anything - but stream format, please...
      ZStr sPayload;

      bool IsNull(void)
         {      
         if(lrStart.IsNull() && lrEnd.IsNull())
            {
            if(sPayload.IsNull())
               return true;
            }
         return false;
         }
      
      };

   // A Citation is a Quote that includes book and author information
   struct Citation
      {
      ZStr sBook;
      ZStr sAuthor;
      
      Quote     ref;

      bool IsNull(void)
         {      
         if(ref.IsNull())
            {
            if(sBook.IsNull())
               {
               if(sAuthor.IsNull())
                  return true;
               }
            }
         return false;
         }
      };
} // namespace

#endif
