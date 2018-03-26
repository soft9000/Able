#include <Able1.hpp>
using namespace Able1;

ZStr DynamicPicketFile::ReadTag(const File& file)
   {
   ZStr str;
   if(file.Exists())
      {
      File file = file;
      str.ReadLine(file.OpenRead());
      }
   return str;
   }

bool DynamicPicketFile::Recall(const File& file, ZStr& sResult, size_t ssPos)
   {
   ZStr sTag = ReadTag(file);
   if(sTag.IsNull())
      return false;
   return PicketFile::Recall(file, sResult, sTag, ssPos);
   }

bool DynamicPicketFile::Recall(const File& file, ZStr& sResult)
   {
   ZStr sTag = ReadTag(file);
   if(sTag.IsNull())
      return false;
   return PicketFile::Recall(file, sResult, sTag);
   }

bool DynamicPicketFile::Write(const File& file, Array<ZStr>& aResult)
   {
   ZStr sTag = ReadTag(file);
   if(sTag.IsNull())
      return false;
   return PicketFile::Write(file, aResult, sTag);
   }

bool DynamicPicketFile::Read(const File& file, Array<ZStr>& aResult)
   {
   ZStr sTag = ReadTag(file);
   if(sTag.IsNull())
      return false;
   return PicketFile::Read(file, aResult, sTag);
   }
