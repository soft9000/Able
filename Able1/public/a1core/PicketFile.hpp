// PicketFile: Parses strings located between "pickets\n" (see below).
// A classic example would be the Unix Fortune file format. Note that the DOS
// "pattern\r\n" format is also completely supported becaue \r is REMOVED from
// both the PICKET and any result.
//
// Payoff idea here is that by using this class recursively, collections of fields
// can be arbitrarily NESTED, as well. Ringer is that ASCII files can be maintained
// using platform editing tools: Either the '\n' and the '\r\n' line sequences are
// supported.
//
// IMO, overall effect makes PicketFile array extraction / insertion a LOT
// faster to (create / use / parse) than XML... (Even XML can be placed between 
// pickets)
//
//
// 10/16/2003: FastFortuneFormat class created, debugged, and tested using test cases provided, R. Nagy
// 01/01/2007: Added Recall() with a record indicator for HyperNews1::EmailedDatabase usage, R. Nagy
// 01/09/2008: Renamed to PicketFile, removed parentage, extracted test cases, and included into the Able1, R. Nagy
//
#ifndef _PF_Format_
#define _PF_Format_

namespace Able1
{
/** The reading and writing of data is based upon the token pattern, not the newline format.
  * This coinvention means that the internal data is normalized to Unix, and can have any
  * style newlines. There is simply no need to worry about Unix -v- DOS newlines (etc).
  * <br>
  * Generated format is:
  * <br>
  * <your_token[[\r]\n]>single multi-line data...<your_token[[\r]\n]>
  * <br>
  * To enforce newlines (any style), then use them as part of your token.
  * <br>====<br>
  * NOTE: The \r's CAN exist in the files, but they are REMOVED from ALL data upon input!
  * (Think I said that one enough?? :)
  * <br>====<br>
  */
   class PicketFile
   {
   public:
      static void Normalize(ZStr& str)
         {
         str.RemovePattern("\r");
         }
      static void Normalize(Array<ZStr>& array)
         {
         for(size_t ss = 0L; ss < array.Nelem(); ss++)
            Normalize(array[ss]);
         }
         
      static size_t Tally(const File& file, const ZStr& sTokenSep)
         {
         ZStr str;
         File::LoadText(file, str);
         return str.Tally(sTokenSep);
         }

      static bool Read(const File& file,   Array<ZStr>& aResult, const ZStr& sTokenSep);
      static bool Read(istream& is,        Array<ZStr>& aResult, const ZStr& sTokenSep);
      static bool Read(const ZStr& sInput, Array<ZStr>& aResult, const ZStr& sTokenSep);

      static bool Write(const File& file,  Array<ZStr>& aResult, const ZStr& sTokenSep);
      static bool Write(ostream& os,       Array<ZStr>& aResult, const ZStr& sTokenSep);
      static bool Write(ZStr& sOutput,     Array<ZStr>& aResult, const ZStr& sTokenSep);

      static bool Recall(const File& file, ZStr& aResult, const ZStr& sTokenSep);
      static bool Recall(const File& file, ZStr& aResult, const ZStr& sTokenSep, size_t ss);
   };

}

#endif
