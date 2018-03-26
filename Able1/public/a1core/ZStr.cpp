#include <Able1.hpp>
using namespace Able1;


ZStr::~ZStr(void)
{
   delete [] psz_alloc;
}


void ZStr::_init(void)
{
   extra_bytes = MIN_GROW_SPACE;
   sz_alloc    = extra_bytes + sizeof(NULL);
   psz_alloc   = new char[sz_alloc];
   *psz_alloc  = NULL;
   Iomax(MAX_READ_DEFAULT);
}


size_t ZStr::Iomax(void)
{
return max_read;
}


void ZStr::Iomax(size_t sz)
{
   if(sz < size_t(-1L)) 
      {
      max_read = sz;
      return;
      }
   max_read = MAX_READ_DEFAULT;
}


size_t ZStr::instance_growth_space(void)
{
return extra_bytes;
}


void ZStr::instance_growth_space(size_t sz) 
{
   if(sz < size_t(-1L)) 
      {
      extra_bytes = ((size_t(-1L)) - sizeof(NULL));
      return;
      }
   if(sz > MIN_GROW_SPACE) 
      {
      extra_bytes = sz;
      return;
      };
}


// "end" is a offset after offset "pos" (inclusive);

char *ZStr::_Substr(const char *psz, size_t start, size_t end) const
{
   if(!psz)
      return NULL;
   size_t dest_len = ::strlen(psz);
   // Full bounds-checking doesn't cost too much these days;
   if(start > dest_len)
      return NULL;
   if(end > dest_len)
      end = dest_len;
   if(start >= end)
      return NULL;         // <= cuz a memcpy(,,0) doesn't make much sense, either...

   // Do it && return an allocated buffer;
   char *pBuf = new char[end - start + sizeof(NULL)];
   ::memcpy(pBuf, &psz[start], end - start);
   pBuf[end - start] = NULL;
   return pBuf;
}

// "end" is NPOS or a count of bytes to take from offset "start" (inclusive);

size_t ZStr::Tally(const ZStr& ch, int ignore_case) const
{
   size_t res = 0L;
   size_t whence = Find(ch, 0L, ignore_case);
   while(whence != NPOS)
      {
      res++;
      whence = Find(ch, whence+1, ignore_case);
      }
   return res;
}


ZStr ZStr::Subpos(size_t start, size_t end) const
{
if(end > Length())
   end = Length();
return Substr(start, end - start);
}

// "end" is NPOS or a count of bytes to take from offset "start" (inclusive);

ZStr ZStr::Substr(size_t start, size_t end) const
{
char *pBuf;
   if(end == NPOS)
      pBuf = _Substr(c_str(), start, Length());
   else
      {
      size_t sz = start + end;
      if(sz > Length())
         sz = Length();
      pBuf = _Substr(c_str(), start, sz);
      }

   ZStr stackResult;
   if(pBuf == NULL)
      stackResult = "";
   else
      {
      stackResult = pBuf;
      delete []pBuf;
      }
   return stackResult;
}


const char *ZStr::Own(char *psz)
{
   delete[] psz_alloc;
   psz_alloc = psz;
   sz_alloc = strlen(psz);
   return c_str();
}


const char *ZStr::Own(char *psz, size_t bytes)
{
   delete[] psz_alloc;
   psz_alloc = psz;
   sz_alloc = bytes; // strlen(psz);
   return c_str();
}

ZStr& ZStr::Assign(const string& str)
{
   return Assign(str.c_str());
}

ZStr& ZStr::Assign(istream& is)
{
ZStr str;
while(is)
   {
   str = "";
   str.ReadLine(is);
   if(str.IsNull() == false)
      Append(str);
   }
return *this;
}


ZStr& ZStr::Assign(const char *psz, size_t start, size_t end)
{
   if(!psz)
      return Assign("");

   char *pBuf = _Substr(psz, start, end);
   if(pBuf)
      {
      Assign(pBuf);
      delete [] pBuf;
      }
   else
      Assign("");
   return *this;
}


ZStr& ZStr::Remove(char ch)
{
   stringstream srm;
   for(size_t ss = 0L; ss < Length(); ss++)
      {
      if(psz_alloc[ss] == ch)
         continue;
      srm << psz_alloc[ss];
      }
   Assign(srm.str().c_str());
   return *this;
}


ZStr& ZStr::Remove(int start)
{
   return Remove((size_t) start);
}


ZStr& ZStr::Remove(size_t start)
{
   if(start < Length())
      psz_alloc[start] = NULL;
   return *this;
}


ZStr& ZStr::RemoveBytes(size_t start, size_t end)
{
   if(!end)
      return *this;
   size_t max = Length();
   if(!max)
      return *this;
   if(start >= max)
      return *this;
   if(end >= max)
      end = max;
   if((start + end) >= max)
      return Remove(start);
   strcpy(&psz_alloc[start], &psz_alloc[start + end]);
   return *this;
}


ZStr& ZStr::RemovePos(size_t start, size_t end)
{
   if(start >= end)
      return *this;
   size_t max = Length();
   if(start >= max)
      return *this;
   if(end >= max)
      end = max;
   strcpy(&psz_alloc[start], &psz_alloc[end]);
   return *this;
}


int ZStr::Cmp(const ZStr& zs, int ignore_case) const
{
return ci_strcmp(psz_alloc, zs.psz_alloc, ignore_case);
}



ZStr& ZStr::RemovePrefix(const ZStr& sPattern, int ignore_case)
{
char chL, chR;
size_t ss = NULL;
size_t max_bytes = (sPattern.Length() < Length()) ? sPattern.Length() : Length();
while(1)
   {
   chL = sPattern[ss];
   chR = (*this)[ss];
   if(ignore_case)
      {
      chL = toupper(chL);
      chR = toupper(chR);
      }
   if(chL != chR)
      break;
   if(ss == max_bytes)
      break;
   ss++;
   }
RemoveBytes(0, ss);
return *this;
}


ZStr& ZStr::Assign(long ii)
{
   char buf[100];
   ::sprintf(&buf[0], "%ld", ii);
   return Assign(&buf[0]);
}


ZStr& ZStr::Assign(int ii)
{
   char buf[20];
   ::sprintf(&buf[0], "%d", ii);
   return Assign(&buf[0]);
}


ZStr& ZStr::Assign(char ch)
{
   char buf[5];
   ::sprintf(&buf[0], "%c", ch);
   return Assign(&buf[0]);
}


ZStr& ZStr::Append(char ch)
{
   char buf[5];
   ::sprintf(&buf[0], "%c", ch);
   return Append(&buf[0]);
}

ZStr&  ZStr::Append(char ch, size_t count)
{
   char *pbuf = new char[count + 1];
   ::memset(pbuf, ch, count);
   pbuf[count] = NULL;
   Append(pbuf);
   delete[] pbuf;
   return *this;
}

ZStr& ZStr::Prepend(char ch)
{
   char buf[5];
   ::sprintf(&buf[0], "%c", ch);
   return Prepend(&buf[0]);
}


int ZStr::operator!=(const ZStr& ss) const
{
   return (!(*this == ss));
}


ZStr& ZStr::operator=(const string& str)
{
   return Assign(str.c_str());
}

ZStr& ZStr::operator=(const ZStr& ss)
{
   if(this == &ss)
      return *this;
   Assign(ss.c_str());
   return (*this);
}


ZStr& ZStr::operator=(const char *ss)
{
   Assign(ss);
   return (*this);
}


ZStr& ZStr::operator=(char ch)
{
   char buf[5];
   ::sprintf(&buf[0], "%c", ch);
   Assign(&buf[0]);
   return *this;
}


int ZStr::operator>(const ZStr& ss) const
{
int cmp = ci_strcmp(psz_alloc, ss.psz_alloc);
switch(cmp)
   {
   case 0:
   case 1:
      return 1;
   default:
      return 0;
   }
}


int ZStr::operator<(const ZStr& ss) const
{
int cmp = ci_strcmp(psz_alloc, ss.psz_alloc);
switch(cmp)
   {
   case 0:
   case 1:
      return 0;
   default:
      return 1;
   }
}


int ZStr::Equals(const ZStr& ss, int ignore_case) const
{
   if(this == &ss)
      return 1;
   if(ci_strcmp(psz_alloc, ss.psz_alloc, ignore_case) == 0)
      return 1;
   return 0;
}


int ZStr::operator==(const ZStr& ss) const
{
   return Equals(ss);
}


char& ZStr::operator[](size_t ss) const
{
   if(ss > sz_alloc)
      return psz_alloc[sz_alloc %ss];  // best chance... (no exception thrown)
   return psz_alloc[ss];
}


size_t ZStr::Length(void) const
{
   return (::strlen(psz_alloc));
}


const char *ZStr::c_str(void) const
{
   return psz_alloc;
}


ZStr& ZStr::Assign(const char *psz)
{
   if(!psz)
      psz = (const char *)"";

   size_t sz2 = ::strlen(psz);

   // 01/22/2000: DEFINING AN ARBITRARY RE-ALLOCATION THRESHOLD
   // ---------------------------------------------------------
   // A simple speed-up: Hitting RAM re-allocations is a REAL performance killer, and
   // allowing more than a small buffer to "hang around" is a REAL space killer when
   // arrays of objects using strings are used. The following represents our compromise 
   // between SPACE and SPEED. We simply pick a "reasonable" `don't-release` thresh-hold;
   if((sz_alloc < (extra_bytes + (extra_bytes/4) )) && sz2 < sz_alloc)
      {
      // when we DON'T mess with sz_alloc, && we'll realize some VERY non-trivial speed-ups:
      ::strcpy(psz_alloc, psz);
      return *this;
      }

   // If the buffer is larger than the arbitrary (small) buffer, then we hit the heap,
   // (or, hopefully, the compilers local-store, or sub-allocation subsystem) for more
   // memory. Traditionally, realloc() has been usefull here;
   sz_alloc = sz2 + extra_bytes + sizeof(NULL);
   char *psz_allocIFDUP = new char[sz_alloc];      // JUST IN CASE we are self-referencing
   ::strcpy(psz_allocIFDUP, psz);

   delete [] psz_alloc;                            // JUST IN CASE we are self-referencing
   psz_alloc = psz_allocIFDUP;
   return *this;
}


ZStr& ZStr::Assign(const ZStr& ss)
{
   Assign(ss.c_str());
   return *this;
}


ZStr& ZStr::Append(const ZStr& ss)
{
   Append(ss.c_str());
   return *this;
}


ZStr& ZStr::Append(const char *psz, size_t start, size_t end)
{
   if(end > Length())
      end = Length();

   char *pBuf = _Substr(psz, start, end);
   if(!pBuf)
      return *this;
   Append(pBuf);
   delete [] pBuf;
   return *this;
}


ZStr& ZStr::Append(const char *psz)
{
   // NOW checking 4 buffer under-use..
   if(!psz)
      return *this;     // Ignore a NULL pointer...
   if(!(*psz))
      return *this;     // Appending a NULL...

   if( sz_alloc < (::strlen(psz_alloc) + ::strlen(psz) + sizeof(NULL)) )
      {
      ZStr ssOld = psz_alloc;
      delete [] psz_alloc;
      sz_alloc  = ssOld.Length() + ::strlen(psz) + extra_bytes + sizeof(NULL);
      psz_alloc = new char[sz_alloc];
      ::strcpy(psz_alloc, ssOld.c_str());
      }
   ::strcat(psz_alloc, psz);    // Zooom!
   return *this;
}


ZStr& ZStr::Prepend(const ZStr& ss)
{
   Prepend(ss.c_str());
   return *this;
}


ZStr& ZStr::Prepend(const char *psz)
{
   // NOW checking 4 buffer under-use..
   ZStr ssOld(psz_alloc);
   if( sz_alloc < (ssOld.Length() + ::strlen(psz) + sizeof(NULL)) )
         {
         delete [] psz_alloc;
         sz_alloc    = ssOld.Length() + ::strlen(psz) + extra_bytes  + sizeof(NULL);
         psz_alloc   = new char[sz_alloc];
         }
   ::strcpy(psz_alloc, psz);     // NO Zoom! (sigh)
   ::strcat(psz_alloc, ssOld.c_str());
   return *this;
}


void ZStr::Reverse(void)
{
   strrev(psz_alloc);
}


void ZStr::ToUpper(void)
{
   for(size_t sz = 0 ; sz < Length(); sz++)
         (*this)[sz] = toupper((*this)[sz]);
}


void ZStr::ToUpLow(void)
{
   ToLower();
   int next_up = 1;
   for(size_t sz = 0 ; sz < Length(); sz++)
      {
      if(next_up)
         {
         next_up = 0;
         (*this)[sz] = toupper((*this)[sz]);  // not going to hurt whitespace (etc)
         }
      if(IsWhite((*this)[sz]) == true)
         next_up = 1;
      if((*this)[sz] == '-')  // hypenation counts in most titles
         next_up = 1;
      }
}


void ZStr::ToLower(void)
{
   for(size_t sz = 0 ; sz < Length(); sz++)
         (*this)[sz] = ::tolower((*this)[sz]);
}


bool ZStr::IsAlnum(size_t pos) const
{
   if(pos > Length())
      return false;
   //if(pos < 0)
   //   return false;
   char ch = (*this)[pos];
	return ( (isalnum( ch )) ? true : false );
}


bool ZStr::IsAlpha(size_t pos) const
{
   if(pos > Length())
      return false;
   //if(pos < 0)
   //   return false;
   char ch = (*this)[pos];
   bool br = (isalpha( ch )) ? true : false;
	return ( br );
}


bool ZStr::IsWhite(char ch) const
{
   /*
   // The result of the test condition for the iscntrl() function depends on the LC_CTYPE 
   // category setting of the current locale; see setlocale for more information;
   return ( ::iscntrl( ch ) );
   */
   // 03/10/2001: THIS IS OUR DEFINITION, AS PER OUR MkWhite();
   if(ch <= ' ')// 0x20
      return true;
   if(ch > '~') // 0x7E
      return true;
   return false;
}


bool ZStr::IsWhite(size_t pos) const
{
   if(pos >= Length())
      return false;
   //if(pos < 0)
   //   return false;
   return IsWhite((*this)[pos]);
}


bool ZStr::IsWhite(void) const
{
for(size_t ss = NULL; ss < Length(); ss++)
   {
   if(!IsWhite((*this)[ss]))
      return false;
   }
return true;
}


bool ZStr::IsNull(void) const
{
   if(!Length())
         return true;
   char ch = (*this)[0];
   if(ch)
         return false;
   return true;
}


istream& ZStr::ReadToDelim(istream& is, char delim)
{
   return Readline(is, delim);
}


istream& ZStr::ReadLine(istream& is, char delim)
{
   return Readline(is, delim);
}


istream& ZStr::ReadString(istream& is, char delim)
{
   return Readline(is, delim);
}


int ZStr::Strip(StripType st, char ch)
{
int res = 0;
switch(st)
   {
   case Leading:
      res = Able1::Strip(*this, ch);
   break;
   case Trailing:
      res = Clip(*this, ch);
   break;
   case Both:
      res = Clip(*this, ch);
      res += Able1::Strip(*this, ch);
   break;
   }
return res;
}


bool ZStr::IsSpace(void) const
{
for(size_t ss = NULL; ss < Length(); ss++)
   {
   if(!isspace((*this)[ss]))
      return false;
   }
return true;
}


size_t ZStr::SeekBinary(int SkipControlChars) const
{
for(size_t ss = NULL; ss < Length(); ss++)
   {
   char ch = (*this)[ss];
   if(ch > 0x7F)
      return ss;
   if(ch < ' ')
      {
      if(SkipControlChars)
         {
         switch((*this)[ss])
            {
            case '\n':
            case '\t':
            case '\r':
            case '\v':
               continue;
            default:
               return ss;
            }
         }
      else
         return ss;
      }
   }
return NPOS;
}


bool ZStr::IsAscii(void) const
{
for(size_t ss = NULL; ss < Length(); ss++)
   {
   char ch = (*this)[ss];
   if(ch > 0x7F)     // 127d
      return false;
   if(ch < 0x00)     // signed / unsigned (portability)
      return false;
   }
return true;
}


bool ZStr::MkWhite(void)
{
bool res = false;
for(size_t ss = NULL; ss < Length(); ss++)
   {
   if(IsWhite((*this)[ss]))
      {
      // Inforce the normalized definition of what a white-space character is;
      (*this)[ss] = ' ';
      res = true;
      }
   }
return res;   
}


int ZStr::Snip(char ch)
{
   size_t pos     = Find(ch);
   if(pos != npos)
         {
         RemovePos(0, pos);
         while((*this)[0] == ch)
            RemovePos(0,1);
         return 1;
         }
   return 0;
}


ostream& ZStr::Write(ostream& ofs) const
{
   // NOTE: If the stream is !binary, the newlines will expand on Wintel!
   ofs << psz_alloc;
   return ofs;
}


istream& ZStr::Read(istream& is, size_t whence)
{
   if(is)
      {
      char *pbuf = new char[whence+1];
      ::memset(pbuf, (int)whence, 0);    // might get less!
      is.read(pbuf, (int)whence);
      pbuf[whence] = NULL;          // REDUNDANT
      if(!is)
         pbuf[0] = NULL;
      Assign(pbuf);
      delete [] pbuf;
      }
   else
      Assign("");
   return is;
}


istream& ZStr::Read(istream& is)
{
   if(is)                              // 7/16/2001, R. Nagy
      {
      char *pbuf = new char[max_read];
      is >> pbuf;                      // 7/16/2001, R. Nagy [BUGFIX]!
      if(!is)
         pbuf[0] = NULL;
      Assign(pbuf);
      delete [] pbuf;
      }
   else
      Assign("");
   return is;
}


ZStr& ZStr::operator=(int i)
{
char buf[100];
sprintf(buf, "%d", i);
*this = buf;
return *this;
}


int ZStr::AsInt(void) const
{
return ::atoi(c_str());
}


long ZStr::AsLong(void) const
{
return (long)::atol(c_str());
}


ostream& ZStr::WriteStream(ostream& ofs) const
{
   // NOTE: If the stream is !binary, the newlines will expand on Wintel!
   ofs << Length() << " ";
   if(IsNull() == false)
      ofs << psz_alloc;
   return ofs;
}


istream& ZStr::ReadStream(istream& is)
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

      delete [] psz_alloc;
      sz_alloc = sz2;      // exact length
      sz2 = sz_alloc + extra_bytes  + sizeof(NULL);
      psz_alloc = new char[sz2];
      is.read(psz_alloc, sz_alloc);
      psz_alloc[sz_alloc] = NULL;
      sz_alloc = sz2;      // grow length
      }
   else
      {
   rd_abort:
      Assign("");
      }
   return is;
}


ostream& ZStr::WriteString(ostream& ofs) const
{
   // Binary compatability with borland -almost (imbedded NULL would mess us READ up!)
   // Borland code DOES insure that termination is a NULL on WRITE (I checked their READ RTL code).
   // Problem might be with write_string: could legacally-have an imbedded NULL, but
   // not sure how Borland handled the conversion of imbedded NULLs (if at all)! 
   // MY legacy stuff did not do imbed NULLS ('cept for crypto string), so this will do for now;
   ofs.write(psz_alloc, Length());
   char sends = NULL;
   ofs.write(&sends, 1);      
   return ofs;
}

ZStr ZStr::GetToken(const ZStr& sTok) const
{
ZStr sResult;
size_t sz = Find(sTok);
if(sz != npos)
   {
   char *pszF = &(*this)[sz];
   char *pszL = &(*this)[sz];

   if(isspace(*pszF))
      {
      sResult = *pszF;
      return sResult;
      }

   while((pszF >= psz_alloc) && !isspace(*pszF))
      pszF--;
   while(*pszL && !isspace(*pszL))
      pszL++;

   if(pszF != psz_alloc)
      pszF++;

   char ch = *pszL;
   *pszL   = NULL;
   sResult = pszF;
   *pszL   = ch;
   }
return sResult;
}


ZStr ZStr::RemoveToken(const ZStr& pattern) const
{
   ZStr sResult = *this;
   size_t ssHit = sResult.Find(pattern, NULL);
   while(ssHit != NPOS)
      {
      sResult.RemovePos(ssHit, ssHit + pattern.Length());
      ssHit = sResult.Find(pattern, ssHit+1);
      }
   return sResult;      
}

ZStr&   ZStr::Remove(const ZStr& str) 
{
   Assign(RemoveToken(str));
   return *this;
}

istream& ZStr::ReadToken(istream& is)
{
   char *psz = new char[A1_MAX_TOKEN];    // a large buffer!
   is >> psz;
   Assign(psz);
   delete [] psz;
   return is;
}


istream& ZStr::Readline(istream& is, const ZStr& delim)
{
*this = ZStr();

size_t sPos = 0L;
stringstream srm;
bool bHitting = false;
char ch = 0;
while(is)
   {
   is.read(&ch, 1);
   if(!is)
      continue;
   if(ch == delim[sPos])
      {
      sPos++;
      bHitting = true;
      if(sPos == delim.Length())
         {
         // Found -
         Assign(srm.str().c_str());
         return is;
         }
      continue;
      }
   if(bHitting)
      {
      bHitting = false;
      srm << delim.Subpos(0, sPos);
      sPos = 0L;
      }
   srm << ch;
   }
Assign(srm.str().c_str());    // Assign whatever we found -
return is;
}

istream& ZStr::Readline(istream& is, char delim)
{
// The better part of valor: I'd rather do it myself
// than trust to the compiler's auto type conversion -
ZStr str;
str.Assign(delim);
return Readline(is, str);
}


ZStr ZStr::Enumerate(char ch)
   {
   ZStr sResult;
   size_t whence = Find(ch);
   if(whence == npos)
      {
      sResult = c_str();
      Assign("");
      }
   else
      {
      sResult = Substr(0, whence);
      RemovePos(0, whence+1);
      }
   return sResult;
   }


int ZStr::RemovePattern(const ZStr& pattern, int ignore_case)
   {
   size_t numHits = NULL;
   size_t ssHit   = Find(pattern, NULL, ignore_case);
   while(ssHit != NPOS)
      {
      numHits++;
      RemovePos(ssHit, ssHit + pattern.Length());
      ssHit = Find(pattern.c_str(), ssHit, ignore_case);
      }
   return numHits;
   }


int ZStr::Replace(const ZStr& pattern, const ZStr& replace, int ignore_case)
   {
   int numHits = NULL;
   size_t ssHit   = Find(pattern, 0, ignore_case);
   while(ssHit != NPOS)
      {
      numHits++;

      RemovePos(ssHit, ssHit + pattern.Length());
      Insert(ssHit, replace.c_str());

      ssHit = Find(pattern.c_str(), ssHit + replace.Length(), ignore_case);
      }
   return numHits;
   }


size_t ZStr::Find(char ch, size_t pos, int ignore_case) const
{
   if(pos >= ::strlen(psz_alloc))
      return npos;
   if(pos == npos)
      pos = 0L;
   if(pos > ::strlen(psz_alloc))
      return npos;

   char *psz = ci_strchr(&psz_alloc[pos], ch, ignore_case);
   if(psz)
      {
      char h = *psz;
      *psz = NULL;
      // Offset index is relative to the ENTIRE ZStr;
      size_t offs = ::strlen(psz_alloc);
      *psz = h;
      return offs;
      }
   return npos;
}


size_t ZStr::Rfind(char ch, size_t pos, int ignore_case) const
{
   strrev(psz_alloc);
   size_t res = Find(ch, pos, ignore_case);
   strrev(psz_alloc);
   if(res == npos)
      return res;
   return (Length() - res -1);
}


size_t ZStr::FindAny(const ZStr& str, size_t pos) const
{
return (Find(str, pos, 1));
}


size_t ZStr::RfindAny(const ZStr& str, size_t pos) const
{
return (Rfind(str, pos, 1));
}


size_t ZStr::FindAny(char ch, size_t pos) const
{
return (Find(ch, pos, 1));
}


size_t ZStr::RfindAny(char ch, size_t pos) const
{
return (Rfind(ch, pos, 1));
}


size_t ZStr::Find(const char *pch, size_t pos, int ignore_case) const
{
   if(pos >= ::strlen(psz_alloc))
      return npos;
   if(pos == npos)
      pos = 0L;

   char *psz = ci_strstr(&psz_alloc[pos], pch, ignore_case);
   if(psz)
      {
      char h = *psz;
      *psz = NULL;
      // Offset index is relative to the ENTIRE ZStr;
      size_t offs = ::strlen(psz_alloc);
      *psz = h;
      return offs;
      }
   return npos;
}


size_t ZStr::FindLast(char ch, size_t pos, int ignore_case) const
{
ZStr sz = ch;
return FindLast(sz.c_str(), pos, ignore_case);
}

size_t ZStr::FindLast(const char *pch, size_t pos, int ignore_case) const
{
size_t ssRes = Find(pch, pos, ignore_case);
if(ssRes == NPOS)
   return ssRes;
while(1)
   {
   size_t ss = Find(pch, ssRes+1, ignore_case);
   if(ss == NPOS)
      break;
   ssRes = ss;
   }
return ssRes;
}

bool ZStr::EndsWith(const ZStr& sToken) const
{
size_t pos = Rfind(sToken);
if(pos == npos)
   return false;
if(pos == Length() - sToken.Length())
   return true;
return false;
}


size_t ZStr::Rfind(const char *pch, size_t pos, int ignore_case) const
{
ZStr str = c_str();
str.Reverse();
ZStr spat = pch;
spat.Reverse();
size_t whence = str.Find(spat, ignore_case);
if(whence == npos)
   return whence;
return (Length() - spat.Length() - whence);
}


size_t ZStr::Find(const ZStr& pch, size_t pos, int ignore_case) const
{
   return Find(pch.c_str(), pos, ignore_case);
}


size_t ZStr::Rfind(const ZStr& pch, size_t pos, int ignore_case) const
{
   return Rfind(pch.c_str(), pos, ignore_case);
}


const char *ZStr::Substr(ZStr& str, size_t start) const
{
   size_t max = Length();
   if(start >= max)
         str = "";
   else
         str = &operator[](start);
   return str.c_str();
}


const char *ZStr::CopyBytes(ZStr& sRes, size_t start, size_t end) const
{
   size_t max = ::strlen(psz_alloc);
   if(start >= max)
         sRes = "";
   else
         {
         sRes = &operator[](start);
         if((start + end) < max)
            sRes.Remove(end);
         }
   return sRes.c_str();
}


const char *ZStr::CopyPos(ZStr& str, size_t start, size_t end) const
{
   size_t max = ::strlen(psz_alloc);
   if(start >= max)
         str = "";
   else
         {
         str = &operator[](start);
         if(end < max)
            str.Remove((int)abs(long(end - start)));
         }
   return str.c_str();
}


void ZStr::Insert(size_t ss, const ZStr& str)
{
Insert(ss, str.c_str());
}


void ZStr::Insert(size_t ss, const char *psz)
{
// usage:: If you insert something at 0, then you'll have a new 0!
   ZStr tmp;
   Substr(tmp, ss);
   Remove(ss);
   Append(psz);
   Append(tmp.c_str());
}


char *ZStr::strrev(char *psz) const 
{
if(*psz)
   {
   size_t len = ::strlen(psz);
   char *psz1 = psz;
   char *psz2 = &psz[len-1];

   char ch;
   len /= 2;      // No need to swap the "odd man out" (think about it!)
   while(len)
      {
      ch = *psz1;
      *psz1 = *psz2;
      *psz2 = ch;
      psz1++; psz2--;
      len--;
      }
   }
return psz;
}


char *ZStr::ci_strstr(const char *str1, const char *str2, int ignore_case) const
   {
   char *cp = (char *) str1;
   char *s1, *s2;
   char mklow = 'A' - 'a';

   if ( !*str2 )
      return NULL;

   while (*cp)
      {
      s1 = cp;
      s2 = (char *) str2;

      if(ignore_case)
         {
         char ch1, ch2;
         while ( *s1 && *s2)
            {
            ch1 = *s1;
            ch2 = *s2;
            if(ch1 >= 'A' && ch1 <= 'Z')
               ch1 -= mklow;
            if(ch2 >= 'A' && ch2 <= 'Z')
               ch2 -= mklow;
            if((ch1-ch2))
               break;
            s1++, s2++;
            }
         }
      else
         {
         while ( *s1 && *s2 && !(*s1-*s2) )
            s1++, s2++;
         }

      if (!*s2)
         return cp;

      cp++;
      }
     return NULL;
   }


int ZStr::ci_strcmp(const char *str1, const char *str2, int ignore_case) const
   {
   char mklow = 'A' - 'a';
   char ch1, ch2;
   int ret = NULL;

   if((!(*str1)) && (!(*str2)))
        return ret;
   if(!(*str1))
        return 1;
   if(!(*str2))
        return -1;

   while(*str1 && *str2)
      {
      ch1 = *str1;
      ch2 = *str2;
      if(ignore_case)
         {
         if(ch1 >= 'A' && ch1 <= 'Z')
            ch1 -= mklow;
         if(ch2 >= 'A' && ch2 <= 'Z')
            ch2 -= mklow;
         }
      ret =  ch1 - ch2;
      if(ret)
         break;
      
      ++str1;
      ++str2;
      }
   if(!ret)
      {
      // This keeps "fl.jobs" from equaling "fl.jobs.www" (and vice versa);
      if(*str1)
        return -1;
      if(*str2)
        return 1;
      }
   if (ret < 0)
      ret = -1 ;
   else if (ret > 0)
      ret = 1;
   return ret;
   }


char *ZStr::ci_strchr(const char *str1, char ch, int ignore_case) const
   {
   char mklow = 'A' - 'a';
   char ch2   = ch;
   if(ignore_case)
      {
      if(ch2 >= 'A' && ch2 <= 'Z')
         ch2 -= mklow;
      }
   while(*str1)
      {
      char ch1 = *str1;
      if(ignore_case)
         {
         if(ch1 >= 'A' && ch1 <= 'Z')
            ch1 -= mklow;
         }
      if(ch1 == ch2)
         return ((char *)str1);
      str1++;
      }
   return NULL;
   }


bool ZStr::Split(const ZStr& ch, Array<ZStr>& array) const
   {
   array.Empty();
   PipeArray::Parse(array, *this, ch);
   if(array.Nelem())
      return true;
   return false;
   }


bool ZStr::Split(char ch, Array<ZStr>& array) const
   {
   array.Empty();
   PipeArray::Parse(array, *this, ch);
   if(array.Nelem())
      return true;
   return false;
   }
   

ZStr  ZStr::SetComma(int nelem)
   {
   ZStr str;
   str.Assign(nelem);
   return SetComma(str);
   }


ZStr  ZStr::SetComma(const ZStr& str)
   {
   ZStr sHold = str;
   sHold.Reverse();
   ZStr sResult;
   for(size_t ss = 0; ss < sHold.Length(); ss++)
      {
      if ((ss) && (!(ss % 3)))
         sResult.Append(',');
      sResult.Append((char)sHold[ss]);
      }
   sResult.Reverse();
   return sResult;
   }


size_t Able1::Strip(ZStr& str, char ch)
   {
   int sp = NULL;
   if(str.IsNull())
      return sp;
   while(str[sp] == ch)
         sp = sp + 1;
   if(sp)
         str.RemovePos(0, sp);
   return sp;
   }


size_t Able1::Clip(ZStr& str, char ch)
   {
   size_t sp      = str.Length();
   size_t count   = NULL;
   if(!sp)
      return count;
   while(str[sp-1] == ch)
      {
      count = count +1;
      if(!sp)
         {
         count = str.Length();
         str = "";
         return count;
         }
      sp = sp - 1;
      }
   if(count)
      str.RemovePos(sp, str.Length());
   return count;
   }


size_t Able1::Snip(const ZStr& str, ZStr& sLeft, ZStr& sRight, char ch)
   {
   ZStr sss = str;
   size_t sp = sss.Find(ch);
   if(sp != NPOS)
      {
      sLeft =  str.Substr(0, sp);
      sRight = str.Substr(sp+1, str.Length());
      }
   return sp;
   }


int Able1::Getline(istream& is, ZStr& str)
   {
   str.Readline(is);
   if(is.good())
         return 1;
   return 0;
   }

size_t Able1::Rfind(const ZStr& sSrc, const ZStr& sPat, int ignore_case)
{
ZStr str = sSrc;
str.Reverse();
ZStr spat = sPat;
spat.Reverse();
size_t whence = str.Find(spat, ignore_case);
if(whence == npos)
   return whence;
whence += spat.Length() - 1;
return (sSrc.Length() - whence - 1);
}



ZStr Able1::TagRemove(const ZStr& sSrc, char chOn, char chOff)
{
// Suitable for html and xml tag removal (only - no diacretic conversions!)
ZStr sResult;
bool bCopying = true;
char ch;
for(size_t ss = 0L; ss < sSrc.Length(); ss++)
   {
   ch = sSrc[ss];
   if(ch == chOn)
      {
      bCopying = false;
      continue;
      }
   if(ch == chOff)
      {
      bCopying = true;
      continue;
      }
   if(bCopying)
      sResult.Append(ch);  
   }
return sResult;
}



 
ZStr Able1::Common(const ZStr& sC, const ZStr& sD)  // Returns what to string have in common
{
ZStr sResult;
for(size_t xx = 0; xx < sD.Length(); xx++)
   {
   if(sC[xx] != sD[xx])
      break;
   sResult.Append(sC[xx]);
   }
return sResult;
}


ZStr Able1::RCommon(const ZStr& s1, const ZStr& s2) // Returns what the END of two strings have in common
{
   ZStr sA = s1;
   ZStr sB = s2;
   sA.Reverse();
   sB.Reverse();
   ZStr sC = Able1::Common(sA, sB);
   sC.Reverse();
   return sC;
}


void Able1::Clone(Array<ZStr>& array1, Array<StreamZStr>& array2)
{
   array2.Empty();
   array2.AddZombies(array1.Nelem());
   for(size_t ss = 0; ss < array1.Nelem(); ss++)
      array2.Append(array1[ss]);
}


void Able1::Clone(Array<StreamZStr>& array1, Array<ZStr>& array2)
{
   array2.Empty();
   array2.AddZombies(array1.Nelem());
   for(size_t ss = 0; ss < array1.Nelem(); ss++)
      array2.Append(array1[ss].c_str());
}

wstring Able1::Convert(const string& str)
   {
   int iBytes = str.length() + 4;
   wchar_t *pDuo = new wchar_t[iBytes + 1];
   ::memset((char *)pDuo, 0, sizeof(wchar_t) * iBytes);

   ::mbstowcs(pDuo, str.c_str(), str.length());

   wstring wstr = pDuo;
   delete[] pDuo;
   return wstr;
   }


string Able1::Convert(const wstring& wstr)
   {
   int iBytes = wstr.length() + 4;
   char *pDuo = new char[iBytes + 1];
   ::memset(pDuo, 0, iBytes);

   ::wcstombs(pDuo, wstr.c_str(), wstr.length());

   string str = pDuo;
   delete[] pDuo;
   return str;
   }
   
ZStr
Able1::operator + (const ZStr& str, const ZStr& cstr)
   {
   ZStr sResult = str;
   sResult.Append(cstr);
   return sResult;
   }


ZStr&
Able1::operator += (ZStr& str, const ZStr& cstr)
   {
   str.Append(cstr);
   return str;
   }

ZStr& Able1::operator >>(ZStr& str, size_t& sz)
   {
   sz = ::atoi(str.c_str());
   return str;
   }


ZStr& Able1::operator <<(ZStr& str, size_t sz)
   {
   char buf[120];
   ::sprintf(buf, "%d", (int)sz);
   str.Append(buf);
   return str;
   }


ZStr& Able1::operator <<(ZStr& str, const ZStr& str2)
   {
   str.Append(str2);
   return str;
   }


ZStr& Able1::operator <<(ZStr& str, const char *psz)
   {
   str.Append(psz);
   return str;
   }

istream& Able1::operator >> (istream& is, ZStr& ss)
   {
   ss.Read(is);
   return is;
   }


ostream& Able1::operator << (ostream& os, const ZStr& ss)
   {
   os << ss.c_str();
   return os;
   }

