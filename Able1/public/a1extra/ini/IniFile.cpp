
#include "IniFile.hpp"

using namespace ini;


IniFile::IniFile(void) : bChanged(false), ss(0)
{
}


IniFile::IniFile(const File& file) : bChanged(false), ss(0)
{
   Use(file);
}

IniFile::~IniFile(void)
{
}


void IniFile::Use(const File& file)
{
   bChanged = false;
   pwFile = file;
}



// ***************************************************************************
// THIS FUNCTION SUPERCEEDS Find();
// ***************************************************************************
ZStr IniFile::Get(const ZStr& section, const ZStr& tag)
{
ZStr sResult;
IniSection *pwSection = FindSection(section);
if(pwSection)
   pwSection->FindValue(sResult, tag);
return sResult;
}

// ***************************************************************************
// THIS FUNCTION SUPERCEEDS Find();
// ***************************************************************************
bool IniFile::Get(const ZStr& section, const ZStr& tag, ZStr& sValue)
{
sValue = Get(section, tag);
return !(sValue.IsNull());
}

// ***************************************************************************
// THIS FUNCTION IS OUR LEGACY;
// ***************************************************************************
const char *IniFile::Find(ZStr& sResult, const ZStr& section, const ZStr& tag)
{
sResult = Get(section, tag);
if(sResult.IsNull())
   return 0L;

return sResult.c_str();
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::Update(const ZStr& section, const ZStr& tag, const ZStr& value)
{
IniSection *pwSection = FindSection(section);
if(!pwSection)
  return false;

IniData *pDat = pwSection->FindData(tag);
if(!pDat)
  return false;

pDat->Put(tag, value);
bChanged = true;
return true;
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::Insert(const ZStr& section, const ZStr& tag, const ZStr& value)
{
IniSection *pwSection = FindSection(section);
if(pwSection)
   {
   // STEP: If a section exists, then update it -
   ZStr str = Get(section, tag);
   if(!str.IsNull())
      return Update(section, tag, value);
   }
if(!pwSection)
   {
   // STEP: If a section does not exist, then create a new section
   IniSection nSection(section);
   if(AddSection(nSection) == false)
     return false;
   // Verify creation
   pwSection = FindSection(section);
   if(!pwSection)
      return false;
  }
// STEP: Add the data -
pwSection->AddData(tag, value);
bChanged = true;
return true;
}

// ***************************************************************************
// ***************************************************************************
bool IniFile::Delete(const ZStr& section, const ZStr& tag)
{
IniSection *pwSection = FindSection(section);
if(!pwSection)
  return false;

bool br = pwSection->RmData(tag);
if(br == true)
  bChanged = true;

return br;
}


// ***************************************************************************
// ***************************************************************************
IniSection *IniFile::FindSection(const ZStr& str)
{
ZStr tag, value;
for(size_t i=NULL; i < aSections.Nelem(); i++)
  {
  if(str == aSections[i].sSectionName.c_str())
     return &aSections[i];
  }
return 0L;
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::AddSection(IniSection& rNew1)
{
   aSections[aSections.Nelem()] = rNew1;
   bChanged = true;
   return true;
}

// ***************************************************************************
// ***************************************************************************
ZStr *IniFile::GetSection(istream& ifs)
{
char buf[MAX_PATH];                   // largest SECTION .. .

while(ifs.getline(&buf[0], MAX_PATH-1))        // This is where the EOF will always be.
  {
  if(buf[0] == '[')                   // we have a winner [section]
     return new ZStr(buf);
  }

return (ZStr *) 0L;                 // "no mo "
}

// ***************************************************************************
// ***************************************************************************
void IniFile::New(void)
{
*this = IniFile(pwFile);
}


// ***************************************************************************
// Loads everything for faster access - From a Directory
// ***************************************************************************
bool IniFile::Load(File& pwFile, const Directory& dir)
{
if(dir.Home(pwFile) == false)
  return false;
return Load(pwFile);
}

// ***************************************************************************
// Loads everything for faster access - From a File
// ***************************************************************************
bool IniFile::Load(const File& file)
{
Use(file);
return Load();
}

// ***************************************************************************
// Re-loads everything for faster access - From default internal file
// ***************************************************************************
bool IniFile::Load(void)
{
aSections.Free();

istream& infile = pwFile.OpenRead();

ZStr *pSection = GetSection(infile);          // Look for a "[section]"
while(pSection)                                       // -if one found then
  {
  pwIniSection = CreateIniSection(*pSection);         // create a section object (ownership to pSection passes, too).
  pwIniSection->Read(infile);                         // stream the data in.
  if(AddSection(*pwIniSection) == false)
     {
     pwFile.Close();
     return false;
     }
  pSection = GetSection(infile);                   // check for another section.
  }

pwFile.Close();

bChanged = false;
if(aSections.Nelem())
   return true;
return false;
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::Save(void)
{
ostream& ofile = pwFile.OpenWrite();

for(size_t i = NULL; i < aSections.Nelem(); i++)
   aSections[i].Write(ofile);                          // stream it out.

pwFile.Close();

bChanged = false;
return true;
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::HasChanged(void)
{
return bChanged;
}


// ***************************************************************************
// ***************************************************************************
bool IniFile::Exists(void)
{
return pwFile.Exists();
}


// ***************************************************************************
// Check for one of a set of options in an INI file. Return the zero based offset if found, -1 on error.
// ***************************************************************************
int IniFile::GetEnum(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions)
   {
   ZStr sData = Get(sSection, sTag);
   if(sData.IsNull())
      return -1;
   Array<ZStr> aOptions;
   if(sOptions.Split('|', aOptions) == false)
      return -1;
   for(size_t ss = 0L; ss < aOptions.Nelem(); ss++)
      aOptions[ss].Strip();
   return aOptions.Contains(sData);
   }

// ***************************************************************************
// Writes one of a set of options in an INI file based upon the offset if found, false on error.
// ***************************************************************************
bool IniFile::PutEnum(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions, int iWhich)
   {
   Array<ZStr> aOptions;
   if(sOptions.Split('|', aOptions) == false)
      return false;
   for(size_t ss = 0L; ss < aOptions.Nelem(); ss++)
      aOptions[ss].Strip();
   if(size_t(iWhich) >= aOptions.Nelem())
      return false;
   if(Get(sSection, sTag).IsNull())
      return Insert(sSection, sTag, aOptions[iWhich]);
   return Update(sSection, sTag, aOptions[iWhich]);
   }
// ***************************************************************************
// Writes the entire set of options to the file, allowing a user to edit the file and choose one.
// ***************************************************************************
bool IniFile::PutEnumOptions(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions)
   {
   if(Get(sSection, sTag).IsNull())
      return Insert(sSection, sTag, sOptions);
   return Update(sSection, sTag, sOptions);
   }
// ***************************************************************************
// Add it if new, update it if not -
// ***************************************************************************
bool IniFile::Put(const ZStr& section, const ZStr& tag, const ZStr& value)
   {
   return Insert(section, tag, value);
   }

