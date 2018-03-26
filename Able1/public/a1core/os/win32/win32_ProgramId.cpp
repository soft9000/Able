#include <a1core/ProgramId.hpp>
#define STRICT
#include <windows.h>

#define BEGIN {
#define END   }

using namespace Able1;

class _pid32 {
   public:
      static bool GetTemp(Directory& dir)                ; // A place for temporary files
      static bool GetProgram(Directory& dir)             ; // File where the executable resides
      static bool GetProgram(File& file)                 ; // Fully qualified executable
      static bool GetSystem(Directory& dir)              ; // This is the WINDOWS (system) directory. On unix, /etc might be a good place. Must be an pre-exisitng operating system defined location, and non-transient.
// 12/03/2004 - Obsolete - Will remove later on, along with any other ground clutter
//    static bool PutInDirectory(const Directory& dir, File& file) ; // Place in the directory
//    static bool PutInDirectory(File& file)             ; // Place the file in the default (program) directory
//    static bool PutInDirectory(Directory& dir)         ; // Place the leaf in the default (program) directory
//    static bool GetTemp(File& file)                    ; // Create a unique temporary file
//    static bool PutInTemp(File& file)                  ; // Put the file into the temp folder
//    static bool PutInTemp(Directory& dir)              ; // Put the directory tree into the temp dir
//    static bool PutInSubDirectory(const Directory& dirSub, File& file) ;
   };


const char *FullName(ZStr& str)
   {
   char *pszBuf = new char[MAX_PATH];
   ::GetModuleFileName(NULL, pszBuf, MAX_PATH);
   str = pszBuf;
   delete [] pszBuf;
   return str.c_str();
   }
const char *ProgramName(ZStr& str)
   {
   char *pszBuf = new char[MAX_PATH];
   ::GetModuleFileName(NULL, pszBuf, MAX_PATH);
   str = pszBuf;
   delete [] pszBuf;
   size_t sz = str.Rfind("\\");
   if(sz != npos)
      str.RemovePos(0, sz+1);
   return str.c_str();
   }
const char *PathTo(ZStr& str)
   {
   char *pszBuf = new char[MAX_PATH];
   ::GetModuleFileName(NULL, pszBuf, MAX_PATH);
   str = pszBuf;
   delete [] pszBuf;
   size_t sz = str.Rfind("\\");
   if(sz != npos)
      str.RemovePos(sz, str.Length());
   return str.c_str();
   }
const char *PlaceInDirectory(ZStr& str)
   {
   ZStr str2;
   PathTo(str2);
   str2.Append('\\');
   str2.Append(str);
   str = str2;
   return str.c_str();
   }
bool SetProgramDirectory(void)
   {
   ZStr sPath;
   if(::SetCurrentDirectory(PathTo(sPath)))
      return true;
   return false;
   }
const char *GetTempDirectory(ZStr& str)
   {
   BEGIN
   char pBuf[MAX_PATH + 1];
   if(GetTempPath(MAX_PATH, pBuf) == NULL)
      FullName(str);    // What if we are on a network drive, or a CDROM?
   else
      str = pBuf;
   END

   // Now here is the directory that WE will use for THIS program's TEMP storage;
   BEGIN
   ZStr str2;
   ProgramName(str2);
   str.Append(str2);
   END
   str.Append(".tmp");

   Directory dir;
   dir.Name(str);
   dir.CreateDirectoryTree(); // (sigh) Legacy - Assume it went okay...
   return str.c_str();
   }
const char *TempFileName(ZStr& str)
   {
   GetTempDirectory(str);
   ZStr sPwd;
   Directory dir1, dir2;
   dir1.Get();
   dir2.Set(str);
   /* Create a temporary filename for the current working directory: */
   ZStr str2 = tmpnam(NULL);     // ANSI
   dir1.Set();
   str.Append(str2);
   return str.c_str();
   }
const char *TempFileName(ZStr& str, const ZStr& sSuffix)
   {
   TempFileName(str);
   str.Append(sSuffix);
   return str.c_str();
   }
const char *PlaceInTempDirectory(ZStr& str)
   {
   ZStr str2;
   GetTempDirectory(str2);
   str2.Append('\\');
   str2.Append(str);
   str = str2;
   return str.c_str();
   }
const char *PlaceInSubDirectory(const ZStr& sSubdir, ZStr& sItem)
   {
   ZStr str2;
   PathTo(str2);
   str2.Append('\\');
   str2.Append(sSubdir);
   str2.Append('\\');
   str2.Append(sItem);
   sItem = str2;
   return sItem.c_str();
   }

bool QuerySystemDirectory(ZStr& str)
   {
   char WinDir[144];
   GetWindowsDirectory(WinDir, sizeof(WinDir));
   str = &WinDir[0];
   return true;
   }


bool _pid32::GetTemp(Directory& dir)
   {
   ZStr str;
   return dir.Name(GetTempDirectory(str));
   }
bool _pid32::GetProgram(Directory& dir)
   {
   ZStr str;
   return dir.Name(PathTo(str));
   }
bool _pid32::GetProgram(File& file)
   {
   ZStr str;
   return file.Name(FullName(str));
   }
bool _pid32::GetSystem(Directory& dir)
   {
   ZStr str;
   QuerySystemDirectory(str);
   return dir.Name(str);
   }
/*
bool _pid32::PutInDirectory(File& file)
   {
   ZStr str;
   file.QueryNode(str);
   return file.Name(PlaceInDirectory(str));
   }
bool _pid32::PutInDirectory(Directory& dir)
   {
   ZStr str = dir.Name();
   return dir.Name(PlaceInDirectory(str));
   }
bool _pid32::PutInSubDirectory(const Directory& sSubdir, File& file)
   {
   ZStr sName, sPath;
   FilePath::Chop(file.Name(), sPath, sName, '\\');
   sPath = sSubdir.Name();
   sPath += '\\';
   sPath += sName;
   return file.Name(sPath);
   }
bool _pid32::PutInTemp(File& file)
   {
   ZStr str = file.Name();
   size_t whence = str.Rfind('\\');
   if(whence != NPOS)
      str.RemovePos(0, whence+1);
   return file.Name(PlaceInTempDirectory(str));
   }
bool _pid32::PutInTemp(Directory& file)
   {
   ZStr str = file.Name();
   size_t whence = str.Rfind('\\');
   if(whence != NPOS)
      str.RemovePos(0, whence+1);
   return file.Name(PlaceInTempDirectory(str));
   }
bool _pid32::GetTemp(File& file)
   {
   ZStr str;
   TempFileName(str);
   return file.Name(str);
   }
*/
