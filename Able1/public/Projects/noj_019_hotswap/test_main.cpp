#include "hotswap.hpp"

void MakeTestFile(string& std)
   {
   std = "TestFile.txt";
   ofstream os(std.c_str(), ios::out);
   for(size_t ss  =  NULL; ss < 10; ss++)
      {
      os << "This is test testtesttest test line " << ss + 1;
      os << endl;
      }
   }

void main(int argc, char *argv[])
   {
   string std;

   MakeTestFile(std);
   HotSwap hs;
   hs.Open(std.c_str());

   hs.Exec("test", "TEST", cout);
   cout.flush();
   }
