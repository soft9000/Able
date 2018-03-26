#include <Able1.hpp>
using namespace Able1;

Url::Url(void) : uType(url_none)
   {
   }

bool Url::Name(const ZStr& sParam)
   {
   uType = url_none;

   ZStr str = sParam;
   size_t whence = str.Find(':');   // Is this right? Always??
   if(whence == npos)
      return false;
   ZStr sub = str.Substr(0, whence);
   sub.ToLower();
   sub.Strip();
   bool br = false;
   if(sub == "http")
      {
      br = true;
      uType = url_http;
      }
   if(sub == "https")
      {
      br = true;
      uType = url_https;
      }
   if(sub == "ftp")
      {
      br = true;
      uType = url_ftp;
      }
   if(sub == "file")
      {
      br = true;
      uType = url_file;
      }
   if(br == true)
      sUrl = sParam;
   return br;
   }
bool Url::Name(const File& file)
   {
   ZStr str = file.Name();
   str.Replace(PathChar(), '/'); // Is this right? Always??
   str.Prepend("file://");
   return Name(str);
   }
bool Url::Name(const Directory& dir)
   {
   ZStr str = dir.Name();
   str.Replace(PathChar(), '/');
   str.Prepend("file://");
   return Name(str);
   }

bool Url::FromString(const ZStr& str)
   {
   return Name(str);
   }

const char *Url::ToString(ZStr& str) const
   {
   str = Name();
   return str.c_str();
   }

ZStr Url::Site(void) const
   {
   ZStr sDelim = "://";
   ZStr str;
   if(uType == url_none)
      return str;
   str = Name();
   size_t pos = str.Find(sDelim);
   if(pos != npos)
      str.RemovePos(0, pos + sDelim.Length());
   pos = str.Find('/');
   if(pos != npos)
      str = str.Subpos(0, pos);
   return str;
   }

ZStr Url::Page(void) const
   {
   ZStr sDelim = "://";
   ZStr str;
   if(uType == url_none)
      return str;
   str = Name();
   size_t pos = str.Find(sDelim);
   if(pos != npos)
      str.RemovePos(0, pos + sDelim.Length());
   pos = str.Find('/');
   if(pos != npos)
      str.RemovePos(0, pos);
   return str;
   }


#ifdef UNIX
#include <a1core/os/unix/unix_Url.cpp>
#endif

#ifdef MSDOS
#include <a1core/os/msdos/msdos_Url.cpp>
#endif

#ifdef WIN32
#include <a1core/os/win32/win32_Url.cpp>
#endif


