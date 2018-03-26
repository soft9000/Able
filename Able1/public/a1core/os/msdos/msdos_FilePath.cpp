/* TODO 1 -cFilePath : Test this feature set. */
// Ref: <core/Node.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Able1
   {
char FilePath::PathChar(void)
   {
   return '\\';
   }
bool FilePath::Open(const ZStr& sPath, Node& result)
   {
   Node blanker;
   result = blanker;
   struct stat info;
   if(::stat(sPath.c_str(), &info) != 0)
      return false;
   result.IsOnline(true);
   result.FullName(sPath);
   if(S_ISDIR(info.st_mode))
      result.IsDir(true);
   if(info.st_mode & S_IRUSR)
      result.IsRead(true);    // owner relative, only
   result.SetCreateDateTime(info.st_ctime);
   result.SetModDateTime(info.st_mtime);
   result.SetAccessDateTime(info.st_atime);
   result.file_size.SetSize(info.st_size);  // off_t
   return true;
   }
bool FilePath::Open(const ZStr& sPath, File& result)
   {
   Node basic;
   if(Open(sPath, basic) == false)
      return false;
   if(basic.IsDir() == true)
      return false;
   if(result.Name(sPath) == false)
      return false;
   if(result.Exists() == false)
      return false;
   return true;
   }
bool FilePath::Open(const ZStr& sPath, Directory& result)
   {
   Node basic;
   if(Open(sPath, basic) == false)
      return false;
   if(basic.IsDir() == false)
      return false;
   if(result.Name(sPath) == false)
      return false;
   if(result.Exists() == false)
      return false;
   return true;
   }

   } // Able1

 
