#ifndef StdSeek2_Hpp
#define StdSeek2_Hpp

// 04/27/2007 Re-factored StdSeek to create StdSeek2, R. Nagy.
//
// #include <a1core/StdSeek.hpp>

#include <Able1.hpp>
#include <a1core/RecArray2.hpp>

#ifdef UNIX
#include <unistd.h>  // unlink
#else
#include <io.h>      // unlink
#endif

#define BEGIN {
#define END   }

namespace Able1
   {
using namespace std;

template <class T, class B>
class StdSeek2
{
private:
	File         fileData;
	RecArray2<B> indexFile;

   bool AppendDataOnly(const T& ref, seek_t& sp);

public:
   static ZStr Type() {return ".STD2";}

	bool Create(const File& file);
	bool Open(const File& file);
	void Destroy(void);

   bool Append(const T& ref);
	bool Read(size_t ss, T& ref);
   bool Update(size_t ss, T& uq);
   bool Swap(size_t ss1, size_t ss2);

	bool Pack(void);

	size_t Nelem(void);
};

template <class T, class B>
bool StdSeek2<T, B>::Open(const File& file)
{
   bool br = false;
   if(file.QueryNode().ends_with(Type()) == false)
      br = fileData.Name(file.Name() + Type());
   else
      br = fileData.Name(file.Name());

   indexFile.name(fileData.Name() + ".idx2");

   return true;
}

template <class T, class B>
bool StdSeek2<T, B>::Create(const File& file)
{
   bool br = false;
   if(file.QueryNode().ends_with(Type()) == false)
      br = fileData.Name(file.Name() + Type());
   else
      br = fileData.Name(file.Name());
   if(br == false)
      return false;

   if(fileData.Exists())
      return false;

   indexFile.Name(ZStr(fileData.Name()) + ".idx2");
   Destroy();

   indexFile.Create();
   if(indexFile.Exists() == false)
      return false;

   fileData.Create();
   if(fileData.Exists() == false)
      return false;

   return true;
}

template <class T, class B>
void StdSeek2<T, B>::Destroy(void)
{
   indexFile.Remove();
   fileData.Remove();
}
template <class T, class B>
bool StdSeek2<T, B>::Append(const T& ref)
{
   seek_t sp;
	if(AppendDataOnly(ref, sp) == true)
		{
      B fart(ref, sp);
	   if(indexFile.Append(fart) == sp_npos)    // 11/26/2003, R. Nagy
         return false;
		return true;
		}
	return false;
}

template <class T, class B>
bool StdSeek2<T, B>::AppendDataOnly(const T& ref, seek_t& sp)
{
   File file = fileData;
   if(file.Exists() == false)
      file.Create();
   iostream &fs = file.OpenReadWrite(File::AT_BINARY);
   fs.seekp(0, ios::end);  // prime the ftell pointer
   sp = fs.tellp();
   if(sp == -1L)
      return false;
   ((T&)ref).Write(fs);
   file.Close();
   return true;
}
template <class T, class B>
bool StdSeek2<T, B>::Read(size_t sssssss, T& ref)
{
   // First, we get the index relative locaiton of the record to read
   B sp;
	bool br = indexFile.Read(sssssss, sp);
   // Either an index read failure, or the index entry has been marked as deleted;
	if(sp == sp_npos)
      return false;
   if(br == true)
      {
      // Now we read the actual record
      File file = fileData;
      istream& fs = file.OpenRead(File::AT_BINARY);
      if(!fs)
         return false;
		fs.seekg(sp);
		if(!fs)
         return false;
		ref.Read(fs);
		if(fs)
         return true;
		}
	return false;
}
template <class T, class B>
bool StdSeek2<T, B>::Update(size_t ss, T& uq)
{
   // Validate that there is an object at ss;
   B sp;
   if(indexFile.Read(ss, sp) == false)
      return false;

   bool br = AppendDataOnly(uq, sp);
   if(br == true)
      return indexFile.Update(ss, sp);
   return br;
}
template <class T, class B>
bool StdSeek2<T, B>::Pack(void)
   {
   return false;
   }
template <class T, class B>
size_t StdSeek2<T, B>::Nelem(void)
   {
   return indexFile.nelem();
   }
template <class T, class B>
bool StdSeek2<T, B>::Swap(size_t ssL, size_t ssR)
   {
   return indexFile.Swap(ssL, ssR);
   }

} // Able1

#endif
