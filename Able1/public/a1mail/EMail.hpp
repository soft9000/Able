// Class EMailHeader: Re-Write of InternetMessage to allow for a less time-consuming
// retreval once stored. Use InternetMessage if you want to keep the EMailMessage intact on-the-disk,
// storing only a header and a reference to the same. Use EMailMessage if you want to IMPORT a file
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
//    Wrote EMailMessage && related Parse()r.
// 01/07/1998, Added newlines and member functions to EMailMessage proper, R. Nagy
//    Added final seekg() on EMailHeader::Parse()r exit routines.
// 01/18/1998, Added MessageID() support, R. Nagy
// 01/31/1998, Added Export(), R. Nagy.
// 10/24/1998, Ran through NOTAB, R. Nagy
// 04/19/1999, Re-wrote Export() and Dump() to support RFC "normal" formatting. RFC "normal" (\r\n)
//   is NOW the default output format, but older format (\n) will still be accepted on INput.
//   Fixed RFC `BUG`: Trapping of ';' on output of _unknown_headers caused MIME recognition failure!
//   (broke hook-up with Microsoft's .EML / .NWS Reader), R. Nagy
// 04/24/1999, Added EMailHeader::MkLocalName(), R. Nagy
// 04/30/1999, Added EMailMessage::First / NextMessageLine(ZStr&) to support article posting, R. Nagy
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

#ifndef EMailProper_hpx
#define EMailProper_hpx

#include "EMailAddress.hpp"
#include "MailBlock.hpp"
#include "RoutingSlip.hpp"
#include "EMailHeader.hpp"
#include "EMailMessage.hpp"
#include "EMailFactory.hpp"

namespace BetterMail {

class EMailAND;
class EMailOR;

// What the mail RFCs expect;
#define TERMINATE "\r\n"

}

#endif

