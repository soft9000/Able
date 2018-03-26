// Class StdPath: We need a common path storage mechanism, as well as
// a way to associate relative paths to the htree type om "mount
// points" (Directory, File, and Url)
//
// 08/25/2005: Created, R. Nagy
//
#ifndef STD_PATH_HPP
#define STD_PATH_HPP


namespace Able1
   {
/** We need a common path storage mechanism, as well as
  * a way to associate relative paths to the htree type om "mount
  * points" (Directory, File, and Url.)
  */
class StdPath
   {
   private:
      bool _relate(const ZStr& sFullPath, ZStr& sResult);
   protected:
      bool _resolve(const ZStr& sMount, const ZStr& sNode, ZStr& sResult);
   public:

      class Path {
         protected:
            ZStr sPath;
         public:
            Path(const Path& ref);
            Path(const ZStr& ref);

            Path& operator=(const ZStr& str);
            operator ZStr(void);

            ostream& Write(ostream& os);
            istream& Read(istream& is);
      };

      // Existance is not verified.
      static bool Mount(const Path&, const Url&, Url& uResult);
      static bool Mount(const Path&, const Url&, File& uResult);
      static bool Mount(const Path&, const Url&, Directory& uResult);

      static bool Mount(const Path&, const File&, File& uResult);
      static bool Mount(const Path&, const File&, Url& uResult);

      static bool Mount(const Path&, const Directory&, Directory& uResult);
      static bool Mount(const Path&, const Directory&, Url& uResult);
   };

   } // Able1
#endif
