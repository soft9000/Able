#include <extra/Searching/hypertext01.hpp>


const char *BabyBool::QueryPhrase(SearchType st)
   {
   switch(st)
      {
      case AND:
         return " <must contain> ";
      case NOT:
         return " <must not contain> ";
      case OR:
         return " <can contain> ";
      case ALL:
         return " <match everything> ";
      }
   return " <ERROR> ";
   }
const char *BabyBool::Query(ZStr& str)
   {
   str = QueryPhrase();
   str.Append(c_str());
   return str.c_str();
   }
bool BabyBool::Create(SearchType stt, const char *sData, bool bFound)
   {
   st = stt;
   assign(sData);
   found = bFound;
   return true;
   }
bool BabyBool::Assign(const ZStr& psz)
   {
   ZStr str = psz;
   size_t sz = str.Find('>');
   if(sz == NPOS)
      return false;
   str.Remove(sz);
   if(str.Find("must not") != NPOS)
      {
      st = NOT;
      goto leap22;
      }
   if(str.Find("must ") != NPOS)
      {
      st = AND;
      goto leap22;
      }
   if(str.Find("can not") != NPOS) // LEGACY SUPPORT (News*NET (ETC))
      {
      st = NOT;
      goto leap22;
      }
   if(str.Find("can ") != NPOS)
      {
      st = OR;
      goto leap22;
      }
   if(str.Find(" everyt") != NPOS)
      {
      st = ALL;
      goto leap22;
      }
   return false;
   leap22:
   // Assign the query-string;
   str = psz;
   assign(str.Substr(sz+2));
   return true;
   }
ostream& BabyBool::Write(ostream& os)
   {
   os.Write((char *)&st, sizeof(int));
   os.Write((char *)&found, sizeof(bool));
   WriteStream(os);
   return os;
   }
istream& BabyBool::Read(istream& is)
   {
   is.Read((char *)&st, sizeof(int));
   is.Read((char *)&found, sizeof(bool));
   ReadStream(is);
   return is;
   }



bool HyperTextKey01::IsKeyAt(const ZStr& str)
   {
   if(str.Find(key) == npos)
      return false;
   return true;
   }
HyperTextSearch01::HyperTextSearch01(void) : ssWip(0L)
   {
   }
HyperTextSearch01::~HyperTextSearch01(void)
   {
   }
bool HyperTextSearch01::AddKey(const ZStr& str, int token)
   {
   if(token == NPOS)
      return false;

   ZStr sB = str;
   sB.MkWhite();
   sB.Replace("   ", ' ');
   sB.Replace("  ", ' ');
   sB.Strip();
   sB.ToLower();
   if(sB.IsNull())
      return false;

   (aKeys[aKeys.Nelem()]).Assign(sB, token);
   return true;
   }
const char *HyperTextSearch01::GetKey(ZStr& str, int token)
   {
   for(size_t ss = NULL; ss < aKeys.Nelem(); ss++)
      {
      if((aKeys[ss]).Token() == token)
         {
         str = (aKeys[ss]).c_str();
         return str.c_str();
         }
      }
   return NULL;
   }
int HyperTextSearch01::FindKey(const ZStr& sBuffer)
   {
   if(sBuffer.IsNull())
      return NPOS;

   if(!aKeys.Nelem())
      return NPOS;

   ssWip  = 0L;
   sSaveBuffer = sBuffer;
   sSaveBuffer.MkWhite();
   sSaveBuffer.Replace("   ", ' ');
   sSaveBuffer.Replace("  ", ' ');
   sSaveBuffer.Strip();
   sSaveBuffer.ToLower();
   return NextKey();
   }
int HyperTextSearch01::FindNextKey(void)
   {
   if(!aKeys.Nelem())
      return NPOS;
   ssWip++;
   if(ssWip > aKeys.Nelem())
      ssWip = 0L;
   return NextKey();
   }
int HyperTextSearch01::NextKey(void)
   {
   if(!aKeys.Nelem())
      return NPOS;
   for(size_t ss = ssWip; ss < aKeys.Nelem(); ss++)
      {
      if((aKeys[ss]).IsKeyAt(sSaveBuffer) == true)
         {
         ssWip = ss;
         return ((aKeys[ss]).Token());
         }
      }
   ssWip = 0L;
   return NPOS;
   }

