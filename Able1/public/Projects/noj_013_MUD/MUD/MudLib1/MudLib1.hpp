#include "DataFile.hpp"
#include "UpDownHome.hpp"
#include "mmVersion.hpp"

#include <extra/stdlog.hpp>
#include <obsolete/Server/FtpInfo.hpp>

namespace MudLib1
{
class DirtFile : public UpDownFile
   {
   public:
      mmVersion version;

      // True to continue, false to abort - (you set the error message on false)
      virtual bool OnBlock(const ZStr& sBlock, ostream& osResult);

      static bool Process(DirtFile& input);
   };

class MudFile  : public UpDownFile
   {
   public:
      mmVersion version;
      Array<DirtFile> aFiles;
   };

class Protocol
   {
   // The MUD file contains a map to all of the Multiply Updated Documents
   static bool Get(const Url& url, MudFile& mudFile);
   static bool Put(const Url& url, MudFile& mudFile, const FtpInfo& ftpUser);

   // The DIRT file contains a map to all of the encoded sections
   static bool Get(const Url& url, DirtFile& mudFile);
   static bool Put(const Url& url, DirtFile& mudFile, const FtpInfo& ftpUser);

   // What they have in common;
   static bool Get(UpDownFile& refCommon);
   static bool Put(UpDownFile& refCommon, const FtpInfo& ftpUser);
   };

class Process
   {
   static bool MUDUpdate(DirtFile& dirtFile, Array<Directory>& sPath, StdLog& sLog);
   static bool MUDUpdate(DirtFile& dirtFile, Directory& sPath, StdLog& sLog);

   static bool MUDDownload(DirtFile& dirtFile, Array<Directory>& sPath, StdLog& sLog);
   static bool MUDDownload(DirtFile& dirtFile, Directory& sPath, StdLog& sLog);

   static bool MUDSee(const DataFile& dataFile);
   };

