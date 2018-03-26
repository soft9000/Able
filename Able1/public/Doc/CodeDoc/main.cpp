#include "CodeDoc.hpp"

int main(int argc, char *argv[])
{
if(argc != 2)
   {
   cout << "Usage: " << argv[0] << " source_file_name" << endl;
   return -1;
   }
File file;
file.Name(argv[1]);
if(file.Exists() == false)
   {
   cerr << "Error: Unable to open " << argv[1];
   return -1;
   }

CodeDoc::CodeFormatter cf;
if(cf.Beautify(file) == false)
   {
   cerr << "Error: Unable to format " << file.Name();
   return -1;
   }
cout << "Success: Re-formatted " << file.Name() << endl;
}