#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;

ZStr OidList::GetUniqueObject(const ZStr sObjName, const ZStr sFieldName, bool bIgnoreCase)
   {
   // NOTE: there is a GIGO here - If there is more than one FIELD, this only finds the first -
   ZStr sResult;
   OidTag oidTag;
   if(FindUnique(sObjName, oidTag, bIgnoreCase) == 1)
      oidTag.ValueFromTag(sFieldName, sResult);
   return sResult;
   }

ZStr OidList::GetUniqueField(const ZStr& sObjName, const ZStr sFieldName, bool bIgnoreCase)
   {
   ZStr sResult;
   OidTag oidTag;
   if(FindUnique(sObjName, oidTag, bIgnoreCase) == 1)
      {
      Array<ZStr> aValued;
      oidTag.ValueFromTag(sFieldName, aValued);
      if(aValued.Nelem() == 1)
         sResult = aValued[0];
      }
   return sResult;
   }

bool OidList::SetUniqueField(const ZStr& sObjName, const ZStr sFieldName, const ZStr& sValue, bool bIgnoreCase)
   {
   ZStr sResult;
   OidTag oidTag;
   bool br = false;
   switch(FindUnique(sObjName, oidTag, bIgnoreCase))
      {
      case 1:
         {
         size_t ss = aTags.Contains(oidTag);
         if(ss != -1L)
            {
            br = oidTag.Update(sFieldName, sValue);
            if(br == true)
               {
               if(ss != -1L)
                  aTags.Replace(oidTag, ss);
               }
            }
         }
      break;
      case 0:
         {
         aTags.Append(OidTag(sObjName, sFieldName, sValue));
         br = true;
         }
      break;
      case 2:
      default:
      break;
      }
   return br;
   }

// 0 = not found, 1 = found ONLY one, 2 = more than one found
int OidList::FindUnique(const ZStr sObjName, OidTag& oidResult, bool bIgnoreCase)
   {
   OidTag oidTag;

   // See if we have at least one -
   size_t ss = FindNext(sObjName, oidTag, 0L, bIgnoreCase);
   if(ss == -1L)
      return 0;

   oidResult = oidTag;  // If it works, then this would be the official result

   // If we have another, then we are not unique ...
   ss = FindNext(sObjName, oidTag, ss, bIgnoreCase);
   if(ss != -1L)
      {
      // If it DOES NOT work, then the result should be NULL, as well -
      oidResult = OidTag();
      return 2;
      }

   // Okay
   return 1;
   }

size_t OidList::FindFirst(const ZStr sObjName, OidTag& oidTag, bool bIgnoreCase)
   {
   return FindNext(sObjName, oidTag, 0L, bIgnoreCase);
   }

// -1L on when none found
size_t OidList::FindNext(const ZStr sObjName, OidTag& oidTag, size_t ssPos, bool bIgnoreCase)
   {
   if(ssPos == -1L)
      return 0L;  // start-over

   if(ssPos >= aTags.Nelem())
      return -1L; // invalid location (protocol response)

   ZStr sObject = sObjName;
   ZStr sObject2;
   if(bIgnoreCase == true)
      sObject.ToLower();
   for(size_t ss = ssPos; ss < aTags.Nelem(); ss++)
      {
      oidTag = aTags[ss];
      sObject2 = oidTag.Name();
      if(bIgnoreCase == true)
         sObject2.ToLower();
      if(sObject == sObject2)
         return (ss+1L);
      }

   oidTag = OidTag();
   return -1L; // no more found (protocol response)
   }

