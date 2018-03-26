
//! This is a handy little noj that you can use to create a node-first listing
//! of a directory tree.
//! 
//! As a utility, there is a lot that we could yet add, test, share, and enjoy... 
//! (most notably the date feature!) Feel free to contribute.
//!

#include <Able1.hpp>
using namespace Able1;

class RTree
{
public:
   
  static bool List(const Directory& dir, ostream& os, bool bPrefixDate)
   {
   bool br = false;
   Array<File> files;
   dir.Query(files);
   for(size_t ss = 0L; ss < files.Nelem(); ss++)
      {
      br = true;
      File& file = files[ss];
      os << file.QueryNode() << "\t";
      if(bPrefixDate)
         {
         StdDateTime sdt(file.GetTime());
         unsigned int yy, mm, dd;
         sdt.DecodeDate(yy, mm, dd);
         os << yy << ":" << mm << ":" << dd << " - ";
         sdt.DecodeTime(yy, mm, dd);
         os << yy << ":" << mm << ":" << dd << "\t";
         }
      os << dir.Name() << endl;
      }
   Array<Directory> dirs;
   dir.Query(dirs);
   for(size_t ss = 0L; ss < dirs.Nelem(); ss++)
      {
      br = true;
      List(dirs[ss], os, bPrefixDate);
      }
      
   return br;
   }
   
  static Usage(ostream& os)
   {
   os << "Version: " << __DATE__ << "(" << __TIME__ << ") " << endl;
   os << "RTree: List the content of a directory tree in sortable order." << endl;
   os << "   RTree [directory] [#]" << endl;
   os << "     directory - Starting point (default is the pwd)" << endl;
   os << "     #         - Follow the node names with node's date" << endl;
   os << endl;
   os << " Example: RTree C:\\WINDOWS | sort | more" << endl;
   }

  static bool Main(Array<ZStr>& array, ostream& os)
   {
   bool bUseDate = false;
   Directory dir;
   dir.Get();  // default is to use the pwd
   ZStr str;
   if(array.Nelem() == 2)
      {
      str = array[1];
      if(str.Find(PathChar()) != npos)
         {
         if(dir.Name(str) == false)
            {
            Usage(os);
            os << "Invalid directory name: " << array[1] << endl;
            return false;
            }
         }
      else
         bUseDate = true;
      
      return RTree::List(dir, os, bUseDate);
      }
   if(array.Nelem() == 3)
      {
      bUseDate = true;
      str = array[1];
      if(str.Find(PathChar()) == npos)
         str = array[2];
      if(dir.Name(str) == false)
         {
         Usage(os);
         os << "Invalid directory name: " << array[1] << endl;
         return false;
         }
      return RTree::List(dir, os, bUseDate);
      }

   Usage(os);
   return false;
   }

  static bool Main(int argc, char *argv[], ostream& os)
   {
   Array<ZStr> array;

   for(int ss = 0; ss < argc; ss++)
      array.Append(argv[ss]);

   return Main(array, os);
   }
   
};

int main(int argc, char *argv[])
   {
   int iResult = (int) true;
   if(RTree::Main(argc, argv, cout) == false)
      {
      iResult = (int) false;
      cerr << "Failure." << endl;
      }
   return iResult;
   }
