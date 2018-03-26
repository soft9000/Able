//#include "sample.hpp"
//#include "treecomp.hpp"

#include "BlastIt.Hpp"
#include <FolderFinder.Hpp>
//#include <File.Hpp>


class Blaster : public FolderReport
{
public:
   Array<StreamZStr> ary;
   bool bQuery;
   ostream& cout;
   ostream& cerr;
public:
   Blaster(const BlastIt& bi, ostream& out,  ostream& err) : cout(out), cerr(err)
      {
      bQuery = bi.bQuery;
      ary = bi.bb.aPatterns;
      }
   virtual void Dispose(const ZStr& pwNode)
      {
      if(bQuery)
         cout << "DEL " << pwNode << endl;
      else
         {
         ::File file;
         if(file.Name(pwNode) == false)
            {
            cerr << "ERROR: Unable to locate file " << pwNode << endl;
            return;
            }
         if(file.Remove() == false)
            {
            cerr << "ERROR: Unable to remove file " << pwNode << endl;
            return;
            }
         cout << "Removed " << pwNode << endl;
         }
      }
   virtual bool Folder(const ZStr& pwDir, const WIN32_FIND_DATA& ffd)
      {
      return true;
      }
   virtual bool File(const ZStr& pwDir, const WIN32_FIND_DATA& ffd)
      {
      ZStr sName;
      sName = ffd.cFileName;
      sName.ToUpper();
      size_t whence = NULL;
      for(size_t ss = NULL; ss < ary.Nelem(); ss++)
         {
         ZStr sPat = ary[ss].c_str();
         sPat.ToUpper();
         whence = sName.rfind(sPat);
         if(whence != NPOS)
            {
            ZStr match = sName.Substr(whence, NPOS);
            if(match == sPat)
               {
               // We have a winner!
               sPat = pwDir;
               sPat.Append('\\');
               sPat.Append(ffd.cFileName);
               Dispose(sPat);
               return true;
               }
            }
         }
      return true;
      }
};


BlastIt::BlastIt(void) : iChanged(0), bQuery(true)
   {
   }
void BlastIt::Load(void)
   {
   iChanged = 0;
   bQuery   =true;
   ProgramId pid;
   ZStr str;
   pid.ProgramName(str);
   str.Append(".dat");
   pid.PlaceInDirectory(str);
   file.Name(str);
   bb.Read(file.OpenRead(File::AT_BINARY));
   file.Close();
   }
BlastIt::~BlastIt(void)
   {
   if(iChanged)
      {
      bb.Write(file.OpenWrite(File::AT_BINARY));
      file.Close();
      }
   }
ZStr BlastIt::RemovePattern(const ZStr& sPattern)
   {
   iChanged = 1;
   return bb.RemovePattern(sPattern);
   }
ZStr BlastIt::AddPattern(const ZStr& sPattern)
   {
   iChanged = 1;
   return bb.AddPattern(sPattern);
   }
ZStr BlastIt::Program(const ZStr& sParam)
   {
   ZStr sResult = "Okay";
   switch(sParam[0])
      {
      case ('-'):
         return RemovePattern(&sParam[1]);
      case ('+'):
         return AddPattern(&sParam[1]);
      default:
         break;
      }
   return sResult;
   }
ZStr BlastIt::Run(int argc, char *argv[], ostream& cout, ostream& cerr)
   {
   bQuery = false;
   ZStr sRes = Query(argc, argv, cout, cerr);
   bQuery = true;
   return sRes;
   }
bool BlastIt::Query(const ZStr& sStartDir, BlastItParams& params, ostream& sOut, ostream& sError)
   {
   bb = params;
   QueryParamDir(sStartDir, sOut, sError);
   return true;
   }
ZStr BlastIt::Query(int argc, char *argv[], ostream& cout, ostream& cerr)
   {
   if(argc == 1)
      return RunParamNone(cout, cerr);
   if(argc == 2)
      {
      if(argv[1][0] == '+' || argv[1][0] == '-')
         return Program(argv[1]);
      return RunParamDir(argv[1], cout, cerr);
      }
   Usage(cout);
   ZStr sRes = "Okay";
   return sRes;
   }
void BlastIt::Version(ostream& cout)
   {
   cout << endl;
   cout << "BlastIt: Version 1.0" << endl;
   cout << "-------- Copyright (c) 2001 Soft9000.com." << endl;
   cout << "         Freely distributable, All Rights Reserved." << endl;
   cout << "         Works fine on my machine, but USE AT YOUR OWN RISK." << endl;
   cout << endl;
   }
void BlastIt::Usage(ostream& cout)
   {
   cout << endl;
   cout << "Usage: BlastIt [ [+suffix] [-suffix] [\"path to run on\"] ]";
   cout << endl;
   cout << "Use + to add, or - to remove items from the list." << endl;
   cout << "(i.e: +.OBJ or -.OBJ (etc) (case sensitive))"      << endl;
   cout << "Use \"path to run on\" to *recursively* destroy ALL files" << endl;
   cout << "ending with `suffix` under path and *ALL* sub-directories." << endl;
   cout << endl;
   }
ZStr BlastIt::RunParamNone(ostream& out, ostream& err)
   {
   out << "BlastIt: Programmed to recursively remove files ending with;" << endl;
   size_t ss = NULL;
   for(ss = NULL; ss < bb.Nelem(); ss++)
      out << bb[ss].c_str() << endl;
   Usage(out);
   ZStr sResult = "Okay";
   if(!ss)
      sResult = "No files";
   return sResult;
   }
long unsigned BlastIt::QueryParamDir(const ZStr& sStartDir, ostream& out, ostream& err)
   {
   bQuery = true;
   Blaster blaster(*this, out, err);
   FolderFinder ff;
   unsigned long res = ff.Run(sStartDir, blaster);
   if(res == -1L)
      res = NULL;
   bQuery = false;
   return res;
   }
long unsigned BlastIt::RunParamDir(const ZStr& sStartDir, ostream& out, ostream& err)
   {
   Blaster blaster(*this, out, err);
   FolderFinder ff;
   unsigned long res = ff.Run(sStartDir, blaster);
   if(res == -1L)
      res = NULL;
   return res;
   }

ZStr BlastItParams::RemovePattern(const ZStr& sPattern)
   {
   ZStr sResult = "Okay";
   StreamZStr sss = sPattern;
   for(size_t ss = NULL; ss < aPatterns.Nelem(); ss++)
      {
      if(sss == aPatterns[ss])
         {
         aPatterns.Remove(ss);
         return sResult;
         }
      }
   sResult = "Pattern `";
   sResult.Append(sPattern);
   sResult = "` not found.";
   return sResult;
   }
ZStr BlastItParams::AddPattern(const ZStr& sPattern)
   {
   ZStr sResult = "Okay";
   StreamZStr sss = sPattern;
   aPatterns.Append(sss);
   return sResult;
   }
ostream& BlastItParams::Write(ostream& os)
   {
   aPatterns.Write(os);
   return os;
   }
istream& BlastItParams::Read(istream& is)
   {
   aPatterns.Read(is);
   return is;
   }

const char *SetComma(long unsigned raw, ZStr& res)
   {
   char buf[MAX_PATH + sizeof(NULL)];
   sprintf(&buf[0], "%lu", raw);
   res = &buf[0];
   res.Reverse();
   size_t len = res.Length();
   size_t sz = (len / 3) +1;
   for(size_t ss = 1; ss < sz; ss++)
      {
      size_t pos = (ss * 3) + ss;
      if(pos != (len + ss))
         res.Insert(pos -1, ",");
      }
   res.Reverse();
   return res.c_str();
   }

/* YYYY/MM/DD format assumed;
bool ParseDate(ZStr& str_in, CTime& cTime)
   {
   const char delim = '/';
   ZStr sDate = str_in;

   ZStr yy, mm, dd;
   long sp2;

   sp2 = sDate.Find(delim);
   if(sp2 == npos)
      return false;
   sDate[sp2] = NULL;
   yy = sDate.c_str();
   sDate.RemovePos(0, sp2+1);

   sp2 = sDate.Find(delim);
   if(sp2 == npos)
      return false;
   sDate[sp2] = NULL;
   mm = sDate.c_str();
   sDate.RemovePos(0, sp2+1);
   dd = sDate.c_str();

   // CTime needs a 1900 base. Make sure it's compliant;
   if(atoi(yy.c_str()) < 1900)
      return false;

   // Record and save the result;
   CTime   cTime2(atoi(yy.c_str()), atoi(mm.c_str()), atoi(dd.c_str()), 0, 0, 0);
   cTime = cTime2;

   return true;
   }
*/

