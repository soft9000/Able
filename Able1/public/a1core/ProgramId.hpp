#ifndef nojProgramId_Hpp
#define nojProgramId_Hpp

// ProgramId is an encapsulation that every operating system can support.
// Its purpose is to allow you to know what, and where, your program is running.
// It also allow you to manipulate files and folders relative to both a system
// wide, and a program relative, location. Very important for IPC and persistance.
//
// 04/28/1998: Class extracted from EzInstall base, R. Nagy
// 09/07/1998: Replaced string with ZStr to use in Job*NET, R. Nagy.
// 11/23/1998: Added SetProgramDirectory(), R. Nagy.
// 06/12/1999: Added PlaceInDirectory(), R. Nagy.
// 06/14/1999: Added TempFileName(), R. Nagy.
// 06/15/1999: Added PlaceInTempDirectory(), R. Nagy.
// 11/25/1999: Added TempFileName(with suffix), R. Nagy
// 12/22/1999: Added GetRepository(), R. Nagy
// 08/24/2000: Added PlaceInSubDirectory() concept, R. Nagy
// 01/01/2003: Added QuerySystemDirectory(), R. Nagy
// 08/30/2003: Re-written as part of port to the noj framework, R. Nagy
// 09/19/2003: Added PutInDirectory(Directory&, File&), R. Nagy
// 12/03/2004: Added SetProgram(File&) to support DOS / UNIX, as well as to over-ride WIN32 API, R. Nagy
//             Re-wrtten to support MSDOS, UNIX, and WIN32.
// Note: DOS and UNIX programs MUST call SetProgram() before using this class.
//       WIN32 programs do not need to, but should now do so none the less (portability).
// 01/11/2006: Added Home(File), R. Nagy
// 02/24/2006: Added Home(Directory), R. Nagy
// 05/06/2006: Renamed PlaceInSubDirectory() to Concat(), R. Nagy
//             Added Home(sDir, sNode, chPath), R. Nagy
// 01/13/2007: Converted File usage in this class - File constructor is now using same, R. Nagy

namespace Able1
   {
// RESULT CONVENTION
// -----------------
// Unless otherwise noted, file and folder objects do not exist until you create them.
// Except for pre-exisitng system and executable paths or files, results returned
// are fully qualified, but not necessarily existing, file system elements.
//
/** ProgramId is an "anchor class" for all .EXE-file and temp-file node management. Perhaps
  * the most usefull class written, it is used to help manage a host of relative file and folder
  * locations.
  */
class ProgramId
   {
   protected:
      // File constructor now uses this class (1/13/2007), so it NEEDS to be a string once again -
      ZStr sFQFileNameEX;
      
   public:
      ProgramId(void)    {}
      ~ProgramId(void)   {}

      bool SetProgram(const ZStr &sFQFileName);

      /** This is the WINDOWS (system) directory. On unix, /etc might be a good place. Must be an pre-exisitng operating system defined location, and non-transient. */
      bool GetSystem(Directory& dir)              const; 
      /** Place in the directory */
      bool PutInDirectory(const Directory& dir, File& file) const; 

      /** File where the executable resides. */
      bool GetProgram(Directory& dir)             const; 
      /** Fully qualified executable. */
      bool GetProgram(File& file)                 const; 
      /** Place the file in the default (program) directory. */
      bool PutInDirectory(File& file)             const; 
      /** Place the leaf in the default (program) directory. */
      bool PutInDirectory(Directory& dir)         const; 
      /** Place the file in the program's home (start-up) location. */
      bool Home(File& file)                       const; 
      /** Place the file in the program's home (start-up) location. */
      bool Home(Directory& file)                  const; 
      /** Place the file in the program's home (start-up) + sub dir location. */
      ZStr Home(const ZStr sSubDir, const ZStr& sNode, char sep = 0) const;

      /** Checks the TEMP environment variable first, then defaults to creating
        * a TEMP dir on the program root. On WIN32, the last chance will use the
        * WIN32 API if SetProgram() has not been called (legacy support). 
        * A place for temporary files */
      bool GetTemp(Directory& dir)                const; 
      /** Create a unique temporary file. */
      bool GetTemp(File& file)                    const; 
      /** Put the file into the temp folder. */
      bool PutInTemp(File& file)                  const; 
      /** Put the directory tree into the temp dir. */
      bool PutInTemp(Directory& dir)              const; 

      /** Call "place in directory" for the sub-directory reference. */
      bool PutInSubDirectory(const Directory& dirSub, File& file) const;

      /** Brute force: Just concatnate them together, and return the result. */
      ZStr Concat(const ZStr& sSubdir, const ZStr& sItem, char sep) const;
      /** Brute force: Just concatnate them together, and return the result. */
      ZStr Concat(const ZStr& sSubdir, const ZStr& sItem) const;
      /** Path seperator. */
      char PathSep(void)                         const;
   };

inline
char ProgramId::PathSep(void) const
   {
   char ch = '\\';
#ifdef UNIX
   ch = '/';
#endif
   return ch;
   }

   }
#endif


