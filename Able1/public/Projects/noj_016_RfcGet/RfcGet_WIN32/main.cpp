
#include <stdnet.hpp>

using namespace stdnet;

int main(int argc, char *argv[])
{
URL param;
if(URL::Test(param, cout) == false)
   return 0;

return 1;
}
