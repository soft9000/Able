// 01/07/2007: Converted to Able1, R. Nagy
//

#ifndef HotSwap_Hpp
#define HotSwap_Hpp

#include <Able1.hpp>
using namespace Able1;

class HotSwap
{
private:
   size_t      _exec(const ZStr& str, const ZStr& sReplacement, ostream& os, bool swapit);
   size_t      _replace_all(ZStr& sBuffer, const ZStr& pattern, const ZStr& replacement);
   const char *_result_name(ZStr& str);
   const char *_old_name(ZStr& str);

protected:
   ZStr   sFileName;

   virtual void   EvFileName(const char *pszFileName);
   virtual void   EvDisplayError(const char *pszFileName, ostream& os);
   virtual bool   EvProgressMeter(size_t lines, ostream& os);
   virtual void   EvHit(const ZStr& sBuffer, size_t offset);
   virtual void   EvHitFixup(const ZStr& sBuffer, size_t offset);

   void           ResultClear(void);
   void           ResultSave(const ZStr& sBuffer);
   void           ResultAssertFinal(bool changed);

public:
   HotSwap(void);
   virtual ~HotSwap(void);

   bool        Open(const ZStr& pszFileName);
   const char *FileName(void);
   size_t      List(const ZStr& str, const ZStr& sReplacement, ostream& os);
   size_t      Exec(const ZStr& str, const ZStr& sReplacement, ostream& os);
};



#endif
