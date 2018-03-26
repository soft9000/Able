
#ifndef TextReader_hpx
#define TextReader_hpx

#include <Able1.hpp>
using namespace Able1;

// A place to put some handy textual (mostly 7-bit) file input and output 
// routines.
//
// (Because Cookpedia.com and TheQuoteforToday exchange a lot of data, I
// thought that we would include a lot of our more "designed" efforts here.)
//
// Keywords: C++, cpp, portable, ANSI, template, patterns, abstract, concrete, X3J11, XJ311, POSIX, WIN32, DOS, Linux, Microsoft Windows, example, examples, sample, samples
//
#include "Linear.hpp"

class FileConversion::Linear;

namespace FileConversion
{

class TextReader {
   private:
      FileConversion::Linear *pReader;

   public:
      File      pwFile;
      ZStr sLastError;

      TextReader() : pReader(0L)
         {
         }
      TextReader(File& file) : pwFile(file), pReader(0L)
         {
         }

      ~TextReader()
         {
         delete pReader;
         }

      bool ReadFirst(Array<ZStr>& aResult, LinearType type);
      bool ReadNext(Array<ZStr>& aResult);

      static bool Recall(size_t zbRecordId, const File& file, Array<ZStr>& aResult, LinearType type = ltTab);
};

}

#endif
