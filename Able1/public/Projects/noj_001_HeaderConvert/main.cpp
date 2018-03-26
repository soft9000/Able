//
// This project will Read a pipe fitting looking for file names. 
// Once validated, an input source file will be updated so as to
// replace obsolete header usages. This updating includes things
// like changing "stdio.h" to "cstdio", "strstrea.h" to "strsteam",
// and "strstream.h" to "strstream". An appropriate "using namespace std;"
// statement is also added where, and as, required by the conversion.
//
// Input files are only updated as needed. Backup file is created / overwritten.
//
// Under Linux, use the "find" command:
//    find /usr/code -type f -name "*.h" -print | HeaderUpdate
//            or 
//    find /usr/code -type f -name "*.h" -print "{}\;" | HeaderUpdate
//
// Under DOS, use the "attrib" command:
//    attrib *.h /s | HeaderUpdate
// 
// **********************************************************
// WORKS FINE ON MY MACHINE, BUT BACKUP YOUR FILES BEFORE USE.
// **********************************************************
//
#include <Able1.hpp>

using namespace Able1;


class shazam
{
protected:
   Array<ZStr> lines;

   long lReplaced;
   bool bChanged;
   int iLastLine;

public:
   shazam(void) : lReplaced(0L), bChanged(false), iLastLine(0)
      {
      // Pre-allocate some space in the array
      lines.AddZombies(10000);
      }

   long Results(void)
      {
      return lReplaced;
      }

   bool Load(File& file)
      {
      iLastLine = 0;
      lines.Empty();
      bChanged = false;
      if(file.Exists() == false)
         return false;

      istream& is = file.OpenRead();
      ZStr sline;
      while(is)
         {
         sline.Readline(is);
         if(is)
            lines[lines.Nelem()] = sline;
         }

      file.Close();

      if(!lines.Nelem())
         return false;

      return true;
      }
   bool Save(File& file)
      {
      if(bChanged == false)
         return true;   // no need to save...

      // Create a fallback position (backup)
      File copy;
      ZStr str = file.Name();
      str += ".backup";
      if(copy.Name(str) == false)
         return false;

      copy.Remove();

      if(file.CopyTo(copy) == false)
         return false;

      // Add a using clause, if required
      if(iLastLine)
         {
         lines.Insert("using namespace std;", iLastLine);
         }

      // Save the update
      ostream& os = file.OpenWrite();
      for(size_t ss = 0L; ss < lines.Nelem(); ss++)
         {
         os << lines[ss] << endl;
         }
      file.Close();

      return file.Exists();
      }
   bool Changed(void)
      {
      return bChanged;
      }
   void SwapPair(const ZStr& sPat1)
      {
      ZStr sPat2 = sPat1;
      sPat2.Append(".h");
      SwapPair(sPat1, sPat2, true);
      }
   void SwapPair(const ZStr& sNew, const ZStr& sOld, bool bStl = false)
      {
      ZStr sBuf;
      for(size_t ss = 0L; ss < lines.Nelem(); ss++)
         {
         sBuf = lines[ss];
         sBuf.ToLower();
         if(sBuf.Find("#include") != npos)
            {
            size_t pos = sBuf.Find(sOld);
            if(pos != npos)
               {
               char ch = sBuf[pos-1];
               if(ch != '<' && ch != '"')
                  continue;
               ch = sBuf[pos+sOld.Length()];
               if(ch != '>' && ch != '"')
                  continue;

               sBuf.RemovePos(pos, pos + sOld.Length());
               sBuf.Insert(pos, sNew);
               lines[ss] = sBuf;
               lReplaced++;
               bChanged = true;
               if(bStl)
                  {
                  int inc = ss + 1;
                  if(iLastLine < inc)
                     iLastLine = inc;
                  }
               }
            }
         }
      }
};


void Fix(shazam& fix, File& file)
{
   if(fix.Load(file) == false)
      {
      cerr << "Unable to load " << file.Name() << endl;
      return;
      }

   fix.SwapPair("cassert", "assert.h"); 
   fix.SwapPair("cctype", "ctype.h"); 
   fix.SwapPair("cerrno", "errno.h"); 
   fix.SwapPair("cfloat", "float.h"); 
   fix.SwapPair("ciso646", "iso646.h"); 
   fix.SwapPair("climits", "limits.h"); 
   fix.SwapPair("clocale", "locale.h"); 
   fix.SwapPair("cmath", "math.h"); 
   fix.SwapPair("csetjmp", "setjmp.h"); 
   fix.SwapPair("csignal", "signal.h"); 
   fix.SwapPair("cstdarg", "stdarg.h"); 
   fix.SwapPair("cstddef", "stddef.h"); 
   fix.SwapPair("cstdio", "stdio.h"); 
   fix.SwapPair("cstdlib", "stdlib.h"); 
   fix.SwapPair("cstring", "string.h"); 
   fix.SwapPair("ctime", "time.h"); 
   fix.SwapPair("cwchar", "wchar.h"); 
   fix.SwapPair("cwtype", "wtype.h");
 
   fix.SwapPair("algorithm");   
   fix.SwapPair("bitset");   
   fix.SwapPair("deque");   
   fix.SwapPair("exception");   
   fix.SwapPair("fstream");   
   fix.SwapPair("functional");   
   fix.SwapPair("iomanip");   
   fix.SwapPair("ios");   
   fix.SwapPair("iosfwd");   
   fix.SwapPair("iostream");   
   fix.SwapPair("istream");   
   fix.SwapPair("iterator");   
   fix.SwapPair("limits");   
   fix.SwapPair("list");   
   fix.SwapPair("locale");   
   fix.SwapPair("map");   
   fix.SwapPair("memory");   
   fix.SwapPair("new");   
   fix.SwapPair("numeric");   
   fix.SwapPair("ostream");   
   fix.SwapPair("queue");   
   fix.SwapPair("set");   
   fix.SwapPair("sstream");   
   fix.SwapPair("stack");   
   fix.SwapPair("stdexcept");   
   fix.SwapPair("streambuf");   
   fix.SwapPair("string");   
   fix.SwapPair("typeinfo");   
   fix.SwapPair("utility");   
   fix.SwapPair("valarray");   
   fix.SwapPair("vector");

   fix.SwapPair("strstream");                     // Hummmmm....
   fix.SwapPair("strstream", "strstrea.h", true); // and again...

   if(fix.Changed() == false)
      {
      cout << "Bypassed " << file.Name() << "." << endl;
      return;
      }

   if(fix.Save(file) == false)
      {
      cerr << "Unable to save " << file.Name() << endl;
      return;
      }
   cout << "Updated " << file.Name() << "." << endl;
}

void debug_main(int argc, char *argv[]) {
   shazam fix;
   File file;
   file.Name("X.TXT");
   ostream& os = file.OpenWrite();
   os << "#" << "include <stdio.h>     // hello!"  << endl; // (common)
   os << "// This should remain." << endl;
   os << "#" << "include <strstrea.h>  // again!!" << endl; // (8.3)
   os << "// This should remain, too" << endl;
   file.Close();
   Fix(fix, file);
   file.Remove();
}

void main(int argc, char *argv[]) {
#if 0
   debug_main(argc, argv);
#else
   shazam fix;
   File file;
   ZStr str;
   while(cin)
      {
      str.Readline(cin);
      size_t pos = str.Find(':');
      if(pos == npos)
         continue;
      str.RemovePos(0, pos - 1);
      str.Strip();
      if(file.Name(str) == false)
         {
         cerr << "Unble to open file " << str << endl;
         continue;
         }
      Fix(fix, file);
      }

   cout << "Replaced " << fix.Results() << " items." << endl;
#endif
}
