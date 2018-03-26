#include <Able1.hpp>
using namespace Able1;
using namespace Able1::Oid;


bool Block::Parse(const ZStr& sBuffer, const ZStr& sStart, const ZStr& sEnd, Array<Block>& aResult)
{
aResult.Empty();

// Detect bad delimiters -
if(sStart == sEnd)
   return false;
if(sStart.Find(sEnd) != npos)
   return false;
if(sEnd.Find(sStart) != npos)
   return false;

const char chOn  = char(0xfd);
const char chOff = char(0xfe);

// Good is good enough - for now -
if(sBuffer.Find(chOn) != npos)
   return false;
if(sBuffer.Find(chOff) != npos)
   return false;

// Make parsing it all a lot easier - (127)
ZStr sBuf = sBuffer;
sBuf.Replace(sStart, chOn);
sBuf.Replace(sEnd, chOff);

// Split it up
bool bFound = false;
int level = 0;
char ch   = 0;

Block bkResult;

for(size_t ss = 0; ss < sBuf.Length(); ss++)
   {
   ch = sBuf[ss];
   if(ch == chOn)
      {
      // Scan along until we find the FIRST delimiter -
      if(level != 0)
         {
         // Preserve any CHILD delimiters -
         bkResult.sPayload.Append(sStart);
         }
      level++;
      continue;
      }
   if(ch == chOff)
      {
      level--;
      if(level == 0)
         {
         // Save the result after we find the LAST delimieter -
         aResult.Append(bkResult);
         bkResult = Block();
         bFound = true;
         continue;
         }
      // Preserve any CHILD delimiters -
      bkResult.sPayload.Append(sEnd);
      continue;
      }

   // Only start BLOCK recording AFTER we find the FIRST delimeiter
   if(!level)
      {
      bkResult.sPrefix.Append(ch);
      continue;
      }

   // BLOCK recording
   bkResult.sPayload.Append(ch);
   }

// NO CLEANUP - If the delimiters are mismatched, then we GIGO -
return bFound;
}

ZStr Block::Compose(const ZStr& sStart, const ZStr& sEnd, const Array<Block>& aResult)
{
ZStr sResult;

// Detect bad delimiters -
if(sStart == sEnd)
   return sResult;
if(sStart.Find(sEnd) != npos)
   return sResult;
if(sEnd.Find(sStart) != npos)
   return sResult;

stringstream srm;
for(size_t ss = 0L; ss < aResult.Nelem(); ss++)
   {
   Block& blk = aResult.Get(ss);
   srm << blk.sPrefix;
   srm << sStart;
   srm << blk.sPayload;
   srm << sEnd;
   }
sResult = PRESTO(srm);
return sResult;
}

