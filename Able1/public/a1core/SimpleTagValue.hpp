// 08/30/2008: Created. R. Nagy
//

#ifndef STagValue_hpp
#define STagValue_hpp


namespace Able1
{
/** SimpleTagValue is a functional replacement for NameTaggedRecord.
 * Since the former was never released to the public, IUO will
 * need to defer to the FastJob namespace for legacy support.
 */
struct SimpleTagValue
{
   /**
    * The tag valued used to delimit array Write()ing and Read()ing.
    * Indicates that the sValue had the Nelem() of the items to be read.
    */
   static ZStr sTagSync;

   /** Public.
     */
   ZStr sTag;

   /* Public.
    */
   ZStr sValue;

   /** Constructor.
     */
   SimpleTagValue(void);

   /** Constructor.
     */
   SimpleTagValue(const ZStr& sT, const ZStr& sV);

   /** Constructor.
     */
   SimpleTagValue(const ZStr& sT, int iVal);

   /** IsNull.
    *
    * @return True of the pair have been unassigned.
    */
   bool IsNull(void);

   /** Write the set.
    *
    * @param os The stream.
    * @return The stream.
    */
   ostream& Write(ostream& os);

   /** Read the set.
    *
    * @param is The stream.
    * @return The stream.
    */
   istream& Read(istream& is);

   /** Peeks to return the stored count of records in a file.
    *
    * An array is a controlled storage of records. As such, the have a
    * stream indication as to how many have been written.
    *
    * @param file Input.
    * @return The number of SimpleTagValues in the file.
    */
   static size_t TallyArray(const File& file);

   /** Loads array-style records from a file.
    *
    * An array is a controlled storage of records. As such, the have a
    * stream indication as to how many have been written.
    *
    * @param file Input.
    * @param result Results.
    * @return True if file was formatted as expected (i.e. it might have 
    *         loaded zero records, but still be a valid Array formatted file.)
    */
   static bool LoadArray(const File& file, Array<SimpleTagValue>& result);

   /** Counts heap records in a file.
    *
    * A heap is simply a dump of records that do not have any
    * stream indication as to how many have been written.
    *
    * @param file Input.
    * @return The number of SimpleTagValues in the file.
    */
   static size_t TallyHeap(const File& file);

   /** Loads heap records from a file.
    *
    * A heap is simply a dump of records that do not have any
    * stream indication as to how many have been written.
    *
    * @param file Input.
    * @param result Results.
    * @return True if anything was loaded.
    */
   static bool LoadHeap(const File& file, Array<SimpleTagValue>& result);

   /** Tally the array of elements sharing a common TAG value.
    *
    * @param array The set.
    * @param sTag  The common TAG value.
    * @return The number of eleentes sharing the common tag identifier.
    */
   static size_t TallyTag(Array<SimpleTagValue>& array, const ZStr& sTag);

   /** Retrieve an array of elements from another array, as identified by
    * a common TAG value.
    *
    * @param array The superset.
    * @param sTag  The common TAG value.
    * @return The subset, if any. Can be empty.
    */
   static Array<SimpleTagValue> FindTag(Array<SimpleTagValue>& array, const ZStr& sTag);

   /** Retrieve THE FIRST element from another array, as identified by
    * a common TAG value.
    *
    * @param array The superset.
    * @param sTag  The common TAG value.
    * @return The result, if any. Can be NULL.
    */
   static SimpleTagValue FindFirstTag(Array<SimpleTagValue>& array, const ZStr& sTag);

   /** Write a string array to a stream, tagging each element.
    * Includes the number of elements in the array for FAST Read()ing.
    *
    * @param array  Where the results go
    * @param sTag   The tag that we will write the LOGICAL point in the
    *         stream. (i.e. after the Nelem() tally for same)
    * @param os     The stream
    * @return True if we got 'em all.
    */
   static bool WriteTagedSeries(Array<ZStr>& array, const ZStr& sTag, ostream& os);


    /** Read the result of a WriteTaggedSeries into the result.
     *
     * @param result Where the results go
     * @param sTag   The tag that we should find at this LOGICAL point in the
     *         stream. (i.e. after the Nelem() tally for same)
     * @param is     The stream
     * @return True if we got 'em all.
     */
   static bool ReadTagedSeries(Array<ZStr>& result, const ZStr& sTag, istream& is);
};

}
#endif
