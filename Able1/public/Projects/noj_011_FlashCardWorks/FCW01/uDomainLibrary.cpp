//---------------------------------------------------------------------------


#pragma hdrstop

#include "uDomainLibrary.h"
#pragma package(smart_init)

const ZStr DomainLibrary::sFileType     = ".FCW";
const ZStr DomainLibrary::sTestFileType = ".FCT";
const ZStr DomainLibrary::sPicket       = "\n[.FCW.]\n";

//---------------------------------------------------------------------------

bool DomainLibrary::Query(Array<File>& files)
   {
   Directory dir;
   if(Query(dir) == false)
      return false;
   dir.Query(files);
   return true;
   }

bool DomainLibrary::Home(File& file)
   {
   Directory dir;
   if(Query(dir) == false)
      return false;
   return dir.Home(file);
   }

bool DomainLibrary::Query(Directory& dir)
   {
   ProgramId pid;
   dir.Name(ZStr("Domains") + sFileType);
   pid.Home(dir);
   if(dir.Exists() == false)
      return dir.Create();
   return true;
   }

bool DomainLibrary::Read(const File& file, Array<FlashRecord>& aData)
   {
   Array<ZStr> array;
   if(PicketFile::Read(file, array, sPicket) == false)
      return false;
   FlashRecord rec;
   aData.AddZombies(array.Nelem());
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      ZStr& sRef = array[ss];
      if(sRef.IsNull())
         continue;
      if(rec.FromString(sRef) == false)
         {
         FlashRecord def;
         rec.sTag = def.sTag;
         rec.sValue = sRef;
         rec.Cleanup();
         aData.Append(rec);
         }
      else
         aData.Append(rec);
      }
   return true;
   }

bool DomainLibrary::Write(const File& file, Array<FlashRecord>& aData)
   {
   Array<ZStr> array;
   array.AddZombies(aData.Nelem());
   for(size_t ss = 0L; ss < aData.Nelem(); ss++)
      array[ss] = aData[ss].ToString();
   return PicketFile::Write(file, array, sPicket);
   }
