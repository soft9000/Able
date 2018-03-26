// 07/09/2005 - After considering my legacy WordWrap.hpp and SimpleTextFlow.hpp
// work, I decided to add a new Paragraph rather than to include those into
// the official namespace, R. Nagy
//
// 01/02/2007: Added ValueParser, R. Nagy
//
#ifndef Able1_utiltrtrt
#define Able1_utiltrtrt

namespace Able1
   {
   /** The ValueParser class is used to manage text in such
    * a way so as to allow TAGS + VALUES to be read, humanly edited,
    * machine re-written, and so on.
    */
   class ValueParser
      {
      public:
         struct TagSet
            {
            ZStr sTag;      // The RAW TAG ("raw" because it is
                                 // sans the chOn / chOff characters)
            ZStr sValue;    // The VALUE between the TAGS

            virtual bool IsNull(void)
               {
               if(sTag.IsNull() == false)
                  return false;
               if(sValue.IsNull() == false)
                  return false;
               return true;
               }
            };
         //! \class The TagBlock class is used to manage our results
         struct TagBlock : public TagSet
            {
            ZStr sPrefix;   // What was found BEFORE any tag
                                 // is read (if any comments, etc.)
            virtual bool IsNull(void)
               {
               if(sPrefix.IsNull() == false)
                  return false;
               return TagSet::IsNull();
               }
            };

         /** Reads past a valid sTag, preserving any prefix block. 
           *  (sValue will ALWAYS be null.)
           */
         static bool ReadPastTag(istream& is,  TagBlock& tvRes,   char chOn = '<', char chOff = '>');

         /** Read a single block (with prefix) from a stream, al-la XML style tag identification.
           *  Any opening comments part of block. Any closing "comment-block-only" is also 100% supported.
           *
           * NOTE: While XML style attributes will pass to the TAG, a CLOSING tag
           * must be included. (i.e. WILL NOT RECOGNIZE UNARY XML TAG CONVENTION YET)
           */
         static bool Read(istream& is, TagBlock& tvRes, char chOn = '<', char chOff = '>', char chCloser = '/');

         static bool Read(istream& is, Array<TagBlock>& array, char chOn = '<', char chOff = '>', char chCloser = '/');
         static bool Read(const ZStr& str, Array<TagBlock>& array, char chOn = '<', char chOff = '>', char chCloser = '/');

         /** Write a block using both an ending and an opening tag set
           */
         static bool Write(ostream& os, const TagBlock& tvRes, char chOn = '<', char chOff = '>', char chCloser = '/');

         /** Write non-null string. Append a \n if string does not end with one.
           * Returns FALSE if nothing was written (string null)
           */
         static bool PrettyWrite(ostream& os, const ZStr& strI);
      };

   /** The Html class is used to encode / decode text in such
     * a way so as to comply with RFC1866 (et al.)
     */
   class Html
      {
      public:
      /** Convert a string with 100% ASCII content over
        * to a 100% "Data Character" encoding (ss 3.2.1)
        */
      static ZStr EncodeAll(const ZStr& sLine);

      /** Convert a string with 100% ASCII and HTML content over
        * to a "Data Character" encoding, yet preserving HTML (ss 3.2.1)
        */
      static ZStr EncodeText(const ZStr& sss);

      // Convert ONLY the RESERVED HTML CHARACTERS in a string with
      // 100% ASCII and HTML content
      // static ZStr EncodeHtmlReserved(const ZStr& sss);

      /** Remove all HTML markup / tags
        */
      static ZStr RemoveHtml(const ZStr& sLine);

      /** Converts all HTML / XML tags to lower case IF present - else same is returned -
        */
      static ZStr LowerTags(const ZStr& sLine);

      /** Lowers case + returns content between <body></body> set IF present.
        * If *NOT* present, nothing will happen (NO lower casing, etc.)
        */
      static ZStr GetBody(const ZStr& sLine);

      /** Re-flow a string with 100% ASCII and HTML content over
        * to an HTML paragraph encoding, yet preserving HTML (ss 3.2.1)
        */
      static ZStr ToParagraphs(const ZStr& sss);
      };

   /** The Paragraph class is used to normalize text in such
     * a way so as allow for the formatting (and re-formatting) of
     * text into lines, characters, and paragraphs suitable for ASCII
     * rendering.
     */
   class Paragraph
      {
      public:
      /** Convert a string with unknown or mixed newline conventions over
        * into a standard, common, vendor-liberated convention: Lines
        * end in \n, paragraphs will end in \n\n, and any 
        * irrgular whitespaces are converted to a single ' '.
        * @param sLine - The line to normalize.
        * @return The normalized line.
        */
      static ZStr Normalize(const ZStr& sLine);

      /** Convert an array of strings with unknown or mixed newline 
        * conventions into a standard, common, vendor-liberated 
        * format: Uses Normalize(ZStr) (above).
        * @param aLines - The lines to normalize.
        * @return The normalized line.
        */
      static ZStr Normalize(const Array<ZStr>& aLines);

      /** Convert an array of strings with unknown or mixed newline 
        * conventions into a standard, common, vendor-liberated 
        * format: Uses Normalize(ZStr) (above).
        * @param aLines - The lines to normalize.
        * @return An array of normalized lines.
        */
      static Array<ZStr> Flow(const Array<ZStr>& aLines);

      /** Word wrapping attempts to break (\n) a line of text at 
        * ASCII spaces (32d). Takes a line and "wraps" it into a 
        * series of lines of the length specified.  
        * Non-newline whitespace is converted to 32d.
        * Normalizes all lines - Paragraphs (\n\n) are honored, 
        * everything else could change (i.e. longer \n's are changed.)
        * @param sLine - The line to normalize and word-wrap.
        * @return The normalized & word-wrapped line.
        */
      static ZStr WordWrap(const ZStr& sLine, int iLen);
 
      /** Normalizes and extracts newline-laden sub-strings into an array.
        * @param sLine - The line to normalize and format into an array.
        * @return The normalized line, as an array.
        */
      static Array<ZStr> List(const ZStr& sLine);
 
      /** Word-wraps, normalizes and extracts newline-laden sub-strings 
        * into an array.
        * @param sLine - The line to normalize and format into an array.
        * @param iLen - The desired word-wrap length of each line
        * @return The normalized & word-wrapped line, as an array.
        */
      static Array<ZStr> List(const ZStr& sLine, int iLen);

      /** Longest line
        */
      static size_t Longest(const Array<ZStr>& array);

      /** Shortest line
        */
      static size_t Shortest(const Array<ZStr>& array);

      /** Includes newlines ... or not
        */
      static size_t Size(const Array<ZStr>& array, bool bUseNewline = true);
      
      };
      
   /** PipeArray creates and parses an array of strings separated by a character.
     * ZStr.Split() can parse same, as well.
     */
   class PipeArray
      {
      public:
         static bool Parse(Array<ZStr>& ary, const ZStr& str, char ch = '|');
         static bool Parse(Array<ZStr>& ary, const ZStr& str, const ZStr& sPattern);
         static bool Gen(Array<ZStr>& ary, ZStr& str, char ch = '|');
      };


template <class T, class SZ = size_t>
class FileObjectHeap {
   public:
      static size_t Tally(Able1::File& file, File::TranslationModes tm);
      static bool   Load(Array<T>& aResult, File& file, File::TranslationModes tm);
      static bool   Save(Array<T>& aResult, File& file, File::TranslationModes tm);
};

template <class T, class SZ>
size_t FileObjectHeap<T, SZ>::Tally(File& file, File::TranslationModes tm)
   {
   size_t iTally = 0L;
   T ref;
   istream& is = file.OpenRead(tm);
   while(is)
      {
      ref.Read(is);
      if(is)
         iTally++;
      }
   return iTally;
   }

template <class T, class SZ>
bool FileObjectHeap<T, SZ>::Load(Array<T>& aResult, File& file, File::TranslationModes tm)
   {
   if(file.Exists() == false)
      return false;
   aResult.AddZombies(FileObjectHeap<T, SZ>::Tally(file, tm) + 1);
   T ref;
   istream& is = file.OpenRead(tm);
   while(is)
      {
      ref.Read(is);
      if(!is)
         continue;
      aResult.Append(ref);
      }
   return true;
   }

template <class T, class SZ>
bool FileObjectHeap<T, SZ>::Save(Array<T>& aResult, File& file, File::TranslationModes tm)
   {
   bool br = true;
   ostream& os = file.OpenWrite(tm);
   for(size_t ss = 0L; ss < aResult.Nelem(); ss++)
      {
      aResult[ss].Write(os);
      if(!os)
         {
         br = false;
         break;
         }
      }
   file.Close();
   return br;
   }

   }

#endif
