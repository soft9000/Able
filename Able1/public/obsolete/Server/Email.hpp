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

#ifndef z_EMailProper
#define z_EMailProper

#include <Able1.hpp>
using namespace Able1;

class EMailHeader;
class EMail;

class EMailAND;
class EMailOR;

ZStr ARTNAME(const char *pszDir, EMail& em, const ZStr& sExtension);
ZStr ARTNAME(Directory& dir, EMail& em, const ZStr& sExtension);

// This function assumes that there is a _local_name (i.e: That the file has been "imported");
bool      ARTRENAME(EMailHeader& em, const ZStr& sExtension, bool bDeleteOriginalFile = false);

#include "RoutingSlip.hpp"
#include "EMailHeader.hpp"

class EMail : public EMailHeader
   {
   private:
      size_t      _ff_marker;
      size_t      _pop3_server_id;

   protected:
      ZStr   _text;

      // If you dare to use these, you simply *MUST* make sure that your
      // stream is in BINARY MODE since \r\n is by definition what TERMINATE is!!
      bool      rfc_Read(istream& ifs);           // Rfc822 format (HEADER AND BODY)
      bool      rfc_Write(ostream& ofs) const;    // Rfc822 format
      bool      rfc_message(istream& ifs);        // Rfc822 format (BODY ONLY)

   public:
      EMail(void)            : _ff_marker(NULL), _pop3_server_id(NULL) {}
      EMail(const EMail& em) : _ff_marker(NULL), _pop3_server_id(NULL) {(*this) = em;}
      virtual ~EMail(void)  {}

      bool      IsNull(void)   const;

#ifdef __BCPLUSPLUS__
      bool              MessagePayloadBinaryONLY(ifstream& ifs);   // Rfc822 format (BODY ONLY)
      bool              ParseMessageBinaryONLY(ifstream& is)  {return MessagePayloadBinaryONLY(is);}
#else
      bool              MessagePayload(ifstream& ifs);   // Rfc822 format (BODY ONLY)
      bool              ParseMessage(ifstream& is)  {return MessagePayload(is);}
#endif
      bool              MessagePayload(stringstream& ifs);  // Rfc822 format (BODY ONLY)
      virtual bool      MessagePayload(const File& ifs); // Now, only RFC ASCII... but later, who knowns?

      // A little better documentation;
      bool              ParseMessage(stringstream& is)      {return MessagePayload(is);}
      bool              ParseMessage(const File& is)     {return MessagePayload(is);}

      bool              SaveBin(const ZStr& sFileName);      // binary format
      bool              LoadBin(const ZStr& sFileName);      // binary format
      bool              SaveBin(const File&);      // binary format
      bool              LoadBin(const File&);      // binary format

      bool              HasMessage(void) const;
      const char *      Message(void) const        {return _text.c_str();}
      void              Message(const char *pMsg)  {_text.assign(pMsg);}

      virtual bool      FirstMessageLine(ZStr&);
      virtual bool      NextMessageLine(ZStr&);

      bool              RemoveTerminalDot(void);
      void              EncodeDots(void);
      void              DecodeDots(void);

      int               operator==(const EMail& em) const;
      EMail&            operator=(const EMail& em);

      ostream&  Write_searchable(ostream& os);
      ostream&  Write(ostream& os);                       // binary format
      istream&  Read(istream& is);                        // binary format

   friend class EMailAND;
   friend class EMailOR;
   friend class OutBoundEmail;
   friend class EMailModifier;
   friend class Pop3Server;
   friend class SmtpServer;
   };

#include "EMailModifier.hpp"
#include "EMailLines.hpp"


const bin_mode = NULL;
inline int SETMODE(ifstream& fs, int mode)  {return mode;}
inline int SETMODE(ofstream& fs, int mode)  {return mode;}
// What the RFC expects;
#define TERMINATE "\r\n"

// Finally, BINARY MODE IS GUARANTEED, so we can do THIS;
inline bool IsEndOfHeader(const ZStr& strLine)
   {
   if(strLine == "\r")
      return true;
   return false;
   }

inline bool IsEndOfMessage(const ZStr& strLine)
   {
   if(strLine[0] == '.' && strLine[1] == '\r')
      return true;
   return false;
   }

inline void Cleanup(ZStr& str2)
   {
   str2.Strip(ZStr::Leading);
   str2.Strip(ZStr::Trailing);
   str2.Strip(ZStr::Trailing, '\n');
   str2.Strip(ZStr::Trailing, '\r');
   }

#endif

