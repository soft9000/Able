// This little ditty demonstrates how to dump a file. Tool is usefull for
// doing things like Inserting license agreements on top of files without 
// using the POSIX `cat` or DOS `COPY /B` commands. Example of use:
//
// merge mit_licenst.txt myfile.c
// 
// or 
//
// merge ! mit_licenst.txt myfile.c
//
// 11/09/2003: Program Created, R. Nagy
//
#include <Able1.hpp>

using namespace Able1;

void Usage(ostream& cerr, ZStr& pName)
{
   cerr << "\tUsage: " << pName << " [!] header_file body_file" << endl;
   cerr << "\tPlaces header_file before body_file (stdout)." << endl;
   cerr << "\tUse ! to overWrite body file with combined content." << endl;
   cerr << "\t(Use of ! option creates a file named \"body_file.old\".)" << endl;
}


void main(int argc, char *argv[])
{
ZStr pName = argv[0];
pName.ToUpper();
if(argc < 3)
   {
   Usage(cerr, pName);
   return;
   }
bool bUpdate = false;
ZStr dtA, dtB;  // Remove the arguments from the DTA (MSDOS)
if(argv[1][0] == '!')
   {
   if(argc != 4)
      {
      Usage(cerr, pName);
      return;
      }
   dtA = argv[2];
   dtB = argv[3];
   File fileSafe;
   if(fileSafe.Name(dtB) == false)
      {
      Usage(cerr, pName);
      return;
      }
   if(fileSafe.Exists() == false)
      {
      Usage(cerr, pName);
      return;
      }
   if(fileSafe.CopyTo(dtB + ".old") == false)
      {
      cerr << "Unable to create file " << fileSafe.Name() << endl;
      return;
      }
   bUpdate = true;
   }
else
   {
   dtA = argv[1];
   dtB = argv[2];
   }

cerr << pName << ": Merge the content of two files together." << endl;

File fileIn;
if(fileIn.Name(dtA) == false)
   {
   cerr << "ERROR: " << dtA << " is not a valid file name (terminated)." << endl;
   return;
   }
File fileOut;
fileOut.MkUniqueName();
ostream& os = fileOut.OpenWrite();
fileIn.DumpContents(os);
if(fileIn.Name(dtB) == false)
   {
   cerr << "ERROR: " << dtB << " is not a valid file name (terminated)." << endl;
   return;
   }
fileIn.DumpContents(os);

if(!bUpdate)
   fileOut.DumpContents(cout);
else
   {
   if(fileOut.CopyTo(fileIn) == false)
      cout << "ERROR: File update failed!" << endl;
   else
      cout << "File content updated." << endl;
   }
fileOut.Remove();
}
