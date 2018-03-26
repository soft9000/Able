/* We extracted CSocketError from SimpleSockets so as to quickly use the 
 * enumerated type as a bridge between the two frameworks.
 * 
 * File:   CSocketError.hpp
 * Author: profnagy
 *
 * Created on April 16, 2012, 11:19 AM
 */

#ifndef CSOCKETERROR_HPP
#define	CSOCKETERROR_HPP

class SocCommon {
public:

    /// Defines all error codes handled by the CSimpleSocket class.

    typedef enum {
        SocketError = -1, ///< Generic socket error translates to error below.
        SocketSuccess = 0, ///< No socket error.
        SocketInvalidSocket, ///< Invalid socket handle.
        SocketInvalidAddress, ///< Invalid destination address specified.
        SocketInvalidPort, ///< Invalid destination port specified.
        SocketConnectionRefused, ///< No server is listening at remote address.
        SocketTimedout, ///< Timed out while attempting operation.
        SocketEwouldblock, ///< Operation would block if socket were blocking.
        SocketNotconnected, ///< Currently not connected.
        SocketEinprogress, ///< Socket is non-blocking and the connection cannot be completed immediately
        SocketInterrupted, ///< Call was interrupted by a signal that was caught before a valid connection arrived.
        SocketConnectionAborted, ///< The connection has been aborted.
        SocketProtocolError, ///< Invalid protocol for operation.
        SocketFirewallError, ///< Firewall rules forbid connection.
        SocketInvalidSocketBuffer, ///< The receive buffer point outside the process's address space.
        SocketConnectionReset, ///< Connection was forcibly closed by the remote host.
        SocketAddressInUse, ///< Address already in use.
        SocketInvalidPointer, ///< Pointer type supplied as argument is invalid.
        SocketEunknown ///< Unknown error please report to mark@carrierlabs.com
    } CSocketError;
};

#endif	/* CSOCKETERROR_HPP */

