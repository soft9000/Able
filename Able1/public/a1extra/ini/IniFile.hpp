// This ancient class is used to parse INI files. It has been thru several incarnations.
// Originally written in C, converted to C++, and finaly ported to Able1, it could use
// some re-deisgn.
//
// 04/19/1998: TABOUT && converting to WIN32 (weekend #2), R. Nagy
// 05/18/1998: Fixed IniSection::FindValue() to take a buffer for the result (no reference caching on ZStr), R. Nagy
// 09/07/1998: Converted to string, R. Nagy.
// 10/19/1998: Fixed a bug in _chop() as a result of conversion of cstring.contains() to string.Find(), R. Nagy
// 10/26/1999: Massively updated to work with "const ZStr&" over "const char *" (etc), R. Nagy.
// 03/10/2001: Re-wrote IniSection::_rmbracket() so that it would work properly? R. Nagy
// 03/13/2005: Converting (in-place - no port!) to Able1, R. Nagy
// 08/29/2006: Updating, R. Nagy
// 08/23/2006: Copied to the Able1 project as IniFile (formerly known as inistrm), R. Nagy
// 10/16/2006: Updated Insert(...) to reflect the more stand-alone usage paradigm, R. Nagy
//             Depricated Update(...) and Insert(...) in favor of Write(...), R. Nagy
//             Changed Read(void) to Load(void). Changed Write(void) to Save(void), R. Nagy
//             Dropped virtual memberships. As a pattern for re-use, TVRs are far better, R.Nagy
// 10/25/2006: Added New(), R. Nagy
// 03/01/2008: Added IsNull(), R. Nahu
//
// TODO
// ====
// This entire namespace is showing its age - It needs to:
//    (1) Be converted to a more publically accessable MVC pattern for IniData and IniSection.
//    (2) Allow for a more public IniFile management of IniSections AS A WHOLE (CRUD&S.)
//
// IMPORTANT
// =========
// For efficiency sake, I do not think that we should eliminate the use of
// pointers in this version of the namespace. Just be sure to check that
// pointers are populated before use. i.e. "If it is not broke, do not fix it."
//
// Also, we need to add support for comments - both before and within sections. 
// As it is now, they are COMPLETELY ignored on Load(), so they are lost on 
// Save() - Not too bad for our purposes, as the main purpose of the INI is
// to provide an easy way for a USER to edit data - But we should still support
// the verbaium Load() and Save() of INI comments and other non-data lines at 
// some point.
//
#ifndef _INISTRM_HPP
#define _INISTRM_HPP

#include <Able1.hpp>
using namespace Able1;

namespace ini
   {
class IniFile;
class IniSection;
class IniData;


class IniData
  {
  protected:
     ZStr pLval;
     ZStr pRval;

  public:
     IniData(void);
     IniData(const ZStr& L, const ZStr& R);
     ~IniData(void);

     void Get(ZStr& L, ZStr& R);
     void Put(const ZStr& L, const ZStr& R);
  };

// ***************************************************************************
// An IniSection is a [section] in an IniFile.  Note that ANY persistance layer
// can be supported with a simple reWrite of the stream operators, since this is
// the only place where []'s and "x=X" expressions are accomodated;
// ***************************************************************************
class IniSection
  {
  private:
     bool     _rmbracket(ZStr&);
     bool     _chop(ZStr&, ZStr&, ZStr&);

     // Set / test end of record (section) members;
     ostream& EorPut(ostream&);
     int      EorIs(ZStr&);

     enum stuff {EnumStart = -1, EnumStop = -1};
     Array<IniData>  aData;            // Where SECTION OPTIONS are stored.

     ZStr sEor;                   // Our end-of-record (section) indicator.

     IniData *FindData(const ZStr& DataTag);
     bool     FindValue(ZStr& sValueResult, const ZStr& sDataTag);

     void     AddData(const ZStr& sDataTag, const ZStr& sValueResult);
     bool     RmData(const ZStr& sDataTag);

  public:
     ZStr sSectionName;           // Where the NAME of THIS SECTION is stored.
     
     IniSection(void);
     IniSection(const ZStr& sectionTag);
     ~IniSection(void);

     size_t  EnumValues(ZStr& tag, ZStr& value, size_t last1=EnumStart);
     
     ZStr Get(const ZStr& sTag) {ZStr str; FindValue(str, sTag); return str;}
     bool      Get(const ZStr& sTag, ZStr& str) {return FindValue(str, sTag);}
     bool      Put(const ZStr& sTag, ZStr& str) {AddData(sTag, str); return true;}
     bool      Delete(const ZStr& sTag)              {return RmData(sTag);}

     ostream& Write(ostream&);
     istream& Read(istream&);

    friend IniFile;
  };


// ***************************************************************************
// An IniFile manages one or many IniSections - Because comments are not (yet?)
// supported, this class is best for READ ONLY use. Use XmIni, instead.
// ***************************************************************************
class IniFile
  {
  private:
     IniSection        *pwIniSection;
     Array<IniSection> aSections;

     ZStr *GetSection(istream&);

     int ss;

     // Find() is obsolete: Use Lookup(), instead;
     const char *Find(ZStr& sResult, const ZStr& section, const ZStr& tag);   // ((LEGACY))

  protected:
     bool bChanged;

     IniSection *CreateIniSection(const ZStr& rs) {return new IniSection(rs);}

     // Locate a section;
     IniSection *FindSection(const ZStr& section);

  private:
     // Dynamically add a new section to the INI file.
     bool        AddSection(IniSection&);
     // (else, use the section as the lookup-key,
     // and use it to traverse the paIniSections[]...)
  protected:
     // Depricated -
     bool      Update(const ZStr& section, const ZStr& tag, const ZStr& value);  // False if section NF
     bool      Insert(const ZStr& section, const ZStr& tag, const ZStr& value);  // Section created if not found

  public:
     File pwFile;

     IniFile(void);
     IniFile(const File& file);

     ~IniFile(void);

     bool      IsNull(void) {return aSections.IsNull();}

     void      Use(const File& file);

     ZStr Get(const ZStr& section, const ZStr& tag);                          // Return tag value from section.
     bool      Get(const ZStr& section, const ZStr& tag, ZStr& sValue);       // Return bool if non-null.
     bool      Put(const ZStr& section, const ZStr& tag, const ZStr& value);  // Update if it exists, Insert if new -
     bool      Delete(const ZStr& section, const ZStr& tag);                       // Remove tag from the section

     bool      HasChanged(void); // true if *file has changed.

     void      New(void);              // Reset the MEMORY content - file content (if any) left unchanged

     bool      Load(File& pwFile, const Directory& dir); // True if file was Read.
     bool      Load(const File& file); // True if file was Read.
     bool      Load(void);             // true if INI FILE was Read.
     bool      Save(void);             // true if "    "   was written.
     bool      Exists(void);           // true if "    "   file exists.

     // Check for one of a set of options in an INI file. Return the zero based offset if found, -1 on error.
     // Example: switch(ReadEnum("DATABASE", "CONTENT_TYPE", "XML | TVR | SDF | CSV | FORTUNE")) {...}
     int       GetEnum(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions);
     // Writes one of a set of options in an INI file based upon the offset if found, false on error.
     // Example: WriteEnum("DATABASE", "CONTENT_TYPE", "XML | TVR | SDF | CSV | FORTUNE"), 4);
     bool      PutEnum(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions, int iWhich);
     // Writes the entire set of options to the file, allowing a user to edit the file and choose one.
     // Example: PutEnumOptions("DATABASE", "RECORD_ACCESS", "REC_SEQUENTIAL | REC_RANDOM")
     bool      PutEnumOptions(const ZStr& sSection, const ZStr& sTag, const ZStr& sOptions);
  };

}

#endif


