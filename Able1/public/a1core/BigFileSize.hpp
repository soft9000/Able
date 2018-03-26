// BigFileSize
// 11/04/1999: Class create to handle same (originally for Node1.Hpp), R. Nagy
//
#ifndef bigfilesize_hpp
#define bigfilesize_hpp

/** BigFileSize provides the namespace with a way record extremely long file (and other)
  * sizes.
  */
using namespace std;

class BigFileSize
   {
   protected:
      long unsigned ulSize;
      long unsigned ulSizePlus;

   public:
      BigFileSize(void) : ulSize(0L), ulSizePlus(0L)  {}
      BigFileSize(const BigFileSize& ffs)             {*this = ffs;}

      void          SetSize(long unsigned ul)         {ulSize = ul;}
      long unsigned GetSize(void)                     {return ulSize;}

      void          SetSizePlus(long unsigned ul)     {ulSizePlus = ul;}
      long unsigned GetSizePlus(void)                 {return ulSizePlus;}

      BigFileSize&   operator= (const BigFileSize& fz);
      int            operator==(const BigFileSize& fz) const;

      ostream& Write(ostream& os) const;
      istream& Read(istream& is);
   };

inline BigFileSize&
BigFileSize::operator=(const BigFileSize& fz)
   {
   if(this == &fz)
      return *this;
   ulSize = fz.ulSize;
   ulSizePlus = fz.ulSizePlus;
   return *this;
   }
inline int
BigFileSize::operator==(const BigFileSize& fz) const
   {
   return ( (ulSize == fz.ulSize) && (ulSizePlus == fz.ulSizePlus) );
   }
inline ostream&
BigFileSize::Write(ostream& os) const
   {
   os << ' ' << ulSize << ' ' << ulSizePlus << ' ';
   return os;
   }
inline istream&
BigFileSize::Read(istream& is)
   {
   char ch;
   is.read(&ch, 1);
   is >> ulSize;
   is.read(&ch, 1);
   is >> ulSizePlus;
   is.read(&ch, 1);
   return is;
   }
#endif
