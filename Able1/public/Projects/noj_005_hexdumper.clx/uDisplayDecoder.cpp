//---------------------------------------------------------------------------
#pragma hdrstop

#include "uDisplayDecoder.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void DisplayDecoder::DecodeText(const ByteBuffer& bb, Array<ZStr>& aResult)
   {
   aResult.Empty();
   ZStr sLine;
   for(int ss = 0L; ss < bb.Length(); ss++)
      {
      byte_t ich = bb[ss];
      if(ich == '\n')
         {
         // ASCII line break
         aResult[aResult.Nelem()] = sLine;
         sLine = "";
         continue;
         }
      if(ich < 32 || ich > 126)
         {
         // Binary character
         sLine.Append('_');
         continue;
         }
      // A normal character ...
      sLine.Append(bb[ss]);
      }

   if(!sLine.IsNull())
      {
      aResult[aResult.Nelem()] = sLine;
      sLine = "";
      }
   }

void DisplayDecoder::DecodeHex(const ByteBuffer& bb, Array<ZStr>& aResult, int chars_per_line)
   {
   ZStr sLine;
   aResult.Empty();
   ByteBuffer cx;
   for(size_t ss = 0L; ss < bb.Length(); ss++)
      {
      if(ss && (ss % chars_per_line) == 0)
         {
         // convert the buffer to hex
         cx.hexline(sLine, false, chars_per_line);
         aResult[aResult.Nelem()] = sLine;
         cx.empty();
         }
      cx.Append(bb[ss]);
      }
   if(cx.IsNull() == false)
      {
      cx.hexline(sLine, false, chars_per_line);
      aResult[aResult.Nelem()] = sLine;
      }
   }
