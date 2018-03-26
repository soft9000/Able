#include <Able1.hpp>
using namespace Able1;

#ifndef a1net2_url_hpx
#define a1net2_url_hpx

namespace a1net2 {
    // URL syntax is Protocol://<user>:<password>@<host>:<port>/<url-path>

    class URL {
    public:
        
        enum RfcProtocol {
            none,
            ftp, // File Transfer Protocol
            http, // Hypertext Transfer Protocol
            gopher, // The Gopher Protocol
            mailto, // Electronic mail address
            news, // USENET news
            nntp, // USENET news using NNTP access
            telnet, // Reference to interactive sessions
            wais, // Wide Area Information Servers
            file, // Host-specific file names
            prospero // Prospero Directory Service
        }; // This is required
        
    protected:
        RfcProtocol protocol;
        
        ZStr sError;

        ZStr sServer; // This is required
        ZStr sPath; // Technically optional, but used frequently.

        // The Specific portion tailors the URL to an access instance -

        struct Specific {
            int iPort;
            ZStr sUserId;
            ZStr sPassword; // RFC1738: "... there is no way to specify a password without specifying a user name."

            Specific(void) : iPort(-1) {
            }

            bool IsNull(void);
        } opt;
    public:
        URL(void);

        bool IsNull(void) const;
        void Reset(void);
        
        int GetPort() {
            return opt.iPort;
        }
        
        ZStr GetServer() {
            return ZStr(sServer);
        }


        int operator==(const URL & url) const;
        int operator!=(const URL & url) const;
        int operator>(const URL & url) const;
        int operator<(const URL & url) const;


        static bool ToString(ZStr& sEncoded, const URL & upResult); // Factorize
        static bool FromString(const ZStr& sEncoded, URL & upResult); // Serialize
        static bool Test(URL& url, ostream & cout); // Resize ;-)
        static int GetDefaultPort(RfcProtocol protocol);
        
    };

}

#endif
