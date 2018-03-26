// 11/13/2004: Converted to static usage, R. Nagy
// 09/01/2008: Updated Chop() and Glue() to eliminate dangling sep's, R. Nagy
//
#ifndef FilePath_Hpp
#define FilePath_Hpp

namespace Able1
   {
   class File;
/** FilePath parses, normalizes, and otherwse manages operating-system paths.
  *
  */      
class FilePath
   {
   public:
      char PathChar(void); // "/" on UNIX, "\" on DOS, ":" on PICK (etc.)

      static bool Open(const ZStr& sPath, Node& result);
      static bool Open(const ZStr& sPath, File& result);
      static bool Open(const ZStr& sPath, Directory& result);

      // Will return FALSE if no path char is found (new 1/17/08) - sFolder will echo input (legacy) -
      static bool      Chop(const ZStr& sPath, ZStr& sFolder, ZStr& sNode, char chSep);
      static ZStr Glue(const ZStr& sFolder, const ZStr& sNode, char chSep);
      static ZStr LiberatedName(const ZStr&, char chSep = '|'); // "Liberates" a name by removing and drive designations & platform specific path separations.
   };
// Always a nagging problem to solve...
inline char PathChar(void)
   {
   FilePath fp;
   return fp.PathChar();
   }
inline ZStr Glue(const ZStr& sFolder, const ZStr& sNode, char chSep);

   } // Able1

#endif   
