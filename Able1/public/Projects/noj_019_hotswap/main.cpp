// 01/07/2007: Converted to Able1, R. Nagy
//             Added support for pipe-fitting convention.
//
#include "hotswap.hpp"


void Usage(const ZStr& str)
   {
   cout << str;
   cout << endl;
   cout << "\t" << "Replace a ZStr in a text file. Renames and saves original file.";
   cout << endl;
   cout << endl;
   cout << "usage:";
   cout << endl;
   cout << str << ": ";
   cout << "[filename | !] target_ZStr = replacement_ZStr";
   cout << endl;
   cout << endl;
   cout << "(space delimiters are required around the \"=\")";
   cout << endl;
   cout << endl;
   cout << "! = use as pipe fitting.";
   }

void main(int argc, char *argv[])
   {
   if(argc != 5 || (argv[3][0] != '='))
      {
      Usage(argv[0]);
      return;
      }

   HotSwap hs;

   ZStr strF = argv[1];
   ZStr strA = argv[2];
   ZStr strB = argv[4];

   if(strF == "!")
      {
      while(cin)
         {
         ZStr str;
         str.Readline(cin);
         if(!cin)
            continue;
         str.RemovePos(0, str.Find(' '));
         str.MkWhite();
         str.Strip();

         strF = str.c_str();

         cout << endl;
         cout << "Updating " << strF;

         if(hs.Open(strF) == false)
            {
            cout << "(file not found)";
            cout << endl;
            cout << endl;
            Usage(argv[0]);
            return;
            }

         hs.Exec(strA, strB, cout);

         cout.flush();
         }
      }
   else
      {
      if(hs.Open(strF) == false)
         {
         Usage(argv[0]);
         return;
         }
      hs.Exec(strA, strB, cout);
      cout.flush();
      }


   }
