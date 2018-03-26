// Formatting text has always been problematic: Either you do it in an easy-to-Read
// & maintainable way (waste processor time), or you do it in a single-pass and make
// it very difficult to maintain and error-prone. With processor speeds well past the 
// 1GHZ limit now, let's do it yet again, only with the object-oriented flare.
//
// 12/12/2001: Class created, R. Nagy
// 04/24/2002: Added bracket capabilities (box without a right side, good for kerned fonts), R. Nagy
// 03/13/2005: Converting (in-place - no port!) to Able1, R. Nagy
// 01/12/2006: Copied from CPP to Extra/Formatting to support AutoEzine, R. Nagy
//
#include <Able1.hpp>
using namespace Able1;

#ifndef SimpleTextFlow_Hpp_
#define SimpleTextFlow_Hpp_

extern char        RandomBorder(void);

// Note: See also <WordWrap.Hpp>

class SimpleTextFlow
{
private:
   size_t    iLineWidth;
   bool      bCenter, bJustify;
   ZStr sText;
   ZStr sError;
   char randchar();

public:
   SimpleTextFlow(void);
   SimpleTextFlow(const SimpleTextFlow& ref);
   virtual ~SimpleTextFlow(void) {}

   // Query / set properties;
   void      Width(size_t iw);
   size_t    Width(void)      const;         
   size_t    WidestLine(void) const;
   size_t    Lines(void)      const;       
   size_t    Extract(Array<ZStr>& ary);    // Returns the WidestLine(), as well.
/*
   void      Center(bool b = true) ;
   void      Justify(bool b = true) ;
   ZStr Error(void);
*/
   // Encode simply means to translate to a Unix-standard newline format.
   // Anything else is up to you to specify, using the format translators;
   bool      Encode(const ZStr& str, int width = 50);     
   ZStr ReEncode(void);
   ZStr Query(void)    const;

   // Format translators;
   ZStr ReflowParagraphs(void);      // preserves paragraphs, re-flows lines therein.
   ZStr ReflowLines(void);           // preserves paragraphs, wraps lines therein (uck).

   // Note that this function does not use tab-stops;
   virtual ZStr UserExpand(size_t tabs = 3);

   SimpleTextFlow& operator=(const SimpleTextFlow& ref);
};


class BoxedText
{
private:
   ZStr sMargin;
   ZStr sHoriz;
   size_t    sigma;
   char      UL, UR, LL, LR, H, V;
   ZStr FormatLine(const ZStr& sRaw, size_t sigma, int boxed = 1)
      {
      ZStr sLine;
      sLine.Append(V);
      sLine.Append(sMargin);
      sLine.Append(sRaw);
      sLine.Remove(sLine.Length() - 1);   // kill the old newline
      sLine.Append(sMargin);
      while(sLine.Length() < sigma + 1)
         sLine.Append(' ');
      if(boxed)
         sLine.Append(V);
      sLine.Append('\n');
      return sLine;
      }
public:
   BoxedText(char horiz, char vert, char ul = '/', char ur = '\\', char ll = '\\', char lr = '/')
      {
      UL = ul; UR = ur;
      LL = ll; LR = lr;
      H = horiz; V = vert;
      sigma = NULL;
      }
   BoxedText(char chAll = RandomBorder())
      {
      UL = UR = LL = LR = H = V = chAll;
      sigma = NULL;
      }
   bool IsUnaryBorder(void)
      {
      return (UL == UR == LL == LR == H == V);
      }
   char GetUnaryChar(void)
      {
      return UL;
      }
   ZStr TitleBox(const ZStr& Title, SimpleTextFlow& flow, size_t lMargin = 1, int boxed = 1)
      {
      ZStr sTitle = Title;
      ZStr sBot = Box(flow, lMargin);   // must be called first, as it sets us up internally
      size_t whence = sBot.Find(UL);
      sBot[whence] = V;
      whence = sBot.Find(UR);
      sBot[whence] = V;

      ZStr sResult;
      sResult.Append(UL);
      sResult.Append(sHoriz);
      sResult.Append(UR);
      sResult.Append('\n');

      whence = sTitle.Find('\r');
      if(whence != NPOS)
         sTitle.Remove(whence);
      whence = sTitle.Find('\n');
      if(whence != NPOS)
         sTitle.Remove(whence);

      sTitle.Append('\n');
      sResult.Append(FormatLine(sTitle, sigma, boxed));
      sResult.Append(sBot);
      return sResult;
      }
   ZStr Box(SimpleTextFlow& flow, size_t lMargin = 1, int boxed = 1)
      {
      sHoriz = sMargin = "";
      Array<ZStr> ary;
      size_t ss = NULL;
      size_t wide = flow.Extract(ary);
      for(ss = NULL; ss < lMargin; ss++)
         sMargin.Append(' ');
      sigma = (wide + (lMargin * 2));
      for(ss = NULL; ss < sigma; ss++)
         sHoriz.Append(H);
      ZStr sResult;
      sResult.Append(UL);
      sResult.Append(sHoriz);
      sResult.Append(UR);
      sResult.Append('\n');
      ZStr sLine;
      for(ss = NULL; ss < ary.Nelem(); ss++)
         {
         sLine = FormatLine(ary[ss], sigma, boxed);
         sResult.Append(sLine);
         }
      sResult.Append(LL);
      sResult.Append(sHoriz);
      sResult.Append(LR);
      sResult.Append('\n');
      return sResult;
      }
   ZStr TitleBracket(const ZStr& Title, SimpleTextFlow& flow, size_t lMargin = 1)
      {
      return TitleBox(Title, flow, lMargin, 0);
      }
   ZStr Bracket(SimpleTextFlow& flow, size_t lMargin = 1)
      {
      return Box(flow, lMargin, 0);
      }

};

#endif
