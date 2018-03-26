// 06/21/2003: Need to modernize my huge legacy.
// 08/21/2004: Renamed more headers from older to newer (cstdio, etc.)
// 11/13/2004: Added CommonObject. Applied parentage to File, Directory, and Node, R. Nagy
// 11/24/2004: Compiling under MSDOS, R. Nagy
// 02/07/2008: Added Heap<T>, R. Nagy
// 05/26/2008: Minor cleanup to eliminate warnings & problems under GPP, R. Nagy
// 06/17/2008: Problems under MSVS6 - Cleaned up the headers so everything uses it the same way. Compiled faster, too, R. Nagy
// 06/19/2008: Cleanup continues. New namespace for Oid. XmIni, PicketFile, + others moved into Able1, R. Nagy
// 08/30/2008: Created SimpleTagValue, our replacement for NameTaggedRecord. R. Nagy
// 09/14/2008: Added IpcMutex to help R&D of new CentOS Web Server CGI Framework, R. Nagy
//
#ifndef zAble1_ns
#define zAble1_ns

//#ifndef __GNUG__
//#endif

#include <a1core/stdheader.hpp>
using namespace std;


#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

/*! \namespace Able1
 * \brief This namespace is the official rewrite of the FastJob Namespace. 
 *        The objective is to (1) rid ourselves of lower-case class signatures, 
 *        (2) Migrate to STL containership, as well as to (3) complete a light 
 *        cleanup of some other annoying class member signatures / usages.
 *
 * NOTE: Able1 is the 2nd generation offspring of the stdnoj namespace. 
 *
 */
namespace Able1
   {
   /**
    * class ZStr
    *
    * @author R. Nagy
    * @comment Considering the gradual introduction of JAVA style documentation a-la CppDoc -
   */
   class ZStr;

   class ShareableObject;
   class FilePath;
   class File;
   class Directory;
   class Node;

   const size_t MIN_GROW_SPACE      = 12;
   const size_t MAX_READ_DEFAULT    = 10240;
   const size_t npos = ((size_t)-1L);
   const size_t NPOS = npos;

   const size_t A1_MAX_TOKEN  = 1024;   // a reasonable buffer size for token-parsing
   }

#include <a1core/Array.hpp>
#include <a1core/ZStr.hpp>

#include <a1core/BigFileSize.hpp>
#include <a1core/Random.hpp>
#include <a1core/CompArray.hpp>
#include <a1core/StringMatcher.hpp>

namespace Able1
   {
   /**
    * PRESTO:
    * @param srm A stream
    * @result A project string
    * @comment This function used to be the way to stop strstream memory leaks.
    * It was the very reason why ZStr had an "own" capability. These days
    * it just converts between STL strings and the project string class.
    */
   ZStr PRESTO(stringstream& srm);

   typedef int TROOL;
   const int tTRUE = (int)true;
   const int tFALSE= (int)false;
   const int tERROR= 9;

#ifndef WIN32
   typedef int XHANDLE;
#endif
#ifndef MAX_PATH
   const int MAX_PATH = 256;
#endif

   extern ZStr LOG_PATTERN; // Default, as used by logging - (ExeLog, etc)

   } // Able1;


#include <a1core/ByteBuffer.hpp>
#include <a1core/CommonObject.hpp>
#include <a1core/Node.hpp>
#include <a1core/FilePath.hpp>
#include <a1core/File.hpp>
#include <a1core/Directory.hpp>
#include <a1core/Utilities.hpp>

#include <a1core/StdDateTime.hpp>
#include <a1core/TimeFormatter.hpp>
#include <a1core/PortTime.hpp>

#include <a1core/BigFileSize.hpp>

#include <a1core/NodeWalker.hpp>
#include <a1core/NodeFinder.hpp>
#include <a1core/FileSystem.hpp>

#include <a1core/ProgramId.hpp>
#include <a1core/RecArray.hpp>
#include <a1core/StdSeek.hpp>
#include <a1core/DFOArray.hpp>
#include <a1core/dfo.hpp>

#include <a1core/Platform.hpp>
#include <a1core/Url.hpp>
#include <a1core/StdPath.hpp>

#include <a1core/StdOid.hpp>

#include <a1core/DelimiterSet.hpp>
#include <a1core/OidMeta.hpp>
#include <a1core/TagValue.hpp>
#include <a1core/OidTag.hpp>
#include <a1core/OidSender.hpp>
#include <a1core/OidParamQuery.hpp>
#include <a1core/OidParamTest.hpp>
#include <a1core/OidList.hpp>
#include <a1core/OidController.hpp>
#include <a1core/OidRegistry.hpp>

#include <a1core/XmIni.hpp>
#include <a1core/PicketFile.hpp>
#include <a1core/DynamicPicketFile.hpp>
#include <a1core/Platform.hpp>
#include <a1core/ExeLog.hpp>
#include <a1core/JulianLog.hpp>
#include <a1core/SimpleTagValue.hpp>
#include <a1core/SimpleTaggedRecord.hpp>
#include <a1core/IpcMutex.hpp>

#endif
