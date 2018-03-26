// Class FileVersion: A way to validate and uniquely identify the version(s) of a data file (saving room
// for backwards-compatibilities). On Read, the class first checks for its own header, then Reads it's data,
// if the file-header properly identifies it as being able to do so. Since file Read() always properly 
// resets to pre-Read position upon failure, file-version testing can be iterative: Use Read() to
// get the result of the header-Read attempt (1 means all went okay).
//
// THE PRODUCT NAME MUST BE THE SAME ACROSS ALL VERSIONS: Suggest that you use a 'REGISTER CLASS' 
// NAME: Once the class insure that the header and product identifiers are okay, then the rest is 
// up to your program to determine if it can Read the specific file-version (etc).
//
// The ProductName() is the *ONLY* thing that operator= is concerned with!! Use Read() to 
// check if the last Read() detected a valid FileVersion header, the operator= with a default
// FileVersion to see if the products match up. See EzInstall::Query() and QueryImport() for 
// an example of how this can be easily implemented using polymorphism.
//
// 03/18/1998: Class created, R. Nagy
// 11/16/1998: Added ProgramId in default constructor to replace "undefined", R. Nagy
//             Virtualized Read() and Read()/Write() to allow class to be "grown", R. Nagy
//
#ifndef FILE_VERSIONx_HPP
#define FILE_VERSIONx_HPP

#include <Able1.hpp>

using namespace Able1;

class FileVersion
   {
   private:
      char cReadOkay;

   protected:
      double      version;          // the FILE-FORMAT VERSION: default is 0.0
      ZStr   sVersionName;     // e.g: "EzInstall 4.6": default is last date of compilation
      ZStr   sProduct;         // default is EXE name
      char        key[6];
   public:
      FileVersion(void);
      virtual ~FileVersion(void);

      // THE PRODUCT NAME MUST BE THE SAME ACROSS ALL VERSIONS: Suggest that you use the REGISTER CLASS NAME.
      // ProductName is the *ONLY* thing that operator= is concerned with!!
      void        ProductName(const char *psz);
      const char *ProductName(void) const;
      // This can be anything, e.g: "EzInstall 4.6";
      void        VersionName(const char *psz);
      const char *VersionName(void) const;
      // This can be anything. It identifies the FILE-FORMAT VERSION!;
      void        VersionNumber(double fv);
      double      VersionNumber(void) const;

      // ProductName is the *ONLY* thing that operator= is concerned with!!
      int operator==(const FileVersion& fv)     {return (sProduct == fv.sProduct);}
      int operator!=(const FileVersion& fv)     {return (!(sProduct == fv.sProduct));}

      // Use this to get a successfull Read indication; 1 means "okay";
      // (file Read() always properly resets to pre-Read position upon failure,
      // so file-version testing can be iterative);
      virtual int Read1(istream& is);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };
   
#endif

