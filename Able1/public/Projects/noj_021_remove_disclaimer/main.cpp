// This little ditty demonstrates how to dump a file. Tool is usefull for
// doing things like removing license agreements on top of files without 
// using the POSIX `cat` or DOS `COPY /B` commands. Example of use:
//
// attrib *.?pp /s | xmitl !
// 
// 02/04/2007: Program Created, R. Nagy
//
#include <Able1.hpp>

using namespace Able1;

const ZStr S_PATTERN = "/* The MIT License (O";

void Usage(ostream& cerr, ZStr& sName)
{
   cerr << "\tUsage: " << sName << " ! " << endl;
   cerr << "\tRemoved MIT license comment from the top of file in. .OLD backup created." << endl;
}

bool PeekPattern(const File& fff, int depth)
{
int times = 0;
File file = fff;
istream& is = file.OpenRead();
ZStr sLine;
while(is)
   {
   sLine.Readline(is);
   if(!is)
      return false;

   times++;
   if(times == depth)
      return false;

   size_t szPos = sLine.Find(S_PATTERN);
   if(szPos != npos)
      return true;

   }
return false;
}


void main(int argc, char *argv[])
{
ZStr sName = argv[0];
sName.ToUpper();
if(argc < 2)
   {
   Usage(cerr, sName);
   return;
   }

while(cin)
   {
   ZStr sLine;
   sLine.Readline(cin);
   if(!cin)
      {
      continue;
      }

   sLine.MkWhite();
   sLine.Strip();

   if(sLine.IsNull())
      {
      cerr << "Error: (NULL) file name line on input.";
      return;
      }
   size_t szPos = sLine.Find(':');
   if(szPos == npos)
      {
      cerr << "Error: Drive specifier not found on file name input.";
      return;
      }
   sName = sLine.subpos(szPos + 1, npos);
   File file;
   if(file.Name(sName) == false)
      {
      cerr << "Error: \"" << sName << "\" is an invalid file name.";
      return;
      }
   if(file.Exists() == false)
      {
      cerr << "Error: \"" << sName << "\" not found.";
      return;
      }

   if(PeekPattern(file, 10) == false)
      continue;

   sName += ".OLD";
   File fileOld;
   if(fileOld.Name(sName) == false)
      {
      cerr << "Error: \"" << sName << "\" not found.";
      return;
      }
   if(file.CopyTo(fileOld) == false)
      {
      cerr << "Unable to clone " << file.Name();
      return;
      }

   cout << "Processing " << file.Name() << endl;

   bool bFound = false;
   bool bSkip = false;
   istream& is = fileOld.OpenRead();
   ostream& os = file.OpenWrite();
   while(is)
      {
      // SETP: Read the line
      sLine.Readline(is);
      if(!is)
         {
         // OBSERVED
         if(sLine.IsNull() == false)
            os << sLine << endl;
         continue;
         }

      if(bFound)
         {
         os << sLine << endl;
         continue;
         }

      // STEP: Check for ending
      if(bSkip)
         {
         size_t szPos = sLine.Find("*/");
         if(szPos != npos)
            {
            // Q: What if there is something on that comment line?
            // A: There never is in this usage!
            bSkip = false;
            bFound = true; // So programs like this one will be unchanged -
            continue;
            }
         } // bSkip end check

      // STEP: Check for start
      size_t szPos = sLine.Find(S_PATTERN);
      if(szPos != npos)
         {
         bSkip = true;
         continue;
         } // bSkip start check

      // STEP: Do the skip -
      if(bSkip)
         continue;

      // STEP: Write it out
      os << sLine << endl;
      }
   } // cin
}
