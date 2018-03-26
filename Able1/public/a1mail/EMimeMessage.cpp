
#include <a1mail/EMimeMessage.hpp>
using namespace BetterMail;



/*
bool  EMimeMessage::Encode(EMailMessage& Writer)
   {
   ZStr sBoundary;
   sBoundary += ".-=";
   sBoundary += "MyNextNojBoundary";
   sBoundary += "=-.";

   ZStr sClause = "\tboundary=\"";
   sClause += sBoundary;
   sClause += "\"";

   if(Writer.mimeBody.Nelem())
      {
      // Intercept this Write to inject the proper header & MIME payload
      stringstream srm;
      ZStr str = Writer.Body();
      if(str.IsNull() == false)
         {
         srm << str;
         srm << TERMINATE;
         }
      // STEP: Fixup the header -
      MimeContentId id;
      id.contentMajor = MimeContentId::maMultipart;
      id.contentMinor = MimeContentId::miAlternative;
      ZStr sType = MimeContentId::Compose(id);
      sType += ";\r\n";
      sType += sClause;
      sType += "\r\n";
      Writer._ctype.Assign(sType);

      // STEP: Format up the body -
      for(size_t ss = 0L; ss < Writer.mimeBody.Nelem(); ss++)
         {
         srm << sBoundary << TERMINATE;
         MimeBlock ref;
         Writer.mimeBody.At(ss, ref);
         srm << ref.sContent;
         }

      // STEP: Always ends with this!
      srm << sBoundary << TERMINATE;
      Writer.Body(srm.str().c_str());
      }

   return true;
   }
bool  EMimeMessage::Decode(EMailMessage& src)
   {
   return MimeBlock::Parse(src);
   }
*/

ZStr EMimeMessage::SampleOutlookPattern(void)
   {
   ZStr str;
   // Common MS Outlook Expression - HTML Viewable on WebMail and MS -
   str.Append("From:	\"R. A. Nagy\" <randall_nagy@soft9000.com>\r\n");
   str.Append("To:	<kayak2006@soft9000.com>\r\n");
   str.Append("Subject: Test\r\n");
   str.Append("Date:	Sat, 11 Nov 2006 05:04:43 -0500\r\n");
   str.Append("MIME-Version: 1.0\r\n");
   str.Append("Content-Type: multipart/alternative;\r\n");
   str.Append("	boundary=\"----=_NextPart_000_0007_01C7054E.E6AD6620\"\r\n");
   str.Append("\r\n");
   str.Append("This is a multi-part message in MIME format.\r\n");
   str.Append("\r\n");
   str.Append("------=_NextPart_000_0007_01C7054E.E6AD6620\r\n");
   str.Append("Content-Type: text/plain;\r\n");
   str.Append("	charset=\"iso-8859-1\"\r\n");
   str.Append("Content-Transfer-Encoding: quoted-printable\r\n");
   str.Append("\r\n");
   str.Append("This is a simple HTML message.=20\r\n");
   str.Append("(C&P)\r\n");
   str.Append("\r\n");
   str.Append("------=_NextPart_000_0007_01C7054E.E6AD6620\r\n");
   str.Append("Content-Type: text/html;\r\n");
   str.Append("	charset=\"iso-8859-1\"\r\n");
   str.Append("Content-Transfer-Encoding: quoted-printable\r\n");
   str.Append("\r\n");
   str.Append("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n");
   str.Append("<HTML><HEAD>\r\n");
   str.Append("<META http-equiv=3DContent-Type content=3D\"text/html; =\r\n");
   str.Append("charset=3Diso-8859-1\">\r\n");
   str.Append("<META content=3D\"MSHTML 6.00.2800.1561\" name=3DGENERATOR>\r\n");
   str.Append("<STYLE></STYLE>\r\n");
   str.Append("</HEAD><FONT face=3DArial><FONT size=3D2>\r\n");
   str.Append("<BODY>\r\n");
   str.Append("<DIV>This is a <FONT color=3D#800080 =\r\n");
   str.Append("size=3D3>simple</FONT>&nbsp;<U><FONT=20\r\n");
   str.Append("color=3D#ff0000 size=3D5><STRONG>HTML</STRONG></FONT></U> message. =\r\n");
   str.Append("</DIV>\r\n");
   str.Append("<DIV>(C&amp;P)</DIV>\r\n");
   str.Append("<DIV>&nbsp;</DIV></BODY></HTML></FONT></FONT>\r\n");
   str.Append("\r\n");
   str.Append("------=_NextPart_000_0007_01C7054E.E6AD6620--\r\n");
   return str.c_str();
   }

bool EMimeMessage::LoadTest(EMailMessage& msg)
   {
   ZStr str = SampleOutlookPattern();
   File file;
   file.Name("EMimeMessageTest.eml");
   file.Remove();
   ostream& os = file.OpenWrite(File::AT_BINARY);
   os << str;
   file.Close();
   if(EMailFactory::Import(file, msg) == false)
      return false;
   return true;
   }
bool EMimeMessage::IsMime(const File& file)
   {
   EMailMessage parser;
   if(parser.ParseMessageBody(file) == false)
      return false;
   return parser.IsMime();
   }

bool EMimeMessage::LoadMime(const File& file, EMailMessage& result)
   {
   EMailMessage parser;
   if(parser.ParseMessageBody(file) == false)
      return false;
   if(parser.IsMime() == false)
      return false;
   if(IsMultipart(parser) == false)
      {
      result = parser;
      return true;
      }
   return false;
   }
bool EMimeMessage::SaveMime(const File& file, EMailMessage& result)
   {
   bool br = false;
   return br;
   }
bool EMimeMessage::IsSupported(const EMailHeader& header)
   {
   if(header.IsMime())
      {
      if(MimeContentId::Parse(header.ContentType()).IsNull())
         return false;
      return true;
      }
   return false;
   }
bool EMimeMessage::IsMultipart(const EMailHeader& header)
   {
   if(header.IsMime())
      {
      MimeContentId id = MimeContentId::Parse(header.ContentType());
      if(id.contentMajor == MimeContentId::maMultipart)
         return true;
      }
   return false;
   }

