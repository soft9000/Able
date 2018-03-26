// NodeFact unifies all of the Nodes and their factories into a single
// usefull point of reuse.
//
// 07/15/1998: Added NodeCollection and GenericNodeArray<node_t>, R. Nagy.
// 11/13/2004: Converted to static usage, R. Nagy
// 12/30/2007: Added TimeFormatter.hpp, R. Nagy
//
#ifndef _FileSystem_HPP
#define _FileSystem_HPP

namespace Able1
   {
/** FileSystem is the lowest-level encapsulation of platform operations.
  */
class FileSystem
   {
   public:
      static size_t Nelem(const ZStr&);

      static size_t Query(const ZStr&, Array<Node>& aResult);
      static size_t Query(const ZStr&, Array<File>& aResult);
      static size_t Query(const ZStr&, Array<Directory>& aResult);

      static bool Create(Node&);
      static bool Create(File&);
      static bool Create(Directory&);

      static bool Delete(Node&);
      static bool Delete(File&);
      static bool Delete(Directory&);

      static PortTime Query(const Node&);           // Not implemented yet.
      static PortTime Query(const File&);           // Not implemented yet.
      static PortTime Query(const Directory&);      // Not implemented yet.

      static bool Touch(Node&, PortTime& pt);       // Not implemented yet.
      static bool Touch(File&, PortTime& pt);       // Not implemented yet.
      static bool Touch(Directory&, PortTime& pt);  // Not implemented yet.
   };


   } // Able1

#endif

