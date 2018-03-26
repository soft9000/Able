#include "HttpLogDatabase.hpp"


bool DatabaseQuery::dqInput::ShouldInclude(const HttpLogEntry& log)
   { 
    switch(qtRequest)
      {
      case qtCommandPatternMatch:
         break;
      case qtUnknown:
      default:
         return false;
      } 
   if(log.sRequest.Find(sParameter, 0, 1) != NPOS)
      {
      bool bInclude = true;
      if(dtFilter != dtNone)
         {
         StdDateTime sdt;
         log.QueryDate(sdt);
         switch(dtFilter)
            {
            case dtOn:
               if(sdtFilter.IsSameDate(sdt) == false)
                  bInclude = false;
            break;
            case dtBefore:
               if(sdt >= sdtFilter)
                  bInclude = false;
            break;
            case dtAfter:
               if(sdt <= sdtFilter)
                  bInclude = false;
            break;
            }
         }
      if(bInclude == false)
         return bInclude;  // single breakpoint
      for(size_t ss = 0L; ss < aExcludePatterns.Nelem(); ss++)
         {
         if(log.sRequest.Find(aExcludePatterns[ss]) != NPOS)
            return false;
         }
      char ch = log.sResultCode[0];
      if(ch == '1' && bExclude1)
         return false;
      if(ch == '2' && bExclude2)
         return false;
      if(ch == '3' && bExclude3)
         return false;
      if(ch == '4' && bExclude4)
         return false;
      if(ch == '5' && bExclude5)
         return false;

      // If you got this far, then all tests have passed
      return true;
      }
   return false;
   }
ostream& DatabaseQuery::dqInput::Write(ostream& os)
   {
   sParameter.Write(os);
   sdtFilter.Write(os);

   ZStr str;
   str.assign(iLimit);
   str.WriteStream(os);

   str = "------------------------------";
   str[0] = (char)dtFilter;
   str[1] = (char)qtRequest;
   str.WriteStream(os);
   Array<StreamZStr> arySpace; // The final frontier...
   arySpace.Write(os);
   return os;
   }
istream& DatabaseQuery::dqInput::Read(istream& is)
   {
   sParameter.Read(is);
   sdtFilter.Read(is);

   ZStr str;
   str.ReadStream(is);
   iLimit = str.AsInt();

   str.ReadStream(is);
   dtFilter = (DateTimeFilter)   str[0];
   qtRequest= (QueryType)        str[1];
   Array<StreamZStr> arySpace; // The final frontier...
   arySpace.Read(is);
   return is;
   }



bool HttpLogDatabase::Use(Directory& dir)
   {
   dirData = dir;
   dirData.Create();
   return dir.Exists();
   }
void HttpLogDatabase::Cache(void)
   {
   // <<<WIP>>> Still need to implement an internal cache load & use.
   }
void HttpLogDatabase::DeCache(void)
   {
   }
bool HttpLogDatabase::Query(DatabaseQuery& dq, bool bNormalize)
   {
   ZStr str;
   Array<File> aFiles;
   dirData.Query(aFiles);
   return Query(dq, aFiles, bNormalize);
   }

bool HttpLogDatabase::Query(DatabaseQuery& dq, Array<File>& aFiles, bool bNormalize)
   {
   dq.out.Reset();
   // Open each physical file & load the data.
   // Would b a good place to cache, but these can be huge.
   // Leave that decision to the user...
   File pwFile;
   for(size_t ss = 0L; ss < aFiles.Nelem(); ss++)
      {
      HttpLog log;
      pwFile = aFiles[ss];
      istream& is = pwFile.OpenRead(File::AT_BINARY);
      log.Read(is);
      if(!is)
         {
         dq.out.sError = "Error: Unable to open log file: ";
         dq.out.sError.Append(aFiles[ss].Name());
         return false;
         }
      if(bNormalize)
         log.Normalize();
      if(AddQuery(log, dq) == false)
         {
         // Error is posted by call
         return false;
         }
      pwFile.Close();     // 12/17/2003 Bugfix: Stopped on 8 (file handle limit), R. Nagy
      }
   return true;
   }
bool HttpLogDatabase::AddQuery(HttpLog& log, DatabaseQuery& dq)
   {
   // Scan the array for result size, first (massive performance improvement)
   size_t max = 0L;
   size_t ss = 0L; // borland 6 -v- ms 6 compilers (sigh)
   for(ss = 0L; ss < log.aLines.Nelem(); ss++)
      {
      if(dq.in.iLimit && (max >= dq.in.iLimit))
         break;
      if(Query(log.aLines[ss], dq, false) == true)
         max++;
      }
   if(!max)
      return true;
   dq.out.aResults.AddZombies(max + 1);

   // Perform the match operation again, this time appending the results
   for(ss = 0L; ss < log.aLines.Nelem(); ss++)
      {
      if(dq.in.iLimit && (dq.out.aResults.Nelem() >= max))
         break;
      Query(log.aLines[ss], dq);
      }
   return true;
   }
bool HttpLogDatabase::Query(HttpLogEntry& log, DatabaseQuery& dq, bool bShould)
   {
   bool bInclude = false;
   bInclude = dq.in.ShouldInclude(log);            
   if(bShould && bInclude)
      dq.out.aResults[dq.out.aResults.Nelem()] = log;
   return bInclude;
   }
void HttpLogDatabase::Dir(Array<ZStr>& aLogs)
   {
   ZStr str;
   Array<File> aFiles;
   dirData.Query(aFiles);

   for(size_t ss = 0L; ss < aFiles.Nelem(); ss++)
      aLogs[aLogs.Nelem()] = aFiles[ss].QueryNode(str);
   }
ZStr HttpLogDatabase::mkPath(const ZStr& sNodeName)
   {
   ZStr sPath;
   sPath = dirData.Name();
   sPath.Append("\\");
   sPath.Append(sNodeName);
   return sPath;
   }
bool HttpLogDatabase::Create(HttpLog& log, const ZStr& sNodeName)
   {
   ZStr sPath = mkPath(sNodeName);
   File file;
   if(file.Name(sPath) == false)
      return false;
   if(file.Exists() == true)
      return false;
   ostream& os = file.OpenWrite(File::AT_BINARY);
   log.Write(os);         
   return true;
   }
bool HttpLogDatabase::Read(HttpLog& log, const ZStr& sNodeName)
   {
   ZStr sPath = mkPath(sNodeName);
   File file;
   if(file.Name(sPath) == false)
      return false;
   if(file.Exists() == false)
      return false;
   istream& is = file.OpenRead(File::AT_BINARY);
   log.Read(is);         
   return true;
   }
bool HttpLogDatabase::Update(HttpLog& log, const ZStr& sNodeName)
   {
   ZStr sPath = mkPath(sNodeName);
   File file;
   if(file.Name(sPath) == false)
      return false;
   ostream& os = file.OpenWrite(File::AT_BINARY);
   log.Write(os);         
   return true;
   }
void HttpLogDatabase::Delete(const ZStr& sNodeName)
   {
   ZStr sPath = mkPath(sNodeName);
   File file;
   if(file.Name(sPath) == false)
      return;
   file.Remove();
   }
