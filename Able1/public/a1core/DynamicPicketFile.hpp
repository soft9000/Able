// DynamicPicketFile: Like PicketFile, but the FIRST line in the file is the delimiter -
//
// 06/30/2008: Created, R. Nagy
//
#ifndef _DYPF_Format_
#define _DYPF_Format_

namespace Able1
{
   /** Unlike a PicketFile, a DYNAMIC picket file uses the FIRST LINE
     * in it's file as the RECORD DELIMITER.
     */
   class DynamicPicketFile
   {
   public:
      // Will return a NULL string on error -
      static ZStr ReadTag(const File& file);

      static bool Read(const File& file,   Array<ZStr>& aResult);

      static bool Write(const File& file,  Array<ZStr>& aResult);

      static bool Recall(const File& file, ZStr& aResult);
      static bool Recall(const File& file, ZStr& aResult, size_t ss);
   };

}

#endif
