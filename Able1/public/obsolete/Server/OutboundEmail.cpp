#include <obsolete/Server/OutboundEmail.hpp>

OutBoundEmail& OutBoundEmail::operator=(const OutBoundEmail& em)
{
if(this == &em)
   return *this;
email = em.email;
email.EncodeDots();
return *this;
}

bool OutBoundEmail::IsOutBoundEmailFile(const ZStr& pszfn)
   {
   EmailHeader emh;
   ifstream ifs(pszfn.c_str(), ios::in | ios::binary);
   if(emh.Read(ifs))
      if(header == emh)
         if(header.VersionNumber() == emh.VersionNumber())
            return true;
   return false;
   }

