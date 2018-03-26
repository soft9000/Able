// 10/24/1998, Ran through NOTAB, R. Nagy
//

#include <a1mail/EMail.hpp>
using namespace BetterMail;

#define BEGIN {
#define END }


void AssignOrAppend(ZStr& subj, const char *psz)
   {
   ZStr str2 = psz;
   MailBlock::Cleanup(str2);
   if(subj == "")
     subj.Assign(str2);
   else
     {
     subj.Append(TERMINATE);
     subj.Append(str2.c_str());
     }
   }


EMailHeader::EMailHeader(void)
   {
   }

EMailHeader::EMailHeader(const EMailHeader& im)
   {
   (*this) = im;
   }
bool EMailHeader::IsNull(void) const
   {
   if(_to.IsNull() && _from.IsNull() && _subject.IsNull())
      return true;
   return false;
   }
bool EMailHeader::Load(const File& file)               
   {
   File fff = file; 
   istream& is = ReadStream(fff.OpenRead(File::AT_BINARY));
   if(is)
      return true;
   return true;
   }
bool EMailHeader::Save(const File& file) const         
   {
   File fff = file; 
   ostream& os = WriteStream(fff.OpenWrite(File::AT_BINARY));
   if(os)
      return true;
   return false;
   }

// RFC Format - one per file
bool EMailHeader::Import(const File& file)             
   {
   File fff = file; 
   return rfc_Read(fff.OpenRead(File::AT_BINARY));
   }
bool EMailHeader::Export(const File& file) const       
   {
   File fff = file; 
   return rfc_Write(fff.OpenWrite(File::AT_BINARY));
   }
bool EMailHeader::ReturnAddress(ZStr& str) const
   {
   // Example;
   //    "From: Rusty Alderson <cessna@phoenix.net>"
   str = From();
   return EMailFactory::AbsEmailAddress(str);
   }

bool EMailHeader::rfc_Write(ostream& ofs) const
   {
   // Write-out the article:
   ZStr str;
   str = InternetPath();
   if(!str.IsNull())
      ofs << "Path: "         << str    << TERMINATE;
   str = From();
   if(!str.IsNull())
      ofs << "From: "         << str    << TERMINATE;
   str = To();
   if(!str.IsNull())
      ofs << "To: "           << str    << TERMINATE;
   str = Newsgroups();
   if(!str.IsNull())
      ofs << "Newsgroups: "   << str    << TERMINATE;

   str = Subject();
   if(!str.IsNull())
      ofs << "Subject: "      << str    << TERMINATE;

   str = Date();
   if(!str.IsNull())
      ofs << "Date: "         << str    << TERMINATE;
   str = MessageID();
   if(!str.IsNull())
      ofs << "Message-ID: "    << str    << TERMINATE;

   if(IsMime())
      {
      str = MimeVersion();
      if(!str.IsNull())
         ofs << "MIME-Version: "  << str    << TERMINATE;
      str =  ContentType();
      if(!str.IsNull())
         {
         ofs << "Content-Type: "  << str;
         str = ContentBoundary();
         if(!str.IsNull())
            {
            ofs << " boundary=\"";
            ofs << str;
            ofs << "\"";
            }
         ofs << TERMINATE;
         }
      }
   else
      {
      str =  ContentType();
      if(!str.IsNull())
         {
         ofs << "Content-Type: "  << str;
         ofs << TERMINATE;
         }
      }

   if(!_unknown_headers.IsNull())
      ofs << _unknown_headers.c_str()    << TERMINATE;

   return true;
   }

bool EMailHeader::Parse(ifstream& ifs)
   {
   bool br = rfc_Read(ifs);
   return br;
   }

bool EMailHeader::rfc_Read(istream& ifs)
   {
   (*this) = EMailHeader();
   bool bParsed = false;

   Array<ZStr> aHeader;
   MailBlock::ParseFirstNwsBlock(ifs, aHeader);
   MailBlock::Unfold(aHeader);

   ZStr strLine;
   for(size_t ss = 0L; ss < aHeader.Nelem(); ss++)
      {
      aHeader.At(ss, strLine);
      size_t whence = strLine.Find(':');
      if(whence != NPOS)
         {
         // Parse the headers -
         ZStr sToken = strLine.Substr(0, whence+1);
         if(sToken == "To:")
            {
            AssignOrAppend(_to, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_date == "" && (sToken == "Date:"))
            {
            AssignOrAppend(_date, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_from == "" && (sToken == "From:"))
            {
            AssignOrAppend(_from, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_subject == "" && (sToken == "Subject:"))
            {
            AssignOrAppend(_subject, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_epath == "" && (sToken == "Path:"))
            {
            AssignOrAppend(_epath, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_newsg == "" && (sToken == "Newsgroups:"))
            {
            AssignOrAppend(_newsg, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_messageid == "" && (sToken == "Message-ID:"))
            {
            AssignOrAppend(_messageid, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_ctype == "" && (sToken == "Content-Type:"))
            {
            ZStr str = Boundary(strLine);
            if(!str.IsNull())
               AssignOrAppend(_cbound, &str[0]);
            AssignOrAppend(_ctype, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_mime_ver == "" && (sToken == "Mime-Version:"))
            {
            AssignOrAppend(_mime_ver, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         if(_mime_ver == "" && (sToken == "MIME-Version:"))
            {
            AssignOrAppend(_mime_ver, &strLine[whence+1]);
            bParsed = true;
            continue;
            }
         }
         // We are not collecting this header yet, so we just put it into;
         AssignOrAppend(_unknown_headers, &strLine[0]);
      }
   return bParsed;
   }

ostream& EMailHeader::WriteStream(ostream& os) const 
   {
   _epath.WriteStream(os);
   _newsg.WriteStream(os);
   _messageid.WriteStream(os);
   _to.WriteStream(os);
   _from.WriteStream(os);
   _subject.WriteStream(os);
   _date.WriteStream(os);
   _unknown_headers.WriteStream(os);
   return os;
   }

istream& EMailHeader::ReadStream(istream& is)
   {
   _epath.ReadStream(is);
   _newsg.ReadStream(is);
   _messageid.ReadStream(is);
   _to.ReadStream(is);
   _from.ReadStream(is);
   _subject.ReadStream(is);
   _date.ReadStream(is);
   _unknown_headers.ReadStream(is);
   return is;
   }

int EMailHeader::operator==(const EMailHeader& im) const
   {
   if(_messageid.IsNull() == false)
      {
      if(im._messageid  == _messageid)
         return 1;
      }
   if((im._date      == _date) &&
      (im._from      == _from) &&
      (im._subject   == _subject) &&
      (im._to        == _to))
      return 1;
   return 0;
   }
EMailHeader& EMailHeader::operator=(const EMailHeader& im)
   {
   if(this == &im)
      return *this;
   _epath      = im._epath;
   _from       = im._from;
   _newsg      = im._newsg;
   _messageid  = im._messageid;
   _subject    = im._subject;
   _date       = im._date;
   _to         = im._to;
   _ctype      = im._ctype;
   _cbound     = im._cbound;
   _mime_ver   = im._mime_ver;
   _unknown_headers = im._unknown_headers;      // 5/30/2002 (yikes!)
   return *this;
   }

void EMailHeader::QueryHeader(Array<ZStr>& aLines)
   {
   stringstream srm;
   EMailHeader::rfc_Write(srm);
   ZStr sLine = srm.str().c_str();
   sLine.Replace("\r\n", 0xfe);
   sLine.Split(0xfe, aLines);
   }

ZStr EMailHeader::Boundary(const ZStr& sLine)
   {
   ZStr str = sLine;
   str.MkWhite();
   ZStr sToken = "boundary=";
   size_t pos = str.Find(sToken);
   if(pos != npos)
      {
      str.RemovePos(0, pos + sToken.Length());
      str.Replace('\"', ' ');
      str.Strip();
      return str;
      }
   sToken = "boundary";
   pos = str.Find(sToken);
   if(pos != npos)
      {
      str.RemovePos(0, pos + sToken.Length());
      pos = str.Find('=');
      if(pos != npos)
         {
         str.RemovePos(0, pos);
         str.Replace('\"', ' ');
         str.Strip();
         return str;
         }
      }
   str = "";
   return str;
   }

