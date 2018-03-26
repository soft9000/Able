#ifndef htmlEvents_hpp
#define htmlEvents_hpp

// 06/24/2008: Framework created, R. Nagy
//
#include "HtmlTag.Hpp"

namespace H27
{

class HtmlEvents
{
protected:
   ZStr sLastError;

public:

   virtual ZStr Error(void)
      {
      return ZStr(sLastError);
      }

   // First member called -
   virtual void OnStart(void)
      {
      sLastError = "";
      }

   // Return FALSE to terminate -
   virtual bool On(const HtmlTag& tag, const ZStr& sPayload) = 0;

   // Return FALSE to terminate -
   virtual bool On(const HtmlTag& tag)
      {
      return On(tag, ZStr());
      }

   // Return FALSE to terminate -
   virtual bool OnGarbage(const ZStr& sGarbage)
      {
      OnError(ZStr("Error: Unparented text '") + sGarbage + "'");
      return false;  // no garbage (i.e. un-tagged text)
      }

   // Either success OR failure - Last member called
   virtual void OnError(const ZStr& sPayload)
      {
      sLastError = sPayload;
      }
   // Either success OR failure - Last member called
   virtual void OnSuccess(void)
      {
      sLastError = "";
      }
};

/*
class HtmlResultPath : public HtmlEvents
{
private:
   size_t iCount;
   ZStr sPath;
public:
   stringstream srm;

   // First member called -
   virtual void OnStart(void)
      {
      HtmlEvents::OnStart();
      iCount = 0L;
      }

   virtual bool On(const HtmlTag& tag, const ZStr& sPayload)
      {
      iCount++;
      ZStr sTag = tag.Key();
      if(tag.IsTagEnd())
         {
         size_t pos = sPath.RFind(ZStr(":") + tag.Token());
         if(pos != npos)
            sPath.Remove(pos);
         }
      else
         {
         sPath.Append(ZStr(":") + tag.Token());
         }
      srm << iCount << "$ " << sPath << " $ " << sPayload << "\r\n";
      return true;
      }

   struct Pattern
      {
      ZStr sDoc;
      ZStr sDelimiter;
      ZStr sReplacement;
      bool bIgnorePrefix;
      bool bRemoveContainer;
      };

   static bool Delimit(const Pattern& sPattern, ZStr& sResult)
      {
      }

};
*/
class HtmlEventParser
{
public:
   static bool ReadHtmlTag(istream& is, ZStr& sTag, ZStr& sGarbage);
   static bool Parse(const File& file, HtmlEvents& model);
};


} // namespace

#endif

