// Class StdSocket: This class is depricated. Use stdnet, instead.
//
// Class created 12/22/1997, R. A. Nagy (WinSock2 version)
//
// Testing results;
// ===============
// "news.iol.it",        119           (worked okay)
// "smtp.ix.netcom.com", IPPORT_SMTP   (worked okay)
// "nntp.ix.netcom.com", 119           (worked okay)
// "popd.ix.netcom.com", IPPORT_MTP    (did not work: it's something other than _MTP!)
//
// 12/24/1997: Added select(TIMEOUT) to IO to keep from blocking-forever, R. Nagy.
//             Added MonitorConnection(), R. Nagy.
// 01/21/1998: Added the Trace facility, R. Nagy.
// 01/31/1998: Implemented the timeout_ai, R. Nagy.
// 12/03/1998: Added timeout value to ::Transact(), R. Nagy.
// 09/23/2003: Ported to Able1, R. Nagy
// 09/24/2003: Changed SOC_TIMEOUT from 100L to 15L (untested), R. Nagy
// 09/15/2006: RETIRED: This class is obsolete. Use nojnet::NetSocket, instead!
//
#ifndef zStdSocket_Hpp
#define zStdSocket_Hpp

// NOTE: Borland uses the older version of windows sockets. Be sure to globally define
// _WINSOCKAPI_ to turn it off!

//#include <presto.hpp>
#ifdef WIN32
#include <winsock2.h>

#include <extra/stdlog.hpp>

const size_t SOC_BUFFER_SZ = 10240; // Most postings are under this size, most attachments are well over..
const long SOC_TIMEOUT = 15L; // Supposed to be seconds, but ..?

class StdSocket {
private:
    long timeout_ai; // This value is adjueted upward to accomidate service slowdowns, etc..
    int connected; // Please don't make the user worry about an "IsConnected()", okay?
    SOCKET port; // -the purpose of this class is to hide the gory details from the user,
    fd_set fdset; // no? -Enough to tell them that we're connected, or no, from the API result.

    int GETLINE(istream&, ostream&, char *, size_t, int& capture, int& converse);
    void LOG(ostream& cout, const char *pszBuf, int capture = 0);
    void LOG_LINE(const char *pszBuf);
    void LOG_LINE(ostream& cout, const char *pszBuf, int capture = 0);

protected:
    StdLog *pTrace;

    fd_set *OneFd(void);

public:
    StdSocket(void);
    virtual ~StdSocket(void);

    // Returns * to logger, in exchange for yours; NULL is okay for both. Deleted on exit.

    virtual StdLog *Trace(StdLog *pt) {
        StdLog *po = pTrace;
        pTrace = pt;
        return po;
    }

    virtual bool Trace(void) {
        return (pTrace) ? true : false;
    }

    virtual void Trace(const ZStr& sLogNam) {
        delete pTrace;
        pTrace = new StdLog(sLogNam);
    }

    // Notice that we default to INTERNET connections (AF_INET);
    bool Connect(const ZStr& sHostName, u_short service_port = IPPORT_ECHO, int af_which = AF_INET);
    void Disconnect(void);

    // This will monitor an existing connection;
    void MonitorConnection(ostream& cout, istream& cin);

    bool Send(const ZStr& std, long timeout = SOC_TIMEOUT);
    bool Receive(ZStr&, size_t sz_largest_expected_from_service = SOC_BUFFER_SZ, long timeout = SOC_TIMEOUT);
    // Response will contain `delim`, and perhaps a little more (depending on host response);
    bool TransactResponseContaining(const ZStr& stdIn, ZStr& stdOut, const char delim = '\n', long l_timeout = SOC_TIMEOUT);
    // Response will only contain what is available on-the-socket (i.e: might not be the ENTIRE host response (a polling / latency thing));
    bool Transact(const ZStr& in, ZStr& out, long timeout = SOC_TIMEOUT);

    const char *GetLastError(void);
    int GetLastErrorCode(void);

    // This is usefull for gang-operations on many sockets 
    // (i.e: a select() that uses a mess of StdSockets);

    operator SOCKET(void) {
        return port;
    }
};

#else
#include <sys/types.h>
#include <sys/socket.h>

// We need to re-do this for UNIX.

#endif

#endif
