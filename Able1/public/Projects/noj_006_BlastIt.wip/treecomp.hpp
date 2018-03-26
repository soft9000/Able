// TreeCompReport: Copied SimpleReport and modified to make TreeCompReport.
// Class created 02/01/1999, R. Nagy.
//
#include "folders.hpp"
#include <crcfile.hpp>


// WARNING: This class is a "one shot". If used multiple times, `bytes` Tally will
// be cumulative;
class TreeCompReport : public FolderReport
   {
   private:
      ZStr sRootDirL;
      ZStr sRootDirR;

   protected:
      long unsigned num_newerL, num_newerR, num_errors, num_okay;
      long unsigned num_uniqueL;
      long unsigned bytes;
      long unsigned folders;

   public:
      TreeCompReport(void) : bytes(0L), num_uniqueL(0L), num_newerL(0L), num_newerR(0L), num_errors(0L), num_okay(0L) {}
      virtual ~TreeCompReport(void)    {}

      virtual void FinalReport(void);

      BOOL Assign(const ZStr& sRootDirLectoryStartPoint, const ZStr& sRootDirRectoryStartPoint);

      long unsigned BytesUsed(void) {return bytes;}

      virtual BOOL File(const ZStr& pwDir, const WIN32_FIND_DATA& FindFileData);
   };

inline
BOOL TreeCompReport::Assign(const ZStr& sRootDirLectoryStartPoint, const ZStr& sRootDirRectoryStartPoint)
   {
   ZStr pwd;
   if(PushPwd(pwd) == FALSE)
      return FALSE;

   if(ChangeDirectory(sRootDirLectoryStartPoint) == FALSE)
      return FALSE;
   if(ChangeDirectory(sRootDirRectoryStartPoint) == FALSE)
      {
      PopPwd(pwd);
      return FALSE;
      }

   sRootDirL = sRootDirLectoryStartPoint;
   sRootDirR = sRootDirRectoryStartPoint;

   Node rNode;
   rNode.NormalizePath(sRootDirL);
   rNode.NormalizePath(sRootDirR);

   PopPwd(pwd);
   return TRUE;
   }

inline
BOOL TreeCompReport::File(const ZStr& pwDir, const WIN32_FIND_DATA& FindFileData)
   {
   cout << "\t";

   // If the date and time-stamps of the files are the same , then verify that
   // their contents are the same;
   ZStr sFileL = pwDir;
   sFileL.Append('/');
   sFileL.Append(FindFileData.cFileName);
   Node *pNodeL = GetNode(sFileL);
   if(!pNodeL)
      {
      num_errors++;
      cout << "ERROR: Unable to stat " << sFileL.c_str() << endl;
      }
   else
      {
      // VERY IMPORTANT
      ZStr sBuf;
      ZStr sTrimPathL;
      sTrimPathL.assign(pNodeL->Drive()); // start with the bonifide path to the node.
      sTrimPathL.Append(pNodeL->Path());  // start with the bonifide path to the node.
      sTrimPathL.remove_prefix(sRootDirL, 1); // Remove the user-specified "root" prefix.

      ZStr sFileR = sRootDirR;
      sFileR.Append(sTrimPathL);          // Use the relative-offset (only).
      sFileR.Append('/');
      sFileR.Append(pNodeL->Name());
      Node *pNodeR = GetNode(sFileR);
      if(!pNodeR)
         {
         num_uniqueL++;
         cout << "Unable to locate " << sFileR.c_str() << endl;
         }
      else
         {
         PortTime timeR, timeL;
         pNodeL->Extract(timeL);
         pNodeR->Extract(timeR);
         if(timeL == timeR)
            {
            CrcFile crcFile;
            CrcFile::CRC crcL = crcFile.Get(pNodeL->FullName(sBuf, '/'));
            if(crcL == CRCERROR)
               {
               num_errors++;
               cout << "ERROR(" << pNodeL->Name() << "): ";
               cout << "CRCERROR ON PRIMARY NODE!" << endl;
               }
            CrcFile::CRC crcR = crcFile.Get(pNodeR->FullName(sBuf, '/'));
            if(crcL != crcR)
               {
               num_errors++;
               cout << "ERROR(" << pNodeL->Name() << "): ";
               cout << "CONTENT OF FILES SHOULD MATCH, BUT DO NOT." << endl;
               }
            else
               {
               num_okay++;
               cout << "OKAY(" << pNodeL->Name() << ") " << endl;
               }
            goto number_next;
            }
         if(timeL > timeR)
            {
            num_newerL++;
            cout << "File " << pNodeL->FullName(sBuf, '/') << " is more recent." << endl;
            goto number_next;
            }

         num_newerR++;
         cout << "File " << pNodeR->FullName(sBuf, '/') << " is more recent." << endl;

         number_next:
         delete pNodeR;
         }
      delete pNodeL;
      }

   bytes += FindFileData.nFileSizeLow;
   //return FolderReport::File(pwDir, FindFileData);
   return TRUE;
   }

inline
void TreeCompReport::FinalReport(void)
   {
   cout << endl;
   cout << endl;
   cout << "========================================";
   cout << endl;
   char buf[100];

   sprintf(buf, "There was: % 8ld unique  node(s) found in ", num_uniqueL);
   cout << buf << sRootDirL.c_str() << endl;
   sprintf(buf, "There was: % 8ld updated node(s) found in ", num_newerL);
   cout << buf << sRootDirL.c_str() << endl;
   sprintf(buf, "There was: % 8ld updated node(s) found in ", num_newerR);
   cout << buf << sRootDirR.c_str() << endl;

   cout << "TOTAL FILES Okay( " << num_okay   << ")" << endl;
   cout << "TOTAL FILES ERROR(" << num_errors << ")" << endl;
   cout << "========================================";
   cout << endl;
   if(num_errors)
      cerr << "ERRORS ENCOUNTERED! Files were located that have the same date stamps, but different contents! (CRC)" << endl;
   }
