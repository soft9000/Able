#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;

OidMeta::OidMeta(const ZStr& sON, const ZStr& sOFF, const ZStr& sSEP, const ZStr& sEQ)
   {
   delim.block.sBegin    = sON;
   delim.block.sEnd   = sOFF;
   delim.block.sLine = sSEP;
   delim.param.sEquals  = sEQ;
   }
bool OidMeta::Use(const OidTag& oid)
   {
   if(oid.Name() != DEFAULT_META_TAG)
      return false;

   bool br = false;
   ZStr str;

   str = oid.ValueFromTag("BLOCK.ON");
   if(!str.IsNull())
      {
      delim.block.sBegin = str;
      br = true;
      }
   str = oid.ValueFromTag("BLOCK.OFF");
   if(!str.IsNull())
      {
      delim.block.sEnd = str;
      br = true;
      }
   str = oid.ValueFromTag("BLOCK.LINE");
   if(!str.IsNull())
      {
      delim.block.sLine = str;
      br = true;
      }
   str = oid.ValueFromTag("LINE.EQ");
   if(!str.IsNull())
      {
      delim.param.sEquals = str;
      br = true;
      }
   str = oid.ValueFromTag("LINE.PARAM");
   if(!str.IsNull())
      {
      delim.param.sSeperator = str;
      br = true;
      }
   return br;
   }
ostream& OidMeta::Write(ostream& os)
   {
   OidTag oid; // USE the default seperators

   oid.Name(DEFAULT_META_TAG);
   oid.Update("BLOCK.ON",     delim.block.sBegin);
   oid.Update("BLOCK.OFF",    delim.block.sEnd);
   // OidMeta ALWAYS use the default seperator!
   if(delim.block.sLine != DEFAULT_SEP)
      oid.Update("BLOCK.LINE", delim.block.sLine);

   oid.Update("LINE.EQ",      delim.param.sEquals);
   oid.Update("LINE.PARAM",   delim.param.sSeperator);

   return oid.Write(os);
   }
istream& OidMeta::Read(istream& is)
   {
   OidTag oid;
   oid.Read(is);
   if(is)
      Use(oid);
   return is;
   }





