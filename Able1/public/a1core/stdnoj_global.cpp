#include <Able1.hpp>
using namespace Able1;

namespace Able1 {

ZStr PRESTO(stringstream& srm)
   {
   ZStr p = srm.str().c_str();
   return p;
   }

void convert(Array<ZStr>& a1, Array<StreamZStr>& a2)
   {
   a2.Empty();
   a2.AddZombies(a1.Nelem());
   for(size_t ss = 0L; ss < a1.Nelem(); ss++)
      {
      ZStr& str = a1[ss];
      StreamZStr sstr(str.c_str());
      a2.Append(sstr);
      }
   }

void convert(Array<StreamZStr>& a1, Array<ZStr>& a2)
   {
   a2.Empty();
   a2.AddZombies(a1.Nelem());
   for(size_t ss = 0L; ss < a1.Nelem(); ss++)
      a2.Append(a1.operator[](ss).c_str());
   }

}  // Able1
