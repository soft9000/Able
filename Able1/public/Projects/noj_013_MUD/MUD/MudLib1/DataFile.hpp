#ifndef DataFile_Hpx
#define DataFile_Hpx

#include <Able1.hpp>

using namespace Able1;

class DataFile
   {
   private:
      File pwFile;

   public:
      ZStr sLastError;

      enum DataType
      {
         dt_tabbed,
         dt_unknown
      } dataType;

      struct DataCell
         {
         ZStr sTag;
         ZStr sValue;
         };

      struct DataRecord
         {
         Array<DataCell> record;
         };
         
      Array<DataRecord> records;

      DataFile(void);

      bool Use(const File& file);

      static bool Load(const File& fIn,  DataFile& dataFile);
      static bool Save(const File& fOut, DataFile& dataFile);
   };

#endif
