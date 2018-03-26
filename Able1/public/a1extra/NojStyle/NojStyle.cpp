#include "NojStyle.hpp"

ZStr TocTemplate::sTemplateParam = "TemplateParam";

bool NojStyle::CalStyle(const File& fff, bool bOverWrite)
   {
   File file = fff;

   if(bOverWrite)
      file.Remove();

   if(file.Exists() == true)
      return true;

   ostream& os = file.OpenWrite();
   os << ".page { " << endl;
   os << "font-family: Verdana;" << endl;
   os << "background-color : #000C00;" << endl;
   os << "}" << endl;

   os << ".body { " << endl;
   os << "font-family: Verdana;" << endl;
   os << "background-color : #0088AA;" << endl;
   os << "}" << endl;

   os << ".link {" << endl;
   os << "color:green;" << endl;
   os << "}" << endl;

   os << ".tr {" << endl;
   os << "background-color : #0088AA;" << endl;
   os << "}" << endl;

   os << ".th {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "}" << endl;

   os << ".month {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "font-size: 16pt;" << endl;
   os << "font-weight:bold;" << endl;
   os << "color:#000066;" << endl;
   os << "background-color: #CACACA;" << endl;
   os << "} " << endl;

   os << ".normal {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "font-size: 16pt;" << endl;
   os << "color: #000000;" << endl;
   os << "}" << endl;

   os << ".today {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "font-size: 16pt;" << endl;
   os << "font-weight:bold;" << endl;
   os << "color:red;" << endl;
   os << "background-color: #CACACA;" << endl;
   os << "} " << endl;

   os << ".weekend { " << endl;
   os << "font-family: Verdana; " << endl;
   os << "font-weight:bold; " << endl;
   os << "font-size: 16pt; " << endl;
   os << "color:#FFFFFF; " << endl;
   os << "} " << endl;

   os << ".selected { " << endl;
   os << "font-family: Verdana; " << endl;
   os << "font-size: 16pt; " << endl;
   os << "color: #0000FF; " << endl;
   os << "background-color: #C00000; " << endl;
   os << "} " << endl;

   os << ".Event { " << endl;
   os << "font-family: Verdana; " << endl;
   os << "font-size: 16pt; " << endl;
   os << "color: yellow; " << endl;
   os << "background-color: green; // #C6D1DC; " << endl;
   os << "} " << endl;

   os << ".head { " << endl;
   os << "color:#CCCCCC; " << endl;
   os << "font:Arial, Helvetica, sans-serif; " << endl;
   os << "font-size:12px; " << endl;
   os << "font-weight:500; " << endl;
   os << "background-color:#000066; " << endl;
   os << "} " << endl;
   os << ".title { " << endl;
   os << "color:#000066; " << endl;
   os << "font:Arial, Helvetica, sans-serif; " << endl;
   os << "font-size:12px; " << endl;
   os << "font-weight:bold; " << endl;
   os << "} " << endl;

   return true;
   }
bool NojStyle::PageStyle(const File& fff, bool bOverWrite)
   {
   File file = fff;

   if(bOverWrite)
      file.Remove();

   if(file.Exists() == true)
      return true;

   ostream& os = file.OpenWrite();
   os << ".page { " << endl;
   os << "font-family: Verdana;" << endl;
   os << "background-color : #00ffff;" << endl;
   os << "}" << endl;

   os << ".body { " << endl;
   os << "font-family: Verdana;" << endl;
   os << "background-color : #0088AA;" << endl;
   os << "}" << endl;

   os << ".link {" << endl;
   os << "color:green;" << endl;
   os << "}" << endl;

   os << ".tr {" << endl;
   os << "background-color : #0088AA;" << endl;
   os << "}" << endl;

   os << ".th {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "}" << endl;

   os << ".normal {" << endl;
   os << "font-family: Verdana;" << endl;
   os << "font-size: 16pt;" << endl;
   os << "color: #000000;" << endl;
   os << "}" << endl;

   os << ".selected { " << endl;
   os << "font-family: Verdana; " << endl;
   os << "font-size: 16pt; " << endl;
   os << "color: #0000FF; " << endl;
   os << "background-color: #C00000; " << endl;
   os << "} " << endl;

   os << ".title { " << endl;
   os << "color:#000066; " << endl;
   os << "font:Arial, Helvetica, sans-serif; " << endl;
   os << "font-size:12px; " << endl;
   os << "font-weight:bold; " << endl;
   os << "} " << endl;

   return true;
   }
