/* 
 * File:   HttpWebService.cpp
 * Author: profnagy
 *
 * Created on April 16, 2012, 1:20 PM
 */

#include "SimpleSockets/ActiveSocket.h"


#include "HttpWebService.hpp"

#ifdef UNIX
#define _LINUX
#endif

#include "SimpleSockets/SimpleSocket.h"


using namespace a1net2;

SocCommon::CSocketError HttpWebService::Download(URL url, File file) {
    CActiveSocket soc;
    if (soc.Open((uint8 *)url.GetServer().c_str(), url.GetPort()) == false)
        return soc.GetSocketError();

    ostream& os = file.OpenWrite(File::AT_BINARY);
    long bytes = soc.Receive(os); // TODO!
    uint8 *pbyes = soc.GetData();
    os.flush();
    file.Close();
    soc.Close();
    return soc.GetSocketError();
}

SocCommon::CSocketError HttpWebService::Transact(URL url, File fileIn, File fileOut) {
    return SocCommon::SocketError;
}



