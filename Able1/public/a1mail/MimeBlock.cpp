
#include <a1mail/EMimeMessage.hpp>
#include <a1mail/MimeBlock.hpp>
#include <a1mail/QuotedPrintable.hpp>
using namespace BetterMail;

Array<ZStr> MimeBlock::aPrefix;

MimeBlock::MimeBlock(void)
   {
   if(!aPrefix.Nelem())
      {
      aPrefix.AddZombies(10);
      aPrefix[0] = "noj0_";
      aPrefix[1] = "noj1_";
      aPrefix[2] = "noj2_";
      aPrefix[3] = "noj3_";
      aPrefix[4] = "noj4_";
      aPrefix[5] = "noj5_";
      aPrefix[6] = "noj6_";
      aPrefix[7] = "noj7_";
      aPrefix[8] = "noj8_";
      aPrefix[9] = "noj9_";
      aPrefix[10] = "nojable_";
      aPrefix[11] = "nojb_";
      aPrefix[12] = "nojc_";
      aPrefix[13] = "nojd_";
      aPrefix[14] = "noje_";
      aPrefix[15] = "nojf_";
      }
   }
MimeBlock MimeBlock::Parse(const ZStr& eMessage)
   {
   MimeBlock block;

   MailBlock mb = MailBlock::Parse(eMessage);
   if(mb.IsNull())
      return block;

   MailBlock::Unfold(mb);

   for(size_t ss = 0L; ss < mb.aHeader.Nelem(); ss++)
      {
      block.contentId = MimeContentId::Parse(mb.aHeader[ss]);
      if(block.contentId.IsNull() == false)
         break;
      }

   if(block.contentId.IsNull() == true)
      {
      block = MimeBlock();
      return block;
      }

   if(block.contentId.IsNull() == false)
      {
      MailBlock::WriteBlockOnly(block.sContent, mb.aBody);
      // TODO: Some day we need to parse the REST of this - 
      /* Example:
      --noj5_1166629662
      Content-Type: text/plain; charset="iso-8859-1"
      Content-Transfer-Encoding: quoted-printable

      This is text.

      --noj5_1166629662
      */
      }
   return block;
   }
bool MimeBlock::Encode(EMailMessage& message, const Array<MimeBlock>& array)
   {
   message._ctype = "";
   message._mime_ver = "";
   message._text = "";

   if(!array.Nelem())
      return true;

   message._mime_ver = "1.0";
   // TODO: Fix this one later - Deduce the content, no hardcode -
   message._ctype = "multipart/alternative;";

      {
   static int iPrefix = 0;
   if(iPrefix >= aPrefix.Nelem())
      iPrefix = 0;
   stringstream srm;
   srm << aPrefix[iPrefix];
   srm << ::time(NULL);
   message._cbound = srm.str().c_str();
   iPrefix++;
      }


   stringstream srm;
   srm << "This is a multi-part message in MIME format." << TERMINATE;
   srm << TERMINATE;

   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      MimeBlock& ref = array.Get(ss);
      srm << "--" << message._cbound << TERMINATE;
      // TODO: Fix this one later - Deduce the content, no hardcode -
      srm << ref.contentId << " charset=\"iso-8859-1\"" << TERMINATE;
      srm << "Content-Transfer-Encoding: quoted-printable" << TERMINATE;
      srm << TERMINATE;
      srm << QuotedPrintable::Encode(ref.sContent);
      srm << TERMINATE;
      }
   srm << "--" << message._cbound << "--" << TERMINATE;

   message._text = srm.str().c_str();
   return true;
   }
bool MimeBlock::Decode(const EMailMessage& eMessage, Array<MimeBlock>& mimeBody)
   {
   // STEP: Inspect the obvious -
   if(eMessage.IsMime() == false)
      return false;

   mimeBody.Empty();

   // SANIT CHECK: For the content identifier - (ONLY)
   ZStr str = eMessage.ContentType();
   MimeContentId id = MimeContentId::Parse(str);
   if(id.contentMajor == MimeContentId::maNone)
      return false;
   if(id.contentMinor == MimeContentId::miNone)
      return false;

   // STEP: Find the boundary -
   ZStr sBounds = eMessage.ContentBoundary();
   if(sBounds.IsNull())
      return false;  /// hummmmm ... ?

   // STEP: Use the boundary to parse the message body
   str = eMessage.Body();
   Array<ZStr> array;
   if(str.Split(sBounds, array) == false)
      return false;

   MimeBlock block;
   for(size_t ss = 0L; ss < array.Nelem(); ss++)
      {
      block = Parse(array[ss]);
      if(block.contentId.IsNull() == true)
         continue;         // email block ends with an empty ContentBoundary! -
      else
          mimeBody.Append(block);
      }
   return true;
   }
ZStr MimeBlock::RawContent(void)
   {
   ZStr sResult = sContent;
   return sResult;
   }
ZStr MimeBlock::Content(void)
   {
   ZStr sResult = sContent;
   QuotedPrintable::Decode(sResult);
   return sResult;
   }
void MimeBlock::Content(const ZStr& sss)
   {
   sContent = QuotedPrintable::Encode(sss);
   }
