/* 
 * File:   HttpWebService.hpp
 * Author: profnagy
 *
 * Created on April 16, 2012, 10:39 AM
 */

#ifndef HTTPWEBSERVICE_HPP
#define	HTTPWEBSERVICE_HPP

#include "a1net2.hpp"
#include "SocCommon.hpp"

namespace a1net2 {

    class HttpWebService : public SocCommon {
    public:

        CSocketError Download(URL url, File file);

        CSocketError Transact(URL url, File fileIn, File fileOut);
    };

}


#endif	/* HTTPWEBSERVICE_HPP */

