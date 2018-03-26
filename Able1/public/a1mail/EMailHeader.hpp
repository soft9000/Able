// Class EMailHeader: Re-Write of InternetMessage to allow for a less time-consuming
// retreval once stored. Use InternetMessage if you want to keep the EMail intact on-the-disk,
// storing only a header and a reference to the same. Use EMail if you want to IMPORT a file
// or buffer into an internalized, non-flat-file, non-redundantly parsed, object.
//
// (InternetMessage) 07/24/1996, Written on NSB Sabatical, R. Nagy
// (InternetMessage) 03/15/1997, Changed Path() to InternetPath(), R. Nagy
// (InternetMessage) 01/06/1998, Converted over to ZStr(), R. Nagy
//
// 01/06/1997, Porting over to EMailHeader.
//    Changed metaphore so as to allow HyperRfc better parsing and storage capabilities, R. Nagy
//    Streams changed to save-out the entire message (not just the file name of same).
//    Rewrote and greatly sped-up the Parse()r.
//    Wrote EMail && related Parse()r.
// 01/07/1998, Added newlines and member functions to EMail proper, R. Nagy
//    Added final seekg() on EMailHeader::Parse()r exit routines.
// 01/18/1998, Added MessageID() support, R. Nagy
// 01/31/1998, Added Export(), R. Nagy.
// 10/24/1998, Ran through NOTAB, R. Nagy
// 04/19/1999, Re-wrote Export() and Dump() to support RFC "normal" formatting. RFC "normal" (\r\n)
//   is NOW the default output format, but older format (\n) will still be accepted on INput.
//   Fixed RFC `BUG`: Trapping of ';' on output of _unknown_headers caused MIME recognition failure!
//   (broke hook-up with Microsoft's .EML / .NWS Reader), R. Nagy
// 04/24/1999, Added EMailHeader::MkLocalName(), R. Nagy
// 04/30/1999, Added EMail::First / NextMessageLine(ZStr&) to support article posting, R. Nagy
//             Added EMailModifier class, R. Nagy
//
// 06/15/1999: Added _pop3_server_id (a transient value), R. Nagy
// 06/19/1999: Added ReturnAddress(), R. Nagy
// 10/02/1999: Added ARTRENAME(...), R. Nagy
// 11/22/1999: Added IsAddressSeparator(). Updated ReturnAddress(), R. Nagy
// 11/23/1999: Re-wrote EMailHeader::Parse() logic, R. Nagy
// 11/25/1999: Added Encode/DecodeDots(), R. Nagy
// 03/29/2000: Added RemoveTerminalDot(void), R. Nagy
// 06/03/2000: Added IsNull(), Write_mime_headers(), RfcOverWrite(),
//             HasMessagePayload(), and Destroy(), R. Nagy
// 03/10/2001: Tightened-up the EMailHeader by adding and re-using AbsEmailAddress, R. Nagy
// 03/10/2002: Fixed slow-Read of eamil under Borland due to !binary mode on header stream Read forcing Read of entire file, R. Nagy
// 05/29/2002: Replaced IsTerminal() with two verisons to fix bug (Noticed was causing HyperNest1 not to Read lines containing "unsubscribe" info), R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
// 06/17/2004: Changed obsolete Import/Export by "const char *" over to "File&", R. Nagy
//             Changed LocalNameAssigned to IsLocalNameAssigned, R. Nagy
//             Added SaveBin/LoadBin for the File type, R. Nagy
// 11/03/2006: Enhancing MIME Support, R. Nagy
// 11/22/2006: Added ablity to update header fields, R. Nagy
// 01/26/2008: rfc_Read() - needed to remove OLD values on re-use (re-init), R. Nagy
/*
Path: ix.netcom.com!ix.netcom.com!ixnews1.ix.netcom.com!howland.reston.ans.net!newsfeed.internetmci.com!news.sprintlink.net!gryphon.phoenix.net!usenet
From: Rusty Alderson <cessna@phoenix.net>
Newsgroups: misc.jobs.offerred,misc.jobs.offered,fl.jobs,comp.lang.c++
Subject: Re: $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++
Date: Wed, 24 Apr 96 14:47:03 PDT
*/

#ifndef EMailHeader_hpx
#define EMailHeader_hpx

#include <Able1.hpp>
using namespace Able1;

namespace BetterMail {

class EMailMessage;

class EMailHeader
   {
   private:
      long spParseLast;
      // Parising and dumping are for buffers (disk or otherwize) r private to
      // better manage newline cooking;
      bool   Parse(ifstream& ifs);
      bool   Parse(stringstream& srm)         {return rfc_Read(srm);}

   protected:
      ZStr _epath;
      ZStr _newsg;
      ZStr _messageid;
      ZStr _to;
      ZStr _from;
      ZStr _subject;
      ZStr _date;
      ZStr _unknown_headers;
      ZStr _ctype, _cbound;
      ZStr _mime_ver;

      // If you dare to use these, you simply *MUST* make sure that your
      // stream is in BINARY MODE since \r\n is by definition what TERMINATE is!!
      virtual ostream& WriteStream(ostream& os) const;  // NATIVE
      virtual istream& ReadStream(istream& is);         // NATIVE
      virtual bool     rfc_Read(istream& ifs);           // RFC
      virtual bool     rfc_Write(ostream& ofs) const;    // RFC

   public:
      EMailHeader(void);
      EMailHeader(const EMailHeader&);
      virtual ~EMailHeader(void)             {}

      virtual bool      IsNull(void)     const;

      // The server assigns a message ID - Ergo when one is absent we are an "outbound" message
      virtual int       IsOutbound(void) const {return _messageid.IsNull();}

      bool              ReturnAddress(ZStr&) const;

      // This does an Export by over-writing any file-name. If no file name exists,
      // then a "ProgramId-style" temp file name is used;
      bool              RfcOverWrite(EMailMessage& email);
      bool              IsMime(void) const {if(_mime_ver.IsNull()) return false; return true;}

      const char *From(void)         const   {return _from.c_str();     }
      const char *To(void)           const   {return _to.c_str();       }
      const char *Date(void)         const   {return _date.c_str();     }
      const char *Subject(void)      const   {return _subject.c_str();  }
      const char *InternetPath(void) const   {return _epath.c_str();    }
      const char *Newsgroups(void)   const   {return _newsg.c_str();    }
      const char *MessageID(void)    const   {return _messageid.c_str();}
      const char *ContentType(void)  const   {return _ctype.c_str();    }
      const char *ContentBoundary(void)const {return _cbound.c_str();    }
      const char *MimeVersion(void)  const   {return _mime_ver.c_str(); }

      // Rite now it is gigo - Later we will validate -
      bool From(const ZStr& str)           {_from = str; return true;     }
      bool To(const ZStr& str)             {_to = str; return true;       }
      bool Date(const ZStr& str)           {_date = str; return true;     }
      bool Subject(const ZStr& str)        {_subject = str; return true;  }
      bool InternetPath(const ZStr& str)   {_epath = str; return true;    }
      bool Newsgroups(const ZStr& str)     {_newsg = str; return true;    }
      bool MessageID(const ZStr& str)      {_messageid = str; return true;}
      bool ContentType(const ZStr& str)    {_ctype = str; return true;    }
      bool MimeVersion(const ZStr& str)    {_mime_ver = str; return true; }

      void QueryHeader(Array<ZStr>& aLines);

      int          operator==(const EMailHeader&) const;
      EMailHeader& operator=(const EMailHeader&);

      ostream& Write(ostream& os) const         {return WriteStream(os);}
      istream& Read(istream& is)                {return ReadStream(is);}

      // Streamable (array compatible) format
      bool Load(const File& file);
      bool Save(const File& file) const;

      // RFC Format - one per file
      bool Import(const File& file);
      bool Export(const File& file) const;

      static ZStr Boundary(const ZStr& sLine);

   friend class EMailAND;
   friend class EMailOR;
   friend class EMailFactory;
   friend class EMailModifier;
   friend class Rfc977NewsGroupServer;
   };


   }

#endif

