// 12/17/2003 Bugfix: Closed file in array after parsing. Stopped on 8 (file handle limit), R. Nagy

#ifndef _Http_Log_Db
#define _Http_Log_Db

#include <Server/HttpLogParser.Hpp>

enum QueryType
   {
   // Lits of others here, but we are woring on the "what is good for me"
   // principle as the aid to incremental development.
   qtCommandPatternMatch = 'a',
   qtUnknown             = 'z'
   };

struct DatabaseQuery
   {
   public:
      DatabaseQuery(void)
         {
         in.Reset();
         out.Reset();
         }
      struct dqInput
         {
         private:
            StdDateTime    sdtFilter;
            enum DateTimeFilter
               {
               dtBefore = '-',
               dtAfter  = '+',
               dtOn     = '=',
               dtNone   = '0'
               } dtFilter;
         public:
            bool bExclude1;
            bool bExclude2;
            bool bExclude3;
            bool bExclude4;
            bool bExclude5;
            QueryType qtRequest;
            ZStr sParameter;
            int       iLimit;    // 0 == "unlimited", other is a pre-allocation amount for the result array

            // Use to omit problem patterns (e.g. cmd.exe site hacking attempts)
            Array<ZStr> aExcludePatterns;

            // Limit results to data within a certain range (inclusive)
            void IncludeOn(StdDateTime& dt)     
               {
               sdtFilter = dt; 
               dtFilter = dtOn;
               }
            void IncludeBefore(StdDateTime& dt) 
               {
               sdtFilter = dt; 
               dtFilter = dtBefore;
               }
            void IncludeAfter(StdDateTime& dt)  
               {
               sdtFilter = dt; 
               dtFilter = dtAfter;
               }
            void Reset(void)
               {
               qtRequest   = qtUnknown;
               dtFilter    = dtNone;
               sParameter  = "";
               iLimit      = 100;
               bExclude1 = bExclude2 = bExclude3 = bExclude4 = bExclude5 = false;
               }
            bool ShouldInclude(const HttpLogEntry& log);

            ostream& Write(ostream& os);
            istream& Read(istream& is);

         } in;

      struct dqOutput
         {
         ZStr           sError;
         Array<HttpLogEntry> aResults;
         void Reset(void)
            {
            sError = "";
            aResults.Empty();
            }
         } out;
   };

class HttpLogDatabase
{
private:
   Array<HttpLog> aLogCache;  // If cache is populated, then it is used (exclusively)

protected:
   Directory dirData;
   ZStr mkPath(const ZStr& sNodeName);

public:
   HttpLogDatabase(void)  {}

   bool Use(Directory& dir);

   void Cache(void);       // Attempt to load all log files to reduce search time
   void DeCache(void);     // Unload all cached log files

   bool Query(DatabaseQuery&, bool bNormalize = true);
   bool AddQuery(HttpLog&, DatabaseQuery&);
   bool Query(HttpLogEntry& log, DatabaseQuery& dq, bool bShouldAddToResult = true);
   bool Query(DatabaseQuery& dq, Array<File>& aFiles, bool bNormalize);

   void Dir(Array<ZStr>& aLogs);

   bool Create(HttpLog&, const ZStr& sNodeName);
   bool Read(HttpLog&, const ZStr& sNodeName);
   bool Update(HttpLog&, const ZStr& sNodeName);
   void Delete(const ZStr& sNodeName);
};
#endif
