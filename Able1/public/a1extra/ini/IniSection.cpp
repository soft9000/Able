// 08/29/2006: Updating, R. Nagy

//#define DEBUGk

#include "IniFile.hpp"
#define MAX_INI_WIDTH  256                  // WINDOWS limitation.

using namespace ini;



// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
IniSection::IniSection(void)
  {
  sSectionName = "[DEFAULT]";          // ownership is here.
  _rmbracket(sSectionName);            // remove brackets (if any)
  sEor = "Section=Eor!";               // Latter we need to parse on inter-section \n's <<WIP>>
  }
IniSection::IniSection(const ZStr& rStg)
  {
  sSectionName = rStg;                 // ownership is here.
  _rmbracket(sSectionName);            // remove brackets (if any)
  sEor = "Section=Eor!";               // Latter we need to parse on inter-section \n's <<WIP>>
  }

// ***************************************************************************
// ***************************************************************************
IniSection::~IniSection(void)
  {
  }

// ***************************************************************************
// ***************************************************************************
bool IniSection::_chop(ZStr &block, ZStr& lval, ZStr& rval)
  {
  if((block.Find('=')== NPOS))
     return false;
  size_t pos = block.Find("=");
  lval = block;
  lval.Remove(pos);                      // remove from "=", onward.

  const ZStr& sSS = block.c_str();
  //size_t sz = sSS.Length();
  rval.assign(&sSS[pos+1]);
#ifdef DEBUGk
  cout << block << " = " << lval << ", " << rval << endl;
#endif
  return true;
  }

// ***************************************************************************
// This function makes a "...[section]..." into a "section".  If no brackets,
// (or unbalanced baracketing) then it returns false.
// ***************************************************************************
bool IniSection::_rmbracket(ZStr& sIn)
   {
   ZStr block = sIn;
   size_t iStart = block.Find('[');
   if(iStart == NPOS)
      return false;
   size_t iEnd   = block.Find(']');
   if(iEnd   == NPOS)
      return false;
   block.Remove(iEnd);
   sIn = &block[iStart+1];
   return true;
   }

// ***************************************************************************
// ***************************************************************************
ostream& IniSection::Write(ostream& ofs)
  {
  // Stream-out the section-tag;
  ofs << "[" << sSectionName << "]" << endl;

  // Stream-out all of the section-values;
  ZStr Tag, Value;
  int ss = EnumValues(Tag, Value);    // -1 == START
  while(ss != EnumStop)
     {
     ofs << Tag << "=" << Value << endl;
#ifdef DEBUGk
     cout << Tag << "=" << Value << endl;
#endif
     ss = EnumValues(Tag, Value, ss); // We'll return your ss to you...
     }
  ofs << endl;                                    // Our new "eor"
  return ofs;
  }

// ***************************************************************************
// Read data into an IniSection.
// ***************************************************************************
istream& IniSection::Read(istream& ifs)
  {
  char buffer[MAX_INI_WIDTH];
  ZStr rIn(" ");

  ZStr Tag, Value;
  while(1)
     {
     ifs.getline(&buffer[0], MAX_INI_WIDTH);
     if(!buffer[0])
        break;                              // We just Read a \n.  Our new eor.
     rIn.assign(&buffer[0]);
     _chop(rIn, Tag, Value);                // break 'em apart at the "=".
     AddData(Tag, Value);
     }
  return ifs;
  }


// ***************************************************************************
// ***************************************************************************
IniData *IniSection::FindData(const ZStr& str)
{
ZStr tag, value;
for(size_t i=NULL; i < aData.Nelem(); i++)
  {
  aData[i].Get(tag, value);
  if(tag == str)
     return &aData[i];
  }
return 0L;
}


// ***************************************************************************
// ***************************************************************************
bool IniSection::FindValue(ZStr& value, const ZStr& str)
{
ZStr tag;
for(size_t i=NULL; i < aData.Nelem(); i++)
  {
  aData[i].Get(tag, value);
  if(tag == str)
     return true;
  }
value = "";
return false;
}


// ***************************************************************************
// ***************************************************************************
void IniSection::AddData(const ZStr& ptag, const ZStr& pvalue)
{
IniData next(ptag, pvalue);
aData[aData.Nelem()] = next;
}


// ***************************************************************************
// ***************************************************************************
bool IniSection::RmData(const ZStr& str)
{
ZStr tag, value;
for(size_t i=NULL; i < aData.Nelem(); i++)
  {
  aData[i].Get(tag, value);
  if(tag == str)
     {
     aData.Remove(i);
     return true; // G'night, Gracey.
     }
  }
return false;
}

// ***************************************************************************
// Protocol here is if "last1" == -1, then start at item 0, else, add 1 to
// "last1" to get which one is "next".
// ***************************************************************************
size_t IniSection::EnumValues(ZStr& tag, ZStr& value, size_t last1)
{
size_t foom = last1;
foom++;
if(foom >= aData.Nelem())
   return IniSection::EnumStop;

aData[foom].Get(tag, value);
return foom;
}
