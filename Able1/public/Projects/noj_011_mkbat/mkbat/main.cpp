
//! This is a handy little noj that you can use to create a script (aka "batch file")
//! from two lists of file names - one before (actual), and one after (desired).
//!
//! e.g: `mkbat rename filea.txt [fileb.txt]`
//! That will (1) Read each line from filea, (2) suffix with with the next line from 
//! fileb (optional), (3) prefix them both with "rename " and (4) Write it all to `stdout`.
//! -Very usefull for uniquely renaming a huge set of files (etc.)
//! 
//! Note that main() only tests a subset of the features. As a utility, there is a
//! lot that we could yet add, test, share, and enjoy... So feel free to contribute.
//!

#include <Able1.hpp>
using namespace Able1;

class MkBat
{
protected:
   bool _load(File& file, Array<ZStr>& aLines, ostream& os)
      {
      aLines.Empty();
      istream& is = file.OpenRead();
      ZStr sLine;
      while(is)
         {
         sLine.Readline(is);
         if(is)
            {
            sLine.MkWhite();
            sLine.Strip();
            aLines.Append(sLine);
            }
         }
         
      file.Close();
      
      if(aLines.Nelem())
         return true;
         
      os << "Warning: File " << file.Name() << " is empty!";
      return false;
      }

public:
   struct mk_injectors
      {
      ZStr sPrefix;
      ZStr sMiddle;
      ZStr sSuffix;
      };
   struct mk_record
      {
      ZStr sLeft;
      ZStr sRight;
      mk_injectors inject;
      };
   struct mk_data
      {
      Array<ZStr> aLeft;
      Array<ZStr> aRight;
      mk_injectors inject;
      };
   struct mk_files
      {
      File fLeft;
      File fRight;
      mk_injectors inject;
      };
      
  void Merge(const mk_record& in, ostream& os)
   {
   if(!in.inject.sPrefix.IsNull())
      os << in.inject.sPrefix << " ";
   os << in.sLeft << " ";

   if(!in.inject.sMiddle.IsNull())
      os << in.inject.sMiddle << " ";
   os << in.sRight;

   if(!in.inject.sSuffix.IsNull())
      os << " " << in.inject.sSuffix;
   os << endl;
   }
      
  bool Merge(mk_data& in, ostream& os)
   {
   if(in.aLeft.Nelem() != in.aRight.Nelem())
      {
      os << "Error: Input data array length mismatch";
      return false;
      }
   for(size_t ss = 0L; ss < in.aLeft.Nelem(); ss++)
      {
      mk_record rec;
      rec.inject = in.inject;
      rec.sLeft = in.aLeft[ss];
      rec.sRight = in.aRight[ss];
      Merge(rec, os);
      }
   return true;
   }
   
  bool Merge(mk_files& in, ostream& os)
   {
   mk_data data;
   data.inject = in.inject;
   
   if(_load(in.fLeft, data.aLeft, os) == false)
      return false;
   if(_load(in.fRight, data.aRight, os) == false)
      return false;
   return Merge(data, os);
   }
   
  static Usage(ostream& os)
   {
   os << "MkBat: Merge the content of two files into a single line." << endl;
   os << "MkBat \"command\" file_left file_right" << endl;
   }

  static bool Main(Array<ZStr>& array, ostream& os)
   {
   if(array.Nelem() != 4)
      {
      Usage(os);
      return false;
      }

   mk_files files;
   files.inject.sPrefix = array[1];

   if(files.fLeft.Name(array[2]) == false)
      {
      os << "Error: Invalid file name " << array[2] << endl;
      return false;
      }

   if(files.fRight.Name(array[3]) == false)
      {
      os << "Error: Invalid file name " << array[3] << endl;
      return false;
      }
      
   MkBat bat;
   return bat.Merge(files, os);
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
   if(MkBat::Main(argc, argv, cout) == false)
      {
      iResult = (int) false;
      cerr << "Failure." << endl;
      }
   return iResult;
   }
