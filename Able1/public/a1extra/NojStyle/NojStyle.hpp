#ifndef NojStyle_hpp
#define NojStyle_hpp

// Create, maintain, and re-use a set of "signature" style sheets, pages, and page templates

#include <Able1.hpp>
using namespace Able1;

inline
ZStr Anchor(const ZStr& sTitle, const ZStr& sPage)
   {
   stringstream srm;
   srm << "<a href=\"" << sPage << "\">" << sTitle << "</a>" << endl;
   return srm.str().c_str();
   }

class NojStyle
   {
   public:
      // Enumerated tokens for use in template exchanges -
      static ZStr TemplateToken(const ZStr& sROOT)
         {
         stringstream srm;
         srm << "<!%" << sROOT << "%/>";
         return ZStr(srm.str().c_str());
         }
      static ZStr TemplateToken(int iPos)
         {
         stringstream srm;
         srm << "<!%" << "NojStyle" << iPos << "%/>";
         return ZStr(srm.str().c_str());
         }
      static ZStr TemplateToken(const ZStr& sROOT, int iPos)
         {
         stringstream srm;
         srm << "<!%" << sROOT << iPos << "%/>";
         return ZStr(srm.str().c_str());
         }
      static ZStr TITLE(void)
         {
         return "NojStyleTITLE";
         }
      static ZStr NEXT(void)
         {
         return "NojStyleNEXT";
         }
      static ZStr PREV(void)
         {
         return "NojStylePREV";
         }
      static ZStr DATE(void)
         {
         return "NojStyleDATE";
         }
      static ZStr SUBJECT(void)
         {
         return "NojStyleSUBJECT";
         }
      static bool CalStyle(const File& fff, bool bOverWrite = false);
      static bool PageStyle(const File& fff, bool bOverWrite = false);
   };


// A Table Of Content (TOC) is a variable height table of DATE and SUBJECT token pairings
// By way of a bonus, a comment is included to tell how many lines have been encoded,
// but the Swap* functions make the need to know that completely unnessary -
class TocTemplate
{
   public:
      static ZStr sTemplateParam; // How we know how many lines are in any TOC - 

      // NPOS on error -
      static int QueryLines(const ZStr& sPage)
         {
         size_t iPos = sPage.Find(sTemplateParam);
         if(iPos == npos)
            return iPos;
         ZStr str = sPage;
         str.RemovePos(0, iPos);
         iPos = str.Find(';');
         if(iPos == npos)
            return iPos;
         str.Remove(iPos);
         iPos = str.Find('=');
         if(iPos == npos)
            return iPos;
         str.RemovePos(0, iPos + 1);
         str.Strip();
         return str.AsInt();
         }
      // Duo table -w- size imbedded into a comment
      static ZStr MkTable(int iHigh = 25)
         {
         stringstream srm;
         srm << "<! " << sTemplateParam << "=" << iHigh << ";/>" << endl;
         srm << "<center>" << endl;
         srm << "<table>" << endl;
         for(int sH = 0; sH < iHigh; sH++)
            {
            srm << "<tr>" << endl;

            srm << "<td>" << endl;
            srm << "&nbsp;" << endl;
            srm << NojStyle::TemplateToken(NojStyle::DATE(), sH + 1) << endl;
            srm << "&nbsp;" << endl;
            srm << "</td>" << endl;

            srm << "<td>" << endl;
            srm << "&nbsp;" << endl;
            srm << NojStyle::TemplateToken(NojStyle::SUBJECT(), sH + 1) << endl;
            srm << "&nbsp;" << endl;
            srm << "</td>" << endl;

            srm << "</tr>" << endl;
            }
         srm << "</table>" << endl;
         srm << "</center>" << endl;
         ZStr str = srm.str().c_str();
         return str;
         }
      // BODY tag with nested MkTable(...) + title and navigaiton tokens
      static ZStr MkBodyTable(int iHigh = 25)
         {
         stringstream srm;
         srm << "<center>" << endl;
         srm << "<table>" << endl;

         srm << "<tr>" << endl;
         srm << "<td>" << endl;
         srm << "&nbsp;" << endl;
         srm << NojStyle::TemplateToken(NojStyle::TITLE());
         srm << "&nbsp;" << endl;
         srm << "</td>" << endl;
         srm << "</tr>" << endl;

         srm << "<tr>" << endl;
         srm << "<td>" << endl;
         srm << MkTable(iHigh) << endl;
         srm << "</td>" << endl;
         srm << "</tr>" << endl;

         srm << "<tr>" << endl;
         srm << "<td>" << endl;
         srm << "&nbsp;" << endl;
         srm << NojStyle::TemplateToken(NojStyle::PREV()) << endl;
         srm << "&nbsp;" << endl;
         srm << "</td>" << endl;
         srm << "<td>" << endl;
         srm << "&nbsp;" << endl;
         srm << NojStyle::TemplateToken(NojStyle::NEXT()) << endl;
         srm << "&nbsp;" << endl;
         srm << "</td>" << endl;
         srm << "</tr>" << endl;

         srm << "</table>" << endl;
         srm << "</center>" << endl;
         return srm.str().c_str();
         }
      // return FALSE if not found -
      static bool SwapTitle(ZStr& sIO, const ZStr& sTitle)
         {
         int iTally = 0;
         iTally = sIO.Replace(NojStyle::TemplateToken(NojStyle::TITLE()), sTitle);
         if(!iTally)
            return false;
         return true;
         }
      // return FALSE if not found -
      static bool SwapNextPrev(ZStr& sIO, const ZStr& sPrev, const ZStr& sNext)
         {
         int iTally = 0;
         iTally = sIO.Replace(NojStyle::TemplateToken(NojStyle::PREV()), sPrev);
         if(!iTally)
            return false;
         iTally = sIO.Replace(NojStyle::TemplateToken(NojStyle::NEXT()), sNext);
         if(!iTally)
            return false;
         return true;
         }
      // Returns FALSE when pages is full / enumerated token not found, else true
      static bool SwapDateSubject(ZStr& sIO, const ZStr& sDate, const ZStr& sSubject, int iWhich)
         {
         int iTally = 0;
         iTally = sIO.Replace(NojStyle::TemplateToken(NojStyle::DATE(), iWhich), sDate, iWhich);
         if(!iTally)
            return false;
         iTally = sIO.Replace(NojStyle::TemplateToken(NojStyle::SUBJECT(), iWhich), sSubject);
         if(!iTally)
            return false;
         return true;
         }
};

struct AuthorInfo
{
// NOTE: Style elements "link" and "head" can be defined in any CSS you may decide to use -
   static ZStr Author(void)
      {
      return "<br>&nbsp; &nbsp;R.A. Nagy <br><center>SourceForge.net, <b>STDNOJ</b> Project</center>";
      }
   static ZStr Contact(void)
      {
      return "<center>&nbsp; &nbsp;Use the 'contact' form at Soft9000.com &nbsp; &nbsp;</center>";
      }
   static ZStr AdLinks(void)
      {
      stringstream srm;
      srm << "<center>";
      srm << "<a class=\"link\" href=\"" << "http://www.saintbook.org" << "\">" << "Saint Book</a>";
      srm << "<br>";
      srm << "<a class=\"link\" href=\"" << "http://www.soft9000.com" << "\">" << "Soft9000</a>";
      srm << "<br>";
      srm << "<a class=\"link\" href=\"" << "http://www.cookpedia.com" << "\">" << "Cookpedia</a>";
      srm << "</center>";
      return srm.str().c_str();
      }
   static ZStr AsTable(void)
      {
      stringstream srm;
      srm << "<center>";
      srm << "<br><table class=\"head\" border=1>";

      srm << "<tr><td>";
      srm << "<i><u>Shared by</u>:</i>" << Author();
      srm << "<br>";
      srm << "</td></tr>";

      srm << "<tr><td>";
      srm << "<i><u>Contact info</u>:</i>" << Contact();
      srm << "<br>";
      srm << "</td></tr>";

      srm << "<tr><td>";
      srm << "<i><u>Author sites</u>:</i>" << AdLinks();
      srm << "</td></tr>";

      srm << "</table>";
      srm << "</center>";
      return srm.str().c_str();
      }

   static bool NagBrag(const ZStr& sProject)
      {
      // Set the default style -
      File fileStyle;
      fileStyle.Name("NojStyle.css");
      Directory dir;
      dir.Get();
      dir.Home(fileStyle);
      NojStyle::PageStyle(fileStyle);

      // Set the content
      File file;
      file.Name("About.HTML");
      dir.Home(file);
      ostream& os = file.OpenWrite();
      os << "<html>" << endl;
      os << "<head>" << endl;
      os << "<title>R.A. Nagy's " << sProject << "</title>" << endl;
      os << "<link rel=\"stylesheet\" type=\"text/css\" href=\"" + fileStyle.QueryNode() + "\">" << endl;
      os << "</head>" << endl;
      os << "<body class=\"page\">" << endl;
      os << AuthorInfo::AsTable();
      os << "</body>" << endl;
      os << "</html>" << endl;
      file.Close();
      return file.Launch();
      }
};

// Good for testing - Not sure is good for anything else ... ?
class PageStyle
{
   private:
      PageStyle(void) {}

   protected:
      File fileStyle;
      Directory dirRoot;

   public:

      PageStyle(const Directory& dir)
         {
         fileStyle.Name("NojStyle.css");
         dir.Home(fileStyle);
         NojStyle::PageStyle(fileStyle);
         dirRoot = dir;
         }

      void BeginPage(ostream& os)
         {
         os << "<html>" << endl;
         os << "<head>" << endl;
         os << "<title>R.A. Nagy's HCal - via SourceForge.net</title>" << endl;
         os << "<link rel=\"stylesheet\" type=\"text/css\" href=\"" + fileStyle.QueryNode() + "\">" << endl;
         os << "</head>" << endl;
         os << "<body class=\"page\">" << endl;
         }

      void EndPage(ostream& os)
         {
         os << AuthorInfo::AsTable();
         os << "</body>" << endl;
         os << "</html>" << endl;
         }

      static bool TitleTemplate(PageStyle& style, const File& fff)
         {
         File file = fff;
         ostream& os = file.OpenWrite();
         style.BeginPage(os);
         os << "<br><br><br><center>" << endl;
         os << "<h1>" << endl;
         os << NojStyle::TemplateToken(1) << endl;
         os << "</h1>" << endl;
         os << "</center><br><br><br>" << endl;
         style.EndPage(os);
         file.Close();
         return file.Exists();
         }

      static ZStr TocTemplate(PageStyle& style)
         {
         stringstream os;
         style.BeginPage(os);

         os << TocTemplate::MkBodyTable();

         style.EndPage(os);
         return os.str().c_str();
         }

      static bool TocTemplate(PageStyle& style, const File& fff)
         {
         File file = fff;
         ostream& os = file.OpenWrite();
         TocTemplate(style).Write(os);
         file.Close();
         return file.Exists();
         }

      static int TocLines(const ZStr& sPage)
         {
         return TocTemplate::QueryLines(sPage);
         }
};

#endif
