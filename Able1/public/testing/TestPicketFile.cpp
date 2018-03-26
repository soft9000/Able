class TestPicketFile
   {
   public:
      // Controls leaving artifacts about the system for debugging purposes.
      bool bDebug;      

      TestPicketFile(void) : bDebug(false) {}

      bool Regress(Array<ZStr>&, StdLog& log, const ZStr& sToken);
      bool TestOne(StdLog& log);
      bool TestTwo(StdLog& log);
      bool TestThree(StdLog& log);
      bool TestFour(StdLog& log);
      bool TestFive(StdLog& log);

      bool TestAll(StdLog& log);
   };


bool TestPicketFile::Regress(Array<ZStr>& sTest, StdLog& log, const ZStr& sTok)
   {
   bool br = false;
   Array<ZStr> sResult;
   PicketFile::Normalize(sTest);

   File file;
   file.Name("TestPicketFile.txt");
   PicketFile::Generate(file, sTest, sTok);
   PicketFile::Parse(file, sResult, sTok);
   if(sTest == sResult)
      br = true;
   if(!bDebug)
      file.Remove();
   if(br == false)
      return br;

   br = false;
   sResult.Empty();
   ZStr strA;
   PicketFile::Generate(strA, sTest, "::SHAZAM::");
   PicketFile::Parse(strA, sResult, "::SHAZAM::");
   cout << strA << endl;
   if(sTest == sResult)
      br = true;
   return br;
   }
bool TestPicketFile::TestOne(StdLog& log)
   {
   Array<ZStr> sTest;
   sTest[sTest.Nelem()] = "This";
   sTest[sTest.Nelem()] = "is a";
   sTest[sTest.Nelem()] = "test.";
   return Regress(sTest, log, "%");
   }
bool TestPicketFile::TestTwo(StdLog& log)
   {
   Array<ZStr> sTest;
   sTest[sTest.Nelem()] = "This";
   sTest[sTest.Nelem()] = "is\na";
   sTest[sTest.Nelem()] = "test.";
   return Regress(sTest, log, "%");
   }
bool TestPicketFile::TestThree(StdLog& log)
   {
   Array<ZStr> sTest;
   sTest[sTest.Nelem()] = "This\n";
   sTest[sTest.Nelem()] = "is\na";
   sTest[sTest.Nelem()] = "\ntest.\n";
   return Regress(sTest, log, "%");
   }
bool TestPicketFile::TestFour(StdLog& log)
   {
   bool br = false;
   Array<ZStr> sTest;
   sTest[sTest.Nelem()] = ":$FIELD$:data 1:$FIELD$:";
   sTest[sTest.Nelem()] = ":$FIELD$:data 2:$FIELD$:";
   sTest[sTest.Nelem()] = ":$FIELD$:data 3:$FIELD$:";
   sTest[sTest.Nelem()] = ":$FIELD$:data 4:$FIELD$:";
   br = Regress(sTest, log, "%");
   if(br == false)
      return false;
   // Nested records
   Array<ZStr> sFields;
   br = PicketFile::Parse(sTest[0], sFields, ":$FIELD$:");
   if(br == false)
      return false;
   if(sFields[0] != "data 1")
      return false;
   return br;
   }
bool TestPicketFile::TestFive(StdLog& log)
   {
   bool br = false;
   Array<ZStr> sTest;
   sTest[sTest.Nelem()] = ":$FIELD$:\r\ndata 1\r\n:$FIELD$:\r\n";
   sTest[sTest.Nelem()] = ":$FIELD$:\r\ndata 2\r\n:$FIELD$:\r\n";
   sTest[sTest.Nelem()] = ":$FIELD$:\r\ndata 3\r\n:$FIELD$:\r\n";
   sTest[sTest.Nelem()] = ":$FIELD$:\r\ndata 4\r\n:$FIELD$:\r\n";
   br = Regress(sTest, log, ":$RECORD$:");
   if(br == false)
      return false;

   // Nested records
   Array<ZStr> sFields;
   br = PicketFile::Parse(sTest[0], sFields, ":$FIELD$:\n");
   if(br == false)
      return false;
   if(sFields[0] != "data 1\n")
      return false;
   return br;
   }
bool TestPicketFile::TestAll(StdLog& log)
   {
   bool br;
   br = TestOne(log);
   if(!br)
      return false;
   br = TestTwo(log);
   if(!br)
      return false;
   br = TestThree(log);
   if(!br)
      return false;
   br = TestFour(log);
   if(!br)
      return false;
   br = TestFive(log);
   if(!br)
      return false;
   return br;
   }
