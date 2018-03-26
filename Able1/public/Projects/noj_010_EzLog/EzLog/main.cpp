
// This program demonstrates how easy it is to use EzLog - a class that allows
// simple messages to be time-stamped and added either to a common `pwd` based 
// log, or to a shared `main program file`.ezlog file. See EzLog::Usage() for 
// more information.

#include <a1extra/StdLog/EzLog.hpp>


int main(int argc, char *argv[])
{
   if(EzLog::Main(argc, argv, cout) == false) {
   cerr << endl << "Error: Logging failure." << endl;
   return 0;
   }
   return 1;
}
