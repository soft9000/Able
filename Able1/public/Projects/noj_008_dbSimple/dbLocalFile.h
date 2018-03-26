#include "dbSimple.h"
#include <FastJob.hpp>
#include <noj/dfo.hpp>

using namespace FastJob;

#ifndef dbLocalFile_hpx_
#define dbLocalFile_hpx_

namespace dbSimple
   {

   template <class T>
   class dbLocalFile : public Database<T>
      {
      private:
         DFO<T> cache;

      protected:
         File pwFile;

      public:
         // As a factory
         Database<T> *Locate(const string& sName);
         bool      Commit(const string& sName, Database<T> *pdbLocalFile, bool bOverwrite = false);

         // Common operations
         bool     Append(vector<T>& aResults);

         record_t FindFirst(T& aResult);
         record_t FindNext(T& aResult, record_t);

         record_t Append(T& aRecord);
         record_t Update(T& aRecord, record_t);
         void     Delete(record_t);
         void     Delete(void);

         record_t Nelem(void);
      };

template <class T>
bool dbLocalFile<T>::Append(vector<T>& vec)
   {
   bool br = false;
   vector<T>::iterator it;
   for(it = vec.begin(); it < vec.end(); it++)
      {
      br = cache.Append(*it);
      if(br == false)
         return br;
      }
   return br;
   }

template <class T>
record_t dbLocalFile<T>::FindFirst(T& aResult)
   {
   record_t rec;
   if(cache.Nelem())
      {
      aResult = cache[0];
      return rec;
      }
   rec.bError = true;
   return rec;
   }

template <class T>
record_t dbLocalFile<T>::FindNext(T& aResult, record_t rec)
   {
   record_t rec2;
   rec2.luMinor = rec.luMinor;
   rec2.luMinor++;
   if(cache.Nelem() < rec2.luMinor)
      {
      aResult = cache[rec2.luMinor];
      return rec2;
      }
   rec.bError = true;
   return rec;
   }

template <class T>
record_t dbLocalFile<T>::Append(T& aRecord)
   {
   record_t rec;
   if(cache.Append(aRecord) == true)
      return rec;
   rec.bError = true;
   return rec;
   }

template <class T>
record_t dbLocalFile<T>::Update(T& aRecord, record_t rec)
   {
   record_t rec2;
   if(cache.Update(aRecord, rec.luMinor) == true)
      return rec;
   rec2.bError = true;
   return rec2;
   }

// As a factory
template <class T>
Database<T> *dbLocalFile<T>::Locate(const string& sName)
   {
   dbLocalFile *pDb = new dbLocalFile();
   if(pDb->cache.Load(sName.c_str()) == true)
      {
      if(pDb->pwFile.Name(sName.c_str()) == true)
         return pDb;
      }
   delete pDb;
   return 0L;
   }

template <class T>
bool dbLocalFile<T>::Commit(const string& sName, Database<T> *pdbLocalFile, bool bOverwrite)
   {
   bool br = cache.SaveAs(sName.c_str());
   if(br == true)
      br = pwFile.Name(sName.c_str());
   return br;
   }

template <class T>
void dbLocalFile<T>::Delete(record_t rec)
   {
   cache.Delete(rec.luMinor);
   }

template <class T>
void dbLocalFile<T>::Delete(void)
   {
   cache.Empty();
   }

template <class T>
record_t dbLocalFile<T>::Nelem(void)
   {
   record_t rec;
   rec.luMinor = cache.Nelem();
   return rec;
   }

}

#endif
