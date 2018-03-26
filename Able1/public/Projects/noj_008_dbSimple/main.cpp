#include "uiSimple.h"

struct DataRec : dbSimple::Record
{
   istream& Read(istream& is)
      {
      return is;
      }
   ostream& Write(ostream& os)
      {
      return os;
      }

   int operator > (const DataRec& rec)
      {
      return (aFields.size() > rec.aFields.size());
      }
};

class PortableDataApplication
{
protected:
   uiSimple::UserInterface           ui;
   dbSimple::dbLocalFile<DataRec>    db;

public:

   bool Main(const vector<string>& aParams, ostream& os);
};


bool PortableDataApplication::Main(const vector<string>& aParams, ostream& os)
   {
   ui.Locate("foo");
   return false;
   }


void main(int argc, char *argv[])
{
vector<string> vect;

string str;
for(int ss = 0; ss < argc; ss++)
   {
   str = argv[ss];
   vect.push_back(str);
   }

PortableDataApplication app;

if(app.Main(vect, cout) == false)
   {
   }
}
