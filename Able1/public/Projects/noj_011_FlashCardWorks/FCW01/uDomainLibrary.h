//---------------------------------------------------------------------------

#ifndef uDomainLibraryH
#define uDomainLibraryH
//---------------------------------------------------------------------------

#include <FastJob.hpp>
using namespace FastJob;

class DomainLibrary
{
   private:
      static const StdString sPicket;

   protected:
      static bool Query(Directory& dir);

   public:
      static const StdString sFileType;
      static const StdString sTestFileType;

      struct FlashRecord : public ValueParser::TagSet
         {
         FlashRecord(void)
            {
            sTag = "TAG";
            sValue = "Enter new value here.";
            }
         void Cleanup(void)
            {
            sTag.strip();
            sValue.strip();
            }
         StdString ToString(void)
            {
            Cleanup();
            stringstream srm;
            srm << sTag << ": " << sValue;
            StdString str = srm.str().c_str();
            return str;
            }
         bool FromString(const StdString& str)
            {
            size_t pos = str.find(':');
            if(pos == npos)
               return false;
            sTag = str.substr(0, pos);
            sValue = str.substr(pos + 1, npos);
            Cleanup();
            return true;
            }
         virtual bool IsNull(void)
            {
            FlashRecord rec;
            if(sTag != rec.sTag)
               return false;
            if(sValue != rec.sValue)
               return false;
            return ValueParser::TagSet::IsNull();
            }
         };

      static File DefaultDomain(void)
         {
         StdString sRoot = "MyOwn";
         File file;
         file.Name(sRoot + DomainLibrary::sFileType);
         DomainLibrary::Home(file);
         return file;
         }

      static File DefaultTest(void)
         {
         StdString sRoot = "MyOwn";
         File file;
         file.Name(sRoot + DomainLibrary::sTestFileType);
         DomainLibrary::Home(file);
         return file;
         }

      static bool IsDomain(const File& file)
         {
         return file.QueryNode().ends_with(DomainLibrary::sFileType);
         }

      static bool IsTest(const File& file)
         {
         return file.QueryNode().ends_with(DomainLibrary::sTestFileType);
         }

      static bool Query(Array<File>& files);
      static bool Home(File& file);

      static bool Read(const File& file, Array<FlashRecord>& aData);
      static bool Write(const File& file, Array<FlashRecord>& aData);
};
#endif
