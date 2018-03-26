
#ifndef Linear_hpx
#define Linear_hpx

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
// Keywords: C++, cpp, portable, ANSI, template, patterns, abstract, concrete, X3J11, XJ311, POSIX, WIN32, DOS, Linux, Microsoft Windows, example, examples, sample, samples, TextReader, TextWriter
//

namespace FileConversion
{
enum LinearType
   {
   ltCsv,            // Comma Seperated Variables (CSV)
   ltSdf,            // Space Delimited Format (SDF)
   ltTab,            // 'Ye olde TAB (or any other odd char) -delimited format (a personal favorite :)
   ltNone            // It happends in the best classes :->
   };

class Linear
   {
   protected:
      ZStr ReadCooked(istream& is);
   public:
      ZStr sLastError;

      virtual bool Readline(istream& is, Array<ZStr>& aResult) = 0;
      virtual bool Writeline(ostream& os, Array<ZStr>& aResult) = 0;
   };

class TabbedLine : public Linear
   {
   private:
      char chDelim;
   public:
      TabbedLine(const char cDelim = '\t') : chDelim(chDelim)
         {
         }
      bool Readline(istream& is, Array<ZStr>& aResult);
      bool Writeline(ostream& os, Array<ZStr>& aResult);
   };

class CsvLine : public Linear
   {
   public:
      bool Readline(istream& is, Array<ZStr>& aResult);
      bool Writeline(ostream& os, Array<ZStr>& aResult);
   };

class SdfLine : public Linear
   {
   private:
      SdfLine() {}
   protected:
      Array<int> aCols;
   public:
      SdfLine(const Array<int>& aPos)
         {
         aCols = aPos;
         }
      bool Readline(istream& is, Array<ZStr>& aResult);
      bool Writeline(ostream& os, Array<ZStr>& aResult);
   };
}

#endif
