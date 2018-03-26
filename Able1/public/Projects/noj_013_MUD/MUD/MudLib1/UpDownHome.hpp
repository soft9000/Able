#ifndef UpDownHome_hpx
#define UpDownHome_hpx

#include <Able1.hpp>

using namespace Able1;

struct UpDownFile
   {
   public:
      ZStr sLastError;
      Url       remotePage;
      File      localFile;
   };

class UpDownHome
   {
   public:
      Directory dirLocal;

      UpDownHome(void);

      static bool AsLocal(const Url& url, const UpDownHome& ref, UpDownFile& fileResult);
   };

#endif
