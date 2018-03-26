#include <Extra/Searching/DosMatch.Hpp>

// Returns the position AFTER the match;
size_t DosMatch::MatchMaskChars(const ZStr& sString, const ZStr& sMask)
   {
   ZStr sPattern = sString;
   size_t ssA = sPattern.Find(sMask);
   if(ssA != NPOS)
      return (ssA + sMask.Length() +1);
   return ssA;   
   }

const char *DosMatch::MaskPortion(const ZStr& sString, ZStr& sMask)
   {
   size_t ss = NULL;
   while(sString[ss] == '?')
      ss++;
   while(sString[ss] == '*')
      ss++;
   if(ss)
      {
      sMask = "";
      return sMask.c_str();
      }
   sMask       = &sString[ss];
   size_t chopA= sMask.Find('?');
   size_t chopB= sMask.Find('*');

   if( (chopA == (size_t)NPOS) && (chopB == (size_t)NPOS))
      return sMask.c_str();

   if(chopA == NPOS)
      chopA =  NULL;
   if(chopB == NPOS)
      chopB =  NULL;

   size_t chop = (chopA > chopB) ? chopA : chopB;

   sMask[chop] = NULL;
   return sMask.c_str();
   }

bool DosMatch::HasWildcard(const ZStr& std)
   {
   if(std.Find('?') != NPOS)
      return true;
   if(std.Find('*') != NPOS)
      return true;
   return false;
   }

bool DosMatch::Match(const ZStr& sPattern, const ZStr& sSubject)
   {
   bool br = false;
   size_t pp = NULL;
   size_t ss = NULL;

   // Fix the "1" == "123" fall-through error;
   if(HasWildcard(sPattern) == false)
      return (sPattern == sSubject);

   // Patterns can be smaller or the same size, but not larger;
   // (fixing another fall-through error);
   if(sPattern.Length() > sSubject.Length())
      return br;

   // Use the string's operator equal 
   // (avoids "" <> "", while "1" == "1") fall-through error;
   if((sPattern.Length() == sSubject.Length()) && (sPattern == sSubject))
      return true;

   // By this time, we HAVE wildcard(s) to expand. 
   // sSubject is assumed to be sane (asciiz);
   // *****
   while(sPattern[pp] && sSubject[ss])
      {
      if(sPattern[pp] == '?')
         {
         pp++;
         ss++;
         if(!sPattern[pp] && sSubject[ss])
            return false;
         br = true;
         continue;
         }
      if(sPattern[pp] == '*')
         {
         if(sPattern[pp + 1] == sSubject[ss])
            {
            size_t count = NULL;
            const char *pPat = &sPattern[pp + 1];
            const char *pSub = &sSubject[ss];
            while(*pPat && *pSub)
               {
               if(*pPat == *pSub)
                  {
                  count++;
                  pPat++; pSub++;
                  // Where we are going next?
                  if((*pPat == '?') || (*pPat == '*'))
                     {
                     // Okay, everything matched and tallied.
                     // Next pattern, please;
                     pp++;
                     break;
                     }
                  }
               else
                  return false;
               }
            pp += count;
            ss += count;
            br = true;
            }
         else
            {
            ss++;
            br = true;
            }
         continue;
         }
      if(sPattern[pp] != sSubject[ss])
         return false;

      br = true;
      pp++;
      ss++;
      }

   // See if the wild-card skipped-it-all, but failed to match the REST of 
   // the pattern specified in the mask;
   if(sPattern[pp] == '*' && sPattern[pp+1])
      return false;     // Yup: Not match, bubbo.

   return br;
   }
