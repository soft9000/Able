#include <Able1.hpp>
using namespace Able1;

using namespace Able1::XmIni;

ostream& TagPair::Write(ostream& os)
   {
   if(ValueParser::Write(os, tb, cOn, cOff, '/') == true)
      {
      }
   return os;
   }

istream& TagPair::Read(istream& is)
   {
   (*this) = TagPair(cOn, cOff);
   if(ValueParser::Read(is, tb, cOn, cOff, '/') == true)
      {
      }
   return is;
   }

ostream& Section::Write(ostream& os)
   {
   if(tb.sPrefix.IsNull() == false)
      {
      os << tb.sPrefix;
      ZStr str = tb.sPrefix;
      str.Strip();
      if(str.EndsWith("\n") == false)
         os << endl;
      }
   os << cOn << Tag() << cOff << endl;
   for(size_t ss = 0; ss < aFields.Nelem(); ss++)
      aFields[ss].Write(os);
   os << cOn << "/" << Tag() << cOff << endl;
   return os;
   }

istream& Section::Read(istream& is)
   {
   if(!is)
      return is;

   ValueParser::Read(is, tb, cOn, cOff);
   if(!is)
      return is;

   Field field;
   Array<ValueParser::TagBlock> array;
   if(ValueParser::Read(tb.sValue, array, field.cOn, field.cOff))
      {
      aFields.AddZombies(array.Nelem());
      for(size_t ss = 0L; ss < array.Nelem(); ss++)
         {
         ValueParser::TagBlock& ref = array[ss];
         field.Assign(ref.sTag, ref.sValue, ref.sPrefix);
         aFields.Append(field);
         }
      }

   return is;
   }

ostream& SectionSet::Write(ostream& os)
   {
   for(size_t ss = 0L; ss < aSections.Nelem(); ss++)
      aSections[ss].Write(os);
   return os;
   }

istream& SectionSet::Read(istream& is)
   {
   aSections.AddZombies(100);
   while(is)
      {
      Section section;
      section.Read(is);
      if(is)
         aSections.Append(section);
      }
   return is;
   }

size_t SectionSet::Locate(const ZStr& sSectionTag, Array<Section>& aResult)
   {
   size_t Tally = 0L;
   for(size_t ss = 0L; ss < aSections.Nelem(); ss++)
      {
      if(aSections[ss].Tag() == sSectionTag)
         {
         aResult.Append(aSections[ss]);
         Tally++;
         }
      }
   return Tally;
   }

bool SectionSet::Update(Section& section)
   {
   bool br = false;
   for(size_t ss = 0L; ss < aSections.Nelem(); ss++)
      {
      if(aSections[ss].Tag() == section.Tag())
         {
         aSections[ss] = section;
         br = true;
         break;
         }
      }
   return br;
   }

bool SectionSet::UpdateOrAppend(Section& section)
   {
   Array<Section> array;

   if(Locate(section.Tag(), array) == 1)
      return Update(section);

   Append(section);
   return true;
   }

size_t SectionSet::NelemTag(const ZStr& sSectionTag)
   {
   size_t Tally = 0L;
   for(size_t ss = 0L; ss < aSections.Nelem(); ss++)
      {
      if(aSections[ss].Tag() == sSectionTag)
         Tally++;
      }
   return Tally;
   }

IniFile IniFile::Create(const File& fff)
   {
   IniFile ini;
   ini.file = fff;
   Section section("XMINI");
   Field field("VERSION", "1.0");
   section.aFields.Append(field);
   ini.Save();
   return ini;
   }

bool IniFile::Load(void)
   {
   istream& is = file.OpenRead(File::AT_BINARY);
   aSections.Read(is);
   file.Close();
   if(aSections.Nelem())
      return true;
   return false;
   }

bool IniFile::Save(void)
   {
   ostream& os = file.OpenWrite(File::AT_BINARY);
   aSections.Write(os);
   file.Close();
   return file.Exists();
   }

bool IniFile::Load(const File& fff)
   {
   (*this) = IniFile();
   this->file = fff;
   return Load();
   }

bool IniFile::Save(const File& fff)
   {
   this->file = fff;
   return Save();
   }
