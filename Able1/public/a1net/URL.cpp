#include "URL.hpp"

using namespace stdnet;

#include <sstream>
using namespace std;

// The Specific portion tailors the URL to an access instance -
bool URL::Specific::IsNull(void)
   {
   if(sUserId.IsNull() == false)
      return false;
   if(sPassword.IsNull() == false)
      return false;
   if(iPort != 0)
      return false;
   return true;
   }


URL::URL(void) : protocol(none) 
   {
   }

int URL::operator==(const URL& url) const
   {
   ZStr sOne, sTwo;
   URL::Encode(sOne, *this);
   URL::Encode(sTwo, url);
   return (sOne == sTwo);
   }
int URL::operator!=(const URL& url) const
   {
   ZStr sOne, sTwo;
   URL::Encode(sOne, *this);
   URL::Encode(sTwo, url);
   return (sOne != sTwo);
   }

int URL::operator>(const URL& url) const
   {
   ZStr sOne, sTwo;
   URL::Encode(sOne, *this);
   URL::Encode(sTwo, url);
   return (sOne > sTwo);
   }
int URL::operator<(const URL& url) const
   {
   ZStr sOne, sTwo;
   URL::Encode(sOne, *this);
   URL::Encode(sTwo, url);
   return (sOne < sTwo);
   }

bool URL::IsNull(void) const
   {
   // Gotta be there - 
   if(sServer.IsNull() == false)
      return false;
   // Gotta be there - 
   if(protocol != none)
      return false;
   return true;
   }

void URL::Reset(void)
   {
   URL url;
   *this = url;
   }

bool URL::Encode(ZStr& sEncoded, const URL& upResult)
   {
   stringstream srm;
   switch(upResult.protocol)
      {
      case (ftp):
         srm << "ftp://";
      break;
      case (http):
         srm << "http://";
      break;
      case (gopher):
         srm << "gopher://";
      break;
      case (mailto):
         srm << "mailto://";
      break;
      case (news):
         srm << "news://";
      break;
      case (nntp):
         srm << "nntp://";
      break;
      case (telnet):
         srm << "telnet://";
      break;
      case (wais):
         srm << "wais://";
      break;
      case (file):
         srm << "file://";
      break;
      case (prospero):
         srm << "prospero://";
      break;
      default:
      case (none):
         sEncoded = "Error: Unsupported RFC Protocol";
      return false;
      }

      if(upResult.opt.sUserId.IsNull() == false)
         {
         srm << upResult.opt.sUserId;

         if(upResult.opt.sPassword.IsNull() == false)
            srm << ":" << upResult.opt.sPassword;

         srm << "@";
         }
      else
         {
         if(upResult.opt.sPassword.IsNull() == false)
            {
            sEncoded = "Error: Password is not allowed without a User ID (RFC 1783.)";
            return false;
            }
         }
      srm << upResult.sServer;
      if(upResult.opt.iPort)
         srm << ":" << upResult.opt.iPort;

      srm << upResult.sPath;

      sEncoded = srm.str().c_str();
      return true;
   }


bool URL::Decode(const ZStr& sEncoded, URL& upResult)
   {
   URL blanker;
   upResult = blanker;

   ZStr sInput = sEncoded;
   ZStr sTmp;

   // STEP: Encode the Protocol
   size_t pos = sInput.Find("//");
   if(pos == npos)
      {
      upResult.sError = "Protocol not defined.";
      return false;
      }

   ZStr sProtocol =  sInput.Subpos(0, pos);;
   sInput.RemovePos(0, pos + 2);

   sTmp = sProtocol;
   pos = sTmp.Find(':');
   if(pos == npos)
      return false;
   sTmp.Remove(pos);
   sTmp.ToLower();
   if(sTmp == "http")
      {
      upResult.protocol = http;
      goto pcl_done;
      }
   if(sTmp == "ftp")
      {
      upResult.protocol = ftp;
      goto pcl_done;
      }
   if(sTmp == "file")
      {
      upResult.protocol = file;
      goto pcl_done;
      }
   if(sTmp == "mailto")
      {
      upResult.protocol = mailto;
      goto pcl_done;
      }
   if(sTmp == "news")
      {
      upResult.protocol = news;
      goto pcl_done;
      }
   if(sTmp == "telnet")
      {
      upResult.protocol = telnet;
      goto pcl_done;
      }
   if(sTmp == "nntp")
      {
      upResult.protocol = nntp;
      goto pcl_done;
      }
   if(sTmp == "gopher")
      {
      upResult.protocol = gopher;
      goto pcl_done;
      }
   if(sTmp == "wais")
      {
      upResult.protocol = wais;
      goto pcl_done;
      }
   if(sTmp == "prospero")
      {
      upResult.protocol = prospero;
      goto pcl_done;
      }

   upResult.sError = "Protocol not supported.";
   return false;

   pcl_done:


   // STEP: Detect and remove any user-id and password -
   /* RFC 1738
   ... there is no way to specify a password without
   specifying a user name. E.g., <URL:ftp://@host.com/> has an empty
   user name and no password, <URL:ftp://host.com/> has no user name,
   while <URL:ftp://foo:@host.com/> has a user name of "foo" and an
   empty password.
   */
   pos = sInput.Find('@');
   if(pos != npos)
      {
      sTmp = sInput.Subpos(0, pos);
      sInput.RemovePos(0, pos+1);

      pos = sTmp.Find(':');
      if(pos != npos)
         {
         upResult.opt.sPassword = sTmp.Subpos(pos+1, npos);
         sTmp.Remove(pos);
         }
      upResult.opt.sUserId = sTmp;
      }

   // STEP: Check what remains for a path
   pos = sInput.Find('/');
   if(pos != npos)
      {
      upResult.sServer = sInput.Subpos(0, pos);
      sInput.RemovePos(0, pos);
      upResult.sPath = sInput;
      }
   else
      upResult.sServer = sInput;

   // STEP: Check what remains OF THE SERVER for a port
   pos = upResult.sServer.Find(':');
   if(pos != npos)
      {
      sInput = upResult.sServer;
      upResult.sServer = sInput.Subpos(0, pos);
      sInput.RemovePos(0, pos+1);
      upResult.opt.iPort = sInput.AsInt();
      }
   return true;
   }

bool URL::Test(URL& url, ostream& cout)
   {
   if(URL::Decode("", url) == true)
      {
      cout << "Error 1.1" << endl;
      return false;
      }
   if(URL::Decode("soft9000.com", url) == true)
      {
      cout << "Error 1.2" << endl;
      return false;
      }
   if(URL::Decode("http://www.soft9000.com", url) == false)
      {
      cout << "Error 1.3" << endl;
      return false;
      }
   if(URL::Decode("ftp://nagy:password@soft9000.com", url) == false)
      {
      cout << "Error 2.1" << endl;
      return false;
      }
   if(URL::Decode("ftp://nagy:password@soft9000.com/goomba/ya.txt", url) == false)
      {
      cout << "Error 2.2" << endl;
      return false;
      }
   if(URL::Decode("ftp://nagy:password@soft9000.com:27/goomba/ya.txt", url) == false)
      {
      cout << "Error 2.3" << endl;
      return false;
      }

   if(url.protocol != ftp)
      {
      cout << "Error 3.1" << endl;
      return false;
      }

   if(url.sServer != "soft9000.com")
      {
      cout << "Error 3.2" << endl;
      return false;
      }

   if(url.sPath != "/goomba/ya.txt")
      {
      cout << "Error 3.3" << endl;
      return false;
      }

   if(url.opt.sUserId != "nagy")
      {
      cout << "Error 3.4" << endl;
      return false;
      }

   if(url.opt.sPassword != "password")
      {
      cout << "Error 3.5" << endl;
      return false;
      }

   if(url.opt.iPort != 27)
      {
      cout << "Error 3.6" << endl;
      return false;
      }


/*
ftp://@host.com/ has an empty user name and no password, 
*/
   if(URL::Decode("ftp://@host.com/", url) == false)
      {
      cout << "Error 4.0" << endl;
      return false;
      }
   if(url.opt.sUserId.IsNull() == false)
      {
      cout << "Error 4.1" << endl;
      return false;
      }
   if(url.opt.sPassword.IsNull() == false)
      {
      cout << "Error 4.2" << endl;
      return false;
      }
   if(url.sServer != "host.com")
      {
      cout << "Error 5.2" << endl;
      return false;
      }
   if(url.sPath != "/")
      {
      cout << "Error 5.3" << endl;
      return false;
      }
   if(url.opt.iPort != 0)
      {
      cout << "Error 5.4" << endl;
      return false;
      }
   if(url.protocol != ftp)
      {
      cout << "Error 5.5" << endl;
      return false;
      }

/*
ftp://foo:@host.com/ has a user name of "foo" and an empty password.
*/
   if(URL::Decode("ftp://foo:@host.com/", url) == false)
      {
      cout << "Error 6.0" << endl;
      return false;
      }
   if(url.opt.sUserId != "foo")
      {
      cout << "Error 6.1" << endl;
      return false;
      }
   if(url.opt.sPassword.IsNull() == false)
      {
      cout << "Error 6.2" << endl;
      return false;
      }
   if(url.sServer != "host.com")
      {
      cout << "Error 6.2" << endl;
      return false;
      }
   if(url.sPath != "/")
      {
      cout << "Error 6.3" << endl;
      return false;
      }
   if(url.opt.iPort != 0)
      {
      cout << "Error 6.4" << endl;
      return false;
      }
   if(url.protocol != ftp)
      {
      cout << "Error 6.5" << endl;
      return false;
      }


   // Decode / Encode Test
   URL uOne;
   ZStr sOne = "ftp://nagy:password@soft9000.com:27/goomba/ya.txt";      
   if(URL::Decode(sOne, uOne) == false)
      {
      cout << "Error 6.1" << endl;
      return false;
      }

   ZStr sTwo;
   if(URL::Encode(sTwo, uOne) == false)
      {
      cout << "Error 6.2" << endl;
      return false;
      }

   if(sOne != sTwo)
      {
      cout << "Error 6.3" << endl;
      return false;
      }

   // Decode / Encode NORMALIZATION Test
   uOne;
   sOne = "ftp://nagy:@soft9000.com:27/goomba/ya.txt";      
   if(URL::Decode(sOne, uOne) == false)
      {
      cout << "Error 6.1" << endl;
      return false;
      }

   sOne = "ftp://nagy@soft9000.com:27/goomba/ya.txt";
   sTwo = "";
   if(URL::Encode(sTwo, uOne) == false)
      {
      cout << "Error 6.2" << endl;
      return false;
      }

   if(sOne != sTwo)
      {
      cout << "Error 6.3" << endl;
      return false;
      }

   /*
   // Misc
   sOne = "ftp://:password@soft9000.com:27/goomba/ya.txt";      
   if(URL::Decode(sOne, uOne) == true)
      {
      cout << "Error m.1" << endl;
      return false;
      }
   */

   return true;
   }
