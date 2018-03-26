#include <Able1.hpp>
using namespace Able1;

namespace Able1 {

bool CommonObject::IsNull(void) const
   {
   ZStr str;
   ToString(str);
   return str.IsNull();
   }

bool CommonObject::Transfer(ostream& os)
   {
   ZStr str;
   ToString(str);
   str.WriteStream(os);
   return true;
   }
bool CommonObject::Transfer(istream& is)
   {
   if(!is)
      return false;
   ZStr str;
   str.ReadStream(is);
   if(!is)
      return false;
   return FromString(str);
   }

ZStr ShareableObject::LiberatedName(char chSep)
   {
   ZStr str;
   ToString(str);
   return FilePath::LiberatedName(str, chSep);
   }
} // Able1
