
#include "SmallChange.hpp"


void main(int argc, char *argv[])
   {
   SmallChangeCommand cmd;
   SmallChange program;
#if 1
   cmd.sOpcode  = "$";
#else
   if(argc < 2)
      {
      program.Usage(cout);
      return;
      }
   cmd.sOpcode  = argv[1];
   if(argc > 2)
      cmd.sOperand = argv[2];
#endif
   program.Exec(cmd);
   }
