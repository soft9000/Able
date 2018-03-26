// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidTV_Hpp
#define StdOidTV_Hpp


namespace Able1
{


namespace Oid
{
/** Designed to be used directly or as part of an OidTag. Use SimpleTagValue, instead. */
struct TagValue
   {
   ZStr sSep;
   ZStr sEQ;
   ZStr sTag;
   ZStr sValue;

   TagValue(void);
   TagValue(const OidMeta& oid);
   TagValue(const ZStr& sTagValuePair);
   TagValue(const ZStr& sTagValuePair, const OidMeta& oid);
   TagValue(const ZStr& sT, const ZStr& sV);
   TagValue(const ZStr& sT, const ZStr& sV, const ZStr& sEQ, const ZStr& sSEP);

   bool FromString(const ZStr& sData);

   ZStr SafeSep(void);

   static ZStr SafeSepDefault(void);

   TagValue operator=(const OidMeta& oid)
      {
      *this = TagValue(oid);
      return *this;
      }
   int operator==(const TagValue& oid)
      {
      if(sTag == oid.sTag)
         if(sValue == oid.sValue)
            return 1;
      return 0;
      }
   int operator!=(const TagValue& oid)
      {
      return (!(*this == oid));
      }
   bool IsNull(void) const;

   void Normalize(void)
      {
      sTag.MkWhite();
      sTag.Strip();
      sValue.MkWhite();
      sValue.Strip();
      }

   ostream& Write(ostream& os);
   istream& Read(istream& is);

   ostream& WriteStream(ostream& os);
   istream& ReadStream(istream& is);
   };
 } // namespace Oid
} // namespace Able1

#endif
