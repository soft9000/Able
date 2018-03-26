//---------------------------------------------------------------------------

#ifndef uDisplayDecoderH
#define uDisplayDecoderH
//---------------------------------------------------------------------------


#include <FastJob.hpp>

using namespace FastJob;

class DisplayDecoder
{
public:
   void DecodeText(const ByteBuffer& bb, Array<StdString>& aResult);
   void DecodeHex(const ByteBuffer& bb, Array<StdString>& aResult, int chars_per_line = 16);
   void DecodeBlock(const ByteBuffer& bb, Array<StdString>& aResult, int chars_per_line = 16);
};


#endif
