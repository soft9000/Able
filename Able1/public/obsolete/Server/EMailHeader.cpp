// 10/24/1998, Ran through NOTAB, R. Nagy
//

#include "Email.hpp"

#define BEGIN {
#define END }


void ffMkLocalFileName(ZStr& std, bool bSkipPathChar = false)
{
for(size_t ss = NULL; ss < std.Length(); ss++)
   {
   switch(std[ss])
      {
      case '\\':
         if(bSkipPathChar == true)
            continue;
      case ':':
         if((bSkipPathChar == true) && ss == 1)
            continue;
      case '<':
      case '>':
      case '*':
      case '?':
      case '/':
      case '\"':
         std[ss] = '_';
      default:
         continue;
      }
   }
}


inline bool FileExists(const ZStr& str)
   {
   File file;
   file.Name(str);
   return file.Exists();
   }

inline bool CopyFile(const ZStr& sSource, const ZStr& sDest)
   {
   File file;
   file.Name(sSource);
   return file.CopyTo(sDest);
   }

bool ARTRENAME(EMailHeader& em, const ZStr& sExtension, bool bDeleteOriginalFile)
   {
   bool br = false;
   if(em._local_name.IsNull())
      return br;

   ZStr sDir;
   size_t sz = em._local_name.rfind('\\');
   if(sz != NPOS)
      {
      sDir = em._local_name;
      sDir.Remove(sz+1);
      } 

   ZStr sNextName;
   em.MkLocalName(sNextName, false);
   if(sNextName.IsNull())
      return br;

   if(!sDir.IsNull())
      sNextName.Prepend(sDir);

   ZStr sName2;
   unsigned long file_count = NULL;
   do
      {
      stringstream srm;
      srm << sNextName;
      if(file_count)
         {
         srm << '.';
         srm << file_count;
         }

      if(sExtension[0] != '.')
         srm << '.';
      srm << sExtension;

      sName2 = PRESTO(srm);

      file_count++;
      if(!file_count)
         return false;

      if( (em._local_name == sName2) && (bDeleteOriginalFile == false) )
         {
         // The idea here is that we are NOT merely DUPLICATING this file
         // out to a redundant ".000x"-name for itself! (eeeewwwwwh)
         return false;
         }

      } while(FileExists(sName2));

   if(CopyFile(em._local_name, sName2) == false)
      return br;

   br = true;
   if(bDeleteOriginalFile == true)
      {
      File file(em._local_name);
      br = file.Remove();
      }

   em._local_name = sName2;
   return br;
   }
ZStr ARTNAME(Directory& dir, EMail& em, const ZStr& sExtension)
   {
   return ARTNAME(dir.Name(), em, sExtension);
   }
ZStr ARTNAME(const char *pszDir, EMail& em, const ZStr& sExtension)
   {
   /*
   // NO! Re-calculate it each time! An prior Import() use could mess-us up
   // if we defer to it, and we are now re-naming (i.e: You just don't know)!
   ZStr std = em.GetLocalName();
   if(!std.IsNull())
      return std;
   */

   // MkLocalName(std) considers the message-ID first; We
   // want a SUBJECT based opportunity, so we check that, first;
   ZStr std = em.Subject();
   if(std.IsNull() || std.IsSpace())
      em.MkLocalName(std);
   else
      ffMkLocalFileName(std);

   ZStr sRes;
   sRes.assign(pszDir);
   sRes.Append("\\");
   sRes.Append(std.c_str());
   sRes.Append(sExtension.c_str());

   em.SetLocalName(sRes);
   std = em.GetLocalName();         // \:(
   return std;                      // \:(
   }



void AssignOrAppend(ZStr& subj, const char *psz)
   {
   ZStr str2 = psz;
   Cleanup(str2);
   if(subj == "")
     subj.assign(str2);
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
bool EMailHeader::IsAddressSeparator(char ch) const
   {
   switch(ch)
      {
      case '<':
      case '>':
      case ' ':
      case '\t':
      case '\n':
      case '\r':
      case ',':
      case ';':   // Microsoft does this...
         return true;
      }
   return false;
   }
bool EMailHeader::AbsEmailAddress(ZStr& std) const
   {
   // It happens that people have newlines and other unspeakable
   // nasties in their email addresses. Our job is simply to make 
   // the best guess here;
   std.MkWhite();    

   // Okay: Now we can assume a somewhat tangendental reality;
   size_t whence = std.Find('@');
   if(whence == NPOS)
      return false;

   size_t start = whence;
   while(start)
      {
      if(IsAddressSeparator(std[start]) == true)
         {
         start++;
         break;
         }
      start--;
      }
   std = &std[start];   // save start point

   size_t end = std.Find('@');
   while(end < std.Length())
      {
      if(IsAddressSeparator(std[end]) == true)
         {
         std.Remove(end);     // terminate (atypical)
         break;
         }
      end++;
      }
   return true;
   }
bool EMailHeader::ReturnAddress(ZStr& std) const
   {
   // Example;
   //    "From: Rusty Alderson <cessna@phoenix.net>"
   std = From();
   return AbsEmailAddress(std);
   }
bool EMailHeader::FormatAsAddress(ZStr& std) const
   {
   ZStr sHold = std;
   if(AbsEmailAddress(std) == false)
      {
      std = sHold;
      return false;
      }
   if(std.Find('<') == NPOS)     // maintenance
      {
      std.Prepend('<');
      std.Append('>');
      }
   return true;
   }
bool EMailHeader::ContainsAbsEmailAddress(const ZStr& sIn)
   {
   ZStr sOut = sIn;
   return AbsEmailAddress(sOut);
   }
bool EMailHeader::AbsEmailAddress(const ZStr& sIn, ZStr& sOut) const
   {
   sOut = sIn;
   return AbsEmailAddress(sOut);
   /*
   sOut = "";
   ZStr std = sIn;
   std.MkWhite();
   std.Strip();
   size_t which = std.rfind(' ');
   if(which != NPOS)
      {
      std = &std[which+1];
      std.Strip();
      }

   sOut = std;
   if(sOut.Find('@') == NPOS)
      return false;
   if(sOut.Find('.') == NPOS)
      return false;

   return true;
   */
   }
bool EMailHeader::IsMessageFile(void) const
   {
   if(_from.IsNull() && _subject.IsNull() &&  _date.IsNull())
      return false;
   return true;
   }

// If there is a pre-existing file name, we will over-Write it with the contents
// of "EMail". Else, we will create a temp file-name, and Write to that, instead.
bool EMailHeader::Destroy(void)
   {
   // STEP: Blow-away any local file;
   ZStr sFileName = GetLocalName();
   if(!sFileName.IsNull())
      {
      File file;
      if(file.Name(sFileName) == false)
         return false;
      if(file.Remove() == false)
         return false;
      }

   // STEP: Blank us out;
   EMailHeader emh;
   *this = emh;
   return true;
   }

// If there is a pre-existing file name, we will over-Write it with the contents
// of "EMail". Else, we will create a temp file-name, and Write to that, instead.
bool EMailHeader::RfcOverWrite(EMail& email)
   {
   ZStr sFileName = email.GetLocalName();
   File file;
   if(file.MkUniqueName() == false)
      return false;
   if(file.Remove() == false)
      return false;
   return Export(file.Name());
   }

bool EMailHeader::Import(const ZStr& str)
   {
   File file;
   if(file.Name(str) == false)
      return false;
   return Import(file);      
   }

bool EMailHeader::Import(File &file)
   {
   if(!file.Exists())
      return false;

   bool br = rfc_Read(file.OpenRead(File::AT_BINARY));

   // No matter what the result is, this is what we were asked to Read;
   SetLocalName(file.Name());
   return br;
   }

bool EMailHeader::Export(const ZStr& str)
   {
   File file;
   if(file.Name(str) == false)
      return false;
   return Export(file);      
   }

bool EMailHeader::Export(File& file)
   {
   /*
Path: ix.netcom.com!ix.netcom.com!ixnews1.ix.netcom.com!howland.reston.ans.net!newsfeed.internetmci.com!news.sprintlink.net!gryphon.phoenix.net!usenet
From: Rusty Alderson <cessna@phoenix.net>
Newsgroups: misc.jobs.offerred,misc.jobs.offered,fl.jobs,comp.lang.c++
Subject: Re: $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++
Date: Wed, 24 Apr 96 14:47:03 PDT
   */
   if(file.Exists() == true)
      return false;

   SetLocalName(file.Name());

   return rfc_Write( file.OpenWrite(File::AT_BINARY) );
   }

bool EMailHeader::Dump(ofstream& ofs) const
   {
   int omode = SETMODE(ofs, bin_mode);
   bool br = rfc_Write(ofs);
   SETMODE(ofs, omode);
   return br;
   }

bool EMailHeader::Write_mime_headers(ostream& os) const
   {
   // When using MIME, we cannot Write the header until
   // we know how many PARTS we have, attachment type (etc).
   return rfc_Write2(os, 0);
   }
bool EMailHeader::rfc_Write(ostream& ofs) const
   {
   return rfc_Write2(ofs, 1);
   }
bool EMailHeader::rfc_Write2(ostream& ofs, int use_subject) const
   {
   // Write-out the article:
   ZStr std;
   std = InternetPath();
   if(!std.IsNull())
      ofs << "Path: "         << std    << TERMINATE;
   std = From();
   if(!std.IsNull())
      ofs << "From: "         << std    << TERMINATE;
   std = To();
   if(!std.IsNull())
      ofs << "To: "           << std    << TERMINATE;
   std = Newsgroups();
   if(!std.IsNull())
      ofs << "Newsgroups: "   << std    << TERMINATE;
if(use_subject)
   {
   std = Subject();
   if(!std.IsNull())
      ofs << "Subject: "      << std    << TERMINATE;
   }
   std = Date();
   if(!std.IsNull())
      ofs << "Date: "         << std    << TERMINATE;
   std = MessageID();
   if(!std.IsNull())
      ofs << "Message-ID: "    << std    << TERMINATE;
   std = ContentType();
   if(!std.IsNull())
      ofs << "Content-Type: "  << std    << TERMINATE;
   std = MimeVersion();
   if(!std.IsNull())
      ofs << "MIME-Version: "  << std    << TERMINATE;

   if(!_unknown_headers.IsNull())
      ofs << _unknown_headers.c_str()    << TERMINATE;

   return true;
   }

#ifdef __BCPLUSPLUS__
bool EMailHeader::ParseBinaryONLY(ifstream& ifs)
#else
bool EMailHeader::Parse(ifstream& ifs)
#endif
   {
   int omode = SETMODE(ifs, bin_mode);
   bool br = rfc_Read(ifs);
   SETMODE(ifs, omode);
   return br;
   }

bool EMailHeader::rfc_Read(istream& ifs)
   {
   BEGIN
   EMailHeader emh;
   *this = emh;
   END
   if(!ifs.good())
      return false;

   ZStr *pLastWrite = &_unknown_headers;

   int   parsing       = NULL;
   ZStr strLine;

   int done = 0;
   int times = NULL;

   while((!ifs.eof()) && ifs && ifs.good())
      {
      if(done)
         break;

      // Get the line;
      strLine = "";
      strLine.Readline(ifs);

	  // Finally, BINARY MODE IS GUARANTEED, so we can do THIS;
      if(IsEndOfHeader(strLine))
         {
         // Usual terminal condition;
		   done = 1;
		   continue;
         }
      if(!ifs || ifs.eof())
         {
         // UNusual terminal condition, but possible (eg: HEADER-ONLY PARSING)
         done = 1;
         continue;
         }
      if(strLine.IsNull())  // This is what the STREAMS BUG in VC++ looks like.
         {					 //  You need to re-install BOTH Visual C++ 5.0 and NTSP 4.0.
         // UNusual terminal condition;
         if(parsing)
            done = 1;
         continue;
         }
      if(strLine[0] == '\t')
         {
         AssignOrAppend(*pLastWrite, &strLine[1]);
         continue;
         }

      size_t whence = strLine.Find(':');
      if(whence == NPOS)
         {
         // Ensure that ";" parameters (such as boundary=)
         // are parsed properly... For example, for _ctype
         // Microsoft Outlook prefixes same with \r\n\t
         if(strLine.Find("boundary=") != npos)
            {
            if(!_ctype.IsNull())
               {
               strLine.MkWhite();
               strLine.Strip();
               _ctype.MkWhite();
               _ctype.Strip();
               if(_ctype.Find(';') != _ctype.Length() - 1)
                  _ctype.Append(';');
               _ctype.Append(strLine);
               continue;
               }
            }
         // Microsoft ignores RFC's;
         AssignOrAppend(_unknown_headers, &strLine[0]);
         continue;
         }
      else
         {
         // Parse the headers;
         ZStr str = strLine.Substr(0, whence+1);
         if(str == "To:")
            {
            AssignOrAppend(_to, &strLine[whence+1]);
            pLastWrite = &_to;
            parsing = 1;
            continue;
            }
         if(_date == "" && (str == "Date:"))
            {
            AssignOrAppend(_date, &strLine[whence+1]);
            pLastWrite = &_date;
            parsing = 1;
            continue;
            }
         if(_from == "" && (str == "From:"))
            {
            AssignOrAppend(_from, &strLine[whence+1]);
            pLastWrite = &_from;
            parsing = 1;
            continue;
            }
         if(_subject == "" && (str == "Subject:"))
            {
            AssignOrAppend(_subject, &strLine[whence+1]);
            pLastWrite = &_subject;
            parsing = 1;
            continue;
            }
         if(_epath == "" && (str == "Path:"))
            {
            AssignOrAppend(_epath, &strLine[whence+1]);
            pLastWrite = &_epath;
            parsing = 1;
            continue;
            }
         if(_newsg == "" && (str == "Newsgroups:"))
            {
            AssignOrAppend(_newsg, &strLine[whence+1]);
            pLastWrite = &_newsg;
            parsing = 1;
            continue;
            }
         if(_messageid == "" && (str == "Message-ID:"))
            {
            AssignOrAppend(_messageid, &strLine[whence+1]);
            pLastWrite = &_messageid;
            parsing = 1;
            continue;
            }
         if(_ctype == "" && (str == "Content-Type:"))
            {
            AssignOrAppend(_ctype, &strLine[whence+1]);
            pLastWrite = &_ctype;
            parsing = 1;
            continue;
            }
         if(_mime_ver == "" && (str == "Mime-Version:"))
            {
            AssignOrAppend(_mime_ver, &strLine[whence+1]);
            pLastWrite = &_mime_ver;
            parsing = 1;
            continue;
            }
         if(_mime_ver == "" && (str == "MIME-Version:"))
            {
            AssignOrAppend(_mime_ver, &strLine[whence+1]);
            pLastWrite = &_mime_ver;
            parsing = 1;
            continue;
            }
         }

         // DEFAULT:
         // We are not interested in the header, so we just put it into;
         AssignOrAppend(_unknown_headers, &strLine[0]);
         pLastWrite = &_unknown_headers;
      } // ewhile

   if(!parsing)
      return false;

   return true;
   }

ostream& EMailHeader::Write(ostream& os)
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

istream& EMailHeader::Read(istream& is)
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
   _local_name = im._local_name;
   _epath      = im._epath;
   _from       = im._from;
   _newsg      = im._newsg;
   _messageid  = im._messageid;
   _subject    = im._subject;
   _date       = im._date;
   _to         = im._to;
   _ctype      = im._ctype;
   _mime_ver   = im._mime_ver;
   _unknown_headers = im._unknown_headers;      // 5/30/2002 (yikes!)
   return *this;
   }

   const char *EMailHeader::MkLocalName(ZStr& std, bool TryMessageID) const
   {
   std = "";

   if(TryMessageID)
      std = MessageID();      // THIS IS OUR LEGACY. USED TO BE THE DEFAULT.

   if(std.IsNull() || (std.Length() <= 2))
      {
      std = Subject();
      if(std.IsNull() || std.IsSpace())
         {
         ZStr scmp;
         std = "Posetd on ";
         scmp = Date();
         if(scmp.IsNull())
            std.Append("unknown date");
         else
            std.Append(scmp);
         std.Append(" from ");
         scmp = From();
         if(scmp.IsNull())
            {
            // This may look nuts, but it happens!
            scmp = InternetPath();
            if(scmp.IsNull() || scmp.IsSpace())
               std.Append("unknown source");
            else
               std.Append(scmp);
            }
         else
            std.Append(scmp);
         }
      }

   ffMkLocalFileName(std);

   return std.c_str();
   }

