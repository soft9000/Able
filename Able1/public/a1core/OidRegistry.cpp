#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;

#define OID_PARAM "-OID="

ZStr OidRegistry::HashName(const File& fileResult)
   {
   ZStr str = fileResult.Name();
   str.Replace(PathChar(), ".");
   str.Replace(":", ".");
   str.Append(".oid");
   return str;
   }
bool OidRegistry::Exists(const ZStr& sParamID, const File& file)
   {
   File fileIPC;
   OidRegistry::RegServer::GetFile(file, sParamID, fileIPC);
   return fileIPC.Exists();
   }
bool OidRegistry::QueryRootRegistry(Directory& dirHome)
   {
   Directory dirSys;
   if(dirHome.Name("OidReg") == false)
      return false;
   ProgramId pid;
   if(pid.GetSystem(dirSys) == false)
      return false;
   if(dirSys.Home(dirHome) == false)
      return false;
   if(dirHome.Exists())
      return true;
   return dirHome.Create();
   }
bool OidRegistry::QueryServerRegistry(Directory& dirHome, const ZStr& sParamID, bool bCreate)
   {
   ProgramId pid;
   File file;
   if(dirHome.Name(sParamID) == false)
      return false;
   Directory dirSys;
   if(QueryRootRegistry(dirSys) == false)
      return false;
   if(bCreate)
      dirSys.Create();
   if(dirSys.Home(dirHome) == false)
      return false;
   if(bCreate)
      dirHome.Create();
   if(dirHome.Exists())
      return true;
   return false;
   }
bool OidRegistry::RegClient::GetFile(const ZStr& sParamID, File& fileResult)
   {
   Directory dirHome;
   if(QueryServerRegistry(dirHome, sParamID, false) == false)
      return false;
   ProgramId pid;
   pid.GetProgram(fileResult);
   if(fileResult.Name(HashName(fileResult)) == false)
      return false;
   if(dirHome.Home(fileResult) == false)
      return false;
   return fileResult.Exists();
   }
bool OidRegistry::RegClient::PopParam(const ZStr& sParamID, OidTag& ref)
   {
   File file;
   if(GetFile(sParamID, file) == false)
      return false;
   ref.Read(file.OpenRead());
   file.Close();
   file.Remove();
   return !(ref.IsNull());
   }
bool OidRegistry::RegClient::Recall(int argc, char *argv[], Array<ZStr>& aParams)
   {
   stringstream srm;
   for(int ss = 0L; ss < argc; ss++)
      srm << argv[ss] << " ";
   ZStr str = srm.str().c_str();
   return Recall(str, aParams);
   }
bool OidRegistry::RegClient::Recall(const ZStr& str, Array<ZStr>& aParams)
   {
   ZStr sResult;
   size_t pos = str.Find(OID_PARAM);
   if(pos == npos)
      return false;
   sResult = str;
   sResult.RemovePos(0, pos);
   pos = str.Find('=');
   sResult.RemovePos(0, pos);
   sResult.MkWhite();
   sResult.Strip();
   if(sResult.Split(' ', aParams) == false)
      return false;
   for(size_t ss = 0L; ss < aParams.Nelem(); ss++)
      aParams[ss].Strip();
   if(aParams.Nelem())
      return true;
   return false;
   }



bool OidRegistry::RegServer::GetFile(const File& fileProgram, const ZStr& sParamID, File& fileResult)
   {
   Directory dirHome;
   if(QueryServerRegistry(dirHome, sParamID, true) == false)
      return false;
   ProgramId pid;
   pid.GetProgram(fileResult);
   if(fileResult.Name(HashName(fileResult)) == false)
      return false;
   return dirHome.Home(fileResult);
   }
bool OidRegistry::RegServer::PushParam(const ZStr& sParamID, const File& fileClient, const OidTag& ooo)
   {
   OidTag oid = ooo;
   File fileIPC;
   if(GetFile(fileClient, sParamID, fileIPC) == false)
      return false;
   oid.Write(fileIPC.OpenWrite());
   fileIPC.Close();
   return fileIPC.Exists();
   }
bool OidRegistry::RegServer::Invoke(const ZStr& sParamID, const File& fileClient, const OidTag& ooo)
   {
   if(PushParam(sParamID, fileClient, ooo) == false)
      return false;
   ZStr str = OID_PARAM;
   str += sParamID;
   return Platform::ShellExec(fileClient.Name(), str);
   }
bool OidRegistry::RegServer::Query(const File& fileTo, OidTag& oid)
   {
   return OidParamQuery::Query(fileTo, oid, 10);
   }
