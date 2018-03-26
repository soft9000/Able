
//! I cobbled this NOJ together while struggling with 
//! the need to expand a tab-delimited file into 
//! something more viewable under a command-line 
//! challenged OS.
//! 
//! (1) Create a funky tab file -
//! MYDIR> RTree # > REPORT.TAB
//! 
//! (2) Use Tab2SDF to view the content
//! MYDIR> Tab2SFD REPORT.TAB
//! 
//! 	Or
//! 
//! (2) Use Tab2SDF to view the content
//! MYDIR> Tab2SFD REPORT.TAB > REPORT.SDF
//! 
//! 	Or
//! 
//! (1) As a pipe fitting:
//! MYDIR> RTree # | sort | Tab2SDF ! > REPORT.SDF
//!
//! How it Works:
//! =============
//! This program scans the REPORT.TAB file twice.
//!    Once to determine the optimal fill for each field and
//!    Once to display file content to cout / stdout.
//! 
//! Simple yet handy, this C++ tool is also neat for people 
//! who work with legacy COBOL or other data file / dataset 
//! mainframe formats. The perfect NOJ!
//!

#include <Able1.hpp>
using namespace Able1;

#include <core/TypeThunk.hpp>

class Tab2SDF
{
public:
   
  static bool SaveStream(const File& fff, istream& is)
   {
   ZStr sLine;
   File file = fff;
   ostream& os = file.OpenWrite();
   while(is)
      {
      sLine.Readline(is);
      if(is)
         os << sLine << endl;
      }
   return true; 
   }
  static bool Scan(const File& fff, ostream& os, Array<TypeThunk<size_t> >& aPos)
   {
   File file = fff;
   aPos.Empty();
   if(file.Exists() == false)
      {
      os << "Error: File " << file.Name() << " not found." << endl;
      return false;
      }
   istream& is = file.OpenRead();
   Array<ZStr> aFields;
   ZStr sLine;
   while(is)
      {
      sLine.Readline(is);   
      aFields = sLine.slice('\t');
      for(size_t ss = 0L; ss < aFields.Nelem(); ss++)
         {
         size_t iPos = aFields[ss].Length();
         iPos++;  // add a space - SDF requires at least one extra -
         if(aPos[ss] < iPos)
            aPos[ss] = iPos;
         }
      }
   return true;
   }
   
  static bool List(const File& fff, ostream& os, Array<TypeThunk<size_t> >& aPos)
   {
   File file = fff;
   if(file.Exists() == false)
      {
      os << "Error: File " << file.Name() << " not found." << endl;
      return false;
      }
   istream& is = file.OpenRead();
   Array<ZStr> aFields;
   ZStr sLine;
   while(is)
      {
      sLine.Readline(is);   
      aFields = sLine.slice('\t');
      for(size_t ss = 0L; ss < aFields.Nelem(); ss++)
         {
         size_t iPos = aPos[ss];
         ZStr& sRef = aFields[ss];
         size_t iLen = sRef.Length();
         if(iLen >= iPos)
            os << sRef << " ";   // GIGO
         else
            {
            // SDF
            iPos -= iLen;
            os << sRef << ZStr(' ', iPos);
            }
         }
      os << endl;
      }
   return true;
   }
   
  static Usage(ostream& os)
   {
   os << endl;
   os << "Version: " << __DATE__ << "(" << __TIME__ << ") " << endl;
   os << "Tab2SDF: List the content of a TAB delimited file in SDF format." << endl;
   os << endl;
   os << "   Tab2SDF [!] | [REPORT.TAB]" << endl;
   os << endl;
   os << " Examples:" << endl;
   os << "    RTREE C:\\MYDIR | sort > REPORT.TAB" << endl;
   os << "    Tab2SDF REPORT.TAB" << endl;
   os << " Or:" << endl;
   os << "    RTREE C:\\MYDIR | sort | Tab2SDF ! > REPORT.SDF" << endl;
   os << endl;
   }

  static bool Main(Array<ZStr>& array, istream& is, ostream& os)
   {
   bool bRemove = false;
   if(array.Nelem() != 2)
      {
      Usage(os);
      return false;
      }
   File file;
   if(array[1] == "!")
      {
      if(SaveStream(file, is) == false)
         {
         os << "Error: Unable to save stream to " << file.Name();
         return false;      
         }
      bRemove = true;
      }
   else
      {
      if(file.Name(array[1]) == false)
         {
         Usage(os);
         return false;
         }
      }
   Array<TypeThunk<size_t> > aPos;
   bool br = Tab2SDF::Scan(file, os, aPos);
   if(br == false)
      return br;
      
   br = Tab2SDF::List(file, os, aPos);
   
   if(bRemove)
      file.Remove();
      
   return br;
   }

  static bool Main(int argc, char *argv[], istream& is, ostream& os)
   {
   Array<ZStr> array;

   for(size_t ss = 0; ss < argc; ss++)
      array.Append(argv[ss]);

   return Main(array, is, os);
   }
   
};

int main(int argc, char *argv[])
   {
   int iResult = (int) true;
   if(Tab2SDF::Main(argc, argv, cin, cout) == false)
      {
      iResult = (int) false;
      cerr << "Failure." << endl;
      }
   return iResult;
   }
   
