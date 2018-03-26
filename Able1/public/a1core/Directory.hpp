// Class Directory: Created to remove and add a name-space to all of theos functions that
// we are building up in the "FILE_FUN.HPP". Like File.Hpp, only for directories.
//
// 12/22/1999: Class created, R. Nagy
// 11/02/2002: Added GoTo and File / Directory Query capabilities, R. Nagy
// 10/30/2003: Added QueryNode() and QueryParent() [to complement File signature], R. Nagy
// 06/17/2004: Updated Name() to prefix with pwd for non-absolute path names, R. Nagy
// 11/13/2004: Lightly updated to support commmon usage, R. Nagy
// 02/28/2006: Added Launch(), R. Nagy
// 08/28/2006: Added QueryTree(recursive) for File and Directory, R. Nagy
//

#ifndef Directory_Hpp
#define Directory_Hpp

namespace Able1
   {
//   class File;
//   class ZStr;
/** Directory is a ShareableObject designed to manage folders much like File. 
  * Added ability to Home() and query folder contents.
  */   
class Directory : public ShareableObject
{
protected:
   ZStr   sStack;
   ZStr   sPwd;

public:
   Directory(void);
   Directory(const Directory& r);
   virtual ~Directory(void);

   bool        Name(const ZStr& sName);
   ZStr        Name(void) const;

   // CommonObject
   bool        FromString(const ZStr&);
   const char *ToString(ZStr&) const;

   const char *QueryNode(ZStr& str) const;       // ONLY the name of the directory (no path is included)
   const char *QueryParent(ZStr& str) const;     // ONLY the path to the directory (no node name)

   ZStr        QueryNode(void) const;                 // ONLY the name of the directory (no path is included)
   ZStr        QueryParent(void) const;               // ONLY the path to the directory (no node name)
   bool        QueryParent(Directory& dir) const;     // Parent directory

   bool        IsNull(void) const   {if(sPwd.IsNull()) return true; return false;}

   bool        Exists(void) const;

   bool        Home(File&) const;            // place file   (leaf node) in the directory
   bool        Home(Directory&) const;       // place folder (leaf node) in the directory
   ZStr        Home(const ZStr&) const;      // place string (entire)    in the directory
 
   bool        Create(void) const;
   bool        Remove(void) const;
   bool        Empty(void)  const;

   bool        Set(void);
   bool        Set(const ZStr& sDir);

   bool        Get(void);

   bool        Push(void);
   bool        Pop(void);
   void        EmptyStack(void);

   bool        CreateDirectoryTree(void);

   bool        CreateTreeFor(File& file);

   int         operator==(const Directory& rDir)   {return (sPwd == rDir.sPwd);}
   Directory&  operator=(const Directory& rDir);

   ostream&    Write(ostream& os);
   istream&    Read(istream& is);

   bool        GoTo(void);

   void        Query(Array<File>&) const;
   void        Query(Array<Directory>&) const;

   void        QueryTree(Array<Directory>& aDirs) const; // Return a list of folders / directories (recursive)
   void        QueryTree(Array<File>& aFiles) const;     // Return a list of files (recursive)

   bool        IsEmpty(void);

   bool        Launch(void);
};

   } // Able1
#endif


