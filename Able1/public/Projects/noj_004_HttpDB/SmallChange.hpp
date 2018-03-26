#ifndef _SmallChange_Hppp
#define _SmallChange_Hppp

#include "HttpLogDatabase.Hpp"
#include <iuo/SetComma.hpp>

struct SmallChangeCommand
   {
   ZStr sOpcode;
   ZStr sOperand;

   const char *Compose(ZStr& str)  {str = sOpcode; str += " "; str += sOperand; return str.c_str();}

   ostream& Write(ostream& os)         {sOpcode.WriteStream(os); sOperand.WriteStream(os); return os;}
   istream& Read(istream& is)          {sOpcode.ReadStream(is); sOperand.ReadStream(is); return is;}
   };

class SmallChangeOptions
{
protected:
   ZStr sOptions;
   File fileOptions;
public:
   Directory dirRepository;
   Array<SmallChangeCommand> aCommands;

   SmallChangeOptions(void);

   bool IsMacroMode(void)        {return (sOptions[0] == '-') ? false : true;}
   void IsMacroMode(bool b)      {sOptions[0] = (b == true) ? '+' : '-';}

   bool Load(void);
   bool Save(void);

   ostream& Write(ostream& os)   {dirRepository.Write(os); aCommands.Write(os); sOptions.WriteStream(os); return os;}
   istream& Read(istream& is)    {dirRepository.Read(is);  aCommands.Read(is);  sOptions.ReadStream(is);  return is;}
};

class SmallChange
   {
   protected:
      class FileStats
         {
         public:
            ZStr      sName;
            long unsigned  luBytes;
            long unsigned  luHits;

            FileStats() : luBytes(0L), luHits(0L) {}
         };

      void     SortByHits(Array<FileStats>& aStats);
      void     QueryStats(Array<HttpLogEntry>&, Array<FileStats>&);
      size_t   FnLookup(Array<FileStats>& aStats, const ZStr& sCommand);
      void     GetDefaultInit(DatabaseQuery& dbqResult);    // restore query defaults
      bool     SetDefaultInit(DatabaseQuery& dbqResult);    // save defaults

      void     FileHistogram(Array<HttpLogEntry>& aData, ostream& os);

      // Opcodes
      bool opAdd(HttpLogDatabase& dbLog, const ZStr& sFile);
      bool opRemove(HttpLogDatabase& dbLog, const ZStr& sFile);

      bool opChangeRepository(HttpLogDatabase& dbLog, const ZStr& sParameter);
      bool opList(HttpLogDatabase& dbLog, const ZStr& sParameter);

      bool opFilesReport(HttpLogDatabase& dbLog, const ZStr& sParameter);
      bool opFileReport(HttpLogDatabase& dbLog, const ZStr& sParameter);

      bool opGlobalFilter(HttpLogDatabase& dbLog, const ZStr& sParameter);

   public:
      SmallChangeOptions options;            // is automatically loaded

      void Usage(ostream&);

      bool Exec(const ZStr& sOperand);  // execute stored program
      bool Exec(SmallChangeCommand& cmd);
      bool Exec(const ZStr& sOpcode, const ZStr& sOperand);
   };


#endif
