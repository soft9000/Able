// 11/24/2004: Created to better support compiling under G++, R. Nagy
//

#ifndef _Common_Object_hpx
#define _Common_Object_hpx

namespace Able1 {
   class ZStr;
   
   /** CommonObjects can be both created and stored using strings.
     * When empty, the object should return NULL.
     */
   class CommonObject
      {
      public:
         CommonObject(void) {}
         virtual ~CommonObject(void) {}

         virtual bool        FromString(const ZStr&) = 0;
         virtual const char *ToString(ZStr&) const   = 0;
         
         ZStr           ToString(void) const {ZStr str; ToString(str); return str;}

         virtual bool IsNull(void) const;

         virtual bool        Transfer(ostream& os);
         virtual bool        Transfer(istream& os);
      };


   /** References to sharable object can be exchanged between both platform
     * and platform independant applications. For this reason, they should
     * share some common operations.
     */
   class ShareableObject : public CommonObject
      {
      public:
         ShareableObject(void) {}
         virtual ~ShareableObject(void) {}

         // DOC: "Liberates" a node name by removing any platform specific 
         // file naming conventions. Great for device and platform
         // independant string comparisons.
         virtual ZStr LiberatedName(char chSep = '|');
      };
      
} // Able1

#endif
