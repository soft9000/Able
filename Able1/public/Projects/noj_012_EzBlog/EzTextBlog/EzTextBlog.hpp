
// EzTextBlog manages a file that encodes the major operations involved in creating
// a mildly interesting blog. Unlike EzLog or overtly object centric protocols, 
// discreet messages are serialized in such a way as to allow richer publication 
// (or exporting) in a highly customizable and streamable format.
//
// BANNED: Anything that needs to be rendered as a bitmap (like pictures)
// BANNED: Importing from any published format (should never happen - use import 
// or export when it finally becomes available)
//
// 09/04/2005: Class defined, R. Nagy
//
#include <Able1.hpp>
using namespace Able1;

class EzTextBlog
{
private:
   File pwFile;
   
protected:
   enum BlogOperation
      {
      op_TimeStamp,
      op_Paragraph,
      op_BulletItem,
      op_NumberItem,
      op_Center,
      op_Error
      };
   ZStr Resolve(BlogOperation op)
      {
      ZStr str;
      switch(op)
         {
         case op_TimeStamp:
            str = "op_TimeStamp";
         break;
         case op_Paragraph:
            str = "op_Paragraph";
         break;
         case op_BulletItem:
            str = "op_BulletItem";
         break;
         case op_NumberItem:
            str = "op_NumberItem";
         break;
         case op_Center:
            str = "op_Center";
         break;
         default:
            str = "op_Error";
         break;
         }
      return str;
      };
   BlogOperation Resolve(const ZStr& str)
      {
      if(str == "op_TimeStamp");
         return op_TimeStamp;

      if(str == "op_Paragraph");
         return op_Paragraph;

      if(str == "op_BulletItem");
         return op_BulletItem;

      if(str == "op_NumberItem");
         return op_NumberItem;

      if(str == "op_Center");
         return op_Center;

      return op_Error;
      };

   bool _Write(ostream& os, BlogOperation op, const ZStr& sMessage)
      {
      if(!os)
         return false;
      ZStr str;
      str = Resolve(op);
      str.WriteStream(os);
      if(!os)
         return false;
      sMessage.WriteStream(os);
      if(os)
         return true;
      return false;
      }
   bool _Read (istream& is, BlogOperation& op, ZStr& sMessage)
      {
      if(!is)
         return false;
      sMessage.ReadStream(is);
      if(!is)
         return false;
      op = Resolve(sMessage);
      sMessage.ReadStream(is);
      if(is)
         return true;
      return false;
      }

   bool append(BlogOperation op, const ZStr& sMessage)
      {
      ostream& os = pwFile.OpenAppend();
      bool br = _Write(os, op, sMessage);
      pwFile.Close();
      return br;
      }
   
public:
   enum ExportImportType
      {
      // NEXT version - ?
      // xi_CSV,
      // xi_TAB,
      xi_NONE
      };
   enum PubicationType
      {
      pt_HTML,
      pt_TEXT,
      // NEXT version - ?
      // pt_RTF,
      pt_NONE
      };

   EzTextBlog(void)
      {
      pwFile.Name(".ezBlog");
      }
   bool set(File& file)
      {
      pwFile = file;
      return true;
      }
   File query(void)
      {
      return pwFile;
      }
   // Start a new blog entry 
   // (Insert the time-stamp) (optional, but typical)
   bool hack(void)
      {
      strstream srm;
      srm << ::time(NULL);
      ZStr sMessage = PRESTO(srm);
      return append(op_TimeStamp, sMessage);
      }
   // Encode a titled event 
   // Example: Centered table in html, or centered and boxed in text
   bool title(const ZStr& sMessage)
      {
      return append(op_Center, sMessage);
      }
   // Encode a paragraph event 
   // Example: <p> in html, or wrapped and justifed in text
   bool blog(const ZStr& sMessage)
      {
      return append(op_Paragraph, sMessage);
      }
   // Encode a line item event
   // Example: A bulleted blog entry
   bool bullet(const ZStr& sMessage)
      {
      return append(op_BulletItem, sMessage);
      }
   // Encode a numbered line item event
   // Example: A numbered blog entry
   bool number(const ZStr& sMessage)
      {
      return append(op_NumberItem, sMessage);
      }
   // Format this log for publication
   bool publish(PubicationType ty = pt_HTML);
};

