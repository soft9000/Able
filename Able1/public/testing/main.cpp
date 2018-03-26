#include "TestCases.hpp"


int main(int argv, char *argc[])
{
int iResult = 0L;
if(TestCases::Test(cout) == false)
   {
   cerr << "Test cases fail." << endl;
   iResult = -1L;
   }
else
   {
   cout << "Success." << endl;
   iResult = 1L;
   }
return iResult;
}
