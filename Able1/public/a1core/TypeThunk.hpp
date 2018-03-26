#ifndef TypeThunk_Hpp
#define TypeThunk_Hpp

//! A TypeThunk<T> is what you use when you want to use manage a simple type
//! as an object. Useful (for example) when managing same in an Array<T>

namespace Able1
   {
   template <class T>
   struct TypeThunk
      {
         T    zType;
         
         TypeThunk(void) : zType(NULL)                    {}
         TypeThunk(const T& ref)                          {zType = ref;}

         operator T(void)                                 {return zType;}
      };

}

#endif
