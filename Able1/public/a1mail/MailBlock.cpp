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

#include "EMail.hpp"

using namespace BetterMail;

bool MailBlock::IsNull(void)
   {
   if(!aBody.Nelem() && !aHeader.Nelem()) return true;
   return false;
   }

// Finally, MODE IS GUARANTEED, so we can do THIS;
bool MailBlock::IsEndOfHeader(const ZStr& strLine, bool bStrict)
   {
   if(bStrict)
      {
      if(strLine == "\r\n")    return true;     // Strict RFC defintion
      return false;
      }
   if(strLine.IsNull())       return true;     // Text Read
   if(strLine == "\r\n")       return true;     // In-namespace Format (TERMINATE)
   if(strLine == "\r")         return true;     // Binary Read
   return false;
   }

bool MailBlock::IsEndOfMessage(const ZStr& strLine, bool bStrict)
   {
   if(bStrict)
      {
      if(strLine == ".\r\n")    return true;    // Strict RFC defintion
      return false;
      }
   if(strLine[0] == '.')
      {
      if(strLine.Length() == 1) return true;    // Text Read
      if(strLine == ".\r\n")    return true;    // In-namespace Format (TERMINATE)
      if(strLine == ".\r")      return true;    // Binary Read
      }
   return false;
   }

void MailBlock::RmLineEnds(ZStr& str)
   {
   str.Strip(ZStr::Trailing, '\n');
   str.Strip(ZStr::Trailing, '\r');
   }

void MailBlock::Cleanup(ZStr& str)
   {
   str.Strip();
   RmLineEnds(str);
   }

void MailBlock::ParseFirstNwsBlock(istream& is, Array<ZStr>& aResult)
   {
   aResult.Empty();
   aResult.AddZombies(24);
   ZStr sLine, sTest;
   while(is)
      {
      sLine.Readline(is);
      sTest = sLine;
      Cleanup(sTest);
      if(IsEndOfHeader(sTest))
         return;
      if(IsEndOfMessage(sTest))
         {
         if(aResult.Nelem())
            return;
         continue;
         }
      aResult.Append(sLine);
      }
   }

MailBlock MailBlock::Parse(const File& file)
   {
   File fff = file;
   return Parse(fff.OpenRead());
   }

MailBlock MailBlock::Parse(istream& is)
   {
   MailBlock mb;
   ParseFirstNwsBlock(is, mb.aHeader);
   ParseFirstNwsBlock(is, mb.aBody);
   return mb;
   }

void MailBlock::WriteBlockOnly(ostream& os, const Array<ZStr>& array)
   {
   ZStr sFixit;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      array.At(ss, sFixit);
      os << sFixit << TERMINATE;
      }
   }

void MailBlock::WriteRfcBlock(ostream& os, const Array<ZStr>& array)
   {
   WriteBlockOnly(os, array);
   os << TERMINATE;
   }

void MailBlock::Compose(ostream& os, const MailBlock& mb)
   {
   WriteBlockOnly(os, mb.aHeader);
   WriteBlockOnly(os, mb.aBody);
   }

bool MailBlock::Unfold(Array<ZStr>& amb)
   {
   bool bUnfolded = false;
   size_t ss = 0L;
   ZStr sFixit;
   for(ss = 0L; ss < amb.Nelem(); ss++)
      {
      amb.At(ss, sFixit);
      sFixit.MkWhite();        // Microsof loves to put a lot of junk here -
      if(sFixit[0] == ' ')
         {
         if(ss)
            {
            bUnfolded = true;
            sFixit.Strip();    // Microsof loves to put a lot of junk here -
            amb[ss-1] += " ";
            amb[ss-1] += sFixit;
            amb[ss] = ZStr();
            }
         }
      }
   if(bUnfolded)
      {
      Array<ZStr> array;
      array.AddZombies(amb.Nelem());
      for(size_t ss = 0L; ss < amb.Nelem(); ss++)
         {
         amb.At(ss, sFixit);
         if(sFixit.IsNull() == false)
            array.Append(sFixit);
         }
      amb = array;
      }
   return bUnfolded;
   }

bool MailBlock::Unfold(MailBlock& mb)
   {
   return Unfold(mb.aHeader);
   }

MailBlock MailBlock::Parse(const ZStr& str)
   {
   stringstream srm;
   srm << str;
   srm << ends;
   return Parse(srm);
   }

void MailBlock::Compose(ZStr& str, const MailBlock& mb)
   {
   stringstream srm;
   Compose(srm, mb);
   str = srm.str().c_str();
   }

void MailBlock::WriteBlockOnly(ZStr& sResult, const Array<ZStr>& array)
   {
   stringstream srm;
   WriteBlockOnly(srm, array);
   sResult = srm.str().c_str();
   }

void MailBlock::WriteRfcBlock(ZStr& sResult, const Array<ZStr>& array)
   {
   stringstream srm;
   WriteRfcBlock(srm, array);
   sResult = srm.str().c_str();
   }
