// 12/20/1998: Created class for QUOTEZ scripture data conversion, R. Nagy
// 01/06/2000: Added stand-alone usage of GetLine(), R. Nagy
// 10/14/2008: Converted selected member to static usage, R. Nagy
//
#ifndef Csv_Hpp
#define Csv_Hpp

#include <Able1.hpp>
using namespace Able1;

enum CsvDataType
   {
   StringsOnly,
   NumericOnly,
   Both
   };

class CsvParser
   {
   private:
      static void NORMALIZE_COMMAS(ZStr& std, size_t sz_start = NULL);

      static void PUSH_LITERAL_QUOTES(ZStr& std, size_t sz_start = NULL);
      static void  POP_LITERAL_QUOTES(ZStr& std);

      static void PUSH_LITERAL_COMMAS(ZStr& std, size_t sz_start = NULL);
      static void  POP_LITERAL_COMMAS(ZStr& std);

   protected:
      istream *pIfs;

      static void ConvertToTight(ZStr& result);

      static istream& GetField(istream& in, ZStr& result);
      static istream& ImportCsvData(istream& in, ZStr& result);

   public:
      CsvParser(void);
      virtual ~CsvParser(void);

      // usage one;
      bool   Open(const char *psz);
      size_t GetLine(Array<ZStr>& result, CsvDataType = Both);
      // Stand-alone usage;
      static size_t GetLine(istream& ifs, Array<ZStr>& result, CsvDataType = Both);
      static size_t GetLine(const ZStr& sInput, Array<ZStr>& result, CsvDataType = Both);

      // This usage assumes that the line ONLY contains strings delimited
      // by quotations;
      size_t GetLineStrings(const ZStr&,Array<ZStr>& result);
      size_t GetLineStrings(Array<ZStr>& result);
      static size_t GetLineStrings(istream& is, Array<ZStr>& result);
   };

// Replacement for the above (untested):
struct CsvParser2
   {
   static ZStr Clean(const ZStr& sInput)
      {
      ZStr str = sInput;
      str.Strip();
      while(str[0] == '\"')
         str[0] = ' ';
      str.Reverse();
      while(str[0] == '\"')
         str[0] = ' ';
      str.Reverse();
      str.Strip();
      return str;
      }
   static void Clean(Array<ZStr>& array)
      {
      ZStr str;
      size_t ss = 0L;
      for(ss = 0L; ss < array.Nelem(); ss++)
         {
         str = Clean(array[ss]);
         array[ss] = str;
         }
      }
   static ZStr Mask(const ZStr& sInput)
      {
      ZStr str = sInput;
      bool bOn = true;
      for(size_t ss = 0L; ss < str.Length(); ss++)
         {
         char ch = str[ss];
         if(ch == '\"')
            {
            bOn = (bOn == true) ? false : true;
            continue;
            }
         if(bOn == false)
            str[ss] = ' ';
         }
      return str;
      }
   static size_t Parse(const ZStr& sInput, Array<ZStr>& result)
      {
      result.Empty();
      ZStr sMask = Mask(sInput);
      size_t ssStart = 0L;
      size_t ssPos = 0L;
      while(ssPos != npos)
         {
         ssPos = sMask.Find(",");
         if(ssPos != npos)
            {
            sMask[ssPos] = ' ';
            result.Append(sInput.Subpos(ssStart, ssPos + 1));
            ssStart = ssPos + 1;
            }
         else
            {
            result.Append(sInput.Subpos(ssStart, ssPos)); // npos
            }
         }
      return result.Nelem();
      }
   };

#endif
