#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;

#define OID_PARAM_TEST "QIDQTEST"


// Returns true if the OidTag is an OidParamTest
OidParamTest::OidParamTest(void) : OidSender(OID_PARAM_TEST)
   {
   }
bool OidParamTest::Respond(const OidTag& oidTag)
   {
   // STEP: Save our response
   ZStr sFile = oidRef.ValueFromTag("FILE");
   if(sFile.IsNull())
      return false;
   File file;
   if(file.Name(sFile) == false)
      return false;

   if(OidRegistry::RegServer::PushParam(oidRef.Name(), file, oidTag) == false)
      return false;

   // STEP: Complete the protocol
   sFile = oidRef.ValueFromTag("SEMAPHORE");
   if(sFile.IsNull())
      return false;
   if(file.Name(sFile) == false)
      return false;
   file.Remove();
   if(file.Exists())
      return false;
   return true;
   }
bool OidParamTest::Query(const File& fileClient, OidTag& oidResult, int iSec)
   {
   // STEP: Submit the QUERY protocol
   OidTag oidProtocol;
   oidProtocol.Name(OID_PARAM_TEST);
   File file;
   ProgramId id;
   id.GetProgram(file);
   oidProtocol.Update("FILE", file.Name());

   file.MkUniqueName();
   file.Create();
   oidProtocol.Update("SEMAPHORE", file.Name());

   if(Submit(fileClient, oidProtocol) == false)
      return false;

   // STEP: Wait for the response
   int iTimes = 0;
   while(file.Exists())
      {
      // SleepEx(1000, false);
      // STEP: Wait for a few platform-independant seconds ....
      time_t ttStart = time(NULL);
      time_t ttEnd   = ttStart + 3;
      while(ttEnd > ttStart)
         ttStart = time(NULL);

      // STEP: Time-about if the operation does not complete in about 10 seconds...
      iTimes++;
      if(iTimes == 5)
         {
         file.Remove();
         return false;
         }
      return true;
      }

   return OidRegistry::RegClient::PopParam(OID_PARAM_TEST, oidResult);
   }

