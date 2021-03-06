// Namespace StringMatcher
// A universally-reusable pattern matcher and result-set manager. If you can express your recird as a
// string, then you can search and display the markup results for any record set.
//
// 03/29/2006: Namespace modeled, most classes implemented, R. Nagy
//
#ifndef StringMatcher_hpx
#define StringMatcher_hpx
 
#include <Able1.hpp>

namespace Able1
{

namespace StringMatcher
{   
   class StringSet;
   class SetManager;
   class StringSearch;

   class StringSet {
   public:
      struct StringRec
         {
         int iArrayId;
         size_t szArrayPos;
         ZStr sPayload;
         
         StringRec(void) : szArrayPos(0L), iArrayId(0)
            {
            }
         StringRec(int iAID, size_t szPos, const ZStr& sPay) : szArrayPos(iAID), iArrayId(szPos), sPayload(sPay)
            {
            }
         void Assign(int iAID, size_t szPos, const ZStr& sPay)
            {
            szArrayPos = iAID;
            iArrayId   = szPos;
            sPayload   = sPay;
            }
         int operator>(const StringRec& rec)
            {
            return sPayload > rec.sPayload;
            }
         int operator<(const StringRec& rec)
            {
            return sPayload < rec.sPayload;
            }
         int operator==(const StringRec& rec)
            {
            return sPayload == rec.sPayload;
            }
         // Mark-up the payload:
         bool Markup(const StringSearch& sQuery, const ZStr& sStart, const ZStr& sStop, ZStr& sResult);
         // Mark-up ANYTHING:
         static bool Markup(const StringSearch& sQuery, const ZStr& sSubject, const ZStr& sStart, const ZStr& sStop, ZStr& sResult);
         
         };
         
      CompArray<StringRec> aRecords;
      
      void Load(const Array<ZStr>& array, int iArrayId = 1);
      void Append(const Array<ZStr>& array, int iArrayId = 1);
      void Append(const ZStr& str, int iArrayId = 1);
      void Sort(MemberComp<StringRec>& comp);
         
   };


   class StringSearch
   {
   public:
      bool bInclude;
      ZStr sPattern;
      
      StringSearch(void) : bInclude(true)
         {
         }
      StringSearch(const ZStr& str, bool bi = true) : bInclude(bi), sPattern(str)
         {
         }
      void AsIncluder(void) {bInclude = true;}
      void AsExcluder(void) {bInclude = false;}
   };

   class SetManager
   {
   public:
      static void Search(StringSet& sA, StringSearch& sB, StringSet& sResult);

      static void Combine(const StringSet& sA, const StringSet& sB, StringSet& sResult);
      static void Exclude(const StringSet& sMajor, const StringSet& sRemove, StringSet& sResult);
      static void Common(const StringSet& sA, const StringSet& sB, StringSet& sResult);
      static void Unique(const StringSet& sA, const StringSet& sB, StringSet& sResult);
   };

   } // namespace StringMatcher

} // namespace Able1

#endif
