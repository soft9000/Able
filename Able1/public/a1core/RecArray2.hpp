#ifndef RecArray2_Hpp
#define RecArray2_Hpp

// This class was originally written to create a index-file of `long`.
// It was generalized into a template, because it is easy to apply it to other
// fixed-length entities. -All that you need to provide is an apropriate
// remove() set for your object. RecArray2 is a fast indexing mechanism for things
// that can be read and written via `ifs.Write((const char *)&T, sizeof(T))`.
//
// Note that your remove() can either delete the record && pack the
// file, or simply update() the same with a record marked as `deleted` (sp_npos,
// as in the default remove() (below));
//
// Member functions don't cache anything, so you can code && reuse this with impunity.
//
// Class created 07/22/1997, by R. Nagy
//
// 12/06/2003: Updated to work with Visual Studio 6, R. Nagy
// 08/04/2004: Fixed the update to File usage after Able1 port under VS.NET 2003, R. Nagy
//             Verified using _spi::test() routine.
// 01/05/2004: Updated seeking to use File logic, R. Nagy
// 08/25/2005: Added is_removed() and swap(). Removed commented-out FILE * logic, R. Nagy
// 08/26/2005: Replaced "const char *" with "const ZStr&" in naming functions, R. Nagy
// 04/27/2007: Copied RecArray to RecArray2. Minor member name updates, R. Nagy
//
#include <cstdio>
#include <fstream>
#include <cassert>

namespace Able1
   {
using namespace std;    // <<imda>> Must be in the namespace block ...

//typedef long unsigned size_t;
//const std::size_t sp_npos = ((std::size_t) -1L);


// THE RecArray2 CLASS WANTS AN OBJECT THAT RESPONDS TO THE SIZEOF() TO WRITE and READ.
template <class T>
class RecArray2
{
protected:
	File iFile;

public:
	RecArray2(void);
	virtual ~RecArray2(void);

	ZStr            Name(void)				      {ZStr str =  iFile.Name(); return str;}
	void                 Name(const File& file)	   {iFile = file;}
	bool                 Name(const ZStr& str)	{return iFile.Name(str);}
   bool                 Create(void)               {return iFile.Create();}
   bool                 Exists(void)               {return iFile.Exists();}
   bool                 Remove(void)               {return iFile.Remove();}

   // The sizeof-based number of elements in the file -
	size_t	Nelem(void);
	// Recall the CONTENT of the logical location -
	bool   Read(size_t logical, T& res);
	// Update the CONTENT of the logical locations -
	bool	Update(size_t, T& sp);
	// Exchange the CONTENTS of the two logical locations -
	bool	Swap(size_t sL, size_t sR);
	// Append the data to the file
	size_t	Append(T& sp);

   // NOTE: WE ASSUME THAT THE SIZEOF(T) >= SIZEOF(size_t) FOR DELETION PURPOSES!
   bool	   Remove(size_t logical);
   bool     IsRemoved(size_t which);
};


template <class T>
RecArray2<T>::RecArray2(void) : iFile("default.idx")
{
   // 08/04/2004 - Changed for backwards compatability
   // - old (iostream.h) long was a long (4 bytes under wintel)
   // - new (iostream)   long is 24 bytes!!
   // assert(sizeof(T) >= sizeof(long));
   assert(sizeof(T) >= sizeof(size_t));
}
template <class T>
RecArray2<T>::~RecArray2(void)
   {
   }
template <class T>
size_t RecArray2<T>::Nelem(void)
	{
   File file = iFile;
   if(file.IsNull())
      return 0L;
   if(file.Exists() == false)
      file.Create();
   iostream &fs = file.OpenReadWrite(File::AT_BINARY);
   fs.seekp(0, ios::end);  // prime the ftell pointer
   long tot = fs.tellp();
   if(tot == -1L)
      return 0L;
   file.Close();
	return ((size_t)(tot / sizeof(T)));
	}
template <class T>
size_t RecArray2<T>::Append(T& ref)
	{
   File file = iFile;
   if(file.Exists() == false)
      file.Create();
   iostream &fs = file.OpenReadWrite(File::AT_BINARY);
   fs.seekp(0, ios::end);  // prime the ftell pointer
   long tot = fs.tellp();
   if(tot == -1L)
      return 0L;
   fs.Write((const char *)&ref, sizeof(T));
   file.Close();
	return ((size_t)(tot / sizeof(T)));
	}
template <class T>
bool RecArray2<T>::Update(size_t which, T& ref)
	{
   File file = iFile;
	iostream& fs = file.OpenReadWrite(File::AT_BINARY);
	if(!fs)
		return false;
	fs.seekp(which * sizeof(T));  // 12/06/2003: Changed seekg to seekp, R. Nagy
	if(fs.bad())
		return false;
	fs.Write((const char *)&ref, sizeof(T));
	if(fs.bad())
		return false;
	return true;
	}
template <class T>
bool RecArray2<T>::Remove(size_t which)
	{
   File file;        // 12/06/2003: Converted to avoid Microsoft stream anomalies in VC 6, R. Nagy
   File file = iFile;
	iostream& fs = file.OpenReadWrite(File::AT_BINARY);
	if(!fs)
		return false;
	fs.seekp(which * sizeof(T));  // 12/06/2003: Changed seekg to seekp, R. Nagy
	if(fs.bad())
		return false;
	fs.Write((const char *)&sp_npos, sizeof(T));
	if(fs.bad())
		return false;
	return true;
	}
template <class T>
bool RecArray2<T>::IsRemoved(size_t which)
	{
   T st;
	Read(which, st);
	if(st == sp_npos)
	   return true;
	return false;
	}
template <class T>
bool RecArray2<T>::Read(size_t which, T& res)
	{
   File file;        // 12/06/2003: Converted to avoid Microsoft stream anomalies in VC 6, R. Nagy
   File file = iFile;
	iostream& fs = file.OpenReadWrite(File::AT_BINARY);
	if(!fs)
		return false;
	fs.seekg(which * sizeof(T));
	if(fs.good())
		{
		fs.Read((char *)&res, sizeof(T));
		if(fs.good())
			return true;
		}
	return false;
	}
template <class T>
bool RecArray2<T>::Swap(size_t sL, size_t sR)
   {
   T tL, tR;
   if(Read(sL, tL) == false)
      return false;
   if(Read(sR, tR) == false)
      return false;
   if(Update(sL, tR) == false)
      return false;
   if(Update(sR, tL) == false)
      return false;
   return true;
   }


} // Able1
#endif
