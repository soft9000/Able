
#include <Able1.hpp>
using namespace Able1;

// A place to put some handy textual (mostly 7-bit) file input and output
// routines.
//
// (Because Cookpedia.com and TheQuoteforToday exchange a lot of data, I
// thought that we would include a lot of our more "designed" efforts here.)
//
// These classes are great for importing / exporting exported excel spReadsheet
// data and / or data from other user-editable spReadsheet / database programs.
//
// Keywords: C++, cpp, portable, ANSI, template, patterns, abstract, concrete, X3J11, XJ311, POSIX, WIN32, DOS, Linux, Microsoft Windows, example, examples, sample, samples
//

#include "Linear.Hpp"
#include "TextReader.Hpp"


namespace FileConversion
{

struct TagValuePair
   {
   ZStr sTag;
   ZStr sValue;

   TagValuePair(void) {}

   bool IsNull(void)
      {
      if(sTag.IsNull() == false)
         return false;
      if(sValue.IsNull() == false)
         return false;
      return true;
      }
   ostream& Write(ostream& os)
      {
      sTag.WriteStream(os);
      sValue.WriteStream(os);
      return os;
      }
   istream& Read(istream& is)
      {
      sTag.ReadStream(is);
      sValue.ReadStream(is);
      return is;
      }
   };

class TagValueRecord
   {
   public:
      Array<TagValuePair> pwArray;

      ostream& Write(ostream& os)
         {
         pwArray.Write(os);
         return os;
         }
      istream& Read(istream& is)
         {
         pwArray.Read(is);
         return is;
         }
   };

class TagValueFile
   {
   public:
      static bool Load(File& file, Array<TagValueRecord>& rResult);
      static bool Save(Array<TagValueRecord>& rResult, File& file);

      static bool Get(StdSeek<TagValueRecord>& file, TagValueRecord& rec, size_t zbWhich = 0L);
   };
}

