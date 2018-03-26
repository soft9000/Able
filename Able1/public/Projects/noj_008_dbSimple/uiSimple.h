// From an absolute portability point of view, a application can be expressed as a
// series of user interfaces - Why not keep them in a database?
//
#include "dbLocalFile.h"

namespace uiSimple
{
   struct ScreenField : public dbSimple::Field
      {
      int x;
      int y;

      ScreenField(void) : x(0), y(0)
         {
         }

      istream& read(istream& is)
         {
         return is;
         }

      ostream& write(ostream& os)
         {
         return os;
         }
      
      int operator > (const ScreenField& ref)
         {
         return (string(c_str()) > ref.c_str());
         }

      };

   struct DisplayScreen
      {
      vector<ScreenField> fields;
      istream& read(istream& is)
         {
         return is;
         }

      ostream& write(ostream& os)
         {
         return os;
         }
      
      int operator > (const DisplayScreen& ref)
         {
         return (fields.size() > ref.fields.size());
         }
      };

   class UserInterface : public dbSimple::dbLocalFile<DisplayScreen>
      {
      public:
         bool Process(const DisplayScreen&);    // Hummmmmm....
      };

}