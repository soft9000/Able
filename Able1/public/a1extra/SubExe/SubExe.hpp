#include <Able1.hpp>
using namespace Able1;
 
class SubExe
{
protected:
   struct IoPair
      {
      void *hRead;
      void *hWrite;

      IoPair() : hRead(0L), hWrite(0L)
         {
         }
      };

   IoPair ChildIn;
   IoPair ChildOut;

private:
   bool CreateChildProcess(const ZStr& szCmdline, IoPair& ChildOut, IoPair& ChildIn);
   bool Write(IoPair& ChildIn, IoPair& ParentIO);
   bool Read(IoPair& ChildOut, IoPair& ParentIO);
   bool SetError(char *lpszMessage);

public:
   ZStr sError;

   bool Exe(const ZStr& szCmdline);
   bool Read(ZStr& str, int iSecToPause = 0L);
   bool Write(const ZStr& str);

}; // class
