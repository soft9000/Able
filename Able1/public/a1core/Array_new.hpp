// ****************************************************************************
// A Template-based array class that stores objects into a file / header set.
// -The only requirement for the object to be stored is that it be streamable,
// and operator= works as expected (4object duplication when array expands).
//
// 11/22/94, R. Nagy.
// Took my ARRAY solution from the ADVANCEDC++ class, fixed numerous bugs, and grew into
// the class you see here.
//
// 04/29/94, R. Nagy
// Renamed a lot of members. Added the Insert() and Remove().
//
// 02/10/96, R. Nagy
// Fixed bug in expandActive(), operator==() calls object== (rather than !=), added Nelem().
// TOOK MEMSET OUT OF ARRAY! IT'S EVIL!! CAN REALY SCREW-UP AN ARRAY OF OBJECTS!!
//
// 02/11/96, R. Nagy
// Re-tested and integrated the 'numZombie' feature.  numZombie allows for the array
// to dynamically contract (create trailing "zombies") THEN expandActive (re-use same)
// so as to bypass expensive node re-allocations. Also added and tested Empty().
//
// ////////////////////////////////////////////////////////////////////////////
// CAREFULL when writing under machines without garbage collection (DOS)!
// If you blow-up on a "new" where trivial operations are taking place && the
// object looks sane, suspect garbage collection && not having enough contiguous
// memory for `new T[]` to succeed: Try storing `T *` and manage allocation
// yourself to keep memory fragmentation to a minimum under primitive memory-management
// machines (i.e: Use Baggie<T>).
// ////////////////////////////////////////////////////////////////////////////
//
// 02/20/96: Fixed a bug I introduced last time: expandActive(0) went to += 0, R. Nagy.
// Split features of Empty() between itself and new `Free()` member (4 BETTER
// SPEED DURING RE-USE, STILL USE Empty()!).
//
// 05/31/97: Fixed bugs in Insert(), R. Nagy.
//
// ////////////////////////////////////////////////////////////////////////////
// SPEED, SPEED, SPEED!  This thing must be written for SPEED!! We can use Baggie<T>
// when we don't need  R-A-W  S-P-E-E-D ! !
// ////////////////////////////////////////////////////////////////////////////
//
// 11/26/1997: Warnings removed, finally re-coded operator >>, R. Nagy
// 01/02/1998: Added Read() and Write(), R. Nagy
// 01/06/1998: Publicized an AddZombies() to support pre-allocation (HyperRFC1), R. Nagy
// 01/09/1998: Re-wrote the AddZombies() operation to do both "expandActive" (IUO)
//    and AddZombies() (public). -Latter expands array, but sets it to zombie space.
//    Former expands the array to active space. R. Nagy.
// 01/20/1998: Fixed bug in operator=() when that.Nelem() == 0 got new T[0] (boom! on free), R. Nagy.
// 03/13/1998: Had operator ==(), saw no harm in adding Contains(T&), R. Nagy.
// 07/23/1998: Fixed a bug in operator=(): Needed to zero-out numZombie, R. Nagy.
// 05/10/1999: Added stream checking on Array<T, SZ>::Read(), R. Nagy
// 08/11/1999: Added At(), R. Nagy.
// 10/09/1999: Added Append(const Array<T>&), R. Nagy
// 01/14/2000: Added SZ as second template parameter, R. Nagy
// 01/19/2000: Added Read(istream, FileVersion&), R. Nagy
// 04/14/2001: Added Append(const T&) and operator +(const T&), R. Nagy
// 08/17/2001: Fixed potential bug in ___xMqFY() that occurred when had no elements and no zombies, R. Nagy
// 11/19/2001: Eliminated the potential of the dangling zombie object feature on erroneous array restoration (chalk one up for the learning curve (yeesh)), R. Nagy
// 05/05/2002: Added AddZombies() to ::Read() to help speed things up, R. Nagy
// 05/26/2002: Ran through NOTAB (new era!), R. Nagy
// 11/02/2004: Moved QuickSort<T, SZ> into this class, R. Nagy
//    In a futile speed-up gesture, increased NZ_BLOCK_SIZE from 20 to 100, R. Nagy
//    Ran through regression testing suite today. Fixed some bugs that (fortunately) were not part of my typical usage pattern. Required updates as indicated, R. Nagy
//    Fixed bug in AddZombie, R. Nagy
// 06/17/2004: Added Load/Save and moved Array underneath the Able1 namespace, R. Nagy
// 11/02/2004: Added QuickSort, R. Nagy
// 11/24/2004: Removed File and FileVersion support to better support G++, R. Nagy
// 01/02/2004: Added Dump(), R. Nagy
// 04/22/2005: Improved the Append(Array<T>) operation - Speed and portability enhancements, R. Nagy
// 04/02/2006: Added operator+(Array) and operator+=(Array), R. Nagy
// 07/07/2006: Added T& At(ss) (const) to return a reference to avoid Assign(meant copying (a speed improvement), R. Nagy
// 09/08/2006: Changed Write() to const by using At() rather than the never-can-be-const ("autogrow") operator[] - R. Nagy
// 10/01/2006: Extracted ObjecThunk into its own file - We do not use it very often, R. Nagy
// 01/19/2007: Added Replace(...), R. Nagy
// 01/25/2007: Added Randomize() and Scramble(), R. Nagy
// 03/07/2008: Fixed a bug that crept into operator=. Discovered while writing Invert(), R. Nagy
// 03/22/2008: Renamed "const At()" to "T& Get()" (no const!), R. Nagy
// 05/21/2008: Bugfix: operator=(Array<T>&) - Zombie count was being ignored after copy, R. Nagy
// 08/29/2008: _Array4_HPP: Converting to vector<t>, R. Nagy
// 08/30/2008: Ran framework test cases, Fixed auto-expansion, R. Nagy
// ****************************************************************************
#ifndef _Array4_HPP
#define _Array4_HPP
#include <vector>
using namespace std;

namespace Able1
   {

template <class T, class SZ = size_t> class QuickSort;


// Class Array<T> does *NOT* assume ownership of the Object;

#define SZ_ERROR (-1L)


template <class T, class SZ = size_t>
class Array
{
private:
   vector<T> varray;

public:
   Array(void);                     // Makes a zombie array of 1.    Nelem() == 0.
   Array(SZ usz);                   // Makes a zombie array of usz.  Nelem() == 0.
   Array(const Array<T> & old);
   virtual ~Array(void);

   bool IsNull(void)  const   {if(Nelem()) return false; return true;}
   
   SZ
      Maximum(void) const     {return SZ(-1L);}    // Maximum array capacity (SAME AS SZ_ERROR)
   SZ
      Nelem(void) const       {return varray.size();}  // Number in array
   SZ
      NumZombies(void) const  {return varray.capacity();}  // was "ZombieCount"
   void
      AddZombies(SZ nelem);         // This function GROWS the array by the number specified.
   // Normally, AddZombies() is not required, as operator[Nelem()] auto-expands the ACTIVE array-set
   // for you. However, since the internal array is contiguous, using AddZombies() to pre-size can speed
   // things up quite a bit, as the array is allocated and re-allocated as a single unit when more space
   // is needed.
   // From the coders viewpoint, using AddZombies() is more formal than merely growing an array by
   // referencing off-of the port-bow: Formally calling AddZombies() announces to everyone what you
   // are up to.
/*
   unsigned int
      Instance(void)  { return instance; }
   unsigned int
      Instances(void) { return instances; }
*/
   Array<T>&
      operator=(const Array<T> & rhs);
   Array<T>&
      operator+(const Array<T> & rhs);
   Array<T>&
      operator+=(const Array<T> & rhs);
   unsigned
      operator == (const Array<T> & rval) const;
   unsigned
      operator != (const Array<T> & rval) const;
   void
      operator +  (const T& rval)         {Append(rval);}
   T&
      operator [](SZ ss);             // THIS, OF COURSE, IS ZERO BASED (AUTO EXPANDS TO FILL REQUEST).
   bool
      At(SZ ss, T&)  const;           // ALLOWS ACCESS TO AN OBJECT IN A CONST ARRAY (NO AUTO_EXPANDING).
   T& 
      Get(SZ ss)  const;               // RETURNS DEFAULT OBJECT ON ERROR: ALLOWS ACCESS TO AN OBJECT IN A CONST ARRAY (NO AUTO_EXPANDING).
   SZ
      Contains(const T&) const;       // SZ_ERROR if !found, else FIRST ZERO-BASED index of hit.
   void
      Insert(const T&, SZ ss);        // THIS IS ZERO BASED, LIKE OPERATOR []!
   void
      Remove(SZ ss);                  // THIS IS ZERO BASED, LIKE OPERATOR []!
   void
      Empty(void);                    // Keeps [] as zombie space, but makes Nelem == 0.
   void
      Replace(const T& ref, SZ ss);
   void
      Free(void);                     // Deletes [], then makes a single [] with a zombie.
   void
      Append(const Array<T>&);
   void
      Append(const T& ref)            {varray.push_back(ref);}
   void
      Dump(ostream& os);
   
   // Randomize an array
   // A simple - yet effective - random partitioned exchange...
   // The more you run it, the more "random" the content will appear.
   // See Scramble() for a good way to do that!
   void Randomize(int iPartitions = 2);
   
   // Randomize an array mulitple times ... with random partition sizes.
   void Scramble(int iTimes);
   void Invert(void);

   ostream& Write(ostream& os) const;
   istream& Read(istream& is);

   friend class QuickSort<T, SZ>;

//Lets keep it public access, only;
//friend ostream & operator << (ostream & os,  const Array<T> & a);
//friend istream & operator >> (istream & is,        Array<T> & a);
};


template <class T, class SZ>
Array<T, SZ>::Array(void)
   {
   }

template <class T, class SZ>
Array<T, SZ>::Array(SZ usz)
   {
   }

template <class T, class SZ>
Array<T, SZ>::Array(const Array<T> & old)
   {
   varray = old.varray;
   }

template <class T, class SZ>
Array<T, SZ>::~Array()
   {
   }

template <class T, class SZ>
void Array<T, SZ>::Empty(void)
   {
#ifdef ARRAY_EMPTY_OKAY
   // Better still (minimize memory fragmentation);
   numZombie += Nelem();
   Nelem() = (SZ)0L;
#else
   Free();     // Problems with memory-overcommits on NT made me hard-code in this
               // Free(): After all, most popular OS' in the 90's FINALLY have
               // garbage collection!
#endif
   }

template <class T, class SZ>
void Array<T, SZ>::Replace(const T& ref, SZ ss)
   {
   if(ss == -1L)
      return;
   if(ss >= Nelem())
      return;  // hummm ... gigo?

   varray[ss] = ref;
   }

template <class T, class SZ>
void Array<T, SZ>::Free(void)
   {
   varray.clear();
   }

template <class T, class SZ>
void Array<T, SZ>::Append(const Array<T>& aAry)
   {
   AddZombies(aAry.Nelem() + 1);    // 04/22/2005 - Speed up, R. Nagy
   T ref;
   for(SZ ss = NULL; ss < aAry.Nelem(); ss++)
      {
      aAry.At(ss, ref);  // 04/22/2005 - Easier for compilers to "see", R. Nagy
      Append(ref);
      }
   }

template <class T, class SZ>
void Array<T, SZ>::Insert(const T& ins, SZ ss)  // THIS IS ZERO BASED, LIKE OPERATOR []!
   {
   if(ss >= Nelem())
      {
      Append(ins);
      return;
      }
   vector<T>::iterator it = varray.begin();
   it += ss;
   varray.insert(it, 1, ins);
   }

template <class T, class SZ>
void Array<T, SZ>::Remove(SZ ss) // THIS IS ZERO BASED, LIKE OPERATOR []!
   {
   vector<T>::iterator it = varray.begin();
   it += ss;
   varray.erase(it);
   }

template <class T, class SZ>
void Array<T, SZ>::AddZombies(SZ nelem)
   {
   varray.reserve(Nelem() + nelem);
   }

template <class T, class SZ>
void Array<T, SZ>::Invert(void)
   {
   if(Nelem())
      {
      Array<T, SZ> aTmp(*this);
      size_t xx = 0L;
      for(size_t ss = Nelem() - 1; true ; ss--)
         {
         operator[](ss) = aTmp[xx];
         xx++;
         if(ss == 0)
            break;
         }
      }
   }

template <class T, class SZ>
Array<T> & Array<T, SZ>::operator=(const Array<T> & rhs)
   {
   varray = rhs.varray;
   return *this;
   }

template <class T, class SZ>
Array<T> & Array<T, SZ>::operator+(const Array<T> & rhs)
   {
   T ref;
   AddZombies(rhs.Nelem());
   for(size_t ss = 0L; ss < rhs.Nelem(); ss++)
      {
      rhs.At(ss, ref);
      Append(ref);
      }
   return *this;
   }

template <class T, class SZ>
Array<T> & Array<T, SZ>::operator+=(const Array<T> & rhs)
   {
   T ref;
   AddZombies(rhs.Nelem());
   for(size_t ss = 0L; ss < rhs.Nelem(); ss++)
      {
      rhs.At(ss, ref);
      Append(ref);
      }
   return *this;
   }

template <class T, class SZ>
bool Array<T, SZ>::At(SZ ss, T& rCopy) const  // THIS, OF COURSE, IS ZERO BASED!
   {
   if (ss >= Nelem())
      {
      // BLANK-IT-OUT;
      T rResult;
      rCopy = rResult;
      return false;
      }
   // COPY IT OUT;
   rCopy = varray[ss];
   return true;
   }

template <class T, class SZ>
T& Array<T, SZ>::Get(SZ ss) const  // THIS, OF COURSE, IS ZERO BASED!
   {
   static T refNull;
   if (ss >= Nelem())
      {
      // RETURN OBJECT DEFAULT;
      T ref;
      refNull = ref;
      return refNull;
      }
   // REFERENCE IT OUT;
   return (T&)(varray[ss]);
   }


template <class T, class SZ>
T& Array<T, SZ>::operator [] (SZ ss)        // THIS, OF COURSE, IS ZERO BASED!
   {
   if(ss >= Nelem())
      {
      SZ nelem = Nelem();
      SZ xx = ss;
      xx += varray.capacity();
      varray.reserve(xx);

      vector<T>::iterator it = varray.end();
      T ins;
      varray.insert(it, ss - nelem + 1, ins);
      }
   return varray[ss];
   }

template <class T, class SZ>
unsigned Array<T, SZ>::operator != (const Array<T> & rval) const
   {
   return !(*this == rval);
   }

template <class T, class SZ>
unsigned Array<T, SZ>::operator == (const Array<T> & rval) const
   {
   if(Nelem() != rval.Nelem())
      return 0;

   for (SZ i = 0; i < Nelem(); i++)
      if (! (varray[i] == rval.varray[i]) )
         return 0;

   return 1;
   }

template <class T, class SZ>
SZ Array<T, SZ>::Contains(const T& rVal) const
   {
   for (SZ i = 0; i < Nelem(); i++)
      if ( (varray[i] == rVal) )
         return i;

   return SZ_ERROR;
   }

template <class T, class SZ>
void Array<T, SZ>::Dump(ostream& os)
   {
   for(size_t ss = 0L; ss < Nelem(); ss++)
      {
      T& rObj = operator[](ss);
      rObj.Write(os);
      }
   }

template <class T, class SZ>
ostream & Array<T, SZ>::Write(ostream & os) const
   {
   SZ nelem = Nelem();
   os << nelem << " ";
   for (SZ ss = 0; ss < nelem; ss++)
      {
      T& ref = (T&) varray[ss];
      ref.Write(os);
      }
   return os;
   }

template <class T, class SZ>
istream & Array<T, SZ>::Read(istream &is)
   {
   Empty();
   SZ nelem = NULL;
   if(!is)
      return is;
   is >> nelem;
   if(!is)
      return is;
   char ch;
   is.read(&ch, 1);
   if(!is)
      return is;
   if(nelem)
      AddZombies(nelem+2);     // 11-22-2002: One more time (sigh)       
   for(SZ ss = 0; ss < nelem; ss++)
      {
      T rObj;
      rObj.Read(is);
      if(!is)
         break;      // 11-19-2001: Eliminated the dangling zombie object.
      (*this)[ss] = rObj;
      }
   return is;
   }
#ifndef __GNUG__
// Poor little GNU - Unable to see the Randomize definition - Yet everyone else can!
template <class T, class SZ>
void Array<T, SZ>::Randomize(int iPartitions)
   {
   if(iPartitions < 2)
      iPartitions = 2;
      
   size_t iPartSize = Nelem() / iPartitions;
   if(iPartSize < iPartitions)
      return;
      
      // For each partition -
   for(size_t iPart = 0L; iPart < iPartitions; iPart++)
      {
      size_t basePart = iPart * iPartSize;
      
      // Swap the present partition with the VERY next partition - 
      for(size_t ss = basePart; ss < iPartSize; ss++)
         {
         size_t szEffective = ss + iPartSize;
         
         if(szEffective >= Nelem()) // maintenance - jic
            return;
         
         if(Random::TF())
            {
            T obj;
            obj = operator[](ss);
            operator[](ss)  = operator[](szEffective);
            operator[](szEffective) = obj;
            }
         }
      }
   }   
   
template <class T, class SZ>
void Array<T, SZ>::Scramble(int iTimes)
   {
   for(size_t ss = 0L; ss < iTimes; ss++)
      Randomize(Random::Rnd(2, 6));
   }   
#endif

template <class T>
ostream & operator << (ostream & os, Array<T>& a)
   {
   return a.Write(os);
   }

template <class T>
istream & operator >> (istream & is, Array<T>& a)
   {
   return a.Read(is);
   }
//template <class T, class SZ = size_t> class QuickSort
#ifdef MSDOS
#define _cdecl
#endif

template <class T, class SZ> class QuickSort
{
private:
   static int _cdecl cmp(const void *pl, const void *pr)
      {
      T l = *((T *)pl);
      T r = *((T *)pr);
      if(l > r)
         return 1;
      if(l < r)
         return -1;
      return 0;
      }

protected:
   virtual void Swap(T& l, T& r)
      {
      T hold = l;
      l = r;
      r = hold;
      }

public:
   void Sort(T *parray, SZ nelem)
      {
      qsort(parray, nelem, sizeof(T), QuickSort::cmp);
      }
      /* Update to vector usage ... later!
   virtual void Sort(Array<T, SZ>& array)
      {
      Sort(array.varray, array.Nelem());
      }
      */
};
   } // namespace Able1

#endif


