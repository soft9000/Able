// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
//
// NOTE: At this point, nested blocks require different delimiters at each
// nesting level. While fine for now, eventually we should use StdOid::Block
// to "peel away" the nesting so as to allow the same tokens to be used
// throughtout the entire block.
//
#ifndef StdOidT_Hpp
#define StdOidT_Hpp


namespace Able1
{

namespace Oid
{
// Designed to be used directly or a part of an OidList,
// an OidTag can contain MANY properly delimited TAG = VALUE statements -
class OidTag
   {
   private:
      void init(void);
      ZStr sObjectName;

   protected:
      OidMeta oidMeta;  // This is the delimer sets that is used to parse the instance -

   public:
      Array<TagValue> aData;

      OidTag(void);
      OidTag(const ZStr& sSet);
      OidTag(const OidMeta& oid);
      OidTag(const ZStr& sName, const ZStr& sTag, const ZStr& sValue);
      OidTag(const ZStr& sName, const ZStr& sTag, const ZStr& sValue, const OidMeta& oidMeta);
      OidTag(const ZStr& sName, const ZStr& aTagValueSet, const OidMeta& oidMeta);
      OidTag(const ZStr& sName, Array<ZStr>& aTagValue);

      operator OidMeta(void)
         {
         OidMeta meta = oidMeta;
         return meta;
         }

      ZStr SafeSep(void)
         {
         if(aData.Nelem())
            return aData[0].SafeSep();
         return TagValue::SafeSepDefault();
         }

      OidTag&   operator=(const OidMeta& oid);
      int       operator==(const OidTag& oid) const;
      int       operator!=(const OidTag& oid) const;

      ZStr Name(void) const;
      bool      Name(const ZStr& sName);

      bool      IsNull(void) const;
      bool      HasName(void) const;
      bool      HasBody(void) const;

      void      Normalize(void);

      // Create just chums your tag onto the end of the array - See Update() for more
      bool      Create(const TagValue& tv);
      bool      Create(const ZStr& sTag, const ZStr& sValue);

      ZStr ValueFromTag(const ZStr& sTag) const;
      bool      ValueFromTag(const ZStr& sTag, ZStr& sValue) const;
      bool      ValueFromTag(const ZStr& sTag, Array<ZStr>& aValues, bool bIgnoreCase = true) const;

      // Not sure if exists? Then use Update - will create it if it does not AE
      bool      Update(const ZStr& sTag, const ZStr& sValue);
      void      Delete(const ZStr& sTag);

      bool      Payload(Array<ZStr>& aTagValue);
      bool      Payload(const ZStr& aTagValueSet, const OidMeta& oidMeta);

      void      print(ostream& os);

      ostream&  Write(ostream& os);
      ostream&  Write(ostream& os, const OidMeta& oid);
      ostream&  WriteStream(ostream& os);

      istream&  Read(istream& is);
      istream&  Read(istream& is, const OidMeta& oid);
      istream&  ReadStream(istream& is);

      static bool Parse(const ZStr& sData, OidTag& oidResult);
   };
 } // namespace Oid
} // namespace Able1

#endif
