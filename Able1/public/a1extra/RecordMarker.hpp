// Class RecordMarker: Associate a user-editable external index postion with any file name. 
//
// 08/03/2004: Created to support tqftd.
//
#ifndef RecordMarker_hpp_
#define RecordMarker_hpp_

class RecordMarker
{
public:
   static bool Name(const File& file, File& fName)
      {
      ZStr str = file.Name();
      return fName.Name(str += ".RecordMarker");
      }
   static bool RemoveMarker(const File& file)
      {
      File file2;
      if(Name(file, file2) == false)
         return false;
      if(file2.Exists() == false)
         return true;         
      file2.Remove();
      return !(file2.Exists());
      }
   static size_t Get(const File& file)
      {
      File file2;
      if(Name(file, file2) == false)
         return npos;
         
      ZStr str;         
      istream& is = file2.OpenRead();
      if(is)
         str.Read(is);
      size_t ss = (size_t)str.AsInt();
      file2.Close();
      return ss;
      }
   static bool Set(const File& file, size_t ss)
      {
      File file2;
      if(Name(file, file2) == false)
         return npos;

      ZStr str;         
      str.assign((int)ss);
      ostream& os = file2.OpenWrite();
      str.Write(os);
      file2.Close();
      return file2.Exists();
      }
};
#endif
