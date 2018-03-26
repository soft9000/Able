#include <Able1.hpp>
using namespace Able1;

#ifdef WIN32
// This is a special layer designed to encapsulate the WIN32 API.
// It is required to support our legacy on this platform
// (i.e. We did not have to call SetProgram() to query system defaults)
#include <a1core/os/win32/win32_ProgramId.cpp>
#endif


namespace Able1
   {

bool ProgramId::SetProgram(const ZStr &sFQFileName)
   {
   File file;
   if(file.Name(sFQFileName) == false)
      return false;
   if(file.Exists() == false)
      return false;
   sFQFileNameEX = sFQFileName;
   return true;
   }


bool ProgramId::PutInDirectory(const Directory& dir, File& file) const
   {
   ZStr str, str1;
   str = dir.Name();
   str.Append(PathSep());
   str.Append(file.QueryNode(str1));
   return file.Name(str);
   }


bool ProgramId::PutInDirectory(File& file) const
   {
   Directory dir;
   if(GetProgram(dir) == false)
      return false;
   ZStr str = dir.Name();
   str += PathSep();
   str += file.QueryNode();
   return file.Name(str);
   }


bool ProgramId::PutInDirectory(Directory& dirSub) const
   {
   Directory dir;
   if(GetProgram(dir) == false)
      return false;
   ZStr str = dir.Name();
   str += PathSep();
   str += dirSub.QueryNode();
   return dirSub.Name(str);
   }


bool ProgramId::PutInSubDirectory(const Directory& sSubdir, File& file) const
   {
   ZStr sName, sPath;
   FilePath::Chop(file.Name(), sPath, sName, '\\');
   sPath = sSubdir.Name();
   sPath += '\\';
   sPath += sName;
   return file.Name(sPath);
   }


ZStr ProgramId::Concat(const ZStr& sSubdir, const ZStr& sItem, char sep) const
   {
   ZStr sResult = sSubdir;
   sResult.Append(sep);
   sResult.Append(sItem);
   return sResult;
   }


ZStr ProgramId::Concat(const ZStr& sSubdir, const ZStr& sItem) const
   {
   return Concat(sSubdir, sItem, PathSep());
   }


bool ProgramId::PutInTemp(File& file) const
   {
   Directory dir;
   if(GetTemp(dir) == false)
      return false;
   ZStr str = dir.Name();
   str += PathSep();
   str += file.QueryNode();
   return file.Name(str);
   }


bool ProgramId::PutInTemp(Directory& file) const
   {
   Directory dir;
   if(GetTemp(dir) == false)
      return false;
   ZStr str = dir.Name();
   str += PathSep();
   str += file.QueryNode();
   return file.Name(str);
   }


bool ProgramId::GetTemp(File& file) const
   {
   Directory dir;
   if(GetTemp(dir) == false)
      return false;
   ZStr str = dir.Name();

   Directory dHold;
   dHold.Get(); // push

   // Create a temporary filename within a current working directory...
   dir.Set();
   ZStr sTemp = ::tmpnam(NULL);     // ANSI

   dHold.Set(); // pop

   str += PathSep();
   str += sTemp;
   return file.Name(str);
   }


bool ProgramId::GetTemp(Directory& dir) const
   {
   ZStr str = ::getenv("TEMP");
   // First we check the environment usual variable
   if(str.IsNull() == false)
      {
      if(dir.Name(str) == true)
         return true;
      }
   // Next, any program override
   if(sFQFileNameEX.IsNull() == false)
      {
      ZStr str = sFQFileNameEX;
      size_t whence = str.Rfind(PathSep());
      if(whence != npos)
         {
         str.Remove(whence);
         if(dir.Name(str) == true)
            {
            whence = str.Find(PathSep()); // might already be "C:\" or "/" ...
            if(whence != npos)
               str.Remove(whence);        // if not, make it so
            str += PathSep();             // and put it on the root of the default device ...
            str += "TMP";
            return dir.Name(str);         // (should always work)
            }
         }
      }
#ifdef WIN32
   // Our WIN32 legacy is not required to call SetProgram - it used the WIN32 API ...
   return _pid32::GetTemp(dir);
#else   
   return false;
#endif
   }



bool ProgramId::GetProgram(Directory& dir) const
   {
   if(sFQFileNameEX.IsNull() == false)
      {
      ZStr str = sFQFileNameEX;
      size_t whence = str.Rfind(PathSep()); 
      if(whence != npos)
         {
         str.Remove(whence);
         if(dir.Name(str) == true)
            return dir.Exists();
         }

      }
#ifdef WIN32
   // Our WIN32 legacy is not required to call SetProgram - it used the WIN32 API ...
   return _pid32::GetProgram(dir);
#else   
   return false;
#endif
   }


bool ProgramId::GetProgram(File& file) const
   {
   bool br = false;
   if(sFQFileNameEX.IsNull() == false)
      br = file.Name(sFQFileNameEX);
#ifdef WIN32
   // Our WIN32 legacy is not required to call SetProgram - it used the WIN32 API ...
   br = _pid32::GetProgram(file);
#endif
   return br;
   }


bool ProgramId::GetSystem(Directory& dir) const
   {
#ifdef WIN32
   // Our WIN32 legacy is not required to call SetProgram - it used the WIN32 API ...
   return _pid32::GetSystem(dir);
#else
   // This will usually work for both DOS and UNIX (a permission thing if it fails on POSIX) -
   ZStr str = PathSep();
   str += "etc";
   return dir.Create();
#endif
   }

// Place the file in the program's home (start-up) location
bool ProgramId::Home(File& file)                       const
   {
   Directory dir;
   if(GetProgram(dir) == true)
      return dir.Home(file);
   return false;
   }

// Place the file in the program's home (start-up) location
bool ProgramId::Home(Directory& file)                  const
   {
   Directory dir;
   if(GetProgram(dir) == true)
      return dir.Home(file);
   return false;
   }
   
// Place the file in the program's home (start-up) + sub dir location
ZStr ProgramId::Home(const ZStr sSubDir, const ZStr& sNode, char cSep) const
   {
   if(!cSep)
      cSep = PathSep();
   Directory dir;
   ZStr sResult;
   if(GetProgram(dir) == true)
      {
      sResult = Concat(sSubDir, sNode, cSep);
      sResult = Concat(dir.Name(), sResult, cSep);
      }
   return sResult;
   }


}

namespace Able1
   {
ProgramId pid;
   }


