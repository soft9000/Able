#include "htmlEvents.Hpp"

using namespace H27;

bool HtmlEventParser::ReadHtmlTag(istream& is, ZStr& sTag, ZStr& sGarbage)
{
sGarbage = sTag = "";
bool bLiteral = false;
bool bGarbage = true;
char ch = 0;
while(is)
   {
   is.read(&ch, 1);
   if(!is)
      return false;
   if(bGarbage == false && ch == '\'' || ch == '\"')
      {
      bLiteral = (bLiteral) ? false : true;
      sTag += ch;
      continue;
      }
   if(bLiteral && bGarbage == false)
      {
      sTag += ch;
      continue;
      }
   if(ch == '<')
      {
      if(sTag.IsNull() == false)
         {
         is.putback(ch);
         sGarbage.MkWhite();
         sGarbage.Strip();
         return true;
         }
      bGarbage = false;
      sTag = ch;  // yes = obliterate -
      continue;
      }
   if(ch == '>')
      {
      sTag += ch; // accumulate -
      sGarbage.MkWhite();
      sGarbage.Strip();
      return true;
      }
   if(bGarbage)
      sGarbage += ch;
   else
      sTag += ch;
   }
   return false;
}

bool HtmlEventParser::Parse(const File& fff, HtmlEvents& model)
{
   model.OnStart();
   File file = fff;
   if(file.Exists() == false)
      {
      model.OnError(ZStr("Error: File not found."));
      return false;
      }
   char ch;
   istream& is = file.OpenRead();
   while(is)
      {
      ZStr sTag, sGarbage;
      HtmlTag tag;
      
      // STEP: Get the TAG
      if(ReadHtmlTag(is, sTag, sGarbage) == false)
         {
         model.OnError(ZStr("Error: Illegal file input '") + sTag + " " + sGarbage + "'");
         return false;
         }
      // STEP: Any garbage is a probable ERROR -
      if(sGarbage.IsNull() == false)
         {
         if(model.OnGarbage(sGarbage) == false)
            return false;
         }
      // STEP: Parse the ATTRIBUTES + token into the tag
      if(HtmlTag::ParseTag(sTag, tag) == false)
         {
         model.OnError(ZStr("Error: Illegal tag syntax '") + sTag + "'");
         return false;
         }
      // STEP: Get any optional "payload" AFTER the tag -
      ZStr sPayload;
      sPayload.ReadLine(is, '<');
      if(is)
         is.putback('<');

      // STEP: Inform the MODEL of the set
      ZStr str = sPayload;
      str.MkWhite();
      str.Strip();
      if(str.IsNull())
         sPayload = str;
      bool br = false;
      if(sPayload.IsNull())
         br = model.On(tag);            // notify - no matter what -
      else
         br = model.On(tag, sPayload);  // notify - no matter what -

      if(br == false)
         return true;                   // model got what it wanted -
      }
   model.OnSuccess();
   return true;
}

