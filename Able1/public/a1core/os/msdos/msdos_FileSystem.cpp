#include <Able1.hpp>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <fnmatch.h>

/* TODO : 16 bit FileSystem needs implemented.  WIN32 version is more complete. Can borrow much from there... */

namespace Able1
   {

size_t FileSystem::Query(const ZStr& path, Array<Node>& aResult)
   {
   return NULL;
   }
size_t FileSystem::Query(const ZStr& path, Array<File>& aResult)
   {
   return NULL;
   }
size_t FileSystem::Query(const ZStr& path, Array<Directory>& aResult)
   {
   return NULL;
   }
bool FileSystem::Create(Node& node)
   {
   return false;
   }
bool FileSystem::Create(File& file)
   {
   return false;
   }
bool FileSystem::Create(Directory& dir)
   {
   return false;
   }
bool FileSystem::Delete(Node& node)
   {
   return false;
   }
bool FileSystem::Delete(File& file)
   {
   return false;
   }
bool FileSystem::Delete(Directory& dir)
   {
   return false;
   }
PortTime FileSystem::Query(const Node& node)
   {
   PortTime pt;
   return pt;
   }
PortTime FileSystem::Query(const File& file)
   {
   PortTime pt;
   return pt;
   }
PortTime FileSystem::Query(const Directory& dir)
   {
   PortTime pt;
   return pt;
   }
bool FileSystem::Touch(Node& node, PortTime& pt)
   {
   return false;
   }
bool FileSystem::Touch(File& file, PortTime& pt)
   {
   return false;
   }
bool FileSystem::Touch(Directory& dir, PortTime& pt)
   {
   return false;
   }

   } // Able1
