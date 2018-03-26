#ifndef HtmlSButtonBar_hpp
#define HtmlSButtonBar_hpp

#include <Able1.hpp>
using namespace Able1;

class SimpleButtonBar
   {
   public:
      stringstream srm;

      SimpleButtonBar(int iBorder = 3, int cellPad = 4, int iColor = 111111)
         {
         srm << "<center>";
         srm << "<table border=\"";
         srm << iBorder;
         srm << "\" cellpadding=\"";
         srm << cellPad;
         srm << "\" cellspacing=\"0\" style=\"border-collapse: collapse\" bordercolor=\"#";
         srm << iColor;
         srm << "\">" << endl;
         srm << "<tr>";
         }
      void AddSpacer(int iSize = 4)
         {
         srm << "<td>";
         for(size_t ss = 0; ss < iSize; ss++)
            srm << "&nbsp;";
         srm << "</td>";
         }
      void AddButton(const ZStr& sText, const ZStr& sNode, const ZStr& iForeColor = "0x00FF", const ZStr& iBackColor = "0xFFFFFF")
         {
         srm << "<td bgcolor=\"";
         srm << iBackColor;
         srm << "\"><font color=\"";
         srm << iForeColor;
         srm << "\"><b><a href=\"";
         srm << sNode;
         srm << "\">";
         srm << sText;
         srm << "</a></b></font></td>";
         }
      ZStr End()
         {
         srm << "</tr>";
         srm << "</table>" << endl;
         srm << "</center>";
         ZStr str;
         str = srm.str().c_str();
         return str;
         }
   };
#endif
 
