#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
 
#define BUFSIZE 4096 

#include "SubExe.hpp"
 
   bool SubExe::CreateChildProcess(const ZStr& szCmdline, IoPair& ChildOut, IoPair& ChildIn)
   {
      PROCESS_INFORMATION piProcInfo; 
      STARTUPINFO siStartInfo;
      bool bFuncRetn = false; 
 
      // Set up members of the PROCESS_INFORMATION structure. 
      ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
      // Set up members of the STARTUPINFO structure. 
      ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
      siStartInfo.cb = sizeof(STARTUPINFO); 
      siStartInfo.hStdError = ChildOut.hWrite;
      siStartInfo.hStdOutput = ChildOut.hWrite;
      siStartInfo.hStdInput = ChildIn.hRead;
      siStartInfo.wShowWindow = SW_HIDE;
      siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
      siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
 
      // Create the child process. 
      bFuncRetn = (bool)CreateProcess(NULL, 
         (char *)szCmdline.c_str(),     // command line 
         NULL,          // process security attributes
         NULL,          // primary thRead security attributes
         TRUE,          // handles are inherited
         0,             // creation flags
         NULL,          // use parent's environment
         NULL,          // use parent's current directory
         &siStartInfo,  // STARTUPINFO pointer
         &piProcInfo);  // receives PROCESS_INFORMATION
   
      if (bFuncRetn == false) 
         return SetError("CreateProcess failed\n");
      else 
      {
         CloseHandle(piProcInfo.hProcess);
         CloseHandle(piProcInfo.hThRead);
      }
      return bFuncRetn;
   }

 
   bool SubExe::SetError(LPSTR lpszMessage) 
   { 
      sError = lpszMessage;
      return false;
   }


   bool SubExe::Exe(const ZStr& szCmdline)
   { 
      SECURITY_ATTRIBUTES saAttr; 
      bool fSuccess; 
 
      // Set the bInheritHandle flag so pipe handles are inherited. 
      saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
      saAttr.bInheritHandle = true; 
      saAttr.lpSecurityDescriptor = NULL; 
 
      // Create a pipe for the child process's STDOUT. 
      if (! CreatePipe(&ChildOut.hRead, &ChildOut.hWrite, &saAttr, 0)) 
         return SetError("Stdout pipe creation failed\n"); 

      // Ensure that the Read handle to the child process's pipe for STDOUT is not inherited.
      SetHandleInformation( ChildOut.hRead, HANDLE_FLAG_INHERIT, 0);

      // Create a pipe for the child process's STDIN. 
      if (! CreatePipe(&ChildIn.hRead, &ChildIn.hWrite, &saAttr, 0)) 
         return SetError("Stdin pipe creation failed\n"); 

      // Ensure that the Write handle to the child process's pipe for STDIN is not inherited. 
      SetHandleInformation( ChildIn.hWrite, HANDLE_FLAG_INHERIT, 0);
 
      // Now create the child process. 
      fSuccess = CreateChildProcess(szCmdline, ChildOut, ChildIn);
      if (! fSuccess) 
         return SetError("Create process failed with"); 
 
      return true; 
   }

   bool SubExe::Read(ZStr& str, int timeout)
   {
      // Read from pipe that is the standard output for child process. 
      DWORD dwRead = 0L; 
      CHAR chBuf[BUFSIZE + 1];
      ::memset(chBuf, 0, BUFSIZE);

      if(timeout)
         {
         time_t tx = ::time(NULL);
         time_t time_stop = tx + timeout;
         while(tx <= time_stop)
            tx = ::time(NULL);
         }
 
      bool br = (bool)ReadFile(ChildOut.hRead, chBuf, BUFSIZE, &dwRead, NULL);
      if(br)
         str = chBuf;
      return br;
   }

   bool SubExe::Write(const ZStr& str)
   {
      DWORD dwWritten = 0L; 
      return (bool)WriteFile(ChildIn.hWrite, str.c_str(), (DWORD)str.Length(), &dwWritten, NULL); 
   }
