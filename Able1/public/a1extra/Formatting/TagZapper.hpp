// Class TagZapper: Removed from htmlParser and encapsulated to create a new class
// for the NOJ Library.
//
// 04/13/2004: Class created by wrappering some functionality from my htmlParser classes, R. Nagy
//
#ifndef _TagZapper_Hpp
#define _TagZapper_Hpp

#include <Able1.hpp>

using namespace Able1;

class TagZapper
   {
   protected:
      static ZStr 
         _ZapHtml(const ZStr& sBlock, const char ch1, const char ch2);

   public:
      static ZStr 
         HtmlTo7Bit(const ZStr& str);

      static ZStr 
         ZapHtml(const ZStr& sBlock, const char ch1 = '<', const char ch2 = '>');
   };

inline
bool RemoveHtml(File& fileIn, File& fileOut)
   {
   stringstream srm;
   if(fileIn.DumpContents(srm) == false)
      return false;

   ZStr sBlock = PRESTO(srm);
   ZStr sResult = TagZapper::ZapHtml(sBlock);

   ostream& os = fileOut.OpenWrite();
   sResult.Write(os);
   fileOut.Close();
   return fileOut.Exists();
   }


#endif
