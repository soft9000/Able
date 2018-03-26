// StdOid Namesapce: Objective was to create a updatable, newline-indepentant
// object naming and object property specification. Purpose is to allow for
// users to MANAGE a file full of MIXED types with heterogenous properties.
// Properties that can be quickly read and maintained by ANY program.
//
// 01/02/2007: Class created, R. Nagy
//
#ifndef StdOidR_Hpp
#define StdOidR_Hpp

namespace Able1
{
namespace Oid
{
class OidRegistry
   {
   public:

      static bool QueryRootRegistry(Directory& dirHome);
      static bool QueryServerRegistry(Directory& dirHome, const ZStr& sParamID, bool bCreate = false);
      static bool Exists(const ZStr& sParamID, const File& file);
      static ZStr HashName(const File& file);

      class RegClient
         {
         protected:
            static bool GetFile(const ZStr& sParamID, File& fileResult);
         public:
            // Check to see if you were started with one or more sParamIDs
            static bool Recall(int argc, char *argv[], Array<ZStr>& aParamID);
            static bool Recall(const ZStr& str, Array<ZStr>& aParamID); // (WimMain, etc.)

            // See if we have a parameter (from the RegServer)
            // EXTRACTS AND REMOVES THE PARAMETER FROM THE REGISTRY!
            static bool PopParam(const ZStr& sParamID, OidTag& ref);

         };
      class RegServer
         {
         protected:
            static bool GetFile(const File& fileProgram, const ZStr& sParamID, File& fileResult);
         public:
            // Runs the program offering OigTag as a parameter - Pram block IS SAVED UNTIL THE PROGRAM CALLS PopParam(above)
            static bool Invoke(const ZStr& sParamID, const File& file, const OidTag& oid);
            // Queryies the program for an "sParamID" parameter set
            static bool Query(const File& file, OidTag& oid);

            // Anyone can push a param - just be sure that your sParamID and / or file are unique
            // by using Exists(above)
            static bool PushParam(const ZStr& sParamID, const File& file, const OidTag& oid);

         friend class OidRegistry;
         };
   };

} // namespace Oid
} // namespace Able1

#endif
