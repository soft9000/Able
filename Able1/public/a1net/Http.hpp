#ifndef stdHttp_hpp
#define stdHttp_hpp

#include <a1net.hpp>

namespace stdnet {

   class Http
   {
      protected:
         static bool   Connect(Socket& soc, const Url& url);
         static size_t Size(Socket& soc, const Url& url, size_t szDefault = SOC_BUFFER_SZ);

      public:
         struct HttpResponse
         {
            HttpResponse();
            int iCode;
            Array<ZStr> aHeaders;
            ZStr sResponse;
            bool Parse(const ZStr& sSocketString);
         };
         static size_t Size(const Url& url, size_t szDefault = SOC_BUFFER_SZ);
         static bool   Download(const Url& url, const File& file, size_t szDefault = SOC_BUFFER_SZ);
   };

}

#endif
