#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;


TagValue::TagValue(void) : sSep(DEFAULT_SEP), sEQ(DEFAULT_EQ)
   {
   }
TagValue::TagValue(const OidMeta& oid)  : sSep(oid.delim.block.sLine), sEQ(oid.delim.param.sEquals)
   {
   }
TagValue::TagValue(const ZStr& sTagValuePair, const OidMeta& oid) :  sSep(oid.delim.block.sLine), sEQ(oid.delim.param.sEquals)
   {
   stringstream srm;
   srm << sTagValuePair << sSep;
   Read(srm);
   Normalize();
   }
TagValue::TagValue(const ZStr& sTagValuePair) : sSep(DEFAULT_SEP), sEQ(DEFAULT_EQ)
   {
   stringstream srm;
   srm << sTagValuePair << sSep;
   Read(srm);
   Normalize();
   }
TagValue::TagValue(const ZStr& sT, const ZStr& sV) : sTag(sT), sValue(sV), sSep(DEFAULT_SEP), sEQ(DEFAULT_EQ)
   {
   Normalize();
   }
TagValue::TagValue(const ZStr& s1, const ZStr& s2, const ZStr& s3, const ZStr& s4)
    : sTag(s1), sValue(s2), sSep(s4), sEQ(s3)
   {
   }
ZStr TagValue::SafeSep(void)
   {
   ZStr sss = sSep;
   return sss;
   }
ZStr TagValue::SafeSepDefault(void)
   {
   ZStr sss = DEFAULT_SEP;
   return sss;
   }
bool TagValue::FromString(const ZStr& sData)
   {
   stringstream srm;
   srm << sData;
   Read(srm);
   return !IsNull();
   };
bool TagValue::IsNull(void) const
   {
   if(sTag.IsNull() && sValue.IsNull())
      return true;
   return false;
   }
ostream& TagValue::Write(ostream& os)
   {
   os << sTag << sEQ << sValue << sSep;
   return os;
   }
istream& TagValue::Read(istream& is)
   {
   ZStr sLine;
   sLine.Readline(is, sSep);
   sTag = "";
   sValue = "";
   Array<ZStr> array;
   if(sLine.Split(sEQ, array) == true)
      {
      sTag   = array[0];
      sValue = array[1];
      sTag.Strip();
      sValue.Strip();
      }
   return is;
   }
ostream& TagValue::WriteStream(ostream& os)
   {
   sSep.WriteStream(os);
   sEQ.WriteStream(os);
   sTag.WriteStream(os);
   sValue.WriteStream(os);
   return os;
   }
istream& TagValue::ReadStream(istream& is)
   {
   *this = TagValue();
   if(!is)
      return is;
   sSep.ReadStream(is);
   sEQ.ReadStream(is);
   sTag.ReadStream(is);
   sValue.ReadStream(is);
   return is;
   }



