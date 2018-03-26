#include "TestCases.hpp"

// #include <core/Array.hpp>


bool TestCases::Test(ostream& os)
{
   TestCases test;

   ZStr str;
   if(test.test(str, cout) != 0)
      return false;

   Paragraph para;
   if(test.test(para, os) == false)
      return false;

   _spi<seek_t> stest;
   if(test.test(stest, os) == false)
      return false;      

   DosMatch dm;
   if(test.test(dm, os) == false)
      return false;
/*
   OidTag oid;
   if(test.test(oid, os) == false)
      return false;
*/
   Array<ZStr> aryT;
   if(test.test(aryT, os) == false)
      return false;
      
   return true;
}


bool TestCases::test(const _spi<seek_t> spxxx, ostream& os)
	{
   size_t count = 100;
	_spi<seek_t> indexFile;
	indexFile.Name("C:\\test.idx");
	File file;
	if(file.Name(indexFile.Name()) == false)
	   {
	   os << "Unable to name _spi file." << endl;
	   return false;
	   }
	file.Remove();   
   seek_t sp;      
	for(size_t ss = 0L; ss < count; ss++)
	   {
	   sp = ss;
	   if(indexFile.Append(sp) == sp_npos)
	      {
	      os << "append(failure)" << endl;
	      return false;
	      }
	   }
   if(indexFile.Nelem() != count)
	   {
	   os << "nelem() or append() failure." << endl;
	   return false;
	   }
   for(int ss = 0L; ss < count; ss++)
      {
      indexFile.Read(ss, sp);
      if((size_t)sp != ss)   
         {
	      os << "Read(failure)" << endl;
	      return false;
	      }
      }
   size_t mid = count / 2;
   seek_t target = 999;
   if(indexFile.Update(mid, target) == false)            
      {
	   os << "update(failure)" << endl;
	   return false;
	   }
   for(int ss = 0L; ss < count; ss++)
      {
      indexFile.Read(ss, sp);
      if(ss == mid)
         {
         if((size_t)sp != target)   
            {
	         os << "update(failure2)" << endl;
	         return false;
	         }
         else
            continue;                  
         }
      if((size_t)sp != ss)   
         {
	      os << "update(failure3)" << endl;
	      return false;
	      }
      }
   if(indexFile.Remove(mid) == false)            
      {
	   os << "remove(failure1)" << endl;
	   return false;
	   }
   target = sp_npos;	         
   for(int ss = 0L; ss < count; ss++)
      {
      indexFile.Read(ss, sp);
      if(ss == mid)
         {
         if(sp != target)   
            {
	         os << "remove(failure2)" << endl;
	         return false;
	         }
         else
            continue;                  
         }
      if((size_t)sp != ss)   
         {
	      os << "remove(failure3)" << endl;
	      return false;
	      }
      }
	file.Remove();
	return true;
	}


/*
int TestCases::io_test(const ZStr& str, Ios_Openmode mo)
   {
   int ires = 0;
   // String construction & i/o testing;
   ZStr test1("String Construction.");
	   {
   ofstream ofs("testing.tmp", mo | ios::out);
   test1.WriteStream(ofs);
   test1.WriteStream(ofs);
   test1.WriteStream(ofs);
	   }
   ifstream ifs("testing.tmp", mo | ios::in);
   ZStr test2;
   test2.ReadStream(ifs);
   if(test1 == test2)
	   cout << "i/o success." << endl;
   else
	   {
	   cout << "i/o failure." << endl;
	   cout << test1 << "<>" << test2 << endl;
      ires++;
	   }
   test2.ReadStream(ifs);
   if(test1 == test2)
	   cout << "i/o success." << endl;
   else
	   {
	   cout << "i/o failure." << endl;
	   cout << test1 << "<>" << test2 << endl;
      ires++;
	   }
   test2.ReadStream(ifs);
   if(test1 == test2)
	   cout << "i/o success." << endl;
   else
	   {
	   cout << "i/o failure." << endl;
	   cout << test1 << "<>" << test2 << endl;
      ires++;
	   }
   return ires;
   }
*/
int TestCases::test(const ZStr& str, ostream& cout)
   {
   int ires = 0;
	   // Test default construction & destruction;
	   {
		   ZStr test;
	   }

	   // Test basic operators, copy constructor, and simple assignment;
	   {
		   ZStr test;
		   test.Assign("This is assigned.");
		   ZStr test2 = test;
		   if(test == test2)
			   cout << "Assignment okay(1)." << endl;
		   else
            {
			   cout << "Assignment failure(1)" << endl << test << endl << test2 << endl;
            ires++;
            }
	   }

      // Test prepend / append
      {
		   ZStr test;
		   test.Assign("ello");
         test.Prepend("H");
         if(test != "Hello")
            cout << "(error) prepend." << endl;
         else
            cout << "(okay) prepend." << endl;
         test.Append(" world!");
         if(test != "Hello world!")
            {
            cout << "(error) append." << endl;
            ires++;
            }
         else
            cout << "(okay) append." << endl;
      }

	   // Test strings in binary mode;
	   io_test(str, ios::binary);

	   // Test strings in text mode; (WARNING! NEWLINES WILL EXPAND ON DOS!)
	   io_test(str, 0);

	   // Test the array operator;
	   {
		   ZStr s("This is a test.");
		   s[4] = (char)NULL;
		   if(s == "This")
			   cout << ".operator[] working fine" << endl;
		   else
            {
			   cout << ".operator[] failed" << endl << s << endl;
            ires++;;
            }
	   }

	   // Test the subst_pos_to_pos;
	   {
		   ZStr  test("Look, it works!");
		   test.CopyPos(test, 0, 4);
		   if(test == "Look")
			   cout << ".CopyPos(okay)" << endl;
		   else
            {
			   cout << ".CopyPos() failed" << endl << test << endl;
            ires++;
            }

		   test.CopyPos(test, 2, 4);
		   if(test == "ok")
			   cout << ".CopyPos(okay)" << endl;
		   else
            {
			   cout << ".CopyPos() failed" << endl << test << endl;
            ires++;
            }

         test = "Look";
		   test.CopyPos(test, 2, 999);
		   if(test == "ok")
			   cout << ".CopyPos(okay)" << endl;
		   else
            {
			   cout << ".CopyPos() failed" << endl << test << endl;
            ires++;
            }

         test = "Look";
		   test.CopyPos(test, 999, 0);
		   if(test == "")
			   cout << ".CopyPos(okay)" << endl;
		   else
            {
			   cout << ".CopyPos() failed" << endl << test << endl;
            ires++;
            }
	   }

	   // Test the CopyBytes;
	   {
		   ZStr  test("Look, it works!");
		   test.CopyBytes(test, 0, 4);
		   if(test == "Look")
			   cout << ".CopyBytes(okay)" << endl;
		   else
            {
			   cout << ".CopyBytes() failed" << endl << test << endl;
            ires++;
            }

		   test.CopyBytes(test, 2, 2);
		   if(test == "ok")
			   cout << ".CopyBytes(okay)" << endl;
		   else
            {
			   cout << ".CopyBytes() failed" << endl << test << endl;
            ires++;
            }

         test = "Look";
		   test.CopyBytes(test, 2, 999);
		   if(test == "ok")
			   cout << ".CopyBytes(okay)" << endl;
		   else
            {
			   cout << ".CopyBytes() failed" << endl << test << endl;
            ires++;
            }

         test = "Look";
		   test.CopyBytes(test, 999, 0);
		   if(test == "")
			   cout << ".CopyBytes(okay)" << endl;
		   else
            {
			   cout << ".CopyBytes() failed" << endl << test << endl;
            ires++;
            }
	   }

	   // Test the CopyBytes;
	   {
		   ZStr  test("Look, it works!");
		   test.Substr(test, 6);
		   if(test == "it works!")
			   cout << ".Substr(okay)" << endl;
		   else
            {
			   cout << ".Substr(n) failed" << endl << test << endl;
            ires++;
            }
	   }

      // Make sure remove() is up to spec;
      {
      int error = 0;
         ZStr std = "This is a test";
         std.RemovePos(0, 5);
         if(std != "is a test")
            {
            cout << "remove(1) failed!" << endl;
            error = 1;
            ires++;
            }
         std.Remove(5);
         if(std != "is a ")
            {
            cout << "remove(2) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.RemoveBytes(1, 2);
         if(std != "ia ")
            {
            cout << "remove(3) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         // overflow
         std = "This is a test";
         std.RemovePos(999, 999);
         if(std != "This is a test")
            {
            cout << "remove(1a) failed!" << endl;
            error = 1;
            ires++;
            }
         std.Remove(999);
         if(std != "This is a test")
            {
            cout << "remove(2a) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.RemoveBytes(999, 999);
         if(std != "This is a test")
            {
            cout << "remove(3a) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         // insane
         std = "This is a test";
         std.RemovePos(1, 999);
         if(std.Length() != 1)
            {
            cout << "remove(1b) failed!" << endl;
            error = 1;
            ires++;
            }
         std = "This is a test";
         std.Remove(std.Length());
         if(std.IsNull())
            {
            cout << "remove(2b) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std = "This is a test";
         std.RemoveBytes(0, 999);
         if(!std.IsNull())
            {
            cout << "remove(3b) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.RemoveBytes(0, 999);
         if(!std.IsNull())
            {
            cout << "remove(3c) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.RemoveBytes(0, 999);
         if(!std.IsNull())
            {
            cout << "remove(3d) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.Remove(1);
         if(!std.IsNull())
            {
            cout << "remove(3e) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }
         std.Remove((size_t)0L);
         if(!std.IsNull())
            {
            cout << "remove(3f) failed!" << " '" << std << "'" << endl;
            error = 1;
            ires++;
            }

         if(!error)
            cout << ".remove && its variants are okay." << endl;
      }


	   // Finally, check-out the find / Rfind;

      // find(char)
      {
         ZStr test = "FOO_LISTING_TOO.DAT";
         size_t sz = test.Find('.');
         test[sz] = NULL;
         if(test != "FOO_LISTING_TOO")
            {
            cout << "(error) .Find(1) failed." << endl;
            ires++;
            }
         else
            cout << "(okay) find(char)" << endl;
      }

      // Rfind(char)
      {
         ZStr test = "FOO_LISTING_TOO.DAT";
         size_t sz = test.Rfind('.');
         test[sz] = NULL;
         if(test != "FOO_LISTING_TOO")
            {
            cout << "(error) .Rfind(1) failed." << endl;
            ires++;
            }
         else
            cout << "(okay) Rfind(char)" << endl;
      }

      // find(const char *)
      {
         ZStr test = "FOO_LISTING_TOO.DAT";
         size_t sz = test.Find(".DAT");
         test[sz] = NULL;
         if(test != "FOO_LISTING_TOO")
            {
            cout << "(error) .Find(2) failed." << " '" << test << "'" << endl;
            ires++;
            }
         else
            cout << "(okay) find(const char *)" << endl;
      }

      // Rfind(const char *)
      {
         ZStr test = "FOO_LISTING_TOO.DAT";
         size_t sz = test.Rfind(".DAT");
         test[sz] = NULL;
         if(test != "FOO_LISTING_TOO")
            {
            cout << "(error) .Rfind(2) failed." << " '" << test << "'" << endl;
            ires++;
            }
         else
            cout << "(okay) Rfind(const char *)" << endl;
      }

      // exhaustive testing of r/find(char);
	   {
		   ZStr std("01234543210");
		   if(std[5] != '5')
            {
			   cout << "Array error!" << endl;
            ires++;
            }
		   size_t sz;

		   // reflective testing;
		   sz = std.Find('5');
		   if(sz != 5)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Find('5', 3);
		   if(sz != 5)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Rfind('5');
		   if(sz != 5)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Rfind('5', 3);
		   if(sz != 5)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }

		   // Rfind Reverse index testing;
		   sz = std.Rfind('3');
		   if(sz != 7)
			   cout << ".Find(error): got " << sz << endl;
		   sz = std.Rfind('2');
		   if(sz != 8)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Rfind('1');
		   if(sz != 9)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Rfind('0');
		   if(sz != 10)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }

		   // find index testing;
		   sz = std.Find('3');
		   if(sz != 3)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Find('2');
		   if(sz != 2)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Find('1');
		   if(sz != 1)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
		   sz = std.Find('0');
		   if(sz != 0)
            {
			   cout << ".Find(error): got " << sz << endl;
            ires++;
            }
            
      {
      // Some more Rfind probem potentials
      ZStr str = "1<b1>2<b2>3<b3>";
      size_t sz = str.Find("<b2>");
      if(sz == npos)
         {
			cout << ".Rfind(error): got " << sz << endl;
         ires++;
         }
      size_t ss = str.Rfind("<b1>", sz);
      if(ss != 1)
         {
			cout << ".Rfind(error): got " << ss << endl;
         ires++;
         }
      }
      
      return ires;         
	   }
   }


bool TestCases::test(const Paragraph& ref, ostream& os)
   {
   ZStr sPattern (
      "AAA AAAA AAAAA\r"
      "BBB BBBB BBBBB\r\n"
      "CCC CCCC CCCCC\n\r"
      "DDD DDDD DDDDD"
                    );
   // TC 01 - Basic normalization
   ZStr sResult = Paragraph::Normalize(sPattern);
   if(sResult[14] != '\n')
      {
      os << "Error 01.1" << endl;
      return false;
      }
   if(sResult[29] != '\n')
      {
      os << "Error 01.2" << endl;
      return false;
      }
   if(sResult[44] != '\n')
      {
      os << "Error 01.3" << endl;
      return false;
      }
   if(sResult[sResult.Length() - 1] != '\n')
      {
      os << "Error 01.4" << endl;
      return false;
      }
   // TC 02 - Basic Word Wrapping (by space - variant)
   sResult = Paragraph::WordWrap(sPattern, 6);
   if(sResult[3] != '\n')
      {
      os << "Error 02.1" << endl;
      return false;
      }
   if(sResult[8] != '\n')
      {
      os << "Error 02.2" << endl;
      return false;
      }
   if(sResult[14] != '\n')
      {
      os << "Error 02.3" << endl;
      return false;
      }
   if(sResult[sResult.Length() - 1] != '\n')
      {
      os << "Error 02.4" << endl;
      return false;
      }
   // TC 03 - Multiple Word Wrapping (skip space - fixed)
   sResult = Paragraph::WordWrap(sPattern, 14);
   if(sResult[14] != '\n')
      {
      os << "Error 03.1" << endl;
      return false;
      }
   if(sResult[29] != '\n')
      {
      os << "Error 03.2" << endl;
      return false;
      }
   if(sResult[44] != '\n')
      {
      os << "Error 03.3" << endl;
      return false;
      }
   if(sResult[sResult.Length() - 1] != '\n')
      {
      os << "Error 03.4" << endl;
      return false;
      }
      
   // TC 04
   Array<ZStr> aResult = Paragraph::List(sPattern);
   if(aResult.Nelem() != 4)
      {
      os << "Error 04.1" << endl;
      return false;
      }
   sResult = Paragraph::Normalize(aResult);
   if(sResult.Length() != Paragraph::Size(aResult))
      {
      os << "Error 04.2" << endl;
      return false;
      }
   Array<ZStr> aResult2 = Paragraph::List(sResult);
   if(aResult2 != aResult)
      {
      os << "Error 04.3" << endl;
      return false;
      }
   return true;
   }

bool TestCases::test(const DosMatch& dm, ostream& cout)
{
   DosMatch match;

   // STEP
   // ****
   // Simple, unary patterns;
   if(match.Match("FOO.EXE", "FOO.EXE") == false)
      {
      cout << "Error 01" << endl;
      return false;
      }

   if(match.Match("FOO.*", "FOO.EXE") == false)
      {
      cout << "Error 02" << endl;
      return false;
      }

   if(match.Match("*.EXE", "FOO.EXE") == false)
      {
      cout << "Error 03" << endl;
      return false;
      }

   if(match.Match("FO?.EXE", "FOO.EXE") == false)
      {
      cout << "Error 04" << endl;
      return false;
      }

   // STEP
   // ****
   // Binary patterns;
   if(match.Match("?O?.EXE", "FOO.EXE") == false)
      {
      cout << "Error 05" << endl;
      return false;
      }

   if(match.Match("?O*.EXE", "FOO.EXE") == false)
      {
      cout << "Error 06" << endl;
      return false;
      }

   if(match.Match("*.?XE", "FOO.EXE") == false)
      {
      cout << "Error 06a" << endl;
      return false;
      }

   // STEP
   // ****
   // false unary patterns;
   if(match.Match("FOO.EXE", "FOO.EXX") == true)
      {
      cout << "Error 07" << endl;
      return false;
      }

   if(match.Match("FOO.*", "FOO:EXE") == true)
      {
      cout << "Error 08" << endl;
      return false;
      }

   if(match.Match("*.EXE", "FOO.EXX") == true)
      {
      cout << "Error 09" << endl;
      return false;
      }

   if(match.Match("FO?.EXE", "FO.EXE") == true)
      {
      cout << "Error 10" << endl;
      return false;
      }

   if(match.Match("*.EXE", "RELEASE1") == true)
      {
      cout << "Error 10a" << endl;
      return false;
      }

   if(match.Match("*", "RELEASE1") == false)
      {
      cout << "Error 10b" << endl;
      return false;
      }

   // STEP
   // ****
   // false binary patterns;
   if(match.Match("?O?.EXE", "FFO.EXE") == true)
      {
      cout << "Error 30" << endl;
      return false;
      }

   if(match.Match("?O*.EXE", "FFO.EXE") == true)
      {
      cout << "Error 31" << endl;
      return false;
      }

   // STEP
   // ****
   // Crash tests;
   if(match.Match("", "") == false)
      {
      cout << "Error 20" << endl;
      return false;
      }

   if(match.Match("?", "") == true)
      {
      cout << "Error 21a" << endl;
      return false;
      }

   if(match.Match("?", "1") == false)
      {
      cout << "Error 21b" << endl;
      return false;
      }

   if(match.Match("?", "111111") == true)
      {
      cout << "Error 21c" << endl;
      return false;
      }

   if(match.Match("*", "1") == false)
      {
      cout << "Error 22a" << endl;
      return false;
      }

   if(match.Match("*", "111111") == false)
      {
      cout << "Error 22b" << endl;
      return false;
      }

   if(match.Match("*", "") == true)    // Hummmmmmm...
      {
      cout << "Error 22c" << endl;
      return false;
      }

   if(match.Match("", "?") == true)
      {
      cout << "Error 23" << endl;
      return false;
      }

   if(match.Match("", "*") == true)
      {
      cout << "Error 24" << endl;
      return false;
      }

   if(match.Match("", "11111") == true)
      {
      cout << "Error 25" << endl;
      return false;
      }

   if(match.Match("11111", "1") == true)
      {
      cout << "Error 26" << endl;
      return false;
      }

   if(match.Match("1", "11") == true)
      {
      cout << "Error 27" << endl;
      return false;
      }
   // cout << "Normal end of test." << endl;
   return true;
}
   
/*
bool TestCases::test(const OidTag& dm, ostream& os)
   {
   if(OidController::Test() == false)
      {
      os << "Default test cases fail.";
      return false;
      }

   // Test nested block parsing -
   {
   stringstream srm;
   srm << "0 {"         << endl;
      srm << "\t1 { "   << endl;
      srm << "\t\t2 { " << endl;
      srm << "\t\t}";
      srm << "\t}";
   srm << "}";
   Array<Block> aResult;
   if(Block::Parse(srm.str().c_str(), "{", "}", aResult) == false)
      {
      os << "Block::Parse test cases fail.";
      return false;
      }
   }

   return true;
   }
*/   

bool TestCases::test(const Array<ZStr>&, ostream& os)
   {
   // Observed an Array<T> bug (?) in AutoEzine today - trying to re-create outside of same.
   ZStr sLine;
   {
   Array<ZStr> array;
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Append(sLine);
      }
   }
   {
   Array<ZStr> array;
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Insert(sLine, 0);
      }
   // CIP -
   for(int ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, 0);
      }
   // CIP -
   for(int ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   // CIP -
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   array.AddZombies(0);
   // CIP -
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   array.AddZombies(1);
   // CIP -
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   array.AddZombies(2);
   // CIP -
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Replace(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Insert(sLine, ss);
      }
   }
   {
   Array<ZStr> array;
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Insert(sLine, ss*2);
      }
   }


   Array<ZStr> array;
   array.AddZombies(1);
   for(size_t ss = 0L; ss < 10; ss++)
      {
      sLine.Assign((int)ss);
      array.Insert(sLine, ss*2);
      }

   Array<ZStr> opEq;
   opEq = array;
   opEq.Append("todo");
   array.Append("todo");
   return (opEq == array);
   }
