// These classes are used to quickly find multiple keys in a ascii-z text.
//
// Classes created 12/28/1998, R. Nagy
// 10/16/1999: Added capability to search binary-buffers, R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
// 01/08/2006: Major bugs removed, R. Nagy
//
#ifndef zHyperTexthj_Hpp
#define zHyperTexthj_Hpp

#include <Able1.hpp>

using namespace Able1;

class BabyBool : public ZStr
{
   public:
      enum SearchType {NONE, AND, OR, NOT, ALL};
   private:
      int         st;
      bool        found;
   public:
      BabyBool(void) : st(NONE), found(false){}
      virtual ~BabyBool(void)                {}

      void        SetType(SearchType stt)    {st = stt;}
      SearchType  QueryType(void)            {return (SearchType)st;}
      const char *QueryPhrase(SearchType);
      const char *QueryPhrase(void)          {return QueryPhrase((SearchType)st);}

      virtual bool         Create(SearchType st, const char *pRawData, bool bFound = false);
      virtual bool         Assign(const ZStr& sQueryFormat);
      virtual const char * Query(ZStr& sResult);

      bool                 Found(void)                   {return found;}
      void                 Found(bool b)                 {found = b;}

      BabyBool&   operator=(const ZStr& str)        {Assign(str.c_str()); return *this;}
      BabyBool&   operator=(const BabyBool& str)         {if(this == &str) return *this; Create((SearchType)str.st, str.c_str(), str.found); return *this;}


      ostream& Write(ostream& os);
      istream& Read(istream& is);
};


class HyperTextKey01
{
private:
   ZStr   key;
   int    tok;

public:
   HyperTextKey01(void) : tok(NULL)          {}
   HyperTextKey01(const HyperTextKey01& hk)  {*this = hk;}
   virtual ~HyperTextKey01(void)             {}

   void              Assign(const ZStr& sss, int token)  {key = sss; tok = token;}
   const char *      c_str(void)                         {return key.c_str();}
   int               Token(void)                         {return tok;}

   bool              IsKeyAt(const ZStr& str);

   HyperTextKey01&   operator=(const HyperTextKey01& hk) {if(this == &hk) return *this; key = hk.key; tok = hk.tok; return *this;}
   int               operator==(const HyperTextKey01& hk){return (key == hk.key);}

   ostream&          Write(ostream& os)                  {key.Write(os); os.write((char *)&tok, sizeof(int)); return os;}
   istream&          Read(istream& os)                   {key.Read(os);  os.read((char *)&tok, sizeof(int)); return os;}
};


class HyperTextSearch01
{
private:
   ZStr   sSaveBuffer;
   size_t      ssWip;

protected:
   Array<HyperTextKey01>  aKeys;

   int         NextKey(void);

public:
   HyperTextSearch01(void);
   virtual ~HyperTextSearch01(void);

   bool        AddKey(const ZStr& sKey, int token);
   const char *GetKey(ZStr& str, int token);

   int         FindKey(const ZStr& sBuffer);
   int         FindNextKey(void);
};
#endif

