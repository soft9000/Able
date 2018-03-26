// Class EMailFilter: Allows filtering of its namesake for desirability. Originally
// written to "grep" rfc977 items (news) for HyperRfc.
//
// 01/16/1998: Classes EMailFilter and EMailAND written, R. Nagy.
// 01/17/1998: Added class EMailOR, R. Nagy
// 12/26/1998: Added EMailAndOrNotExtended, R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
//
#ifndef zEMailFiltre_Hpp
#define zEMailFiltre_Hpp

#include <Able1.hpp>

#include <obsolete/Server/Email.hpp>

#include <Extra/Searching/HyperText01.hpp>

#include <Extra/Searching/SearchData.hpp>

using namespace Able1;

class Proximity;

class Proximity
   {
   protected:
      size_t      which;
      long   sp;

   public:
      Proximity(void);

      void        Reset(void);

      bool        Found(void);
      long   At(void);

   friend class EMailFilter;
   };

   typedef long unsigned mail_t;

class EMailFilter
   {
   public:
      enum SearchRange
         {
         SEARCH_NEW,
         DEFAULT = SEARCH_NEW,
         GET_NEW,
         xSEARCH_ALL,   // used by News*NET2
         GET_ALL,
         SEARCH_RANGE,
         GET_RANGE,
         LOCAL_SEARCH,
         TOO_BIG
         };
   private:
      enum SearchRange eSearchRange;
      ZStr        sType;

   protected:
      mail_t   mtMaxArticles;
      bool     Contains(const ZStr&, EMail&, Proximity&);
      bool     Contains(const ZStr&, Proximity&, stringstream& srm);

   public:
      enum SearchType
         {
         st_DEFAULT,
         st_AND,
         st_OR,
         st_ANDORNOT,
         st_ANDORNOTEX
         };

      EMailFilter(void);
      EMailFilter(const EMailFilter& ef);
      virtual ~EMailFilter(void);

      virtual bool Assign(enum SearchRange sr)     {eSearchRange = sr; return true;}
      enum SearchRange  Range(void)  const         {return eSearchRange;}
      void EmailExtension(const ZStr& s)      {sType = s;}
      const char *EmailExtension(void)             {return sType.c_str();}

      mail_t MaxArticles(void)                     {return mtMaxArticles;}
      void   MaxArticles(mail_t ma)                {mtMaxArticles = ma;}

      virtual enum SearchType Type(void)           {return st_DEFAULT;}

      virtual bool Qualifies(EMail& em)            {return true;}

      virtual EMailFilter& operator=(const EMailFilter& ef);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };

// Used to see if EMail contains ALL of a series (logical AND);
class EMailAND : public EMailFilter
   {
   protected:
      Array<ZStr>   sAND;

   public:
      EMailAND(void);
      EMailAND(const EMailAND& ef);
      virtual ~EMailAND(void);

      virtual enum SearchType Type(void)                {return st_AND;}

      virtual void AND(const ZStr&);

      virtual bool Qualifies(EMail& em);

      virtual EMailAND& operator=(const EMailAND& ef);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };


// Used to see if EMail contains ONE of a series (logical OR);
class EMailOR : public EMailFilter
   {
   protected:
      Array<ZStr>   sOR;

   public:
      EMailOR(void);
      EMailOR(const EMailOR& ef);
      virtual ~EMailOR(void);

      virtual enum SearchType Type(void)                {return st_OR;}

      virtual void OR(const ZStr&);

      virtual bool Qualifies(EMail& em);

      virtual EMailOR& operator=(const EMailOR& ef);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };




class EMailAndOrNot : public EMailFilter
   {
   protected:
      Array<BabyBool>   aStrings;

   public:
      EMailAndOrNot(void);
      EMailAndOrNot(const EMailAndOrNot& ef);
      virtual ~EMailAndOrNot(void);

      virtual SearchType Type(void)                {return st_ANDORNOT;}

      // Returns false is string is not supported;
      virtual bool Assign(Array<ZStr>&);
      virtual bool Assign(ZStr&);

      virtual bool Qualifies(EMail& em);

      virtual EMailAndOrNot& operator=(const EMailAndOrNot&);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };
   


class SearchDataManager
   {
   private:
      bool        found;
      Array<bool> aHitResult;
      bool _and_check(void);

   protected:
      EnhancedSearchData eSearch;
      bool AppendYourTokens(HyperTextSearch01&, size_t offset_base);
      void MarkAsFound(size_t offset_base, size_t token);
      bool CanWeContinue(void);
      bool WillUserWantThisOne(void);

   public:
      SearchDataManager(void) : found(false)          {}
      virtual ~SearchDataManager(void)                {}

      virtual bool Assign(const char *psz);

   // "hit" storage areas;
      bool        Found(void)                {return found;}

      ostream& Write(ostream& os)            {return os;}
      istream& Read(istream& is)             {return is;}

   friend class EMailAndOrNotExtended;
   };

class EMailAndOrNotExtended : public EMailFilter
   {
   protected:
      Array<SearchDataManager>   aStrings;

   public:
      EMailAndOrNotExtended(void);
      EMailAndOrNotExtended(const EMailAndOrNotExtended& ef);
      virtual ~EMailAndOrNotExtended(void);

      // Returns false if string is not supported;
      virtual bool Assign(Array<ZStr>&);
      virtual bool Assign(ZStr&);
      virtual bool Assign(enum SearchRange sr)             {return EMailFilter::Assign(sr);}

      virtual SearchType Type(void)                {return st_ANDORNOTEX;}

      virtual bool Qualifies(EMail& em);

      virtual EMailAndOrNotExtended& operator=(const EMailAndOrNotExtended&);

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);
   };

#endif
