//-++--------------------------------------------------------------------------

#ifndef uProjectDataH
#define uProjectDataH

#include <FastJob.hpp>
using namespace FastJob;

//---------------------------------------------------------------------------

class ProjectData
{
public:
   Url              sURL;
   Array<StdString> aFileTypes;
   Directory        dirLocal;

   static bool Load(const File& fff, ProjectData& project)
   {
   File file = fff;
   project = ProjectData();
   istream& is = file.OpenRead();
   if(!is)
      return false;
   StreamString srm;
   srm.read(is);
   if(project.sURL.Name(srm.c_str()) == false)
      return false;
   srm.read(is);
   if(project.dirLocal.Name(srm.c_str()) == false)
      return false;
   srm.read(is);
   project.aFileTypes == StdString(srm.c_str()).slice('|');
   return true;
   }

   static bool Save(const File& fff, ProjectData& project)
   {
   File file = fff;
   ostream& os = file.OpenWrite();
   os << StreamString(project.sURL.Name());
   os << StreamString(project.dirLocal.Name());
   stringstream srm;
   for(size_t ss = 0L; ss < project.aFileTypes.Nelem(); ss++)
      srm << StreamString(project.aFileTypes[ss]) << "|";
   os << StreamString(srm.str().c_str());
   file.Close();
   return file.Exists();
   }

   static StdString DefaultTemaplate()
   {
   StdString sResult = "";
   sResult = "<link rel=\"meta\" href=\"http://soft9000.com/labels.rdf\" type=\"application/rdf+xml\" title=\"ICRA labels\" />";
   sResult += "<link rel=\"meta\" href=\"http://soft9000.com/labels.rdf\" type=\"application/rdf+xml\" title=\"ICRA labels\" />";
   sResult += "<meta http-equiv=\"pics-Label\" content='(pics-1.1 \"http://www.icra.org/pics/vocabularyv03/\"";
   sResult += " l gen true for \"http://soft9000.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://www.soft9000.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://cookpedia.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://www.cookpedia.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0)";
   sResult += " gen true for \"http://saintbook.org\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://www.saintbook.org\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://lulu.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://www.lulu.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://ss.webring.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0) ";
   sResult += " gen true for \"http://www.ss.webring.com\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0)";
   sResult += " gen true for \"http://quotationring.net\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0)";
   sResult += " gen true for \"http://www.quotationring.net\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0)";
   sResult += " gen true for \"http://promo.net\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0)";
   sResult += " gen true for \"http://www.promo.net\" r (n 0 s 0 v 0 l 0 oa 0 ob 0 oc 0 od 0 oe 0 of 0 og 0 oh 0 c 0))' />";
   return sResult;
   }
};

#endif
