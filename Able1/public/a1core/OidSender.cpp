#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;


bool OidSender::IsObject(const ZStr& str)
   {
   if(oidRef.Name() == str)
      return true;
   return false;
   }
// Returns true if the OidTag is an OidSender
bool OidSender::Use(const OidTag& oidTag)
   {
   if(IsObject(oidRef.Name()) == false)
      return false;
   oidRef = oidTag;
   return true;
   }
bool OidSender::Submit(const File& fileClient, const OidTag& oidParam)
   {
   if(fileClient.Exists())
      return false;

   if(OidRegistry::RegServer::Invoke(oidParam.Name(), fileClient, oidParam) == false)
      return false;
      
   return true;
   }

