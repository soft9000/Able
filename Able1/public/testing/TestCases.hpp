// Note: Parameter overloading is used to define the test cases. 
// The class parameter should not be used, so make it const.
//
// 01/28/1998: Updated test cases to reflect new usage paradigm, R. Nagy
// 06/23/2003: Updated to test initial Able1 usage.
//   Updated to support changes in remove() usage.
// 08/04/2004: Created _spi::test(), R. Nagy
//   Runs fine under VS.NET 2003.
// 01/04/2005: Moving test cases here for a more unified regression testing capability, R. Nagy
// 08/30/2008: Updated + ran to verify new Array<T> - Same still needs work, going with other, R. Nagy
//

#ifndef Able1_testcases_Hpp
#define Able1_testcases_Hpp

#include <Able1.hpp>

using namespace Able1;


#include <a1extra/Searching/DosMatch.hpp>

class TestCases
{
   private:
      int io_test(const ZStr& str, int mo);

   public:
      bool test(const _spi<seek_t> spx, ostream& os);
      int  test(const ZStr& str, ostream& os);
      bool test(const Paragraph& ref, ostream& os);
      bool test(const DosMatch& dm, ostream& os);
/*
      bool test(const OidTag& dm, ostream& os);
*/
      bool test(const Array<ZStr>& array, ostream& os);
      
      static bool Test(ostream& os);
};

#endif
