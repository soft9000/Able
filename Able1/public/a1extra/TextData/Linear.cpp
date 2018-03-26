#include "Linear.hpp"

using namespace FileConversion;


ZStr Linear::ReadCooked(istream& is)
{
ZStr sLine;
sLine.Readline(is);
if(is)
   {
   size_t ssLast = sLine.Length()-1;
   if(sLine[ssLast] == '\r')
      sLine[ssLast] = 0;
   }
return sLine;
}


bool TabbedLine::Readline(istream& is, Array<ZStr>& aResult)
{
bool br = false;
aResult.Empty();
ZStr sLine = ReadCooked(is);
if(is)
   {
   br = true;
   aResult = sLine.slice('\t');
   }
else
   sLastError = "Readline: no line Read.";
return br;
}
bool TabbedLine::Writeline(ostream& os, Array<ZStr>& aResult)
{
if(aResult.Nelem())
   {
   sLastError = "Writeline: Input array is empty.";
   return false;
   }
size_t ssLast = aResult.Nelem() - 1;
for(size_t ss = 0L; ss < aResult.Nelem(); ss++)
   {
   os << aResult[ss];
   if(ss != ssLast)
      os << "\t";
   }
os << endl;
return true;
}


bool CsvLine::Readline(istream& is, Array<ZStr>& aResult)
{
bool br = false;
aResult.Empty();
ZStr sLine = ReadCooked(is);
if(is)
   {
   // Archaic usage would have numbers seperated by a comma, and strings quoted.
   // Observed modern covention seems to just quote them all. If your  mileage
   // varies, then feel free to use the <extra/CsvParser.hpp> class, instead.
   br = true;
   // VERY RARE that this would EVER cause a problem
   sLine.Replace("\",\"", "\t");  
   aResult = sLine.slice('\t');
   }
else
   sLastError = "Readline: no line Read.";
return br;
}
bool CsvLine::Writeline(ostream& os, Array<ZStr>& aResult)
{
if(aResult.Nelem())
   {
   sLastError = "Writeline: Input array is empty.";
   return false;
   }
size_t ssLast = aResult.Nelem() - 1;
for(size_t ss = 0L; ss < aResult.Nelem(); ss++)
   {
   os << aResult[ss];
   if(ss != ssLast)
      os << "\",\"";
   }
os << endl;
return true;
}


bool SdfLine::Readline(istream& is, Array<ZStr>& aResult)
{
sLastError = "work in progress";
return false;
}
bool SdfLine::Writeline(ostream& os, Array<ZStr>& aResult)
{
sLastError = "work in progress";
return false;
}
