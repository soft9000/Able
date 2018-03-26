#include "HtmlTag.hpp"

using namespace H27;

bool HtmlTag::Attribute::Parse(const ZStr& sOneParam, Attribute& result)
   {
   result = Attribute();
   ZStr str = sOneParam;
   Array<ZStr> array;
   str.Split('=', array);
   if(array.Nelem() != 2)
      return false;
   result.sTag = array[0];
   result.sTag.Strip();
   result.sValue = array[1];
   result.sValue.Strip();
   return true;
   }

HtmlTag::HtmlTag(void) : stStart(0L)
   {
   }

HtmlTag::HtmlTag(const HtmlTag& hb)
   {
   *this = hb;
   }

HtmlTag::~HtmlTag(void)
   {
   }

bool HtmlTag::IsComment(void) const
   {
   if(sKey == "!--")
      return true;
   return false;
   }

bool HtmlTag::IsUnary(void) const
   {
   ZStr str = sKey;
   str.ToLower();
   if(str == "br")
      return true;
   if(str == "hr")
      return true;
   return IsComment();
   }

bool HtmlTag::IsTagStart(void) const
   {
   if(IsUnary())
      return true;
   return !(IsTagEnd());
   }

bool HtmlTag::IsTagEnd(void) const
   {
   if(sStartTag.Find("</") != npos)
      return true;
   if(sStartTag.Find("/>") != npos)
      return true;
   if(IsUnary())
      return true;
   return false;
   }

bool HtmlTag::IsTagStartEnd(void) const
   {
   if(IsTagStart() == false)
      return false;
   if(IsTagEnd() == false)
      return false;
   return true;
   }

ZStr HtmlTag::Key(void) const
   {
   return ZStr(sKey);
   }

ZStr HtmlTag::Token(void) const
   {
   ZStr str(sKey);
   str.Remove('/');
   return str;
   }

long HtmlTag::PosStart(void) const
   {
   return stStart;
   }

ZStr HtmlTag::BlockStart(void) const
   {
   return ZStr(sStartTag);
   }

void HtmlTag::NormalizeKey(void)
   {
   sKey.ToLower();
   }

bool HtmlTag::IsNull(void) const
   {
   bool br = false;
   if(stStart == (long)0L)
      br = sStartTag.IsNull();
   if(br == false)
      return false;
   return true;
   }

HtmlTag& HtmlTag::operator=(const HtmlTag& hb)
   {
   if(this == &hb)
      return *this;
   stStart      = hb.stStart;
   sKey         = hb.sKey;
   sStartTag    = hb.sStartTag;
   return *this;
   }

bool HtmlTag::ParseTag(const ZStr& sData, HtmlTag& tag)
   {
   // STEP: Cleanup / qualify the input-string
   ZStr str = sData;
   size_t pos = str.Find('<');
   if(pos == npos)
      return false;
   str.RemovePos(0, pos + 1);
   pos = str.RFind('>');
   if(pos == npos)
      return false;
   str.Remove(pos);
   tag.sStartTag = sData;

   // STEP: Special CLEANUP for COMMENTS
   if(str.Find("!--") != npos)
      if(str.Find("!-- ") == npos)
         str.Replace("!--", "!-- ");

   // STEP: Assing a 'normal' ATTRIBUTE payload
   pos = str.Find(' ');
   if(pos == npos)
      {
      tag.sKey = str;
      return true;
      }
   tag.sKey = str.Substr(0, pos);
   str.RemovePos(0, pos);
   str.Replace(" =", "=");
   str.Replace("= ", "=");
   Array<ZStr> array;
   str.Split(" ", array);
   Attribute attr;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      if(Attribute::Parse(array[ss], attr) == true)
         tag.aAttributes.Append(attr);
      }
   return true;
   }
