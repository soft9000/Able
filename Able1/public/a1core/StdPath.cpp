#include <Able1.hpp>
using namespace Able1;

namespace Able1
{

StdPath::Path::Path(const Path& ref)
   {
   sPath = ref.sPath;
   }
StdPath::Path::Path(const ZStr& ref)
   {
   *this = ref;
   }
StdPath::Path& StdPath::Path::operator=(const ZStr& s)
   {
   ZStr str = s;
   if(str.IsNull())
      {
      sPath = str;
      return *this;
      }
   // Paths
   //   -All use a POSIX (or Internet) path naming convention
   str.Replace('\\', '/');
   //   -Do not have mount points ("d:", "ftp:". etc.)
   str.RemovePos(0, str.Find(':'));
   //   -Do not have a leading "//"
   str.Replace("//", '/');
   size_t whence = str.Length()-1;
   //   -Do not end with '/'
   if(str[whence] == '/')
      str.Remove(whence);
   //   -Begin with either '/', './', or '../'
   sPath = str;
   return *this;
   }
StdPath::Path::operator ZStr(void)
   {
   ZStr str = sPath;
   return str;
   }
ostream& StdPath::Path::Write(ostream& os)
   {
   sPath.WriteStream(os);
   return os;
   }
istream& StdPath::Path::Read(istream& is)
   {
   sPath.ReadStream(is);
   return is;
   }

bool StdPath::_relate(const ZStr& sFull, ZStr& sResult)
   {
   sResult = "";
   ZStr str = sFull;

   str.Replace("/./", '/');      // it happens...

   // Is there anything to expand?
   if(str.Find("../") == npos)
      {
      sResult = str;
      return true;
      }

   // Check if a node requires the relative elimination of any previous nodes
   Array<ZStr> array;
   PipeArray::Parse(array, str, '/');
   if(!array.Nelem())
      {
      sResult = str;
      return true;
      }

   // By now, we should have a mount point. Relative prefixes are now illegal...
   if(array[0] == "..")
      return false;
   if(array[0] == ".")
      return false;

   // Resolve relative
   size_t ss = 0L;
   for(ss = 1; ss < array.Nelem(); ss++)
      {
      if(array[ss] == "..")
         {
         // Remove the prior, non-null, non-relative node
         size_t prev = ss;
         while(array[prev].IsNull() && array[prev] != "..")
            {
            if(prev == 0)
               {
               prev = -1L;
               break;
               }
            prev--;
            }
         if(prev != -1L)
            array[prev] = "";
         array[ss] = ""; // remove the relative markup indicator
         }
      }
   // Finally, we build the final result;
   for(ss = 0; ss < array.Nelem(); ss++)
      {
      sResult.Append(array[ss]);
      sResult.Append('/');
      }
   return true;
   }
bool StdPath::_resolve(const ZStr& sMount, const ZStr& sNode, ZStr& sResult)
   {
   ZStr str = sMount;
   str.Replace('\\', '/'); // normalize it
   if(str[str.Length()-1] != '/')
      str.Append('/');
   str += sNode;
   return _relate(sNode, sResult);
   }
bool StdPath::Mount(const Path& path, const Url& url, Url& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path& path, const Url& url, File& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path&, const Url& url, Directory& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path&, const File& file, File& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path& path, const File& file, Url& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path& path, const Directory& dir, Directory& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
bool StdPath::Mount(const Path&, const Directory& dir, Url& uResult)
   {
/* TODO 1 -oR. Nagy -c<<<WIP>>> : Need to finish this, as required. */
   return false;
   }
} // Able1

