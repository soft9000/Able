// SpaceReport: Created to demonstrate ease-of-use and testing of Folders classes...
// -- but made a cool tool, too.
// Class created 10/02/1997, R. Nagy.
//
#include <folders.hpp>


// WARNING: This class is a "one shot". If used multiple times, `bytes` Tally will
// be cumulative;
class SpaceReport : public FolderReport
   {
   protected:
      long unsigned bytes;
      long unsigned folders;
   public:
      SpaceReport(void) : bytes(0L) {}
      virtual ~SpaceReport(void)    {}

      long unsigned BytesUsed(void) {return bytes;}

      virtual BOOL File(const ZStr& pwDir, const WIN32_FIND_DATA& FindFileData);
   };

inline
BOOL SpaceReport::File(const ZStr& pwDir, const WIN32_FIND_DATA& FindFileData)
   {
   bytes += FindFileData.nFileSizeLow;
   return FolderReport::File(pwDir, FindFileData);
   }
