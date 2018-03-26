
THIS CLASS IS OBSOLETE. USE IT TO COMPLETE THE FILE AND DIRECTORY CLASSES, THEN DELETE IT.

#include <Able1.hpp>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <fnmatch.h>
namespace Able1
   {

void NodeWalker::Start(void)
   {
   }
bool NodeWalker::GetDirectory(ZStr& sDir)
   {
   char buf[PATH_MAX+2];
   if(::getcwd(&buf[0], PATH_MAX) != 0)
      {
      sDir = &buf[0];
      return true;
      }
   return false;
   }
bool NodeWalker::SetDirectory(const ZStr& sDir)
   {
   if(::chdir(sDir.c_str()) == 0)
      return true;
   return false;
   }
bool NodeWalker::PushPwd(ZStr& std)
   {
   bool br = false;
   ZStr sBuf;
   if(GetDirectory(sBuf))
      {
      std.Append(";");
      std.Append(sBuf);
      br = true;
      }
   return br;
   }
bool NodeWalker::PopPwd(ZStr& std)
   {
   bool br = false;
   size_t sz = std.rfind(";");
   if(sz == NPOS)
      return false;
   ZStr sDir;
   std.CopyPos(sDir, sz+1, std.Length());
   if(SetDirectory(sDir.c_str()))
      br = true;
   std.Remove(sz);
   return br;
   }
bool NodeWalker::FirstNode(const ZStr& sDir, Node& node)
   {
   return false;
   }
bool NodeWalker::NextNode(Node& FindFileData)
   {
   return false;
   }
void NodeWalker::LastNode(void)
   {
   }

   } // Able1
