#include <Able1.hpp>
using namespace Able1;

using namespace Able1::StringMatcher;

void StringSet::Load(const Array<ZStr>& array, int iArrayId)
   {
   aRecords.Empty();
   Append(array, iArrayId);
   }

void StringSet::Append(const Array<ZStr>& array, int iArrayId)
   {
   aRecords.AddZombies(array.Nelem());
   StringRec rec;
   ZStr str;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      str;
      array.At(ss, str);
      rec.Assign(iArrayId, ss, str);
      aRecords.Append(rec);
      }
   }

void StringSet::Append(const ZStr& str, int iArrayId)
   {
   StringRec rec(iArrayId, aRecords.Nelem(), str);
   aRecords.Append(rec);
   }

void StringSet::Sort(MemberComp<StringRec>& comp)
   {
   aRecords.Sort(comp);
   }

bool StringSet::StringRec::Markup(const StringSearch& sQuery, const ZStr& sStart, const ZStr& sStop, ZStr& sResult)
   {
   return Markup(sQuery, sPayload, sStart, sStop, sResult);
   }

bool StringSet::StringRec::Markup(const StringSearch& sQuery, const ZStr& sPayload, const ZStr& sStart, const ZStr& sStop, ZStr& sResult)
   {
   sResult = sPayload;
   ZStr sPattern = sStart + sQuery.sPattern + sStop;
   int iCount = sResult.Replace(sQuery.sPattern, sPattern);
   if(iCount)
      return true;
   return false;
   }
   

void SetManager::Search(StringSet& aLarger, StringSearch& sB, StringSet& sResult)
   {
   sResult.aRecords.Empty();
   sResult.aRecords.AddZombies(aLarger.aRecords.Nelem());
   for(size_t ss1 = 0L; ss1 < aLarger.aRecords.Nelem(); ss1++)
      {
      StringSet::StringRec& rRec = aLarger.aRecords[ss1];
      size_t szPos = rRec.sPayload.Find(sB.sPattern);
      if(sB.bInclude == true)
         {
         if(szPos == NPOS)
            continue;
         sResult.aRecords.Append(rRec);
         continue;
         }
      if(sB.bInclude == false)
         {
         if(szPos != NPOS)
            continue;
         sResult.aRecords.Append(rRec);
         continue;
         }
      }
   }

void SetManager::Combine(const StringSet& sA, const StringSet& sB, StringSet& sResult)
   {
   sResult.aRecords.Empty();
   sResult.aRecords.AddZombies(sA.aRecords.Nelem() + sB.aRecords.Nelem() + 1);
   sResult.aRecords =  sA.aRecords;
   sResult.aRecords += sB.aRecords;
   }

void SetManager::Exclude(const StringSet& sMajor, const StringSet& sRemove, StringSet& sResult)
   {
   StringSet aLarger, aSmaller;
   if(sMajor.aRecords.Nelem() > sRemove.aRecords.Nelem())
      {
      aLarger = sMajor;
      aSmaller = sRemove;
      }
   else
      {
      aLarger = sRemove;
      aSmaller = sMajor;
      }

   MemberComp<StringSet::StringRec> comp;
   aLarger.Sort(comp);
   aSmaller.Sort(comp);
   
   size_t ssResume = 0L;
   for(size_t ss1 = 0L; ss1 < aLarger.aRecords.Nelem(); ss1++)
      {
      bool bIgnore = false;
      for(size_t ss2 = ssResume; ss2 < aSmaller.aRecords.Nelem(); ss2++)
         {
         if(aLarger.aRecords[ss1] > aSmaller.aRecords[ss2])
            {
            ssResume = ss2;
            break;
            }
         if(aLarger.aRecords[ss1] == aSmaller.aRecords[ss2])
            {
            bIgnore = true;
            ssResume = ss2 + 1;
            break;
            }
         }
      if(bIgnore == false)
         sResult.aRecords.Append(aLarger.aRecords[ss1]);
      }
   }

void SetManager::Common(const StringSet& sA, const StringSet& sB, StringSet& sResult)
   {
   }

void SetManager::Unique(const StringSet& sA, const StringSet& sB, StringSet& sResult)
   {
   }


