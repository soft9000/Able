#include <Able1.hpp>
using namespace Able1;

namespace Able1 {

// "Liberates" a name by removing any drive designations
// and platform specific path separations.
ZStr FilePath::LiberatedName(const ZStr& strIn, char chSep) 
{
   ZStr str = strIn;
   if(str[1] == ':')
      str.RemovePos(0, 1);
   if(chSep != '\\')
      str.Replace('\\', chSep);
   if(chSep != '/')
      str.Replace('/', chSep);
   return str;
}

// Always a nagging problem to solve...
ZStr FilePath::Glue(const ZStr& sFolder, const ZStr& sNode, char chSep)
   {
   ZStr sResult = sFolder;
   if(sResult.EndsWith(chSep) == false)
      sResult.Append(chSep);
   if(sResult.Find(chSep) != 0)
      sResult.Append(sNode);
   return sResult;
   }

bool FilePath::Chop(const ZStr& sName, ZStr& sPath, ZStr& sFile, char chSep)
   {
   sPath = sFile = "";
   size_t whence = sName.Rfind(chSep);
   if(whence == NPOS)
      {
      sPath = sName;
      return false;
      }

   sPath = sName.Substr(0, whence);
   if(chSep)
      while(sPath.EndsWith(chSep))
         sPath.Remove(sPath.Length() - 1);

   sFile = sName.Substr(whence+1, sName.Length());
   if(chSep)
      while(sFile[0] == chSep)
         sFile.RemovePos(0, 1);

   return true;
   }

} // Able1

#ifdef UNIX
#include <a1core/os/unix/unix_FilePath.cpp>
#endif

#ifdef MSDOS
#include <a1core/os/msdos/msdos_FilePath.cpp>
#endif

#ifdef WIN32
#include <a1core/os/win32/win32_FilePath.cpp>
#endif


