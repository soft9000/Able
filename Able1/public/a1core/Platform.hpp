// 06/17/2003: Implemented a plausable DirectoryEmpty() for all platforms. Only tested on WIN32, R. Nagy
//
#ifndef zzPlatform_Hpp
#define zzPlatform_Hpp

namespace Able1
   {
/** Lowest level platform encapsulation of operating-system operations. Some overlap
  * with FileSystem.
  */   
class Platform
   {
   public:
      static bool ShellExec(const ZStr& sUrl, const ZStr& str);
      static bool ShellExec(const ZStr& sUrl);

      static bool GetPwd(ZStr& str);
      static bool PushPwd(ZStr& std);
      static bool PopPwd(ZStr& std);

      static bool DirectoryChange(const ZStr& sDir);
      static bool DirectoryExists(const ZStr& sDir);
      static bool IsValidDirName(const ZStr& std, bool bAllowDriveSpecifier = true);

      static bool FileRename(const ZStr& sFrom, const ZStr& sTo);
      static bool FileHide(const ZStr& sFileName);
      static bool FileShow(const ZStr& sFileName);
      static bool IsFileHidden(const ZStr& sFileName);
      static bool Touch(const ZStr& sFileName);

      static bool FileCopy(const ZStr&, const ZStr&);
      static bool FileReadable(const ZStr&);
      static bool FileWritable(const ZStr&);
      static bool FileExists(const ZStr&);

      static bool DirectoryRemove(const ZStr&);
      static bool DirectoryEmpty(const ZStr&); // Remove all files from a folder (ONLY). True on success.
      static bool DirectoryCreate(const ZStr&);
   };

   } // Able1

#endif
