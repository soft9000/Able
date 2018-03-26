#include <a1mail/MimeContentId.hpp>
using namespace BetterMail;

MimeContentId::MimeContentId(void) : contentMajor(maNone), contentMinor(miNone)
   {
   }

bool MimeContentId::IsNull(void) const
   {
   if(contentMajor == maNone && contentMinor == miNone)
      return true;
   return false;
   }

ZStr MimeContentId::Compose(const MimeContentId& mid)
   {
   ZStr sResult;
   if(mid.IsNull())
      return sResult;

   sResult = "Content-Type: ";
   switch(mid.contentMajor)
      {
      case maImage:
         sResult.Append("image");
      break;       // discrete-type
      case maText:
         sResult.Append("text");
      break;        // discrete-type
      case maApplication:
         sResult.Append("application");
      break; // discrete-type
      case maMessage:
         sResult.Append("message");
      break;     // composite-type
      case maMultipart:
         sResult.Append("multipart");
      break;   // composite-type
      case maNone:
      default:
         return sResult;
      }

   switch(mid.contentMinor)
      {
      case miPlain:
         sResult.Append("/plain");
      break;
      case miHtml:
         sResult.Append("/html");
      break;
      case miGif:
         sResult.Append("/gif");
      break;
      case miJpeg:
         sResult.Append("/jpeg");
      break;
      case miAlternative:
         sResult.Append("/alternative");
      break;
      case miNone:
      default:
         {
         sResult = "";
         return sResult;
         }
      }
   sResult.Append(';');
   return sResult;
   }

MimeContentId MimeContentId::Parse(const File& file)
   {
   MimeContentId result;
   ZStr str = file.Name();
   size_t pos = str.Rfind('.');
   if(pos == npos)
      return result;
   str.RemovePos(0, pos);
   str.ToLower();
   if(str == "txt")
      {
      result.contentMajor = maText;
      result.contentMinor = miPlain;
      return result;
      }
   if(str == "html")
      {
      result.contentMajor = maText;
      result.contentMinor = miHtml;
      return result;
      }
   if(str == "htm")
      {
      result.contentMajor = maText;
      result.contentMinor = miHtml;
      return result;
      }
   if(str == "jpg")
      {
      result.contentMajor = maImage;
      result.contentMinor = miJpeg;
      return result;
      }
   if(str == "jpeg")
      {
      result.contentMajor = maImage;
      result.contentMinor = miJpeg;
      return result;
      }
   if(str == "gif")
      {
      result.contentMajor = maImage;
      result.contentMinor = miGif;
      return result;
      }
   return result;
   }
const char *MimeContentId::Query(ZStr& sResult)
   {
   sResult = Compose(*this);
   return sResult.c_str();
   }
MimeContentId MimeContentId::Parse(const ZStr& sMimeContentString)
   {
   MimeContentId nada, wip;

   ZStr str = sMimeContentString;
   str.ToLower();

   size_t pos = str.Find(';');
   if(pos != npos)
      str.Remove(pos);

   ZStr sToken = "ype:";
   pos = str.Find(sToken);
   if(pos != npos)
      str.RemovePos(0, pos + sToken.Length());

   str.MkWhite();
   str.Strip();

   pos = str.Find('/');
   if(pos == npos)
      {
      /* Naaah - Consider it just part of the protocol -
      pos = str.Find("mime");
      if(pos != npos)
         {
         // "This is a multipart message in MIME format."
         wip.contentMajor = maText;
         wip.contentMinor = miPlain;
         return wip;
         }
      */
      return nada;
      }
   ZStr sLeft = str;
   sLeft.Remove(pos);
   ZStr sRight = str;
   sRight.RemovePos(0, pos+1);

   // MAJOR
   bool bSupported = false;
   if(sLeft == "text")
      {
      wip.contentMajor = maText;
      bSupported = true;
      }
   if(sLeft == "image")
      {
      wip.contentMajor = maImage;
      bSupported = true;
      }
   if(sLeft == "application")
      {
      wip.contentMajor = maApplication;
      bSupported = true;
      }
   if(sLeft == "multipart")
      {
      wip.contentMajor = maMultipart;
      bSupported = true;
      }
   if(sLeft == "message")
      {
      wip.contentMajor = maMessage;
      bSupported = true;
      }
   if(bSupported == false)
      return nada;

   // MINOR
   bSupported = false;
   if(sRight == "alternative")
      {
      wip.contentMinor = miAlternative;
      bSupported = true;
      }
   if(sRight == "jpeg")
      {
      wip.contentMinor = miJpeg;
      bSupported = true;
      }
   if(sRight == "gif")
      {
      wip.contentMinor = miGif;
      bSupported = true;
      }
   if(sRight == "plain")
      {
      wip.contentMinor = miPlain;
      bSupported = true;
      }
   if(sRight == "html")
      {
      wip.contentMinor = miHtml;
      bSupported = true;
      }

   if(bSupported)
      return wip;

   // NULL
   return nada;
   }

