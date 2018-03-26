
#ifndef no_extortion_Disclaimer_
#define no_extortion_Disclaimer_

#include <Able1.hpp>

using namespace Able1;

class Disclaimer
{
public:
   static void Header(ostream& os)
   {
   os << "DISCLAIMER: This is free software, as distributed under the " << endl;
   os << "MIT License (Open Source Approved). By using this software, " << endl;
   os << "you agree to hold the author free from any legal action," << endl;
   os << "tort or otherwise." << endl;
   }

};

#endif
