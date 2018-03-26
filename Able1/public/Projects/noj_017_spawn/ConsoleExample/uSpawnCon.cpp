#include <Able1.hpp>
using namespace Able1;

//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

#include <Extra/StdLog.hpp>
class SpawnProgram
{
   private:

   protected:
      // A Spawn-compatible program is attempting to find out more about us.
      virtual int OnParamQuery(OidTag& oidTag)
         {
         oidTag.Update("ECHO", "An echo service");
         }
      // A Spawn-compatible program wants to test a user's Spawn definition.
      virtual int OnParamTest(OidTag& oidTag)
         {
         oidTag.Update("ECHO", "An echo service");
         }
      // Run as a Spawn-compatible program.
      virtual int OnMain(OidTag& oid)
         {
         return 0;
         }
      // Run as a non-Spawn program. Apply standard command-line processing
      // to the array of strings.
      virtual int  OnMain(const Array<ZStr>& array)
         {
         for(int ss = 0; ss < array.Nelem(); ss++)
            {
            ZStr str = array.At(ss);
            cout << str << endl;
            }

         char buf[100];
         cout << "Press any key, then press enter ...";
         cin >> buf;
         return 0;
         }
   public:

      // Return true if you were able to log, else false.
      virtual bool Log(const ZStr& sMsg)
         {
         StdLog log;

         }

      // Return true if you were able to log, else false.
      virtual bool LogError(const ZStr& sMsg)
         {
         }

      // Parss the inputs to Main and automate the program.
      static int  Main(int argc, char *argv[], SpawnProgram& program);
};



int SpawnProgram::Main(int argc, char* argv[], SpawnProgram& prog)
{
Array<ZStr> array;
if(OidRegistry::RegClient::Recall(argc, argv, array) == true)
   {
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      // STEP: CHECK for a PARAMETER QUERY
      OidParamQuery query;
      if(query.IsObject(array[ss]))
         {
         OidTag oidTag;
         if(OidRegistry::RegClient::PopParam(array[ss], oidTag) == true)
            {
            if(query.Use(oidTag) == true)
               {
               int iRes = prog.OnParamQuery(oidTag);
               query.Respond(oidTag);
               return iRes;
               }
            }
         }

      // STEP: CHECK for a SPAWN PARAMETER LIST
      OidSender oidSender("TEST");
      if(oidSender.IsObject(array[ss]))
         {
         OidTag oidTag;
         if(OidRegistry::RegClient::PopParam(array[ss], oidTag) == true)
            return prog.OnParamTest(oidTag);
         }

      // STEP: The default -
      OidTag oidTag;
      if(OidRegistry::RegClient::PopParam(array[ss], oidTag) == true)
         return prog.OnMain(oidTag);

      } // end for
   }

// Not a Spawn program - Just do it!
Array<ZStr> aParams;
aParams.AddZombies(argc);
for(int ss = 0; ss < argc; ss++)
   aParams.Append(argv[ss]);
return prog.OnMain(aParams);
}
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
SpawnProgram progEcho;
return SpawnProgram::Main(argc, argv, progEcho);
}
