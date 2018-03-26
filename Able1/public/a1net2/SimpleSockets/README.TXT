2012/04/16: We will attempt to encapsulate "SimpeScoket" at the driver layer.
We will need to test our encapsulation across the "big 3" platforms 
before final acceptance / endorsement.

Approach was to simply:

  o Extract the _support/Release_clsockets_1_4_3.tgz to SimpleScoket
  o Move (as needed) or delete the CSimpleSocket::CSocketError into SocCommon::CSocketError
  o Change CSimpleSocket to inherit from SocCommon


