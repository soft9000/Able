#ifndef htmlEventPaths_hpp
#define htmlEventPaths_hpp

// 06/24/2008: Framework created, R. Nagy
//
#include "HtmlEvents.Hpp"

namespace H27
{

class HtmlEventPaths : public HtmlEvents
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
      srm << iCount << " $ " << sPath << " $ " << sPayload << "\r\n";
      return true;
      }

   struct Pattern
      {
      ZStr sDoc;
      ZStr sPattern;
      ZStr sInsert;
      bool bIgnorePrefix;
      bool bRemoveContainer;
      bool bDiscardLast;
      Pattern(void) : bDiscardLast(false), bRemoveContainer(false), bIgnorePrefix(false)
         {
         }
      };

   static ZStr GetPath(const ZStr& sLine)
      {
      Array<ZStr> array;
      if(sLine.Split(" $ ", array) == false)
         return ZStr();
      if(array.Nelem() < 2)
         return ZStr();
      return ZStr(array[1]);
      }
   static bool Delimit(const Pattern& job, ZStr& sResult)
      {
      Array<ZStr> aDoc;
      if(job.sDoc.Split("\r\n", aDoc) == false)
         return false;
      Array<ZStr> aPattern;
      if(job.sPattern.Split("\r\n", aDoc) == false)
         return false;
      int iHits = 0;
      ZStr sPwHit = GetPath(aPattern[iHits]);
      if(sPwHit.IsNull())
         return false;
      ZStr str;
      sResult = "";
      for(size_t ss = 0L; ss < aDoc.Nelem(); ss++)
         {
         str = GetPath(aDoc[ss]);
         if(str.IsNull())
            return false;
         sResult += aDoc[ss];  // alway there -
         sResult += "\r\n";
         if(sPwHit == str)
            {
            iHits++;
            if(iHits >= aPattern.Nelem())
               {
               // FOUND ONE!
               sResult += job.sInsert;
               sResult += "\r\n";
               iHits = 0;
               ZStr sPwHit = GetPath(aPattern[iHits]);
               continue;
               }
            ZStr sPwHit = GetPath(aPattern[iHits]);
            if(sPwHit.IsNull())
               return false;
            continue;
            }
         }
      return true;
      }

};

} // namespace

#endif

