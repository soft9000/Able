#ifndef XmIni_Hpp
#define XmIni_Hpp

// Namespace XmIni: Combine [SECTION] style-tagging with XML-style 
// field / element concepts. 
//
// The use of [SECTIONS] allows for more human-managable files to 
// be created.
//
// Objective is to allow faster parsing of payloaded [RECORD]s, as 
// well as to support multi-line (XML-style) field definitions. 
//
// Example:
// -------
//
// Any text that is written before a secion (like this)
// will be treated as a comment. Comments are preserved.
// [SECTION]
//      <PROJECT>
//        This project supports 
//        multi-line 'INI' entries
//        via XML style tags.
//      </PROJECT>
// [/SECTION]
//
// We can have more than one section with the same name.
//
// [SECTION]
//      <INFO>
//      Multiple SECTION support (in arrays)
//      allows for true database usage.
//      </INFO>
// [/SECTION]
//
// The XMINI Section is optional, but a good idea.
// [XMINI]
//      <COMMENT>This is an optional section.</COMMENT>
//      <XMINI VERSION> 1.0 </XMINI VERSION>
// [/XMINI]
//
// The APPLICATION Section is optional, but also a good idea.
// [APPLICATION]
//      <FILE> YourProgramName.EXE </FILE>
//      <AUTHOR> Your credits </AUTHOR>
//      <INFO> Things you want to say about it (usage, copyrights, etc.) </INFO>
// [/APPLICATION]
//
// 01/02/2007: Created, R. Nagy
//

namespace Able1
{
/** An XML INI file. Very easy to use, much nicer implementation over that of the old INI model. */
namespace XmIni
{

/** Every Section or Field therein is a tag / value pair. */
class TagPair
   {
   protected:
      ValueParser::TagBlock tb;

   public:
      char cOn, cOff;

      TagPair(char chOn = '<', char chOff = '>')
         {
         cOn = chOn; cOff = chOff;
         }

      virtual ~TagPair(void) 
         {
         }

      virtual bool IsNull(void)
         {
         return tb.IsNull();
         }

      void Assign(const ZStr& sTag, const ZStr& sValue, const ZStr& sComment = "")
         {
         tb.sTag   = sTag;
         tb.sValue = sValue;
         tb.sPrefix = sComment;
         }

      ZStr Tag(void)
         {
         return tb.sTag;
         }

      ZStr Value(void)
         {
         return tb.sValue;
         }

      ZStr Comment(void)
         {
         return tb.sPrefix;
         }

      virtual ostream& Write(ostream& os);

      virtual istream& Read(istream& is);
   };

/** Fields live in sections. */
class Field : public TagPair
   {
   public:
      Field(void) : TagPair('<', '>')
         {
         }
      Field(const ZStr& sTag, const ZStr& sValue) : TagPair('<', '>')
         {
         tb.sTag = sTag;
         tb.sValue = sValue;
         }
   };

/* Sections are the main (parent) element.
 * -It is all about making it easier for both
 * humans and computers to read. So like the 
 * old INI files, a section identifier is 
 * surrounded by square braces. 
 */
class Section : public TagPair
   {
   public:
      Array<Field> aFields;

      Section(void) : TagPair('[', ']')
         {
         }

      Section(const ZStr& sSectionName) : TagPair('[', ']')
         {
         tb.sTag = sSectionName;
         }

      // Probable helper functions include -
      // Field   Locate(const ZStr& sFieldTag);
      // bool    Update(Field& section);
      // bool    Append(Field& section);
      // bool    UpdateOrAppend(Field& section);

      virtual ostream& Write(ostream& os);

      virtual istream& Read(istream& is);
   };

/** Any stream / file will maintian a set of 
  * sections - Note that leading comments will
  * be part of the first section in the array.
  */
class SectionSet
   {
   public:
      Array<Section> aSections;

      size_t  Nelem(void)                    {return aSections.Nelem();}
      size_t  NelemTag(const ZStr& sSectionTag);

      Section operator[](size_t ss)          {return aSections[ss];}

      size_t  Locate(const ZStr& sSectionTag, Array<Section>& aResult);
      bool    Update(Section& section);
      bool    UpdateOrAppend(Section& section);
      void    Append(const Section& section) {aSections.Append(section);}

      virtual ostream& Write(ostream& os);

      virtual istream& Read(istream& is);
   };

/** IniFile is our key persistance object. */
class IniFile : public SectionSet
   {
   public:
      File    file;

      bool    Load(void);
      bool    Save(void);
      bool    Load(const File& file);
      bool    Save(const File& file);
      bool    Exists(void)                   {return file.Exists();}
      void    Empty(void)                    {aSections.Empty();}

      static ZStr  TYPE(void)           {return ".INX";}
      static IniFile    Create(const File& file);
   };

}  // XmIni

} // Able1

#endif
