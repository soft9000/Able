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
/*
Path: ix.netcom.com!ix.netcom.com!ixnews1.ix.netcom.com!howland.reston.ans.net!newsfeed.internetmci.com!news.sprintlink.net!gryphon.phoenix.net!usenet
From: Rusty Alderson <cessna@phoenix.net>
Newsgroups: misc.jobs.offerred,misc.jobs.offered,fl.jobs,comp.lang.c++
Subject: Re: $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++ $$$ C++
Date: Wed, 24 Apr 96 14:47:03 PDT
*/

#ifndef z_EMailHeader
#define z_EMailHeader

#include <Able1.hpp>
using namespace Able1;

class EMailHeader
   {
   private:
      long spParseLast;

   protected:
      ZStr _epath;
      ZStr _newsg;
      ZStr _messageid;
      ZStr _to;
      ZStr _from;
      ZStr _subject;
      ZStr _date;
      ZStr _unknown_headers;
      ZStr _ctype;
      ZStr _mime_ver;
      ZStr _local_name;

      void SetLocalName(const ZStr& sName)    {_local_name = sName;}

      // If you dare to use these, you simply *MUST* make sure that your
      // stream is in BINARY MODE since \r\n is by definition what TERMINATE is!!
      virtual bool      rfc_Read(istream& ifs);
      virtual bool      rfc_Write(ostream& ofs) const;
      bool              rfc_Write2(ostream& ofs, int use_subject = 0) const;

   public:
      EMailHeader(void);
      EMailHeader(const EMailHeader&);
      virtual ~EMailHeader(void)             {}

      virtual bool      IsNull(void)                const;
      bool              IsAddressSeparator(char ch) const;

      virtual bool      Destroy(void);    // Completely reclaims disk AND string-space.

      // Importing and exporting are to enumerated file-names to control cooking;
      bool              Import(File& file);
      bool              Import(const ZStr& sfn);
      bool              Export(File& file);
      bool              Export(const ZStr& sfn);

      // This does an Export by over-writing any file-name. If no file name exists,
      // then a "ProgramId-style" temp file name is used;
      bool              RfcOverWrite(EMail& email);

      // Parising and dumping are for buffers (disk or otherwize) to control cooking;
#ifdef __BCPLUSPLUS__
      bool              ParseBinaryONLY(ifstream& ifs);
#else
      bool              Parse(ifstream& ifs);
#endif
      bool              Dump(ofstream& ofs) const;
      bool              Parse(stringstream& srm)         {return rfc_Read(srm);}
      bool              Dump(stringstream& srm) const    {return rfc_Write(srm);}

      virtual bool      IsMessageFile(void)  const;
      virtual bool      IsMime(void)         {if(_mime_ver.IsNull()) return false; return true;}

      // Reduces a single address to just the '@' part;
      bool              AbsEmailAddress(ZStr& std) const;
      bool              AbsEmailAddress(const ZStr& sIn, ZStr& sOut) const;
      bool              ContainsAbsEmailAddress(const ZStr& sIn);
      // Same as AbsEmailAddress(), but returns result with the required <>'s;
      bool              FormatAsAddress(ZStr& std) const;

      // From() is what came to us over Rfc822, the "ReturnAddress() is what we
      // need from a Smtp point of view (they might not be the same!),
      // (e.g: A reply via OutBoundEmail is different, as From() is To(etc))
      // false means that we can not convert the FROM: to anything Smtp-able!
      virtual bool   ReturnAddress(ZStr&) const;


      const char *From(void)         const   {return _from.c_str();     }
      const char *To(void)           const   {return _to.c_str();       }
      const char *Date(void)         const   {return _date.c_str();     }
      const char *Subject(void)      const   {return _subject.c_str();  }
      const char *InternetPath(void) const   {return _epath.c_str();    }
      const char *Newsgroups(void)   const   {return _newsg.c_str();    }
      const char *MessageID(void)    const   {return _messageid.c_str();}
      const char *ContentType(void)  const   {return _ctype.c_str();}
      const char *MimeVersion(void)  const   {return _mime_ver.c_str(); }

      // At the moment, local names are not persistant; You might want to engineer in
      // an "X-NNS-LocalName: " in the header for use later, but it's not important
      // at the moment;
      const char *MkLocalName(ZStr&, bool TryMessageID = true) const;
      const char *GetLocalName(void)        const {return _local_name.c_str();}
      bool        IsLocalNameAssigned(void) const {return (!_local_name.IsNull());}

      int               operator==(const EMailHeader&) const;
      EMailHeader&      operator=(const EMailHeader&);

      // MIME requires special subject line in multi-part mode.
      // This function Writes all headers, sans the "Subject:"
      bool             Write_mime_headers(ostream& os) const;

      virtual ostream& Write(ostream& os);
      virtual istream& Read(istream& is);

   friend class EMailAND;
   friend class EMailOR;
   friend class OutBoundEmail;
   friend class EMailModifier;
   friend ZStr ARTNAME(const char *pszDir, EMail& em, const ZStr& sExtension);
   friend bool      ARTRENAME(EMailHeader& em, const ZStr& sExtension, bool bDeleteOriginalFile);
   };

#endif

