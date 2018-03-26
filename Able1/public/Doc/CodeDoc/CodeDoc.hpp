#include <Able1.hpp>
using namespace Able1;

namespace CodeDoc
{

class CodeFormatter
{
   private:
      int iTab;

      char Scroll(istream& is);
      void ReadToken(istream& is, ZStr& str);
      void ParseBlockOrStatement(istream& is, ZStr& str);
      void PassQuote(ostream& os, istream& is, char ch);
      void PassBlock(ostream& os, istream& is, char chOn, char chOff);
      void Newline(ostream& os, int iLevel);
      bool FormatCode0(const File& fileIn, const File& fileOut);
      bool FormatCode1(const File& fileIn, const File& fileOut);
      bool FormatCode(const File& fileIn, const File& fileOut);
      bool Normalize(const File& fileIn, const File& fileOut);
      bool NormalizeF(const File& fff, File& fileDest);
      bool Normalize(const File& fff);
   public:
      CodeFormatter(void);

      enum BlockType
      {
         bt_Simple,
         bt_Complex,
         bt_Statement
      };

      static BlockType GetBlockType(const ZStr& str);


      bool Beautify(const File& fff);
};

struct DocPoint
   {
   ZStr sName;
   };

class DocMaker
   {
   public:
      Array<ZStr> aTokens1;
      DocMaker(void)
         {
         aTokens1.Append("namespace");
         aTokens1.Append("class");
         aTokens1.Append("struct");
         }
      bool Parse(const File& file, Array<DocPoint>& array)
         {
         return false;     // to do
         }
   };
}
