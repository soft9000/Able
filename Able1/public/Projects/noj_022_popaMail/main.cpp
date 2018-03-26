#include <Able1.hpp>
using namespace Able1;

#include <BetterMail.hpp>
using namespace BetterMail;

int main(int argc, char *argv[])
{
ProgramId pid;
if(argc != 3)
   {
   cout << "Usage: " << argv[0] << " # PopServer.ini" << endl;
   cout << "         Get mail for this ini." << endl;
   cout << "Usage: " << argv[0] << " = PopServer.ini" << endl;
   cout << "         Create a setup file for this ini." << endl;
   return 0;
   }

ZStr sOption = argv[1];

File file;
if(file.Name(argv[2]) == false)
   {
   cout << "Invalid file name - " << argv[2] << endl;
   return 0;
   }

IniFile ini;

// GENERATE AN INI FILE -
if(sOption == "=")
   {
   if(file.Exists() == true)
      {
      cout << "File  - " << file.Name() << " exists. Cannot create new file." << endl;
      return 0;
      }
   ini.Use(file);
   Directory dir;
   if(pid.GetProgram(dir) == false)
      {
      cout << "Error: Unable to stat the program folder." << endl;
      return 0;
      }
   if(MailServerIni::Create(ini, dir) == false)
      {
      cout << "Error: Unable to create the default ini file." << endl;
      return 0;
      }
   return 1;
   }

// DOWNLOAD THE MAIL -
if(file.Exists() == false)
   {
   cout << "File not found - " << file.Name() << endl;
   return 0;
   }
if(ini.Load(file) == false)
   {
   cout << "Unable load INI - " << file.Name() << endl;
   return 0;
   }

HostName host; UserData user;

if(MailServerIni::QueryPop3Default(ini, host, user) == false)
   {
   cout << "Unable to find host and / or user data in " << argv[2] << endl;
   return 0;
   }

StdLog log;
MailboxRed red;
MailboxProcessor::ReceiveAll(red, host, user, log);

return 1;
}

