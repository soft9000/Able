#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;


void OidTag::init(void)
   {
   }
OidTag::OidTag(void)
   {
   init();
   }
OidTag::OidTag(const OidMeta& oid)
   {
   init();  // maintenance - jic
   oidMeta = oid;
   }
OidTag::OidTag(const ZStr& aTagValueSet)
   {
   init();
   stringstream srm;
   srm << aTagValueSet;
   Read(srm);
   Normalize();
   }
OidTag::OidTag(const ZStr& sName, const ZStr& aTagValueSet, const OidMeta& oidMeta44)
   {
   init();
   oidMeta = oidMeta44;
   Name(sName);
   Payload(aTagValueSet, oidMeta44);
   Normalize();
   }
OidTag::OidTag(const ZStr& sName, Array<ZStr>& aTagValue)
   {
   init();
   Name(sName);
   Payload(aTagValue);
   Normalize();
   }
OidTag::OidTag(const ZStr& sName, const ZStr& sTag, const ZStr& sValue)
   {
   sObjectName = sName;
   aData.Append(TagValue(sTag, sValue));
   }
OidTag::OidTag(const ZStr& sName, const ZStr& sTag, const ZStr& sValue, const OidMeta& oidMeta44)
   {
   sObjectName = sName;
   oidMeta     = oidMeta44;
   aData.Append(TagValue(sTag, sValue));
   }
ZStr OidTag::ValueFromTag(const ZStr& sTag) const
   {
   ZStr sResult;
   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      {
      TagValue& tv = aData.Get(ss);
      if(tv.sTag == sTag)
         return tv.sValue;
      }
   return sResult;
   }
bool OidTag::ValueFromTag(const ZStr& sTag, ZStr& sValue) const
   {
   sValue = ValueFromTag(sTag);
   if(sValue.IsNull())
      return false;
   return true;
   }
bool OidTag::ValueFromTag(const ZStr& sTag, Array<ZStr>& aValues, bool bIgnoreCase) const
   {
   aValues.Empty();

   ZStr sA, sB;
   sA = sTag;
   if(bIgnoreCase == true)
      sA.ToLower();

   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      {
      TagValue& tv = aData.Get(ss);

      sB = tv.sTag;
      if(bIgnoreCase == true)
         sB.ToLower();

      if(sA == sB)
         aValues.Append(tv.sValue);
      }

   if(aValues.Nelem())
      return true;
   return false;
   }
bool OidTag::Name(const ZStr& sName)
   {
   sObjectName = sName;
   sObjectName.MkWhite();
   sObjectName.Strip();
   return true;
   }
bool OidTag::Payload(const ZStr& aTagValues, const OidMeta& oidMeta44)
   {
   oidMeta = oidMeta44;
   Array<ZStr> array;
   if(aTagValues.Split(oidMeta44.delim.block.sLine, array) == false)
      return false;
   return Payload(array);
   }
bool OidTag::Payload(Array<ZStr>& aTagValue)
   {
   ZStr str;
   aData.Empty();
   for(size_t ss = 0L; ss < aTagValue.Nelem(); ss++)
      {
      str = aTagValue[ss];
      str.MkWhite();
      str.Strip();
      if(str.IsNull())
         continue;

      TagValue tv = TagValue(str, oidMeta);
      if(tv.IsNull())
         return false;
      if(Update(tv.sTag, tv.sValue) == false)
         return false;
      }
   return true;
   }
bool OidTag::IsNull(void) const
   {
   if(sObjectName.IsNull())
      {
      if(!aData.Nelem())
         return true;
      }
   return false;
   }
ostream& OidTag::Write(ostream& os, const OidMeta& oid)
   {
   oidMeta = oid;
   return Write(os);
   }
istream& OidTag::Read(istream& is, const OidMeta& oid)
   {
   oidMeta = oid;
   return Read(is);
   }
ostream& OidTag::WriteStream(ostream& os)
   {
   oidMeta.delim.block.sBegin.WriteStream(os);
   oidMeta.delim.block.sEnd.WriteStream(os);
   sObjectName.WriteStream(os);
   os << aData.Nelem() << " ";
   for(size_t ss= 0L; ss < aData.Nelem(); ss++)
      aData[ss].WriteStream(os);
   return os;
   }
istream& OidTag::ReadStream(istream& is)
   {
   *this = OidTag(oidMeta);
   if(!is)
      return is;
   oidMeta.delim.block.sBegin.ReadStream(is);
   oidMeta.delim.block.sEnd.ReadStream(is);
   sObjectName.ReadStream(is);

   ZStr str;
   str.Read(is);
   int iss = str.AsInt();
   aData.AddZombies(iss + 1);
   for(int ss = 0; ss < iss; ss++)
      aData[ss].ReadStream(is);
   return is;
   }
ostream& OidTag::Write(ostream& os)
   {
   os << sObjectName <<  " " << oidMeta.delim.block.sBegin << " ";
   for(size_t ss2 = 0L; ss2 < aData.Nelem(); ss2++)
      {
      aData[ss2].Write(os);
      os << " ";
      }
   os << " " << oidMeta.delim.block.sEnd << " ";
   return os;
   }
istream& OidTag::Read(istream& is)
   {
   ZStr sLine;
   sLine.Readline(is, oidMeta.delim.block.sEnd);
   if(sLine.IsNull())
      {
      *this = OidTag(oidMeta);
      return is;
      }
   size_t whence = sLine.Find(oidMeta.delim.block.sBegin);
   if(whence == npos)
      {
      *this = OidTag(oidMeta);
      return is;
      }
   ZStr sName = sLine.Subpos(0, whence - 1);
   sLine = sLine.RemovePos(0, whence + oidMeta.delim.block.sBegin.Length());
   *this = OidTag(sName, sLine, oidMeta);
   return is;
   }
bool OidTag::Update(const ZStr& sTag, const ZStr& sValue)
   {
   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      {
      TagValue& ref = aData[ss];
      if(ref.sTag == sTag)
         {
         ref.sValue = sValue;
         return true;
         }
      }
   return Create(sTag, sValue);
   }
void OidTag::Delete(const ZStr& sTag)
   {
   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      {
      TagValue& ref = aData[ss];
      if(ref.sTag == sTag)
         {
         aData.Remove(ss);
         return;
         }
      }
   }
bool OidTag::Create(const TagValue& tv)
   {
   aData.Append(tv);
   return true;
   }
bool OidTag::Create(const ZStr& sTag, const ZStr& sValue)
   {
   TagValue tv(sTag, sValue);
   aData.Append(tv);
   return true;
   }
bool OidTag::HasName(void) const
   {
   if(sObjectName.IsNull())
      return false;
   return true;
   }
bool OidTag::HasBody(void) const
   {
   if(aData.IsNull())
      return false;
   return true;
   }
OidTag& OidTag::operator=(const OidMeta& oidMeta44)
   {
   *this = OidTag(oidMeta44);
   return *this;
   }

int OidTag::operator==(const OidTag& oid) const
   {
   if(sObjectName == oid.sObjectName)
      {
      for (size_t i = 0; i < aData.Nelem(); i++)
         {
         TagValue& tv1 = aData.Get(i);
         TagValue& tv2 = oid.aData.Get(i);
         if (!(tv1 == tv2))
            return 0;
         }
      return 1;
      }
   return 0;
   }
int OidTag::operator!=(const OidTag& oid) const
   {
   return !(*this == oid);
   }
ZStr OidTag::Name(void) const
   {
   ZStr s = sObjectName;
   return s;
   }
void OidTag::Normalize(void)
   {
   sObjectName.MkWhite();
   sObjectName.Strip();
   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      aData[ss].Normalize();
   }
void OidTag::print(ostream& os)
   {
   os << sObjectName <<  endl << oidMeta.delim.block.sBegin << endl;
   for(size_t ss2 = 0L; ss2 < aData.Nelem(); ss2++)
      {
      os << "   ";
      aData[ss2].Write(os);
      os << endl;
      }
   os << endl << oidMeta.delim.block.sEnd << endl;
   }
bool OidTag::Parse(const ZStr& sData, OidTag& oidResult)
   {
   stringstream srm;
   srm << sData;
   oidResult.Read(srm);
   if(oidResult.IsNull())
      return false;
   return true;
   }

