
#include "IniFile.hpp"

using namespace ini;

IniData::IniData(void)
   {
   }
IniData::IniData(const ZStr& L, const ZStr& R) :  pLval(L), pRval(R)
   {
   }
IniData::~IniData(void)
   {
   }
void IniData::Get(ZStr& L, ZStr& R)
   {
   L = pLval; 
   R = pRval;
   }
void IniData::Put(const ZStr& L, const ZStr& R)
   {
   pLval = L; 
   pRval = R;
   }



