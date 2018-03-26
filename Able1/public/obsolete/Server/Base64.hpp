// 09/23/2003: Ported to Able1, R. Nagy
#ifndef base64_ed_h
#define base64_ed_h

#include <Able1.hpp>

using namespace Able1;

class Base64
   {
   protected:
      TROOL _encode(const char *_in, unsigned inlen, char *_out, unsigned outmax, unsigned *outlen);
      TROOL _decode(const char *in, unsigned inlen, char *out, unsigned *outlen);
   public:
      // Destructive usage:
      bool Encode(ZStr& strIO);
      bool Decode(ZStr& strIO);
      // Non-destructive:
      bool Encode(const ZStr& sIn, ZStr& sOut);
      bool Decode(const ZStr& sIn, ZStr& sOut);
   };

#endif



