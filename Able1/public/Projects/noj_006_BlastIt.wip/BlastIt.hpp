// Wrote this one years ago to help clan-up a directory tree. It recursively
// descends a tree, looking for pre-defined file types to remove. Great for
// automatically removing .obj, o, (etc.) files after a hard-days work.
//
// 01/25/2005: Ported the Able1 as noj_06, R. Nagy
//
#ifndef _blastit_hpp
#define _blastit_hpp

#include <Able1.hpp>
using namespace Able1;

class Balster;    // a FolderFinder

class BlastItParams
{
private:
   Array<StreamZStr> aPatterns;
public:
   ZStr RemovePattern(const ZStr& sParam);
   ZStr AddPattern(const ZStr& sParam);

   size_t    Nelem(void)               {return aPatterns.Nelem();}
   StreamZStr& operator[](size_t ss) {return aPatterns[ss];}

   BlastItParams& operator=(const BlastItParams& bb)
      {
      aPatterns = bb.aPatterns;
      return *this;
      }
   void Use(const Array<StreamZStr>& bb)
      {
      aPatterns = bb;
      }

   istream& Read(istream&);
   ostream& Write(ostream&);
   
   friend class Blaster;
};

class BlastIt
{
private:
   int  iChanged;
   bool bQuery;
   File file;
   BlastItParams bb;
   ZStr RemovePattern(const ZStr& sParam);
   ZStr AddPattern(const ZStr& sParam);

protected:
   ZStr RunParamNone(ostream& out, ostream& err);
// ZStr RunParamPipe(ostream& out, ostream& err);
   long unsigned RunParamDir(const ZStr& sStartDir, ostream& out, ostream& err);
   long unsigned QueryParamDir(const ZStr& sStartDir, ostream& out, ostream& err);

public:
   BlastIt(void);
   virtual ~BlastIt(void);

   void      Load(void);

   void      Version(ostream& cout);
   void      Usage(ostream&);

   ZStr Program(const ZStr& sParam);

   // RUN deletes files
   ZStr Run(int argc, char *argv[], ostream& out, ostream& err);

   // QUERY prints a report
   ZStr Query(int argc, char *argv[], ostream& out, ostream& err);
   bool      Query(const ZStr& sStartDir, BlastItParams& bp, ostream& out, ostream& err);

   friend class Blaster;
};

const char *SetComma(long unsigned raw, ZStr& res);


