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
// 12/23/2006: Built a class around the functions used to detect RFC message headers, bodies, and terminal conditions for re-use by MimeBlock, R. Nagy
// 01/13/2008: Added Parse(const File), R. Nagy
//

#ifndef MailBlock_hpx
#define MailBlock_hpx

namespace BetterMail {

// No matter what the line ending, this class will break a header away
// from any newline-seperated stream - The first block of strings is
// an array of newline terminated HEADER, followed by a newline, then
// followed by a newline terminated set of BODY lines, then a newline
// or a single "." line. While \n is okay, this class will handle either
// that, the REF MESSAGE TERMINATE set, or an EOS. While extracted, no
// stream, RFC, or block terminal conditions are placed into the result
// arrays.
//
// On streams: Binary or text mode, no problem. All this class needs is
// something Readline() understands.
//
struct MailBlock
   {
   Array<ZStr> aHeader;
   Array<ZStr> aBody;

   ostream& Write(ostream& os)
      {
      aHeader.Write(os);
      aBody.Write(os);
      return os;
      }

   istream& Read(istream& is)
      {
      aHeader.Read(is);
      aBody.Read(is);
      return is;
      }

   bool IsNull(void);

   // This keystone member will parse until it encounters a series
   // of non-white-space (NWS) lines. Once found, it returns AFTER
   // it encounters an empty line, a line with a . (RFC Message
   // Terminator), or an EOF.
   //
   // NOTE: While extracted from the stream, none of the terminal
   // condition (newling, RFC Message Terminate, nor EOF) is
   // represented in the resulting array.
   static void ParseFirstNwsBlock(istream& is, Array<ZStr>& aResult);

   // Write each line in the array with a TERMINATE
   static void WriteBlockOnly(ostream& os, const Array<ZStr>& array);
   static void WriteBlockOnly(ZStr& sResult, const Array<ZStr>& array);

   // Same as WriteBlockOnly, but adds a closing TERMINATE
   static void WriteRfcBlock(ostream& os, const Array<ZStr>& array);
   static void WriteRfcBlock(ZStr& sResult, const Array<ZStr>& array);

   // Parse an RFC-style Header / Body block. No terminal conditions will be represented in the result.
   static MailBlock Parse(const File& file);
   static MailBlock Parse(istream& is);
   static MailBlock Parse(const ZStr& str);

   // Create an object that can be extraced by Parse(above)
   static void      Compose(ostream& os, const MailBlock& mb);
   static void      Compose(ZStr& str, const MailBlock& mb);

   // Unfold any folded lines in the header.
   static bool      Unfold(MailBlock& mb);

   // Unfold any folded lines as per RFC822
   static bool      Unfold(Array<ZStr>& amb);

   // Checks for an empty line - Use strict when a verbatim TERMINATE sequence is required.
   static bool      IsEndOfHeader(const ZStr& strLine, bool bStrict = false);

   // Checks for a line containing a single "." - Use strict when a verbatim TERMINATE sequence is required.
   static bool      IsEndOfMessage(const ZStr& strLine, bool bStrict = false);

   // Removes (in order) terminal \n, then terminal \r
   static void      RmLineEnds(ZStr& str);

   // Removes leading and training whitespece, then calls RmLineEnds()
   static void      Cleanup(ZStr& str);
   };

}

#endif

