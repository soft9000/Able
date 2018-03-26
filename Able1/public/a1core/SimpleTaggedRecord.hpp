// 09/15/2008: Created. R. Nagy
//

#ifndef STaggedRecord_hpp
#define STaggedRecord_hpp


namespace Able1
{
/** SimpleTaggedRecord allows us to use templates (like StdSeek<T>)
 * to store an Array<T> of SimpleTagValue.
 */
struct SimpleTaggedRecord
{
   Array<SimpleTagValue> record;

   /** IsNull.
    *
    * @return True if payload is unassigned.
    */
   bool IsNull(void)
      {
      if(record.Nelem() == 0L)
         return true;
      return false;
      }

   /**
     * Conveniance function. Uses Array.AddZombies.
     */
   void AddZombies(size_t sz)
      {
      record.AddZombies(sz);
      }

   /**
     * Conveniance function. Uses Array.Append.
     */
   void Append(const SimpleTagValue& ref)
      {
      record.Append(ref);
      }

   /** Write the payload.
    *
    * @param os The stream.
    * @return The stream.
    */
   ostream& Write(ostream& os)
      {
      return record.Write(os);
      }

   /** Read the payload.
    *
    * @param is The stream.
    * @return The stream.
    */
   istream& Read(istream& is)
      {
      return record.Read(is);
      }
};

}
#endif
