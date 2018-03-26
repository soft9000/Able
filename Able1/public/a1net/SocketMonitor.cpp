#include <a1net.hpp>

using namespace stdnet;

void SocketMonitor::LOG(ostream& cout, const char *pszBuf, int capture)
   {
   if(pwSocket.pwLog.Enabled())
      {
      LOG(cout, pszBuf, capture);
      return;
      }
   else
      cout << pszBuf;
   }
void SocketMonitor::LOG_LINE(const char *pszBuf)
   {
   if(pwSocket.pwLog.Enabled())
      {
      ZStr str = pwSocket.pwLog.Format(pszBuf);
      cout << str << endl;
      }
   }
void SocketMonitor::LOG_LINE(ostream& cout, const char *pszBuf, int capture)
   {
   if(pwSocket.pwLog.Enabled() && capture)
      {
      LOG_LINE(cout, pszBuf, capture);
      return;
      }
   else
      {
      if(pwSocket.pwLog.Enabled())
         {
         ZStr str;
         if(capture)
            str = pwSocket.pwLog.Format(pszBuf);
         else
            str = pwSocket.pwLog.Log(pszBuf);
         cout << str << endl;
         }
      else
         cout << pszBuf << endl;         
      }
   }
int SocketMonitor::GETLINE(istream& cin, ostream& cout, char *pszBuf, size_t szBuf, int& capture, int& converse)
   {
   // <<<WIP>>> This needs to be character-oriented before we do anything commercial!!
   cin.getline(pszBuf, szBuf);

   ZStr sBuf;

   // *****
   // CHECK FOR USER REQUESTS:
   switch(pszBuf[0])
      {
      case '!':
         LOG_LINE(cout, "Monitor mode terminated", capture);
      return 0;
      case '@':
         LOG_LINE(cout, pwSocket.GetError(sBuf, GetLastError()), capture);
      break;
      case '+':
         capture = !capture;
         if(capture)
            LOG_LINE(cout, "CAPUTRE ON", capture);
         else
            LOG_LINE(cout, "capture off", capture);
      break;
      case '~':
         converse = !converse;
         if(converse)
            LOG_LINE(cout, "CONVERSATIONAL MODE = OFF", converse);
         else
            LOG_LINE(cout, "CONVERSATIONAL MODE = ON ", converse);
      break;
      case '?':
         LOG_LINE(cout, "Enter \"!\" to stop", capture);
         LOG_LINE(cout, "Enter \"+\" to toggle capture", capture);
         LOG_LINE(cout, "Enter \"@\" to see error state", capture);
         LOG_LINE(cout, "Enter \"~\" to toggle listen-after-send (default = ON)", capture);
         LOG_LINE(cout, "Enter \"?\" to see this help message", capture);
      break;

      default:
      return 2;
      }
   return 1;
   }

void SocketMonitor::MonitorConnection(Socket& soc, ostream& cout, istream& cin)
   {
   pwSocket = soc;

   int capture  = 0;
   int converse = 1;
   ZStr str;

   LOG_LINE(cout, "MONITOR MODE", capture);
   LOG_LINE(cout, "~~~~~~~~~~~~", capture);

   if(pwSocket.IsConnected() == false)
      {
      LOG_LINE(cout, "ERROR: No connection established. Cannot monitor socket.", capture);
      return;
      }

   LOG_LINE(cout, "Enter \"?\" for help, capture", capture);

   char *pszBuf = new char[1024];
   *pszBuf     = NULL;
   int running = 1;
   while(running)
      {
      str = "";
      // *****
      // PROMPT && BUFFER-KEY-IN:
      if(capture)
         str.Append("$ ");
      str.Append("Monitor: ");

      LOG(cout, str.c_str(), capture);
      pszBuf[0] = NULL;

      // *****
      // GET USER RESPONSE & PROCESS ANY USER MACROS:
      running = GETLINE(cin, cout, pszBuf, 1024, capture, converse);
      switch(running)
         {
         case 0:
         case 1:
            continue;

         case 2:
         default:
            break;
         }

      // *****
      // PROCESS INTERNET-FORMATTED COMMAND SEQUENCE (i.e: use <CR><LF>)
      size_t sz = ::strlen(pszBuf);
      pszBuf[sz] = NULL;

      if(!(*pszBuf))
         str.Assign(" \r\n");
      else
         {
         str.Assign(pszBuf);
         str.Append("\r\n");
         }

      LOG_LINE(cout, str.c_str(), capture);

      // *****
      // TRANSACTION ROUND-TRIP;
      if(pwSocket.Send(str) == false)
         str.Assign("Socket: SEND FAILED / TIMEDOUT");
      else
      if(converse && pwSocket.Receive(str) == false)
         str.Assign("Socket: RECEIVE FAILED / TIMEDOUT");

      LOG_LINE(cout, str.c_str(), capture);
      }
   delete [] pszBuf;
   }

