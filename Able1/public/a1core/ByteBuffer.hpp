// Class ByteBuffer: Used to manipulate arrays of same, with allignemnt.
//
// 03/03/1998, Class created, R. Nagy
// 03/18/1998, Added Read(is), Write(os), and operator==(), R. Nagy
// 04/28/1999, Added hexline(ZStr&), R. Nagy
// 05/19/1999, Added Assign(const void *, size_t), R. Nagy
// 05/21/1999, Fixed a classic "uni-buffer-freed" self-Assign(emnt bug, R. Nagy
// 12/02/2000, Added read_file(), read_bytes() and more, and fixed a bug or two, R. Nagy
// 11/30/2003: Renamed _hexdump xdump and made it public, R. Nagy
// 04/26/2003: Changed IsNull() to boolean usage, R. Nagy.
// 11/21/2004: Added a few members to integrate better into the Able1 paradigm, R. Nagy
// 11/08/2006: Added read_stream and write_stream - Exact same IO as ZStr, R. Nagy
// 11/12/2006: Removed byte_t - Most have figgured that one out by now, R. Nagy
// 09/11/2008: Renamed selected members to match new UpLow conventions, R. Nagy

#ifndef ByteBuffer_Hpp
#define ByteBuffer_Hpp

namespace Able1
   {
/** ByteBuffer is designed to manage an array of characters. The length
 *  of the buffer is managed by an encapsulated size_t.
 */
class ByteBuffer
   {
   private:
      size_t len;
      char *pBuf;

   public:
      ByteBuffer(void);
      ByteBuffer(const ZStr& str);
      ByteBuffer(const char *buf, size_t cb);
      ByteBuffer(size_t cb);
      ByteBuffer(const ByteBuffer& bb);
      ~ByteBuffer(void);

      void           Empty(void);

      bool           IsNull(void) const;    // 1 == true

      void           Hexline(ZStr&, bool address = true, int option_base = 16) const;
      void           Hexdump(ostream&, bool address = true, int option_base = 16) const;
      void           Xdump(ostream& os, bool address = true, int option_base = 16) const;

      const char *   Bytes(void)  const   {return pBuf;}
      size_t         Length(void) const   {return len;}

      void Assign(const char *pin, size_t ss);
      void Assign(const void   *pin, size_t ss);
      void Assign(const ZStr& str);

      void Fill(char ch = NULL);
      void Prepend(const ByteBuffer& by);

      void Append(const ByteBuffer& by);
      void Append(char by);
      void Append(void *psz, size_t nelem);

      void PadToAlignment(size_t mod);

      ByteBuffer& operator=(const ByteBuffer& bb);
      ByteBuffer& operator=(const ZStr& str);
      int         operator==(const ByteBuffer& bb);
      char      operator[](size_t ss) const {return pBuf[ss];}

      ostream& Write(ostream& os) const;
      istream& Read(istream& is);
      size_t   ReadFile(istream& fs);
      size_t   ReadBytes(istream& is, size_t);

      // Common stream format - as shared with ZStr -
      ostream& WriteStream(ostream& os) const;
      istream& ReadStream(istream& is);
   };

   } // Able1
#endif
