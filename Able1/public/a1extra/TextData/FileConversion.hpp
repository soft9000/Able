
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
#include "TagValueRecord.hpp"

namespace FileConversion
{

enum CONTENT_TYPE
   {
   FILE_UNKNOWN,
   
   FILE_TVR_HEAP,     // TagValueRecord (internal format - heap)
   FILE_TVR_ARRAY,    // TagValueRecord (internal format - load / array)
   FILE_TVR_INDEXED,  // Heap + indexed

   FILE_INSERT,       // Copy the content of the entire file
   FILE_SPECIAL,      // Special format / Add-on conversion

   // TEXT conversions
   FILE_SDF,          // Space Delimited Format
   FILE_TABBED,       // TAB format
   FILE_FORTUNE,      // UNIX Fortune Format
   FILE_NEWLINE       // 1 single field per line
   };

   class ConvertFile
   {
      public:
         struct TVR
            {
            static bool CreateIndexed(const File& file, CONTENT_TYPE type, StdSeek<TagValueRecord>& sskResult);
            static bool CreateArray(const File& file,   CONTENT_TYPE type, File& sskResult);
            static bool CreateHeap(const File& file,    CONTENT_TYPE type, File& sskResult);
            };
   };

}

