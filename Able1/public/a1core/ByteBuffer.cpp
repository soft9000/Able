#include <Able1.hpp>
using namespace Able1;

namespace Able1
   {

ByteBuffer::ByteBuffer(void)                          : len(NULL), pBuf(NULL)
   {
   }
ByteBuffer::ByteBuffer(const ZStr& str)          : len(NULL), pBuf(NULL)
   {
   *this = ByteBuffer(str.c_str(), str.Length());
   }
ByteBuffer::ByteBuffer(const char *buf, size_t cb)    : len(cb  ), pBuf(NULL)
   {
   pBuf = new char[len+1];
   ::memset(pBuf, 0, len);
   ::memcpy(pBuf, buf, len);
   }
ByteBuffer::ByteBuffer(size_t cb)                     : len(cb  ), pBuf(NULL)
   {
   pBuf = new char[len+1];
   ::memset(pBuf, 0, len);
   }
ByteBuffer::ByteBuffer(const ByteBuffer& bb)          : len(NULL), pBuf(NULL)
   {
   *this = bb;
   }
ByteBuffer::~ByteBuffer(void)
   {
   delete [] pBuf;
   pBuf = NULL;
   }
bool ByteBuffer::IsNull(void) const
   {
   if(!len)
      return true;
   if(!pBuf)
      return true;
   return false;
   }
void ByteBuffer::Assign(const char *pin, size_t ss)
   {
   delete [] pBuf;
   len = ss;
   if(!len)
      {
      pBuf = NULL;
      return;
      }
   pBuf = new char [len+1];
   ::memcpy((void *)pBuf, (void *)pin, len);
   }
void ByteBuffer::Fill(char ch)
   {
   ::memset(pBuf, ch, len);
   }
void ByteBuffer::Prepend(const ByteBuffer& by)
   {
   if(!by.len)
      return;
   char *pbytes = new char[len + by.len +1];
   ::memcpy((void *)pbytes,           (void *)by.pBuf, by.len);
   if(len)
      ::memcpy((void *)&pbytes[by.len], (void *)pBuf,    len);
   delete [] pBuf;
   len   += by.len;
   pBuf  =  pbytes;
   }
void ByteBuffer::Append(const ByteBuffer& by)
   {
   if(!by.len)
      return;
   char *pbytes = new char[len + by.len +1];
   if(len)
      {
      ::memcpy((void *)pbytes,        (void *)pBuf,    len);
      ::memcpy((void *)&pbytes[len],  (void *)by.pBuf, by.len);
      }
   else
      ::memcpy((void *)pbytes, (void *)by.pBuf, by.len);
   delete [] pBuf;
   len   += by.len;
   pBuf  =  pbytes;
   }
void ByteBuffer::PadToAlignment(size_t mod)
   {
   if(!len)
      return;
   size_t len2 = len % mod;
   if(len2)
      {
      ByteBuffer by(len2);     // constructor zeros it out
      Append(by);
      }
   } 
ByteBuffer& ByteBuffer::operator=(const ByteBuffer& bb)
   {
   if(this == &bb)
      return *this;
   delete [] pBuf;
   len = bb.len;
   if(!len)
      {
      pBuf = NULL;
      return *this;
      }
   pBuf = new char[len+1];
   pBuf[len] = NULL;
   ::memcpy((void *)pBuf, (void *)bb.pBuf, len);
   return *this;
   }
void ByteBuffer::Append(void *psz, size_t nelem)
   {
   ByteBuffer by;
   by.Assign((char *)psz, nelem);
   Append(by);
   }
void ByteBuffer::Xdump(ostream& os, bool address, int option_base) const
   {
   if(!pBuf)
      {
      os << "<NULL>";
      os << endl;
      return;
      }
   size_t which, ss2, ss1;
   which = ss2 = ss1 = NULL;
   char *pbuf = new char[100];
   for(ss1 = NULL; (ss1 * option_base) < len; ss1++)
      {
      // Address
      if(address)
         {
         ::sprintf(pbuf, "%04d: ", ss1 * option_base);
         os << pbuf;
         }
      // Hexdump
      for(ss2 = NULL; ss2 < option_base; ss2++)
         {
         which = (ss1 * option_base) + ss2;
         if(which <= len)
            ::sprintf(pbuf, " %02x", pBuf[which]);
         else
            ::strcpy(pbuf, "   ");
         os << pbuf;
         }
      // Translational (clear text)
      ::strcpy(pbuf, ":   ");
      os << pbuf;
      for(ss2 = NULL; ss2 < option_base; ss2++)
         {
         which = (ss1 * option_base) + ss2;
         if(which <= len)
            {
            char bb = pBuf[which];
            if((bb >= ' ') && (bb <= '~'))
               ::sprintf(pbuf, "%c", bb);
            else
               ::strcpy(pbuf, ".");
            }
         else
            ::strcpy(pbuf, " ");
         os << pbuf;
         }
      os << endl;
      }
   delete [] pbuf;
   }
void ByteBuffer::Hexdump(ostream& os, bool address, int option_base) const
   {
   char *pbuf = new char[100];
   os << endl;
   sprintf(pbuf, "Block has %04d bytes:", len);
   os << pbuf;
   os << endl;
   delete [] pbuf;

   Xdump(os, address, option_base);
   os << endl;
   }
void ByteBuffer::Hexline(ZStr& str, bool address, int option_base) const
   {
   str = "";  // maybe free some mega-memory.
   stringstream srm;
   Xdump(srm, address, option_base);
   str = PRESTO(srm);
   }
int ByteBuffer::operator==(const ByteBuffer& bb)
   {
   if(len == bb.len)
      {
      int ires = ::memcmp(pBuf, bb.pBuf, len);
      if(!ires)
         return 1;
      }
   return 0;
   }
ostream& ByteBuffer::Write(ostream& os) const
   {
   os.write((char *)&len, sizeof(size_t));
   if(len)
      os.write((const char *)pBuf, len);
   return os;
   }
istream& ByteBuffer::Read(istream& os)
   {
   delete [] pBuf;
   pBuf = NULL;
   os.read((char *)&len, sizeof(size_t));
   if(len)
      ReadBytes(os, len);
   return os;
   }
ostream& ByteBuffer::WriteStream(ostream& os) const
   {
   os << len << " ";
   if(len)
      os.write((const char *)pBuf, len);
   return os;
   }
istream& ByteBuffer::ReadStream(istream& is)
   {
   if(is)
      {
      size_t sz2 = NULL;
      is >> sz2;
      if(!is)
         goto rd_abort;
#ifdef DEBUG
      if(sz2 > max_read)
         throw "Possibly a too-large ZStr error!";
#endif
      char ch[5];
      is.read(ch, 1);   // skip the ' '
      if(!is)
         goto rd_abort;

      delete [] pBuf;
      len = sz2;      // exact length
      pBuf = new char[len + 2];
      is.read(pBuf, len);
      }
   else
      {
   rd_abort:
      ByteBuffer blanker;
      *this = blanker;
      }
   return is;
   }
size_t ByteBuffer::ReadFile(istream& fs)
   {
   long sp1 = fs.tellg();
   fs.seekg(0L, ios::end);
   long sp2 = fs.tellg();
   len = sp2 - sp1;
   fs.seekg(sp1);
   return ReadBytes(fs, len);
   }
size_t ByteBuffer::ReadBytes(istream& is, size_t sz)
   {
   len = sz;
   delete [] pBuf;
   pBuf = new char[len+1];
   pBuf[len] = (char)NULL;
   size_t in = 0L;
   int ich;
   while(len != in)
      {
      ich = is.get();
      if(!is)
         break;
      pBuf[in] = (char)ich;
      in++;
      }
   len = in;
   return in;
   }
void ByteBuffer::Assign(const void   *pin, size_t ss)
   {
   Assign((char *)pin, ss);
   }
void ByteBuffer::Empty(void)
   {
   ByteBuffer bb;
   *this = bb;
   }
void ByteBuffer::Assign(const ZStr& str)
   {
   Assign(str.c_str(), str.Length());
   }
void ByteBuffer::Append(char by)
   {
   // Expensive... Do someting faster later...
   ByteBuffer cp(len+1);
   ::memcpy(cp.pBuf, pBuf, len);
   cp.pBuf[len] = by;
   *this = cp;
   }
ByteBuffer& ByteBuffer::operator=(const ZStr& str)
   {
   Assign(str);
   return *this;
   }

}; // Able1
