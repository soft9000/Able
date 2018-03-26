// Created for DOC and NUMBERS: A FASTER way to get at the records, without
// storage. Great for when number of records is large, and you are "goal seeking"
// a record / set / dump.
//
// 06/23/1997, Class Created (bare essentials!), R. Nagy.
// 05/22/1998, Now using "ZStr" rather than "ZStr", R. Nagy.
//    Created BinRecEnum, R. Nagy.
//
#ifndef RecEnum_Hpp
#define RecEnum_Hpp

#ifdef LEGACY
#include <HANDY.H>
#else
#include <Able1.hpp>
using namespace Able1;
#endif


template <class T>
   class RecEnum
      {
      protected:
         ZStr FileName;
         RecEnum(void) : FileName("Default.Dat") {}

      public:
         RecEnum(const char *pszFile) : FileName(pszFile) {}
         virtual long Enumerate(T& r, long sp = ios::beg);
      };


template <class T>
   class BinRecEnum : RecEnum<T>
      {
      public:
         virtual long Enumerate(T& r, long sp = ios::beg);
      };


template <class T>
long RecEnum<T>::Enumerate(T& r, long sp)
   {
   ifstream ifs(FileName.c_str(), ios::in);  // ios::nocreate;
   if(!ifs || ifs.bad())
      return ios::beg;

   ifs.seekg(sp);
   r.Read(ifs);
   if(ifs.eof())
      return ios::beg;

   return ifs.tellg();
   }


template <class T>
long BinRecEnum<T>::Enumerate(T& r, long sp)
   {
   ifstream ifs(FileName.c_str(), ios::in | ios::binary | ios::nocreate);
   if(!ifs || ifs.bad())
      return ios::beg;

   ifs.seekg(sp);
   r.Read(ifs);
   if(ifs.eof())
      return ios::beg;

   return ifs.tellg();
   }
#endif
