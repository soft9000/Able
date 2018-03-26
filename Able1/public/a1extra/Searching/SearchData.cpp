//---------------------------------------------------------------------------
#ifdef BORLAND_C
#include <vcl.h>
#pragma package(smart_init)
#else
#include <windows.h>
#endif

#pragma hdrstop

#include "searchdata.hpp"

//---------------------------------------------------------------------------


SearchData::SearchData(void)
   {
   Reset();
   }
SearchData::~SearchData(void)
   {
   }
void SearchData::Reset(void)
   {
   type              = 0; 
   sKeyString        = "";
   bMustContain      = false;
   }

bool SearchData::ExportControlString(ZStr& std)
   {
   if(sKeyString.IsNull())
      return false;
   std = sKeyString;
   return true;
   }
bool SearchData::ImportControlString(const ZStr& std)
   {
   bool br = false;

   ZStr std2 = std;
   size_t whence = std2.Find('>');
   if(whence == NPOS)
      {
      type = 1;
      sKeyString = std;
      return true;
      }

   type = 1;
   std2[whence] = NULL;
   if(std2.Find(" not ") == NPOS)
      MustContain(true);
   else
      MustContain(false);

   sKeyString = std;
   return true;
   }


EnhancedSearchData::EnhancedSearchData(void)
   {
   Reset();
   }
EnhancedSearchData::~EnhancedSearchData(void)
   {
   }
bool SearchData::GetWords(Array<StreamZStr>& aWords)
   {
   aWords.Free();
   if(sKeyString.IsNull())
      return false;
      
   size_t whence = sKeyString.Find('>');
   if(whence != NPOS)
      {
      // NOTE THAT WE ADD 2 TO SKIP BOTH THE TOKEN AND THE TRAILING SPACE!
      aWords[aWords.Nelem()] = &sKeyString[whence+2];
      return true;
      }

   aWords[aWords.Nelem()] = sKeyString.c_str();
   return true;
   }
bool EnhancedSearchData::PutWords(Array<StreamZStr>& aWords)
   {
   bool br = true;
   stringstream srm;

   // *****
   // First, we give the user something to Read;
   srm << "ENHANCE(";
   for(size_t ss = NULL; ss < aWords.Nelem(); ss++)
      {
      if(ss)
         srm << ", ";
      srm << aWords[ss].c_str();
      }

   // *****
   // Now here is the stuff that WE Read;
   srm << ")                             \t";
   aWords.Write(srm);

   // STORE a unique (non GUI) "seek to" marker;
   srm << '\v';
   // This a bninary choice, so lets us a "grep-able" character;;
   if(bOneOrMore)
      srm << '+';
   else
      srm << '-';

   // This a bninary choice, so lets use a "grep-able" character;;
   if(bWholeWordsOnly)
      srm << '+';
   else
      srm << '-';

   srm << ends;
   sKeyString = PRESTO(srm).c_str();
   
   return br;
   }
bool EnhancedSearchData::GetWords(Array<StreamZStr>& aWords)
   {
   bool br = false;
   aWords.Free();
   size_t where = sKeyString.Find('\t');
   if(where == NPOS)
      return SearchData::GetWords(aWords);
   stringstream srm;
   srm << &(sKeyString[where +1]);
   srm << ends;
   srm.seekg(0, ios::beg);
   aWords.Read(srm);
   if(aWords.Nelem())
      br = true;
   return br;
   }
bool EnhancedSearchData::ImportControlString(const ZStr& std)
   {
   Reset();
   if(SearchData::ImportControlString(std) == false)
      return false;

   size_t where = sKeyString.Find('\v');
   if(where != NPOS)
      {
      type = 3;
      if(std[where+1] == '+')
         OneOrMore(true);
      else
         OneOrMore(false);

      if(std[where+2] == '+')
         WholeWordsOnly(true);
      else
         WholeWordsOnly(false);
      }
   return true;
   }
void EnhancedSearchData::Reset(void)
   {
   SearchData::Reset();
   bOneOrMore        = true;
   bWholeWordsOnly   = false;
   }
bool EnhancedSearchData::OneOrMore(void)
   {
   return bOneOrMore;
   }
bool EnhancedSearchData::WholeWordsOnly(void)
   {
   return bWholeWordsOnly;
   }
bool EnhancedSearchData::ExportControlString(ZStr& std)
   {
   return SearchData::ExportControlString(std);
   }
