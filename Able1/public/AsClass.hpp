// AsClass<T>: Allow a base-type to participate in the Array<T> (etc).
// 03/25/2000: Class created, R. Nagy
// 08/03/2004: Ported over to Able1, R. Nagy
//
#ifndef AsClass1B_Hpp
#define AsClass1B_Hpp

template <class T> 
class AsClass
   {
   protected:
      T which;

   public:
      AsClass(void)            {}
      AsClass(const T& qt)     {which = qt;}
      virtual ~AsClass(void)   {}

      T& operator=(const T& qt){which = qt; return which;}
         operator T(void)      {return which;}
      T& operator *(void)      {return which;}

      int operator==(T& qt)    {return which == qt;}
      int operator!=(T& qt)    {return which != qt;}
      int operator>=(T& qt)    {return which >= qt;}
      int operator<=(T& qt)    {return which <= qt;}
      int operator>(T& qt)     {return which > qt;}
      int operator<(T& qt)     {return which < qt;}

      ostream& Write(ostream& os)   {os << which << endl;return os;}
      istream& Read(istream& is)    {is >> which; return is;}
   };

#endif
