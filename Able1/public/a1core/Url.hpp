//
// Note: Url is a partial implementation of rfc1738 - Just what I needed, 
// as I needed it. When fully implemented, it will become stdnet::URL.
//
// Targeted syntax is "protocol://<user>:<password>@<host>:<port>/<url-path>"

//
// 08/21/2004: Started, R. Nagy
//
#ifndef xzUrl_Hpp
#define xzUrl_Hpp


namespace Able1
   {
   enum UrlType
      {
      url_none,
      url_http,
      url_https,
      url_ftp,
      url_file
      };
/** Url is a ShareableObject that has the ability to differentiate a URL from
  * another node type in the namespace.
  */
   class Url : public ShareableObject
      {
      private:
         UrlType   uType;
         ZStr sUrl;

      public:
         Url(void);

         UrlType   Type(void) const {return uType;}

         ZStr Site(void) const;
         ZStr Page(void) const;

         bool      Name(const ZStr& str);
         bool      Name(const File& file);
         bool      Name(const Directory& dir);

         ZStr Name(void) const {ZStr s = sUrl; return s;}

         bool        FromString(const ZStr& str);
         const char *ToString(ZStr& str) const;

         ostream& Write(ostream& os) const
            {
            ZStr str;
            ToString(str);
            str.WriteStream(os);
            return os;
            }
         istream& Read(istream& is)
            {
            ZStr str;
            str.ReadStream(is);
            FromString(str);
            return is;
            }

         bool      Launch(void) const;
      };

inline
bool OpenURL(const ZStr& str)
   {
   Url url;
   if(url.Name(str) == false)
      return false;
   return url.Launch();
   }

 } // namespace Able1


#endif
