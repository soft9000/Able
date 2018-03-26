// 10/24/1998, Ran through NOTAB, R. Nagy
//

#include <obsolete/Server/Email.hpp>

#define BEGIN {
#define END }

//#pragma message "BINARY STREAMS REQUIRED: SETMODE is not going to do anything!!"


bool EMail::SaveBin(const ZStr& sFileName)       // binary format
   {
   File file;
   if(file.Name(sFileName) == false)
      return false;
   return SaveBin(file);      
   }


bool EMail::SaveBin(const File& fff)       // binary format
   {
   File file = fff;
   ostream& os = file.OpenWrite(File::AT_BINARY);
   if(!os)
      return false;
   Write(os);
   return true;
   }

bool EMail::LoadBin(const ZStr& sFileName)       // binary format
   {
   File file;
   if(file.Name(sFileName) == false)
      return false;
   return LoadBin(file);      
   }
   
bool EMail::LoadBin(const File& fff)       // binary format
   {
   File file = fff;
   istream& is = file.OpenRead(File::AT_BINARY);
   if(!is)
      return false;
   Read(is);
   return true;
   }
bool EMail::RemoveTerminalDot(void)
   {
   size_t last = NPOS;
   size_t whence = _text.Find("\r\n.");   // observed && guaranteed minimum signature.
   while(whence != NPOS)
      {
      last = whence;
      whence = _text.Find("\r\n.", last+1);
      }
   if(last != NPOS)
      {
      // We have a potential terminal (RFC) "dot";
      ZStr std = _text.Substr(last);
      std[2] = ' ';
      if(std.is_white())
         {
         _text.Remove(last);
         return true;
         }
      }
   return false;
   }
bool EMail::FirstMessageLine(ZStr& std)
   {
   _ff_marker = NULL;
   return NextMessageLine(std);
   }
// RETURN an RFC-terminated portion of the article;
bool EMail::NextMessageLine(ZStr& std)
   {
   if(_ff_marker >= _text.Length())
      return false;

   size_t _ff = _text.Find(TERMINATE, _ff_marker);
   if(_ff == NPOS)
      _ff = _text.Length();
   else
      _ff+=2;      // INCLUDE the NEWLINE

   std = _text.Substr(_ff_marker, (_ff - _ff_marker));
   _ff_marker = _ff;
   return true;
   }
void EMail::EncodeDots(void)
   {
   ZStr std;
   bool br = FirstMessageLine(std);
   size_t start_pos = NULL;

   while(br == true)
      {
      if(std == ".")      // The LAST ONE looks like this.
         {
         std = "..";
         _text.RemovePos(start_pos, _ff_marker+1);
         _text.Insert(start_pos, std);
         _ff_marker += start_pos + std.Length();
         std = "";
         }
      if(std == ".\r\n")  // An IMBEDDED ONE looks like this.
         {
         std = "..\r\n";
         _text.RemovePos(start_pos, _ff_marker+1);
         _text.Insert(start_pos, std);
         _ff_marker += start_pos + std.Length();
         std = "";
         }
      start_pos = _ff_marker;
      br = NextMessageLine(std);
      }
   }
void EMail::DecodeDots(void)
   {
   ZStr std;
   bool br = FirstMessageLine(std);
   size_t start_pos = NULL;

   while(br == true)
      {
      if(std == "..")      // The LAST ONE looks like this.
         {
         std = ".";
         _text.RemovePos(start_pos, _ff_marker+1);
         _text.Insert(start_pos, std);
         _ff_marker += start_pos + std.Length();
         std = "";
         }
      if(std == "..\r\n")  // An IMBEDDED ONE looks like this.
         {
         std = ".\r\n";
         _text.RemovePos(start_pos, _ff_marker+1);
         _text.Insert(start_pos, std);
         _ff_marker += start_pos + std.Length();
         std = "";
         }
      start_pos = _ff_marker;
      br = NextMessageLine(std);
      }
   }
bool EMail::rfc_Write(ostream& ofs) const
   {
   if(EMailHeader::rfc_Write(ofs) == false)
      return false;

   ofs << TERMINATE;

   ofs << _text.c_str();
   ofs << TERMINATE;
   return true;
   }
bool EMail::MessagePayload(stringstream& ifs)
   {
   return rfc_message(ifs);
   }
#ifdef __BCPLUSPLUS__
bool EMail::MessagePayloadBinaryONLY(ifstream& ifs)
#else
bool EMail::MessagePayload(ifstream& ifs)
#endif
   {
   int omode = SETMODE(ifs, bin_mode);
   bool br = rfc_message(ifs);
   SETMODE(ifs, omode);
   return br;
   }
bool EMail::MessagePayload(const File& fff)
   {
   File file = fff;
   bool br = rfc_message(file.OpenRead(File::AT_BINARY));
   file.Close();
   return br;
   }
bool EMail::HasMessage(void) const
   {
   if(_text.IsNull())
      return false;
   return true;
   }
bool EMail::rfc_message(istream& ifs)
   {
   ZStr std, text;
   _text = std;     // empty it out
   if(!ifs)
      return false;

   while((!ifs.eof()) && ifs && ifs.good())
      {
      std.Readline(ifs);

      if(IsEndOfMessage(std))
         {
         // Usual terminal condition;
		   // done = 1;
		   break;
         }
         
      if(ifs)
         {
         Cleanup(std);                    // This might wind-up being NULL
         text.Append(TERMINATE);          // and this both RFC-joins && will put same, back.
         if(!text.IsNull())
            text.Append(std);             // (i.o will terminate)
         }
      }

   _text = text;     // VERY IMPORTANT TO RE-ASSIGN SO WE CAN RAM-FREE THE HUGE GROWTH SPACE.
   return true;
   }
bool EMail::rfc_Read(istream& ifs)
   {
   BEGIN
   EMail   emh;
   *this = emh;
   END
   if(EMailHeader::rfc_Read(ifs) == true)
      return rfc_message(ifs);
   return false;
   }
int EMail::operator==(const EMail& em) const
   {
   // Man, there ain't no reason to do a strcmp on a huge string
   // when we have headers;
   return EMailHeader::operator==((const EMailHeader&) em);
   }
EMail& EMail::operator=(const EMail& em)
   {
   if(this == &em)
      return *this;
   _pop3_server_id = em._pop3_server_id;
   _text.assign(em._text);
   EMailHeader::operator=(em);
   return *this;
   }
bool EMail::IsNull(void)   const
   {
   if(_text.IsNull() && EMailHeader::IsNull())
      return true;
   return false;
   }
ostream& EMail::Write(ostream& os)
   {
   EMailHeader::Write(os);
   _text.WriteStream(os);
   return os;
   }
ostream& EMail::Write_searchable(ostream& os)
   {
   EMailHeader::Write(os);
#if 1
   if(IsMime() == false)
      _text.Write(os);
#else
   if(IsMime() == false)
      _text.Write(os);
   else
      {
      ZStr sSearchable;
      size_t whence     = NULL;
      size_t sz_found   = NULL;
      size_t count      = NULL;
      size_t sanity     = NULL;
      size_t lines      = NULL;
      while(sz_found != NPOS)
         {
         sz_found = _text.Find('\n', whence);
         // Detect a size_t overflow;
         if(sz_found < sanity)
            sz_found = NPOS;
         else
            sanity = sz_found;
         if(sz_found == NPOS)
            {
            os << TERMINATE;
            os << sSearchable.c_str();
            continue;
            }

         sSearchable = _text.Substr(whence, sz_found - whence);
         whence = sz_found +1;
         Cleanup(sSearchable);
         if( (sSearchable.Length() > 60) && (sSearchable.Find(' ') == false) )
            {
            // Crude, but universal hex-encoded attachment detection;
            count++;
            if(count >= 15)
               {
               sz_found = NPOS;     // bye!
               continue;
               }
            }
         else
            count = NULL;

         // Write-out the string;
         lines++;
         os << TERMINATE;
         os << sSearchable.c_str();
         } // ewhile
      } // if mime

   os << TERMINATE;
#endif
   return os;
   }
istream& EMail::Read(istream& is)
   {
   EMailHeader::Read(is);
   _text.ReadStream(is);
   return is;
   }

