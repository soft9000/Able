#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;

bool OidController::Load(const File& file, OidList& oidList, ZStr& sError)
   {
   oidList.aTags.Empty();
   File fff = file;
   sError = "";
   ZStr sLine;
   istream& is = fff.OpenRead(File::AT_TEXT);   // Text, but it does not mater -
   Read(is, oidList, sError);
   if(sError.IsNull())
      return true;
   return false;
   }
bool OidController::Save(const File& file, const OidList& oidList)
   {
   File fff = file;
   ostream& os = fff.OpenWrite(File::AT_TEXT);
   Write(os, oidList);
   if(os.good())
      return true;
   return false;
   }
ostream&  OidController::Write(ostream& os, const OidList& oidList)
   {
   OidMeta oidMeta;
   return Write(os, oidList, oidMeta);
   }
ostream&  OidController::Write(ostream& os, const OidList& oidList, const OidMeta& om)
   {
   OidMeta oidMeta = om;
   for(size_t ss = 0L; ss < oidList.aTags.Nelem(); ss++)
      {
      OidTag& ref = oidList.aTags.Get(ss);
      if(ref.Name() == DEFAULT_META_TAG)
         {
         ref.Write(os, oidMeta);
         oidMeta.Use(ref);
         continue;
         }
      ref.Write(os, oidMeta);
      }
   return os;
   }
istream&  OidController::Read(istream& is, OidList& oidList, ZStr& sError)
   {
   OidMeta oidMeta;
   return Read(is, oidList, oidMeta, sError);
   }
istream&  OidController::Read(istream& is, OidList& oidList, const OidMeta& om, ZStr& sError)
   {
   OidMeta oidMeta = om;
   sError = "";
   OidTag oidTag;
   while(is)
      {
      oidTag.Read(is, oidMeta);
      if(!is)
         continue;
      if(oidTag.IsNull())
         {
         sError = "Error: Bad tag format.";
         return is;
         }
      if(oidTag.Name() == DEFAULT_META_TAG)
         oidMeta.Use(oidTag);

      oidList.aTags.Append(oidTag);
      }
   return is;
   }
bool OidController::ListObject(const ZStr sObjName, const OidList& oidList, OidList& aResult, bool bIgnoreCase)
   {
   aResult = OidList();

   ZStr sObject = sObjName;
   ZStr sObject2;
   if(bIgnoreCase == true)
      sObject.ToLower();
   for(size_t ss = 0L; ss < oidList.aTags.Nelem(); ss++)
      {
      OidTag& oid = oidList.aTags.Get(ss);
      sObject2 = oid.Name();
      if(bIgnoreCase == true)
         sObject2.ToLower();
      if(sObject == sObject2)
         aResult.aTags.Append(oid);
      }
   if(oidList.aTags.Nelem())
      return true;

   return false;
   }


bool OidController::Test(void)
   {
   File file;
   ProgramId pid;
   pid.GetProgram(file);

   OidTag oid1, oid2;

   if(oid1 != oid2)
      return false;

   // First time creates it -
   if(oid1.Update("NAME", "TODAY") == false)
      return false;

   if(oid1 == oid2)
      return false;

   // Next time updates it -
   if(oid1.Update("NAME", "TODAY") == false)
      return false;

   if(oid1 == oid2)
      return false;

   if(OidRegistry::RegServer::PushParam("TEST", file, oid1) == false)
      return false;

   if(OidRegistry::RegClient::PopParam("TEST", oid2) == false)
      return false;

   if(oid1 != oid2)
      return false;

   return true;
   }



