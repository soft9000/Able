#include <Able1.hpp>
using namespace Able1;

class Params
{
protected:
   Params(void) {}

   Array<ZStr> aParams;

public:
   Params(int argc, char *argv[])
      {
      for(size_t ss = 0L; ss < argc; ss++)
         aParams.Append(ZStr(argv[ss]));
      }
   int Nelem(void) const
      {
      return aParams.Nelem();
      }
   ZStr operator[](size_t ss)
      {
      ZStr sResult;
      if(ss < aParams.Nelem())
         aParams.At(ss, sResult);
      return sResult;
      }
   bool Update(size_t ss, ZStr str)
      {
      if(ss >= aParams.Nelem())
         return false;
      aParams[ss] = str;
      return true;
      }
};

bool try_autoexec_inf(void)
{
File file;
if(file.Name("\\autoexec.inf") == false)
   {
   cerr << "\\autoexec.inf is a bad name on this system!" << endl;
   return false;
   }
if(file.Exists() == false)
   {
   cerr << "\\autoexec.inf is a not on this system!" << endl;
   return false;
   }
ZStr str;
istream& is = file.OpenRead();
while(is)
   {
   str.Read_line(is);
   if(is)
      {
      ZStr sTmp = str;
      sTmp.ToUpper();
      sTmp.Strip();
      if(sTmp.Find("UOPEN") == 0L)
         {
         // First position ...
         size_t pos = str.Find('=');
         if(pos != npos)
            {
            str.RemovePos(0, pos + 1);
            str.Strip();
            file.Name(str);
            return file.Launch();
            }
         }
      }
   }
   return false;
}


int main(int argc, char *argv[])
{
Params param(argc, argv);
if(param.Nelem() != 2)
   {
   if(try_autoexec_inf() == true)
      return 1;
      
   cerr << "Usage: " << param[0] << " url" << endl;
   return 0;
   }

if(param[1] == ".")
   {
   Directory dir;
   dir.Get();
   param.Update(1, ZStr("file://") + dir.Name());
   Url url;
   if(url.Name(param[1]) == false)
      {
      cerr << "Error: \"" << param[1] << "\" bad url name" << endl;
      return 0;
      }
   url.Launch();
   return 1;
   }
File file;
if(file.Name(param[1]) == false)
   {
   cerr << "Error: \"" << param[1] << "\" bad file name" << endl;
   return 0;
   }

if(file.Launch() == true)
   return 1;

return 0;
