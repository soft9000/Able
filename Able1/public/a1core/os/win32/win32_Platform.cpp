#include <cstdio> // unlink()

#include <sys/stat.h>
#include <fstream>
#include <ctime>             // time_t

#ifdef UNIX
#include <unistd.h>
#endif

#ifdef WIN32
#define STRICT
#include <windows.h>
#include <shellapi.h>// shellexecute()
#endif

const int HUGE_PATH = 1024;


inline bool TOBOOL(BOOL a)
   {
   if(a == TRUE)
      return true;
   return false;
   }

namespace Able1
{

bool Platform::ShellExec(const ZStr& sUrl, const ZStr& str) 
{
if(int(ShellExecute(NULL, "open", sUrl.c_str(), str.c_str(), NULL, SW_SHOWNORMAL)) <= 32)
   return false;
return true;
}

bool Platform::ShellExec(const ZStr& sUrl) 
{
if(int(ShellExecute(NULL, "open", sUrl.c_str(), NULL, NULL, SW_SHOWNORMAL)) <= 32)
   return false;
return true;
}

bool Platform::GetPwd(ZStr& str) 
{
   bool br = false;
   char *pBuf = new char[MAX_PATH + 1];
   if(GetCurrentDirectory(MAX_PATH, pBuf))
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
   if(GetCurrentDirectory(MAX_PATH, pBuf))
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
   if(::SetCurrentDirectory(sDir.c_str()))
      br = true;
   str.Remove(sz);
   return br;
}

bool Platform::DirectoryChange(const ZStr& sDir) 
{
   if(::SetCurrentDirectory(sDir.c_str()))
      return true;
   return false;
}

bool Platform::DirectoryExists(const ZStr& sDir) 
{
   bool br = false;
   ZStr str;
   PushPwd(str);
   if(::SetCurrentDirectory(sDir.c_str()))
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
   if(::MoveFile(pszFrom.c_str(), pszTo.c_str()))
      return true;
   return false;
}

bool Platform::FileHide(const ZStr& sFileName)
{
   bool br = false;
   HANDLE hFile = ::CreateFile(sFileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hFile == INVALID_HANDLE_VALUE)
      return br;

   DWORD dw = ::GetFileAttributes(sFileName.c_str());
   if(dw == 0xFFFFFFFF)
      return br;

   dw |= FILE_ATTRIBUTE_HIDDEN;

   br = false;
   if(::SetFileAttributes(sFileName.c_str(), dw))
      br = true;

   ::CloseHandle(hFile);
   return br;
}

bool Platform::FileShow(const ZStr& sFileName)
{
   bool br = false;
   HANDLE hFile = ::CreateFile(sFileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hFile == INVALID_HANDLE_VALUE)
      return br;

   DWORD dw = ::GetFileAttributes(sFileName.c_str());
   if(dw == 0xFFFFFFFF)
      return br;

   dw ^= FILE_ATTRIBUTE_HIDDEN;

   br = false;
   if(::SetFileAttributes(sFileName.c_str(), dw))
      br = true;

   ::CloseHandle(hFile);
   return br;
}

bool Platform::IsFileHidden(const ZStr& sFileName)
{
   Node node;
   FilePath::Open(sFileName, node);
   return node.IsHidden();
}

bool Platform::Touch(const ZStr& sFileName)
{
   SYSTEMTIME st;
   ::GetSystemTime(&st);
   FILETIME ft;
   if(::SystemTimeToFileTime(&st, &ft) == false)
      return false;

   HANDLE hFile = ::CreateFile(sFileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hFile == INVALID_HANDLE_VALUE)
      return false;

   if(::SetFileTime(hFile, &ft, &ft, &ft) == false)
      {
      ::CloseHandle(hFile);
      return false;
      }
   ::CloseHandle(hFile);
   return true;
}

bool Platform::FileCopy(const ZStr& strFrom, const ZStr& strTo)
{
   // file is over written if it alReady exists
   if(::CopyFile(strFrom.c_str(), strTo.c_str(), FALSE))
      return true;
   return false;
}

bool Platform::FileReadable(const ZStr& str)
{
   Node node;
   FilePath::Open(str, node);
   return node.IsRead();
}

bool Platform::FileWritable(const ZStr& str)
{
   Node node;
   FilePath::Open(str, node);
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
   if(::RemoveDirectory(str.c_str()))
      return true;
   return false;
}

bool Platform::DirectoryEmpty(const ZStr& sPwd) 
{
   bool br = true;
   Array<File> ary;
   FileSystem::Query(sPwd, ary);
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
// Copied this from my Archive class;
   bool br = false;
   char *pBuf = new char[MAX_PATH];
   if(::GetCurrentDirectory(MAX_PATH, pBuf))
      {
      ZStr sDest = str;     // a ZStr that we can "eat".
      long sp = sDest.Find('\\');
      if(sDest[1] == ':')
         sp = sDest.Find('\\');

      while(size_t(sp) != NPOS)
         {
         ZStr sTrunk;
         sDest.CopyPos(sTrunk, 0, sp);

         if(::SetCurrentDirectory(sTrunk.c_str()))
            br = true;
         else
            br = false;

         if(br == false)
            {
            br = TOBOOL(::CreateDirectory(sTrunk.c_str(), NULL));
            }

         if(br == false)
            goto DONE_IT1333;     // Could only be too deep, or an access violation.
         sp = (size_t)sDest.Find('\\', size_t(sp)+1);
         }
      br = TOBOOL(::CreateDirectory(sDest.c_str(), NULL));
      }
   DONE_IT1333:
   ::SetCurrentDirectory(pBuf);
   delete [] pBuf;
   return br;
}

} // Able1
