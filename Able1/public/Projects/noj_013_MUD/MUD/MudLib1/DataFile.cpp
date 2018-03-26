#include "DataFile.hpp"


DataFile::DataFile(void) : dataType(dt_unknown)
   {
   }

bool DataFile::Use(const File& file)
   {
   // Tabbed fles must end with ".TAB"
   dataType = dt_unknown;
   ZStr str = file.Name();
   str.ToLower();
   ZStr sType = ".tab";
   size_t pos = str.rfind(sType);
   if(pos == npos)
      return false;
   if(pos != str.Length() - sType.Length())
      return false;

   pwFile = file;
   dataType = dt_tabbed;
   return true;
   }

bool DataFile::Load(const File& fIn, DataFile& dataFile)
   {
   dataFile.sLastError = "";

   File file = fIn;
   if(file.Exists() == false)
      {
      dataFile.sLastError = "Data file not found";
      return false;
      }

   if(dataFile.Use(fIn) == false)
      {
      dataFile.sLastError = "Invalid data file type";
      return false;
      }

   Array<ZStr> aData;
   Array<ZStr> aHeader;

   ZStr sLine;
   istream& is = file.OpenRead();

   sLine.Readline(is);
   aHeader = sLine.slice('\t');

   while(is)
      {
      sLine.Readline(is);
      aData = sLine.slice('\t');
      if(aHeader.Nelem() != aData.Nelem())
         {
         dataFile.sLastError = "Field mismatch";
         return false;
         }

      DataRecord dr;
      DataCell cell;

      for(size_t ss = 0L; ss < aHeader.Nelem(); ss++)
         {
         cell.sTag   = aHeader[ss];
         cell.sValue = aData[ss];
         dr.record.Append(cell);
         }
      dataFile.records.Append(dr);
      }

   return true;
   }


bool DataFile::Save(const File& fOut, DataFile& dataFile)
   {
   File file = fOut;
   size_t maxRec = -1L;

   dataFile.sLastError = "";

   ostream& os = file.OpenWrite();

   for(size_t ss = 0L; ss < dataFile.records.Nelem(); ss++)
      {
      DataRecord& rec = dataFile.records[ss];
      if(maxRec == -1L)
         {
         maxRec = rec.record.Nelem();
         for(size_t hh = 0L; hh < rec.record.Nelem(); hh++)
            {
            if(hh)
               os << "\t";
            os << rec.record[hh].sTag;
            }
         os << endl;
         }

      if(maxRec != rec.record.Nelem())
         return false;

      for(size_t hh = 0L; hh < rec.record.Nelem(); hh++)
         {
         if(hh)
            os << "\t";
         os << rec.record[hh].sValue;
         }
      os << endl;
      }

   return true;
   }
