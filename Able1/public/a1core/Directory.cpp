#include <Able1.hpp>
using namespace Able1;

namespace Able1
   {

Directory::Directory(void)
   {
   //Get();    No! We need a NULL directory ability! (5/27/2002)
   }


Directory::Directory(const Directory& rDir)
   {
   *this = rDir;
   }


Directory::~Directory(void)
   {
   }

bool Directory::IsEmpty(void)
   {
      {
   Array<File> af;
   Query(af);
   if(af.Nelem())
      return false;
      }
   Array<Directory> ad;
   Query(ad);
   if(ad.Nelem())
      return false;
   return true;
   }

bool Directory::FromString(const ZStr& str)
   {
   return Name(str);
   }
const char *Directory::ToString(ZStr& str) const
   {
   str = Name();
   return str.c_str();
   }

bool Directory::Home(File& file) const
   {
   FilePath fp;
   ZStr sPath, sNode;
   fp.Chop(file.Name(), sPath, sNode, fp.PathChar());
   sPath = fp.Glue(Name(), sNode, fp.PathChar());
   return file.Name(sPath);
   }

bool Directory::Home(Directory& dir) const
   {
   FilePath fp;
   ZStr sPath, sNode;
   fp.Chop(dir.Name(), sPath, sNode, fp.PathChar());
   sPath = fp.Glue(Name(), sNode, fp.PathChar());
   return dir.Name(sPath);
   }

ZStr Directory::Home(const ZStr& sNode) const
   {
   FilePath fp;
   return fp.Glue(Name(), sNode, fp.PathChar());
   }

bool Directory::Exists(void) const
   {
   return Platform::DirectoryExists(sPwd);
   }


bool Directory::Name(const ZStr& sName)
   {
   // Cannot use FilePath::Open(rStr, *this) because folders 
   // do not have to exist upon creation...
   if(Platform::IsValidDirName(sName) == true)
      {
      FilePath fp;
      char ch = fp.PathChar();
      size_t whence = sName.Find(ch);
      if(whence != npos)    // 06/17/2004, R. Nagy
         {
#ifndef UNIX
         if(whence == 2 && sName[1] == ':')
#else
         if(whence == 0)
#endif
            {
            // Assign the absolute path name & return
            sPwd = sName;
            return true;
            }
         // It is NOT an absolute path name - we need to prefix it...            
         }
      // Prefix it with the current default directory
      Get();
      sPwd.Append(ch);
      sPwd.Append(sName);
      return true;
      }
   return false;
   }


ZStr Directory::Name(void) const
   {
   return ZStr(sPwd);
   }


const char *Directory::QueryNode(ZStr& str) const
   {
   FilePath fp;
   ZStr sPath;
   fp.Chop(sPwd, sPath, str, fp.PathChar());
   return str.c_str();
   }


ZStr Directory::QueryNode(void) const
   {
   ZStr str;
   QueryNode(str);
   return str;
   }


const char *Directory::QueryParent(ZStr& str) const
   {
   FilePath fp;
   ZStr sNode;
   fp.Chop(sPwd, str, sNode, fp.PathChar());
   return str.c_str();
   }

bool Directory::QueryParent(Directory& dir)  const    // Parent directory
   {
   if(dir.Name(QueryParent())) 
      return dir.Exists();
   return false;
   }

ZStr Directory::QueryParent(void) const
   {
   ZStr str;
   QueryParent(str);
   return str;
   }

bool Directory::Create(void) const
   {
   if(Platform::DirectoryCreate(sPwd))
      return true;
   return false;
   }


bool Directory::Remove(void) const
   {
   if(Platform::DirectoryRemove(sPwd.c_str()))
      return true;
   return false;
   }


bool Directory::Empty(void) const
   {
   return Platform::DirectoryEmpty(sPwd);
   }


bool Directory::Get(void)
   {
   return Platform::GetPwd(sPwd);
   }


bool Directory::Set(void)
   {
   return Platform::DirectoryChange(sPwd);
   }


bool Directory::Set(const ZStr& sDir)
   {
   if(Name(sDir) == true)
   {
      ZStr sHold = sPwd;
      sPwd = sDir;
      if(Set() == false)
         {
         sPwd = sHold;
         return false;
         }
      return true;
      }
   return false;
   }


bool Directory::Push(void)
   {
   return Platform::PushPwd(sStack);
   }


bool Directory::Pop(void)
   {
   if(Platform::PopPwd(sStack) == true)
      {
      Get();
      return true;
      }
   return false;
   }


void Directory::EmptyStack(void)
   {
   sStack = "";
   }


bool Directory::CreateDirectoryTree(void)
   {
   return Create();
   }


Directory& Directory::operator=(const Directory& rDir)
   {
   if(this == &rDir)
      return *this;
   sStack = rDir.sStack;
   sPwd   = rDir.sPwd;
   return *this;
   }


ostream& Directory::Write(ostream& os)
   {
   sStack.WriteStream(os);
   sPwd.WriteStream(os);
   return os;
   }


istream& Directory::Read(istream& is)
   {
   sStack.ReadStream(is);
   sPwd.ReadStream(is);
   return is;
   }


bool Directory::CreateTreeFor(File& file)
   {
   if(file.Exists())
      return true;

   ZStr sHold;
   sHold = sPwd;
   file.QueryParent(sPwd);

   bool br = Create();
   sPwd = sHold;
   return br;
   }

//#include <File_Fun.Hpp>

bool Directory::GoTo(void)
   {
   return Platform::DirectoryChange(sPwd.c_str());
   }

void Directory::Query(Array<File>& ary) const
   {
   FileSystem::Query(sPwd, ary);
   }

void Directory::Query(Array<Directory>& ary) const
   {
   FileSystem::Query(sPwd, ary);
   }

bool Directory::Launch(void)
   {
   File file;
   if(file.Name(Name()) == true)
      return file.Launch();
   return false;
   }

void Directory::QueryTree(Array<Directory>& aFileNames) const
   {
   Array<Directory> aDirs;
   Query(aDirs);

   for(size_t ssD = 0L; ssD < aDirs.Nelem(); ssD++)
      aDirs[ssD].QueryTree(aFileNames);

   aFileNames.Append(aDirs);
   }


void Directory::QueryTree(Array<File>& aFileNames) const
   {
   Array<Directory> aDirs;
   Query(aDirs);

   for(size_t ssD = 0L; ssD < aDirs.Nelem(); ssD++)
      aDirs[ssD].QueryTree(aFileNames);

   Array<File> files;
   Query(files);
   aFileNames.Append(files);
   }


   } // Able1
