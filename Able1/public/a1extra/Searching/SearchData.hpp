//---------------------------------------------------------------------------
#ifndef SearchDataH
#define SearchDataH
//---------------------------------------------------------------------------

#include <Able1.hpp>

// 09/23/2003: Ported to Able1, R. Nagy

using namespace Able1;

class SearchData
   {
   protected:
      int   type;
      ZStr sKeyString;
      bool bMustContain;

   public:
      SearchData(void);
      virtual ~SearchData(void);

      virtual void Reset(void);

      // These must Read and Write your data in such a manner as to allow their
      // user-discernable display / parsing in a standard WINDOWS control.
      virtual bool   ExportControlString(ZStr& std);
      virtual bool   ImportControlString(const ZStr& std);

      virtual bool   GetWords(Array<StreamZStr>&);

      bool MustContain(void)                 {return bMustContain;}
      bool MustNotContain(void)              {return !bMustContain;}

      void MustContain(bool b)               {bMustContain = b;}
      void MustNotContain(bool b)            {bMustContain = !b;}
   };

class EnhancedSearchData : public SearchData
   {
   protected:
      bool bOneOrMore;
      bool bWholeWordsOnly;
   public:
      EnhancedSearchData(void);
      virtual ~EnhancedSearchData(void);

      bool IsEnhancedSearch(void)      {if(type == 3) return true; return false;} 

      virtual void Reset(void);

      // These must Read and Write your data in such a manner as to allow their
      // user-discernable display / parsing in a standard WINDOWS control.
      virtual bool   ExportControlString(ZStr& std);
      virtual bool   ImportControlString(const ZStr& std);

      virtual bool   GetWords(Array<StreamZStr>&);
      virtual bool   PutWords(Array<StreamZStr>&);

      void           OneOrMore(bool b)       {bOneOrMore       = b;}
      bool           OneOrMore(void);
      bool           MustHaveAll(void)       {return (!bOneOrMore);}

      bool           WholeWordsOnly(void);
      void           WholeWordsOnly(bool b)  {bWholeWordsOnly  =  b;}
   };


#endif
