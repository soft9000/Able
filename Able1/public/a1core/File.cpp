#include <Able1.hpp>
using namespace Able1;

#define DEFAULT_FILE_NAME "default.file"

namespace Able1
   {

void File::_init(void)
   {
   _bDestructorDeletes = false;
   }


File::File(void) : pIOStream(NULL)
   {
   _init();
   sFQName = DEFAULT_FILE_NAME;
   Qualify(sFQName);
   }


File::File(const File& rf) : pIOStream(NULL)
   {
   _init();
   *this = rf;
   }


File::File(const ZStr& stdName) : pIOStream(NULL)
   {
   _init();
   Name(stdName);
   }


File::~File(void)
   {
   if(pIOStream)
      Close();
   delete pIOStream;
   pIOStream = NULL;

   if(_bDestructorDeletes)
      Remove();
   }


bool File::FromString(const ZStr& str)
   {
   return Name(str);
   }


const char *File::ToString(ZStr& str) const
   {
   str = Name();
   return str.c_str();
   }


const char *File::QueryNode(ZStr& str) const
   {
   FilePath fp;
   ZStr sPath;
   fp.Chop(sFQName, sPath, str, fp.PathChar());
   return str.c_str();
   }


ZStr File::QueryNode(void) const
   {
   ZStr str;
   QueryNode(str);
   return str;
   }

const char *File::QueryParent(ZStr& str) const
   {
   FilePath fp;
   ZStr sNode;
   fp.Chop(sFQName, str, sNode, fp.PathChar());
   return str.c_str();
   }

bool File::Here(void)   // Present directory
   {
   Directory dir;
   dir.Get();
   return dir.Home(*this);
   }

bool File::QueryParent(Directory& dir) const   // Parent directory
   {
   if(dir.Name(QueryParent())) 
      return dir.Exists();
   return false;
   }

ZStr File::QueryParent(void) const
   {
   ZStr str;
   QueryParent(str);
   return str;
   }


bool File::IsNull(void) const
   {
   if(sFQName.IsNull())
      return true;      // Not there is not there!
   ZStr str = QueryNode();
   if(str == DEFAULT_FILE_NAME)
      return true;      // Un-Assign(ed (what we are looking for)
   return false;        // A prior name Assign(ment means it is not null.
   }


bool File::Launch(void) const
   {
   return Platform::ShellExec(Name());
   }


bool File::Qualify(ZStr& sName)
   {
   char evil = '\\';
#ifdef WIN32
   evil = '/';
#endif
   // Map any ALIEN path separators to PLATFORM;
   sName.Replace(evil, PathChar());

   if(sName.Find(PathChar()) == NPOS)
      {
      // Home it ONLY if it needs it (default NOW (1/13/07) is HOME DIR);
      // (Since HOME calls THIS, we must home this manually -)
      ProgramId pid;
      Directory dir;
      pid.GetProgram(dir);
      ZStr str = dir.Name();
      str += PathChar();
      str += sName;
      sName = str;
      }
   return Platform::IsValidDirName(sName);
   }



bool File::FQN(const ZStr& sMondo)
   {
   if(sMondo.Find(PathChar()) == npos)
      return false;
   sFQName = sMondo;
   return true;
   }

bool File::NamePwd(const ZStr& str)
   {
   Directory dir;
   if(dir.Get() == false)
      return false;
   return Name(dir, str);
   }

bool File::Name(const Directory& dir, const ZStr& str)
   {
   if(FQN(str) == true)
      return true;
   sFQName = ZStr(dir.Name()) + PathChar() + str;
   return dir.Home(*this);
   }


bool File::Name(const ZStr& fffff)
   {
   bool bok = false;

   Close();

   // If there is a path char, then use it - verbatim - (gigo)
   if(FQN(fffff) == true)
      return true;

   ZStr sMondo = fffff;

   // STEP: Only NULLS are Home()ed
   if(IsNull() == false)
      {
      // STEP: If not null (default), then use the DYNAMIC PARENT folder
      Directory dir;
      if(QueryParent(dir) == true)
         {
         sMondo = dir.Name();
         sMondo += PathChar();
         sMondo += fffff;
         bok = true; // NO NEED to qualify -
         }
      }

   if(bok == false)
      {
      // STEP: If null or error, then use the STATIC PROGRAM folder.
      if(Qualify(sMondo) == false)
         return false;
      }

   // fin -
   sFQName = sMondo;
   return true;
   }


bool File::MkUniqueName(void)
   {
   Directory dir;
   if(QueryParent(dir) == false)
      {
      if(dir.Get() == false)
         return false;
      }
   return MkUniqueName(dir);
   }


bool File::MkUniqueName(const ZStr& sSuffix)
   {
   ZStr str;
   File file;
   for(int ss = 0; ss < TMP_MAX; ss++)
      {
      file.MkUniqueName();
      str = file.Name();
      str.Append(sSuffix);
      if(file.Name(str) == false)
         return false;
      if(file.Exists() == false)
         {
         *this = file;
         return true;
         }
      }
   return false;
   }

bool File::MkUniqueName(const Directory& dir, const ZStr& sSuffix)
   {
   ZStr str;
   File file;
   for(int ss = 0; ss < TMP_MAX; ss++)
      {
      file.MkUniqueName(dir);
      str = file.Name();
      str.Append(sSuffix);
      if(file.Name(str) == false)
         return false;
      if(file.Exists() == false)
         {
         *this = file;
         return true;
         }
      }
   return false;
   }


bool File::MkUniqueName(const Directory& dir)
   {
   ZStr sPwd = dir.Name();
   ZStr str = tmpnam(NULL);     // ANSI
   size_t pos = str.Find(P_tmpdir);
   if(pos != npos)
      str.RemovePos(0, pos + 1);       // jic not defined to "\\" or "/"
   sPwd.Append(PathChar());
   sPwd.Append(str);
   return FQN(sPwd);
   }


ZStr File::Name(void) const
   {
   return ZStr(sFQName);
   }


const char* File::QueryFileNode(ZStr& std) const
   {
   std = sFQName;
   size_t sp = sFQName.Rfind('\\');
   if(sp != NPOS)
      std.RemovePos(0, sp+1);
   return std.c_str();
   }


const char* File::QueryPathTo(ZStr& std) const
   {
   std = sFQName;
   size_t sp = sFQName.Rfind('\\');
   if(sp != NPOS)
      std[sp] = NULL;
   return std.c_str();
   }


bool File::Rename(const ZStr& std)
   {
   if(sFQName == std)
      return true;
   if(Platform::FileExists(sFQName) == true)
      {
      if(Platform::FileRename(sFQName.c_str(), std.c_str()) == false)
         return false;
      }
   return Name(std);
   }


ZStr File::Query(Directory& dir) const
   {
   ZStr str;
   QueryParent(str);
   dir.Name(str);
   return dir.Name();
   }


bool File::MoveTo(const Directory& dir)
   {
   bool br = CopyTo(dir);
   if(br == false)
      return br;
   return Remove();
   }


bool File::CopyTo(const File& file)
   {
   return CopyTo(file.Name());
   }


bool File::CopyTo(const Directory& dir)
   {
   ZStr str;
   if(dir.Exists() == false)
      dir.Create();
   return CopyTo(dir.Home(QueryNode(str)));
   }


bool File::CopyTo(const ZStr& str)
   {
   if(sFQName.IsNull())
      return false;
   Close();             // 11/09/2003, R. Nagy
   // This was a "file_fun" call;
   if(sFQName == str)
      return true;
   if(Platform::FileCopy(sFQName.c_str(), str.c_str()))
      return true;
   return false;
   }


time_t File::GetTime(void) const
   {
   struct stat info;
   ZStr bugfix = sFQName;
   if(::stat(bugfix.c_str(), &info) == -1)
      return NULL;
   return info.st_ctime;
   }


bool File::Touch(void)
   {
   time_t timex = ::time(NULL);
   return Touch(timex);
   }


bool File::Touch(time_t timex)
   {
   if(sFQName.IsNull())
      return false;
return false;
   }


bool File::Create(void)
   {
   ofstream ofs(sFQName.c_str());
   if(ofs) 
      return true;
   return false;
   }


bool File::Hide(void)
   {
   return Platform::FileHide(sFQName);
   }


bool File::UnHide(void)
   {
   return Platform::FileShow(sFQName);
   }


bool File::IsHidden(void)
   {
   if(sFQName.IsNull())
      return false;
   return Platform::IsFileHidden(sFQName);
   }


bool File::Exists(void)  const
   {
   if(sFQName.IsNull())
      return false;
   return Platform::FileExists(sFQName.c_str());
   }


bool File::CanRead(void)  const
   {
   if(sFQName.IsNull())
      return false;
   return Platform::FileReadable(sFQName.c_str());
   }


bool File::CanWrite(void)  const
   {
   if(sFQName.IsNull())
      return false;
   return Platform::FileWritable(sFQName.c_str());
   }


bool File::Remove(void)
   {
   Close();
   if(sFQName.IsNull())
      return false;
   if(::unlink(sFQName.c_str()))
      return false;
   return true;
   }


bool File::Empty(void)
   {
   return Create();
   }


bool
File::DumpContents(ostream& os, TranslationModes at)
   {
   istream& is = OpenRead(at);
   if(!is)
      return false;

   char ch;
   while(is)
      {
      is.read((char *)&ch, 1);
      if(is)
         os.write((char *)&ch, 1);
      }
   Close();

   return true;
   }


bool
File::DumpContents(long spStart, long spEnd, ostream& os, TranslationModes at)
   {
   istream& is = OpenRead(at);
   if(!is)
      return false;

   is.seekg(spStart);
   char ch;
   while(is)
      {
      if((spEnd != (long)-1L) && (is.tellg() >= spEnd))
         break;

      is.read((char *)&ch, 1);
      if(is)
         os.write((char *)&ch, 1);
      }
   Close();
   return true;
   }


char File::Drive(void)
   {
   if(sFQName.IsNull())
      return '?';
   if(sFQName[1] == ':')
      {
      ZStr std = sFQName[0];
      std.ToUpper();
      return std[0];
      }
   return '?';
   }


int File::Device(void)
   {
   char ch = Drive();
   if(ch == '?')
      return -1;
   return (ch - 'A');
   }


File& File::operator=(const File& rf)
   {
   if(this == &rf)
      return *this;
   sFQName = rf.sFQName;
   return *this;
   }


ostream& File::Write(ostream& os) const
   {
   sFQName.WriteStream(os);
   return os;
   }


istream& File::Read(istream& is)
   {
   sFQName.ReadStream(is);
   return is;
   }


istream& File::OpenRead(TranslationModes at)
   {
   Close();
   pIOStream = new fstream;

   if(at == AT_BINARY)
      pIOStream->open(sFQName.c_str(), ios::in | ios::binary);
   else
      pIOStream->open(sFQName.c_str(), ios::in);
   return *pIOStream;
   }


ostream& File::OpenWrite(TranslationModes at)
   {
   Close();
   Remove();      // For the benefit of Microsoft's legacy.
   pIOStream = NULL;
   pIOStream = new fstream;

   if(at == AT_BINARY)
      pIOStream->open(sFQName.c_str(), ios::out | ios::binary);
   else
      pIOStream->open(sFQName.c_str(), ios::out);
   return *pIOStream;
   }


void File::Close(void)
   {
   if(pIOStream)
      pIOStream->close();
   }


ostream& File::OpenAppend(TranslationModes at)
   {
   Close();
   delete pIOStream;
   pIOStream = NULL;
   pIOStream = new fstream;

   if(at == AT_BINARY)
      pIOStream->open(sFQName.c_str(), ios::out  | ios::app | ios::binary);
   else
      pIOStream->open(sFQName.c_str(), ios::out  | ios::app);
   return *pIOStream;
   }


iostream& File::OpenReadWrite(TranslationModes at)
   {
   Close();
   delete pIOStream;
   pIOStream = NULL;
   pIOStream = new fstream;

   if(at == AT_BINARY)
      pIOStream->open(sFQName.c_str(), ios::in | ios::out | ios::binary);
   else
      pIOStream->open(sFQName.c_str(), ios::in | ios::out);
   return *pIOStream;
   }


iostream& File::Resume(void)
   {
   if(!pIOStream)
      pIOStream = new fstream;
   return *pIOStream;
   }


bool File::SaveText(const File& fff, const ZStr& sResult)
   {
   File file = fff;
   file.OpenWrite() << sResult;
   file.Close();
   return file.Exists();
   }

bool File::LoadText(const File& fff, ZStr& sResult)
   {
   File file = fff;
   bool br = false;
   ZStr sLine;
   sResult = sLine; // clear it out ...
   istream& is = file.OpenRead();
   while(sLine.Readline(is))
      {
      sResult += sLine;
      sResult += '\n';
      br = true;
      }
   return br;
   }

bool File::LoadPureText(const File& fff, ZStr& sResult, char chStart, char chEnd)
   {
   File file = fff;
   bool br = false;
   ZStr sLine;
   sResult = sLine; // clear it out ...
   istream& is = file.OpenRead();
   while(sLine.Readline(is))
      {
      sResult += TagRemove(sLine, chStart, chEnd);
      sResult += '\n';
      br = true;
      }
   return br;
   }


#ifdef FileInformation_Hpp


bool LoadTextFile(ZStr& sResult, File& file)
   {
   FileInformation info;
   if(file.Get(info) == false)
      return false;
   if(info.IsFileHuge())
      return false;
   sResult.Read(file.OpenRead(File::AT_TEXT), info.FileSize());
   if(sResult.Length())
      return true;
   return false;
   }


bool LoadBytes(File& file, ByteBuffer& bytes)
   {
   FileInformation info;
   if(file.Get(info) == false)
      return false;
   if(info.IsFileHuge())
      return false;
   ifstream ifs(file.Name());
   char *pBuf = new char[info.FileSize()+1];
   ifs.Read(pBuf, info.FileSize());
   bytes.Assign(pBuf, info.FileSize());
   return true;
   }
#endif


bool IsTextFile(const File& file)
   {
   File f = file;
   istream& is = f.OpenRead(File::AT_BINARY);
   char ich = NULL;
   while(is)
      {
      is.read(&ich,1);                        // Let the OS buffer it...
   	if((ich >= ' ') && ich <= '~')		// 0x20 to 0x7e
   		continue;

   	if((ich >= 0x09) && ich <= 0x0d)	   // ASCII control chars
   		continue;

   	if(ich == 0x1a)							// Necessary evil on DOS..
   		continue;

     	return false;
      }
   f.Close();
   return true;
   }


void MkLocalFileName(ZStr& std, bool bSkipPathChar)
   {
   for(size_t ss = NULL; ss < std.Length(); ss++)
      {
      switch(std[ss])
         {
         case '\\':
            if(bSkipPathChar == true)
               continue;
         case ':':
            if((bSkipPathChar == true) && ss == 1)
               continue;
         case '<':
         case '>':
         case '*':
         case '?':
         case '/':
         case '\"':
            std[ss] = '_';
         default:
            continue;
         }
      }
   }

bool File::SetNode(ZStr& str)
   {
   bool br = false;
   Directory dir;
   if(dir.Name(QueryParent()) == true)
      {
      if(Name(str))
         br = dir.Home(*this);
      }
   return br;
   }

bool File::SetParent(ZStr& sDir)
   {
   ZStr str = QueryNode();
   return Name(FilePath::Glue(sDir, str, PathChar()));
   }

bool File::SetParent(Directory& dir)
   {
   ZStr str;
   str = dir.Name();
   return SetParent(str);
   }

File File::MkGenerationName(const Directory& dir, const File& fff)
   {
   File file = fff;
   if(dir.Home(file) == false)
      {} // =:-0

   unsigned long lCount = 0L;
   while(file.Exists())
      {
      lCount++;
      if(!lCount) // wrap - not likley - but all the same - could happen - some day -
         {
         file.MkUniqueName(dir); // Failsafe
         return file;
         }
      stringstream srm;
      srm << lCount << "." << fff.QueryNode();
      file.Name(srm.str().c_str());
      }
   return file;
   }

   } // Able1
