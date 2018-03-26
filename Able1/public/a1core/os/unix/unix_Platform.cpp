#include <Able1.hpp>

#include <fstream>
#include <ctime>             // time_t

#include <sys/stat.h>
#include <unistd.h>

const int HUGE_PATH = 1024;

/* TODO : Need to implement several POSIX platform equivalents here. */

namespace Able1
{

bool Platform::ShellExec(const ZStr& sUrl, const ZStr& str)
{
return false;
}

bool Platform::ShellExec(const ZStr& sUrl)
{
return false;
}

bool Platform::GetPwd(ZStr& str)
{
   bool br = false;
   char *pBuf = new char[MAX_PATH + 1];
   if(::getcwd(pBuf, MAX_PATH) != NULL)
      {
      str = pBuf;
      br = true;
      }
   delete [] pBuf;
   return br;
}

bool Platform::PushPwd(ZStr& str)
{
   bool br = false;
   char *pBuf = new char[MAX_PATH + 1];
   if(::getcwd(pBuf, MAX_PATH))
      {
      str.Append(";");
      str.Append(pBuf);
      br = true;
      }
   delete [] pBuf;
   return br;
}

bool Platform::PopPwd(ZStr& str) 
{
   bool br = false;
   size_t sz = str.Rfind(";");
   if(sz == NPOS)
      return false;
   ZStr sDir;
   str.CopyPos(sDir, sz+1, str.Length());
   if(::chdir(sDir.c_str()))
      br = true;
   str.Remove(sz);
   return br;
}

bool Platform::DirectoryChange(const ZStr& sDir) 
{
   if(::chdir(sDir.c_str()))
      return true;
   return false;
}

bool Platform::DirectoryExists(const ZStr& sDir) 
{
   bool br = false;
   ZStr str;
   PushPwd(str);
   if(::chdir(sDir.c_str()))
      br = true;
   PopPwd(str);
   return br;
}

bool Platform::IsValidDirName(const ZStr& str, bool bAllowDriveSpecifier)
{
   if(str.IsNull())
      return false;

   if(str.Find('/') != NPOS)
      return false;
   if(str.Find('*') != NPOS)
      return false;
   if(str.Find('?') != NPOS)
      return false;
   if(str.Find('\"') != NPOS)
      return false;
   if(str.Find('<') != NPOS)
      return false;
   if(str.Find('>') != NPOS)
      return false;
   if(str.Find('|') != NPOS)
      return false;

   if(bAllowDriveSpecifier == true)
      {
      size_t ss = str.Find(':');
      if(ss != NPOS)
         {
         if(ss != 1)
            return false;
         return IsValidDirName(&str[ss+1], false);
         }
      }
   else
      {
      if(str.Find(':') != NPOS)
         return false;
      }
   return true;
}

bool Platform::FileRename(const ZStr& pszFrom, const ZStr& pszTo)
{
   if(::rename(pszFrom.c_str(), pszTo.c_str()) == 0)
      return true;
   return false;
}

bool Platform::FileHide(const ZStr& sFileName)
{
   bool br = false;
   return br;
}

bool Platform::FileShow(const ZStr& sFileName)
{
   bool br = false;
   return br;
}

bool Platform::IsFileHidden(const ZStr& sFileName)
{
   File node;
   FilePath fs;
   fs.Open(sFileName, node);
   return node.IsHidden();
}

bool Platform::Touch(const ZStr& sFileName)
{
   bool br = false;
   return br;
}

bool Platform::FileCopy(const ZStr& strFrom, const ZStr& strTo)
{
   bool br = false;
   return br;
}

bool Platform::FileReadable(const ZStr& str)
{
   Node node;
   FilePath fs;
   fs.Open(str, node);
   return node.IsRead();
}

bool Platform::FileWritable(const ZStr& str)
{
   Node node;
   FilePath fs;
   fs.Open(str, node);
   return node.IsWrite();
}

bool Platform::FileExists(const ZStr& str)
{
   struct stat info;
   if(::stat(str.c_str(), &info) != 0)
      return false;
   return true;
}

bool Platform::DirectoryRemove(const ZStr& str)
{
   bool br = false;
   if(::rmdir(str.c_str()) == 0)
      br = true;
   return br;
}

bool Platform::DirectoryEmpty(const ZStr& sPwd)
{
   bool br = true;
   Array<File> ary;
   FileSystem fs;
   fs.Query(sPwd, ary);
   for(size_t ss = 0L; ss < ary.Nelem(); ss++)
      {
      // We will give it our best try...
      if(ary[ss].Remove() == false)
         br = false;
      }
   return br;
}

bool Platform::DirectoryCreate(const ZStr& str)
{
   bool br = false;
   if(::mkdir(str.c_str(), S_IRWXU) == 0)
      br = true;
   return br;
}

} // Able1
