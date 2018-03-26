#include <Able1.hpp>
using namespace Able1;

namespace html01
{

// A symetrical HTML table having a self-maintained, balanced, number of cells.
class TableWrapper
   {
   private:
      bool bOpen;
      int iWidth;
      int iTimes;

   public:
      TableWrapper(int iNumAcross) : iWidth(iNumAcross), iTimes(0), bOpen(false)
         {
         }
      void OpenTable(stringstream& srm)
         {
         bOpen = true;
         iTimes = 0;
         srm << endl << "<table>" << endl;
         }
      bool IsOpen(void)
         {
         return bOpen;
         }
      void Write(stringstream& srm, const ZStr& sPat)
         {
         srm << sPat;
         }
      void WriteLink(stringstream& srm, const ZStr& sTitle, const ZStr& sUrl)
         {
         if(iTimes == 0)
            srm << "<tr>" << endl;

         srm << "<td>";
         srm << "<a target=\"_blank\" href=\"" << sUrl << "\">" << sTitle << "</a>";
         srm << "</td>";

         iTimes++;
         if(iTimes == iWidth)
            {
            srm << endl << "</tr>";
            iTimes = 0;
            }
         }
      void CloseTable(stringstream& srm)
         {
         if(IsOpen() == false)
            return;

         while(iTimes < iWidth)
            {
            iTimes++;
            srm << "<td>&nbsp;";
            srm << "</td>";
            }
         srm << "</tr>";
         srm << endl << "</table>" << endl << endl;
         bOpen = false;
         iTimes = 0;
         }
   };
}