#include <Able1.hpp>
using namespace Able1;

void HomeBody(void)
{
// Using ProgramId to home-in 
// on resources
ProgramId pid;

Directory dir;
pid.Home(dir);

File file;
pid.Home(file);

}


void IndexFile(const File& file)
{
DFO<ZStr> tabFile;
tabFile.Name(file);
// Loads a binary file from a "heap"
tabFile.Load(File::AT_TEXT, false);

// WARNING: This over Writes the file
// with the indexed content!
StdSeek<ZStr> indexFile;
indexFile.Name(file);
for(size_t ss = 0L; ss < tabFile.Nelem(); ss++)
   indexFile.Append(tabFile[ss]);
}

#include <a1core/DFO.hpp>

void FileImport(const File& file)
{
// "Direct File Object" are either in a "heap"
// (one after another) or in an "Array" (prefixed 
// with the number of objects saved)
DFO<ZStr> tabFile;
tabFile.Name(file);
// Loads a binary file from a "heap"
tabFile.Load(File::AT_TEXT, false);
// Saves a text file of strings in a "Array"
tabFile.Save(File::AT_BINARY, true);
}



Array<ZStr> SplitTabs(const ZStr& sTab)
{
return sTab.slice('\t');
}

void TheZStr(void)
{
Array<ZStr> array;
array[0] = "this";
array[1] = "is a";
array[2] = "test!";

File file;
array.Write(file.OpenWrite());
file.Close();
}

void TheString(void)
{
Array<string> array;
array[0] = "this";
array[1] = "is a";
array[2] = "test!";
}


void QueryContent(const Directory& dir)
{
Array<File> aryFiles;
dir.Query(aryFiles);
for(size_t ss = 0L; ss < aryFiles.Nelem(); ss++)
   cout << "Got " << aryFiles[ss].Name() << endl;

Array<File> aryDirs;
dir.Query(aryDirs);
for(size_t ss = 0L; ss < aryDirs.Nelem(); ss++)
   cout << "Got " << aryDirs[ss].Name() << endl;
}

void QueryFileContent(void)
{
// The array class is the major container
// for this namespace
Array<File> aryFiles;

Directory dir;
// Both folders and files and be queried
dir.Query(aryFiles);
// Nelem() returns the count of the objects 
// (ones based)
for(size_t ss = 0L; ss < aryFiles.Nelem(); ss++)
   cout << "Got " << aryFiles[ss].Name() << endl;
}

int main(int argc, char *argv[])
{
// Create a file - default name is "default.file"
File file;
// Name the file something
if(file.Name("myfile.txt") == false)
   cerr << "bad platform name";

// Directories default to the present working directory (pwd)
Directory dir;
// The "Home" function places a node into a folder
if(dir.Home(file) == false)
   cerr << "bad folder name";
