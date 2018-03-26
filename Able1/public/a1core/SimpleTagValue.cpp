#include <Able1.hpp>
using namespace Able1;

ZStr SimpleTagValue::sTagSync = "NeLeN(.)";

SimpleTagValue::SimpleTagValue(void)
   {
   }

SimpleTagValue::SimpleTagValue(const ZStr& sT, const ZStr& sV)
   {
   sTag = sT; sValue = sV;
   }

SimpleTagValue::SimpleTagValue(const ZStr& sT, int iVal)
   {
   sTag   = sT; 
   sValue.Assign(iVal);
   }

bool SimpleTagValue::IsNull(void)
   {
   if(sTag.IsNull() && sValue.IsNull())
      return true;
   return false;
   }

ostream& SimpleTagValue::Write(ostream& os)
   {
   sTag.WriteStream(os);
   sValue.WriteStream(os);
   return os;
   }

istream& SimpleTagValue::Read(istream& is)
   {
   sTag.ReadStream(is);
   sValue.ReadStream(is);
   return is;
   }

size_t SimpleTagValue::TallyArray(const File& file)
   {
   SimpleTagValue rec;
   File fff = file;
   istream& is = fff.OpenRead(File::AT_BINARY);
   rec.Read(is);
   if(!is)
      return 0L;
   if(rec.sTag != sTagSync)
      return 0L;
   return (size_t) rec.sValue.AsLong();
   }

bool SimpleTagValue::LoadArray(const File& file, Array<SimpleTagValue>& result)
   {
   SimpleTagValue rec;
   File fff = file;
   istream& is = fff.OpenRead(File::AT_BINARY);
   rec.Read(is);
   if(!is)
      return false;

   if(rec.sTag != sTagSync)
      return false;

   result.AddZombies(rec.sValue.AsLong());
   while(is)
      {
      rec.Read(is);
      if(!is)
         break;
      result.Append(rec);
      }
   return true;
   }

size_t SimpleTagValue::TallyHeap(const File& file)
   {
   SimpleTagValue rec;
   size_t szCount = 0L;
   File fff = file;
   istream& is = fff.OpenRead(File::AT_BINARY);
   while(is)
      {
      rec.Read(is);
      if(!is)
         break;
      szCount++;
      }
   return szCount;
   }

bool SimpleTagValue::LoadHeap(const File& file, Array<SimpleTagValue>& result)
   {
   SimpleTagValue rec;
   size_t szCount = TallyHeap(file);
   if(!szCount)
      return false;
   File fff = file;
   istream& is = fff.OpenRead(File::AT_BINARY);
   while(is)
      {
      rec.Read(is);
      if(!is)
         break;
      result.Append(rec);
      }
   return true;
   }

size_t SimpleTagValue::TallyTag(Array<SimpleTagValue>& array, const ZStr& sTag)
   {
   size_t szCount = 0L;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      SimpleTagValue& result = array[ss];
      if(result.sTag == sTag)
         szCount++;
      }
   return szCount;
   }

Array<SimpleTagValue> SimpleTagValue::FindTag(Array<SimpleTagValue>& array, const ZStr& sTag)
   {
   Array<SimpleTagValue> ares;
   size_t szCount = TallyTag(array, sTag);
   if(!szCount)
      return ares;

   ares.AddZombies(szCount);
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      SimpleTagValue& result = array[ss];
      if(result.sTag == sTag)
         ares.Append(result);
      }
   return ares;
   }

SimpleTagValue SimpleTagValue::FindFirstTag(Array<SimpleTagValue>& array, const ZStr& sTag)
   {
   Array<SimpleTagValue> ares = FindTag(array, sTag);
   SimpleTagValue result;
   if(ares.Nelem())
      result = ares[0];
   return result;
   }

bool SimpleTagValue::WriteTagedSeries(Array<ZStr>& array, const ZStr& sTag, ostream& os)
   {
   SimpleTagValue rec(sTagSync, array.Nelem());
   rec.Write(os);
   if(!os)
      return false;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      rec = SimpleTagValue(sTag, array[ss]);
      rec.Write(os);
      if(!os)
         return false;
      }
   return true;
   }


bool SimpleTagValue::ReadTagedSeries(Array<ZStr>& result, const ZStr& sTag, istream& is)
   {
   SimpleTagValue rec;
   rec.Read(is);
   if(!is)
      return false;
   if(rec.sTag != sTagSync)
      return false;

   size_t max = rec.sValue.AsInt();
   result.AddZombies(max);

   for(size_t ss = 0L; ss < max; ss++)
      {
      rec.Read(is);
      if(!is)
         return false;
      result.Append(rec.sValue);
      }
   return true;
   }