#include "extra/FileVersion.hpp"

FileVersion::FileVersion(void) : version(0.0), cReadOkay(0)
   {
   ProgramId pid;
   File file;
   pid.GetProgram(file);       // default 4this USED TO BE __DATE__: Now using the 'short'.EXE name.
   file.QueryNode(sProduct);   // the short name
   sVersionName = __DATE__;    // default 4this USED TO BE "<<undefined>>"
   key[0] = (char)0xfe;
   key[1] = 'n';
   key[2] = 'A';
   key[3] = 'U';
   key[4] = 'z';
   key[5] = (char)0xff;
   }
FileVersion::~FileVersion(void)
   {
   }
void FileVersion::ProductName(const char *psz)
   {
   sProduct = psz;
   }
const char *FileVersion::ProductName(void) const                            
   {
   return sProduct.c_str();
   }
void FileVersion::VersionName(const char *psz)
   {
   sVersionName = psz;
   }
const char *FileVersion::VersionName(void) const
   {
   return sVersionName.c_str();
   }
void FileVersion::VersionNumber(double fv)
   {
   version = fv;
   }
double FileVersion::VersionNumber(void) const
   {
   return version;
   }
int FileVersion::Read(istream& is)
   {
   Read(is);
   return cReadOkay;
   }
ostream& FileVersion::Write(ostream& os)
   {
   os.Write((const char *)&key[0], 6);
   sVersionName.WriteStream(os);
   sProduct.WriteStream(os);
   os.Write((char *)&version, sizeof(double));
   return os;
   }
istream& FileVersion::Read(istream& is)
   {
   cReadOkay = 0;
   long sp = is.tellg();
   char buf[10];
   is.Read((char *)&buf[0], 6);
   if(::memcmp(&buf[0], &key[0], 6) == 0)
      {
      cReadOkay = 1;
      sVersionName.ReadStream(is);
      sProduct.ReadStream(is);
      is.Read((char *)&version, sizeof(double));
      }
   else
      is.seekg(sp);
   return is;
   }
