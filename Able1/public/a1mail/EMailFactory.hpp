// 11/12/1998, Created OutboundEMail to support PostJOB1, R. Nagy
// 11/16/1998, Added FileVersion support, R. Nagy
// 05/17/1999, Now MUST use "Load()" and "Save()": Moved Read() and Write() into "protected", R. Nagy
// 09/23/2003: Ported to Able1, R. Nagy
// 06/17/2004: Added Load and Save for file objects, R. Nagy
// 01/10/2008: Updated Pop3Server::Get() to use subject name (new EMailFactory member MkLocalName() overload), R. Nagy
//
#ifndef EMailFactory_Hpx
#define EMailFactory_Hpx
#include <a1mail/EMail.hpp>
#include <a1extra/FileVersion.hpp>

using namespace Able1;

namespace BetterMail
{
/**
 * class EMailFactory
 *
 * @author R. Nagy
 */
class EMailFactory
   {
   public:
      /**
       * Import:
       * @param file RFC-encoded file to load
       * @param header The result
       * @result True if imported
       * @comment In order to control newline cooking, importing and exporting are to files.
       */
      static bool Import(const File& file, EMailHeader& header);
      /**
       * Export:
       * @param file RFC-encoded file name to save to
       * @param header The subject
       * @result True if exported
       * @comment In order to control newline cooking, importing and exporting are to files.
       */
      static bool Export(const File& file, EMailHeader& header);

      /**
       * Import:
       * @param file RFC-encoded file to load
       * @param email The result
       * @result True if imported
       * @comment In order to control newline cooking, importing and exporting are to files.
       */
      static bool Import(const File&, EMailMessage&  email);
      /**
       * Export:
       * @param file RFC-encoded file name to save to
       * @param email The subject
       * @result True if exported
       * @comment In order to control newline cooking, importing and exporting are to files.
       */
      static bool Export(const File&, EMailMessage&  email);

      /**
       * IsEMailFactoryFile:
       * @param file RFC-encoded OR native-encoded header file
       * @result True if it contains either type of valid header
       * @comment Use OmniLoad to load either RFC or native file type.
       */
      static bool IsEMailFactoryFile(const File& file);
      /**
       * OmniLoad:
       * @param file RFC-encoded OR native-encoded header file
       * @param header result
       * @result True if it contains either type of valid header
       * @comment Use OmniLoad to load either RFC or native file type.
       */
      static bool OmniLoad(const File& file, EMailHeader& header);
      /**
       * OmniLoad:
       * @param file RFC-encoded OR native-encoded header file
       * @param message result
       * @result True if it contains either type of valid content
       * @comment Use OmniLoad to load either RFC or native file type.
       */
      static bool OmniLoad(const File& file, EMailMessage& emh);
      static bool Load(const File& file, EMailMessage&  email);
      static bool Save(const File& file, EMailMessage&  email);

      // List the lines in the message as if we were going to send them to the server
      static bool List(const EMailMessage& email, Array<ZStr>& aLines);
      static bool ListBody(const EMailMessage& email, Array<ZStr>& aLines);

      // Mostly used by servers to encode / decode an email message -
      static bool RemoveTerminalDot(EMailMessage& emb);
      static void EncodeDots(EMailMessage& emb);
      static void DecodeDots(EMailMessage& emb);

      // Logical names are NOT checked for physical exstance - You might want to engineer
      // in an "X-NNS-LocalName: " in the header for use later, but it's not important at
      // the moment;
      static bool MkLogicalName(File& file, const EMailHeader& emh, const ZStr& sExtension, bool TryMessageID);

      // This version checks to see if the enumerated file exists in the folder.
      // If it does and headers are the same, then the same file name is returned.
      // This means that if the file returned exists, then the content has been
      // previously saved to the folder specified.
      static File MkLocalName(const Directory& dir, EMailHeader& em, const ZStr& sExtension);
      // Like MkLocalName(above), but favors the string provided (emh.Subject(), etc.)
      // Does NOT check file content. Guaranteed unique file name returned, only.
      static File MkLocalName(const Directory& dir, const ZStr& sNodeRoot, const ZStr& sExtension);

      // Reduces a single address to just the '@' part;
      static bool AbsEmailAddress(ZStr& std);
      static bool AbsEmailAddress(const ZStr& sIn, ZStr& sOut);
      static bool ContainsAbsEmailAddress(const ZStr& sIn);
      // Same as AbsEmailAddress(), but returns result with the required <>'s;
      static bool FormatAsAddress(ZStr& std);
      static bool IsAddressSeparator(char ch);
   };
}
#endif
