
#ifndef z_EMailModifier
#define z_EMailModifier

#include <Able1.hpp>
using namespace Able1;

class EMailModifier
   {
   protected:
      EMail *pEm;
   public:
      EMailModifier(void)  : pEm(NULL)    {}
      virtual ~EMailModifier(void)        {}
      void Assign(EMail *pem)             {pEm = pem;}

      // Outbound modifiers;
      bool To(const ZStr& sto)          {if(!pEm) return false; pEm->_to      = sto; return true;}
      bool Newsgroups(const ZStr& sto)  {if(!pEm) return false; pEm->_newsg   = sto; return true;}
      bool From(const ZStr& sto)        {if(!pEm) return false; pEm->_from    = sto; return true;}
      bool Subject(const ZStr& sto)     {if(!pEm) return false; pEm->_subject = sto; return true;}
      bool Message(const ZStr& sto)     {if(!pEm) return false; pEm->_text    = sto; return true;}

      // Other modifiers <<<WIP>>>
      bool Forward(const ZStr& ToList)  {return false;}
      bool ReplyAll(void)                    {return false;}
      bool ReplySender(void)                 {return false;}
   };

#endif

