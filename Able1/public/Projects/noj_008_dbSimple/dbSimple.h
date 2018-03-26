// The dbSimple namespace
// ------------
// Since before my days as a principal engineer at large database companies, I have
// studied the problems of database access. From ISAM to CORBA, and from secured 
// high-transactional databases to ODBC. I have learned from many patterns, technologies,
// and usage paradigms,
//
// After years of trying to simplify "it all" down to an elegant and portable way to
// access the data types that most of us need to use, I have come to the conclusion
// that just a few conventions are required. I created this namespace to demonstrate
// both the simple paradigm, and nomenclarue, that most people will need to use
// to store just about everything that most people want to - even if they have to
// rely upon a few oddities as MIME or BASE64 to do things like convert BLOB's to strings - 
// 
// Randally Nagy
//
// kayak@soft9000.com
//
// NOTES
// =====
// In classic "CRUD" database operations (cREATE, rEAD, uPDATE, dELETE), the "C" can be problematic. 
// For maximum portability (and to keep form having empty records accumulate between 
// abnormally terminated sessions), it is usually better to use "Append".
// 
// rEAD is also archaic - More often than not, today data users want to "enumerate" through
// both databases, and data *sets*.
//
// For maximum portaility across as many technologies as possible, the design of any generic
// database encapsulation needs to concentrate on a different paradigm than most of us have
// learned to utilize. In short:
//
//  CLASSIC       PORTABLE
//  =======       ========
//             -> LOCATE
//  CREATE     -> APPEND
//  READ       -> ENUMERATE
//  UPDATE     -> UPDATE
//  DELETE     -> DELETE
//             -> SEARCH
//             -> COMMIT
//
// CRUD        => LA-EDU-SC 
//                (Memonic use only...)
//                (Nothing to do with educational institutions in Los Langeles or South Carolina...:)
//
// You might be tempted to ask the database for the number of records that it has -
// From a portable abstraction point of view, that is a bad idea here - best to leave that for 
// the implementation. Why? Because depending upon the technology that you are using, 
// the record tallying operation can cost a lot!
// 
// If you absolutely *have* to know the number of records in a database/set, then 
// either (1) construct a special query operation to do it via SizeableDatabase - or (less idealy)
// (2) implement the interface using FindFirst / FindNext (that is always a portable operational 
// paradigm!)
//

#ifndef dbSimple_hpx_
#define dbSimple_hpx_

#include <string>
#include <vector>

using namespace std;

// 03/27/2005 - Namespace Created, R. Nagy
//
//

namespace dbSimple {

   struct record_t
      {
      bool bError;
      long unsigned luMajor;
      long unsigned luMinor;

      record_t(void) : bError(false), luMajor(0L), luMinor(0L)
         {
         }
      };

   struct Field
      {
      string sNameTag;  // This is not efficient - but it is succinct & easier to understand - (GUI, etc)
      string sValue;    // This, of course, is required

      virtual  const char *c_str(void) const
         {
         return sValue.c_str();
         }
      virtual  const char *name(void) const
         {
         return sNameTag.c_str();
         }
      };

   class Record
      {
      public:
         vector<Field> aFields;
      };

   template <class T>
   class Database
      {
      public:
         // As a factory
         virtual  Database<T> *Locate(const string& sName) = 0;
         virtual  bool      Commit(const string& sName, Database<T> *pDatabase, bool bOverwrite = false) = 0;

         // Common operations
         virtual  bool     Append(vector<T>& aResults) = 0;

         virtual  record_t FindFirst(T& aResult) = 0;
         virtual  record_t FindNext(T& aResult, record_t) = 0;

         virtual  record_t Append(T& aRecord) = 0;
         virtual  record_t Update(T& aRecord, record_t) = 0;
         virtual  void     Delete(record_t) = 0;
         virtual  void     Delete(void) = 0;                         // empty the database / dataset

      };

   struct SimpleQuery
      {
         enum Set
            {
            Include,
            Exclude
            } venn_op;

         string sPattern;  // Yes, this could be an SQL operation ...
      };

   template <class T>
   class SearchableDatabase : public Database<T>
      {
      public:
         // As a result set
         virtual  Database<T> *Locate(const vector<SimpleQuery>& qIn) = 0;
         virtual  bool      Commit(const string& sName,  bool bOverwrite = false) = 0;

         virtual  record_t FindFirst(const SimpleQuery& qIn, T& aResult) = 0;
         virtual  record_t FindNext(const SimpleQuery& qIn, T& aResult, record_t) = 0;
      };

   template <class T>
   class SizeableDatabase : public SearchableDatabase<T>
      {
      public:
         virtual record_t Size(void) = 0;
      };

}

#endif
