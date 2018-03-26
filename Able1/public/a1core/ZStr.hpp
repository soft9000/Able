// 06/21/08: ZStr created by copying ZStr & renaming / refactoring same, R. Nagy
// 10/22/08: Added IsAlNum(), R. Nagy
//
#ifndef ZStr_hpp
#define ZStr_hpp

namespace Able1 {

    class ZStr // DOC: The `ZStr` class and it's derivatives are copyright (c) 1997 - 2008 by R. A. Nagy. Permission is granted to use and modify these classes as long as copyright holder is not held responsible for any problems resulting from use. All rights reserved.
    {
    private:
        char *psz_alloc;
        size_t sz_alloc;
        size_t max_read;
        void _init(void);
        char * strrev(char *) const;

    protected:
        size_t extra_bytes;
        // "case insensitive" comparison functions;
        char *ci_strstr(const char *str1, const char *str2, int ignore_case = 0) const;
        int ci_strcmp(const char *str1, const char *str2, int ignore_case = 0) const;
        char *ci_strchr(const char *str1, char ch, int ignore_case = 0) const;

        char *_Substr(const char *psz, size_t start, size_t end = npos) const;

        // instance_growth_space can be arbitrarily HUGE so as to create a RAM "byte cache".
        // NOTE THAT THE VALUE APPLIES TO THE LOCAL INSTANCE ONLY! This limitation means
        // that your instance_growth_space WILL NOT be re-Assign(ed via operator=, so any
        // "wasted space" at the end of a huge buffer can be easily reclaimed by simple
        // re-Assign(emnt;
        void instance_growth_space(size_t sz); // DOC: Allows you to create an instance-based cache-size for string-growth.

    public:

        enum StripType {
            Leading, Trailing, Both
        };

        ZStr(void) {
            _init();
        } // DOC: Object constructor - default.

        ZStr(const ZStr& ss) {
            _init();
            Assign(ss);
        } // DOC: Object constructor for itself.

        ZStr(const char *ss) {
            _init();
            Assign(ss);
        } // DOC: Object constructor for a char pointer.

        ZStr(char ch) {
            _init();
            Assign(ch);
        } // DOC: Object constructor for a char.

        ZStr(int iss) {
            _init();
            Assign(iss);
        } // DOC: Object constructor for an int.

        ZStr(long iss) {
            _init();
            Assign(iss);
        } // DOC: Object constructor for a long.

        ZStr(bool iss) {
            _init();
            Assign(int(iss));
        } // DOC: Object constructor for a bool.

        ZStr(char ch, size_t size) // DOC: Object constructor. Creates a string containing the series of n chars.
        {
            _init();
            char *pBuf = new char[size + 1];
            ::memset(pBuf, ch, size);
            pBuf[size] = 0L;
            Own(pBuf);
        }

        virtual ~ZStr(void); // DOC: Virtual object destructor.

        void Iomax(size_t sz); // DOC: Allows you to over-ride the default i/o buffer size.
        size_t Iomax(void); // DOC: Returns the value set-up by iomax(size_t).
        size_t instance_growth_space(void); // DOC: Returns the value set-up by instance_growth_space(size_t).

        const char *Own(char *psz); // ASCIIZ buffers, only!               // DOC: CAUTION! ASCIIZ strings only! Member expects a string from an externally, dynamically-allocated, source. Will free same upon object destruction (i.e: ownership transferes in). Allocation *MUST* occur with `new char[n]`, as `delete [] *psz` is used.
        const char *Own(char *psz, size_t); // DOC: CAUTION! Member expects a string from an externally, dynamically-allocated, source. Will free same upon object destruction (i.e: ownership transferes in). Allocation *MUST* occur with `new char[n]`, as `delete [] *psz` is used.

        int Equals(const ZStr& ss, int ignore_case = 0) const;

        ZStr& Assign(const char *psz, size_t start, size_t end = npos); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(const char *psz_alloc); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(const ZStr& ss); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(char ch); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(int); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(long); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(istream&); // DOC: Assigns item to object. Prior contents (if any) are destroyed.
        ZStr& Assign(const string& str);

        ZStr& Append(const char *psz, size_t start, size_t end = npos); // DOC: Insert item from `start` to `end` (inclusive) at the end of the string. Default includes all characters at and after 'start'.
        ZStr& Append(const char *psz_alloc); // DOC: Insert item at the end of the string (after last char).
        ZStr& Append(const ZStr& ss); // DOC: Insert item at the end of the string (after last char).
        ZStr& Append(char ch); // DOC: Insert item at the end of the string (after last char).
        ZStr& Append(char ch, size_t count); // DOC: Append a number of a single char.

        ZStr& Prepend(const char *psz_alloc); // DOC: Insert item at the begining of the string (before first char).
        ZStr& Prepend(const ZStr& ss); // DOC: Insert item at the begining of the string (before first char).
        ZStr& Prepend(char ch); // DOC: Insert item at the begining of the string (before first char).

        size_t Length(void) const; // DOC: Returns the number of bytes in the string using strlen(STDLIB). Returns the number of characters in string, excluding the terminal NULL.
        void Reverse(void); // DOC: Inverts the string.
        void ToUpper(void); // DOC: Converts string to upper-case using toupper(STDLIB).
        void ToLower(void); // DOC: Converts string to lower case using tolower(STDLIB).
        void ToUpLow(void);
        const char *c_str(void) const; // DOC: Returns the null-terminated string.

        bool IsNull(void) const; // DOC: Returns 1 is the string is empty (i.e: (*this)[0] == NULL).
        bool IsWhite(char) const; // DOC: Base testing for is_white().
        bool IsWhite(size_t) const; // DOC: Same as is_white(), but starts at zero-based position in string.
        bool IsAlnum(size_t) const; // DOC: Same as is_alnum(), but starts at zero-based position in string.
        bool IsAlpha(size_t) const; // DOC: Same as is_alpha(), but starts at zero-based position in string.
        bool IsWhite(void) const; // DOC: Returns 1 if the string iscntrl(STDLIB) or 0x32.
        bool IsSpace(void) const; // DOC: Returns 1 is the string isspace(STDLIB).
        bool IsAscii(void) const; // DOC: Returns 1 is string is all ASCII characters (0 - 127).

        int Strip(StripType = Both, char ch = ' '); // DOC: Removes all contiguous occurences of 'ch' from either 'Leading', 'Trailing', or 'Both' relative string-positions. Returns 1 if operation performed. else 0.
        int Snip(char delim = ' '); // DOC: Removes 'delim' prefix from string AND ALL SUBSEQUENT CONTIGUIOUS DELIMITERS! Eg: Snip('-') from "123--456--759-0" => "456--789-0";  Returns 1 if operation performed. else 0.
        bool MkWhite(void); // DOC: Maps any !is_white() values over to spaces (0x32). Returns 1 if operation performed. else 0.
        size_t SeekBinary(int SkipControlChars = 0) const; // DOC: Returns the location of the first LOW-ascii, non-print-control, or non-ascii, character.

        istream& ReadToken(istream& is); // DOC: Extracts and stores the first white-space delimited token (i.e: uses '>>').
        ZStr GetToken(const ZStr& sTok) const; // DOC: If token is contained in the string, it is extracted, else result IsNull().
        ZStr RemoveToken(const ZStr& sTok) const; // DOC: Single case-sensitive token is removed from the string. To remove multiple, use RemovePattern. New string is returned.

        bool Split(const ZStr& str, Array<ZStr>&) const; // DOC: Carve up a string into an array of strings, each separated by a single character. The delimiting character is removed.
        bool Split(char ch, Array<ZStr>&) const; // DOC: Carve up a string into an array of strings, each separated by a single character. The delimiting character is removed.
        //Array<ZStr> as_array(char ch) const {return slice(ch);}                     // DOC: Carve up a string into an array of strings, each separated by a single character. The delimiting character is removed.

        istream& Read(istream& is, size_t); // DOC: Extracts number of charcters from stream. Underflows are treated properly (NULL terminated, etc).
        istream& Readline(istream& is, char delim = '\n'); // DOC: Extracts charcters from stream, up-to and including 'delim'. If the delimiter is found, it is extracted but not stored.
        istream& ReadLine(istream& is, char delim = '\n'); // DOC: See Readline()
        istream& ReadString(istream& is, char delim = '\0'); // DOC: See Readline()
        istream& ReadToDelim(istream& is, char delim = '\n'); // DOC: See Readline()
        istream& Readline(istream& is, const ZStr& delim); // DOC: Extracts charcters from stream, up-to and including 'delim'. If the delimiter is found, it is extracted but not stored.

        // "ignore case" option is not ANSI;
        size_t Tally(const ZStr& pattern, int ignore_case = 0) const; // DOC: Returns the number of times `pattern` is located in object.
        void Insert(size_t ss, const char *); // DOC: Places NULL at 'ss', then appends string.
        void Insert(size_t ss, const ZStr&); // DOC: Places NULL at 'ss', then appends string.
        size_t FindAny(const ZStr& str, size_t pos = 0L) const; // DOC: Locates caseless pattern in string. Returns zero-based location, else `NPOS`.
        size_t RfindAny(const ZStr& str, size_t pos = 0L) const; // DOC: Reverse-locates caseless pattern in string. Returns zero-based location, else `NPOS`.
        size_t FindAny(char ch, size_t pos = 0L) const; // DOC: Locates caseless pattern in string. Returns zero-based location, else `NPOS`.
        size_t RfindAny(char ch, size_t pos = 0L) const; // DOC: Reverse-locates caseless pattern in string. Returns zero-based location, else `NPOS`.
        size_t Find(char ch, size_t pos = 0L, int ignore_case = 0) const; // DOC: Locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t Rfind(char ch, size_t pos = 0L, int ignore_case = 0) const; // DOC: Reverse-locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t Find(const char *pch, size_t pos = 0L, int ignore_case = 0) const; // DOC: Locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t Rfind(const char *pch, size_t pos = 0L, int ignore_case = 0) const; // DOC: Reverse-locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t Find(const ZStr&, size_t pos = 0L, int ignore_case = 0) const; // DOC: Locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t Rfind(const ZStr&, size_t pos = 0L, int ignore_case = 0) const; // DOC: Reverse-locates pattern in string. Returns zero-based location, else `NPOS`.
        size_t FindLast(const char *pch, size_t pos = 0L, int ignore_case = 0) const; //    // DOC: Locates the last pattern in string. Returns zero-based location, else `NPOS`.
        size_t FindLast(char ch, size_t pos = 0L, int ignore_case = 0) const; //    // DOC: Locates the last pattern in string. Returns zero-based location, else `NPOS`.
        bool EndsWith(const ZStr& sToken) const; // DOC: Return true if the string ends with a suffux

        int Replace(const ZStr& tok, const ZStr& rep, int ignore_case = 0); // DOC: (NON-ANSI) Swaps all occurances of 'tok' with 'rep'. Returns number replaced;

        // The member function returns an object whose controlled sequence is a copy of up to `count`
        // elements of the controlled sequence beginning at position `pos`:
        ZStr Substr(size_t start, size_t end = NPOS) const; // DOC: 'end' is a count of the bytes to use, starting at the zero-based position 'start'.
        ZStr Subpos(size_t start, size_t end = NPOS) const; // DOC: 'end' is a a position to use, starting at the zero-based position 'start'.

        const char *CopyBytes(ZStr& sRes, size_t start, size_t end) const; // DOC: 'end' is inclusive: Puts a NULL at 'end'. Characters at and after 'end' are removed.
        const char *CopyPos(ZStr& sRes, size_t start, size_t end) const; // DOC: 'end' is inclusive: Puts a NULL at 'end'. Characters at and after 'end' are removed.
        const char *Substr(ZStr& sRes, size_t start) const; // DOC: 'start' is inclusive. Characters from 'start' to end of string are copied to 'sRes'.

        ZStr& Remove(char ch); // DOC: Removes all occurances of the pattern from the string.
        ZStr& Remove(int end); // DOC: same as remove(size_t)
        ZStr& Remove(size_t end); // DOC: 'end' is inclusive: Puts a NULL at 'end'. Characters at and after 'end' are removed.
        ZStr& Remove(const ZStr& str); // DOC: Removes all occurances of the pattern from the string. Macro for remove_token.
        ZStr& RemoveBytes(size_t start, size_t end); // DOC: 'end' is exclusive: Character at 'end' IS PRESERVED IN strING.
        ZStr& RemovePos(size_t start, size_t end); // DOC: 'end' is exclusive: Character at 'end' IS PRESERVED IN strING.
        ZStr& RemovePrefix(const ZStr& sPattern, int ignore_case = 0);
        int RemovePattern(const ZStr& tok, int ignore_case = 0); // DOC: (NON-ANSI) Removed all occurances of 'tok' in string. Returns number removed;
        ZStr Enumerate(char ch); // DOC: Removes leading string delimited by ch. Last one does not have to be delimited, but it leaves the string empty. Delimiting character is consumed.

        int Cmp(const ZStr&, int ignore_case = 0) const; // DOC: Compares strings using `strcmp(STDLIB)` type of results: 0 == equal, 1 == greater, -1 == less than.
        char& operator[](size_t ss) const; // DOC: Zero-based array opererator returns type of 'char&'.
        int operator>(const ZStr& str) const; // DOC: (BOOLEAN) Returns 1 if greater than string, else 0.
        int operator<(const ZStr& str) const; // DOC: (BOOLEAN) Returns 1 if less than string, else 0.
        int operator==(const ZStr& ss) const; // DOC: (BOOLEAN) Returns 1 if equal to string, else 0.
        int operator!=(const ZStr& ss) const; // DOC: (BOOLEAN) Returns 1 if not equal to string, else 0.

        ZStr& operator=(const ZStr& ss); // DOC: Assignment.
        ZStr& operator=(const char *ss); // DOC: Assignment.
        ZStr& operator=(char ch); // DOC: Assignment.
        ZStr& operator=(const string& str);

        ZStr& operator=(int i); // DOC: Integer Assign(ment.
        int AsInt(void) const; // DOC: Expression string as an integer value.
        long AsLong(void) const; // DOC: Expression string as a long value.

        virtual ostream& Write(ostream& os) const; // DOC: Empties entire string out to stream using "<<".
        virtual istream& Read(istream& is); // DOC: Reads stream using ">>". Same as read_token().

        // Common stream format - as shared with ByteBuffer  -
        virtual ostream& WriteStream(ostream& os) const; // DOC: Writes entire string to stream. Make sure binary-modes ('newline cooking') match on read and write.
        virtual istream& ReadStream(istream& is); // DOC: Writes entire string to stream. Make sure binary-modes ('newline cooking') match on read and write.

        virtual ostream& WriteString(ostream& os) const; // DOC: Writes entire string to stream, then appends a binary NULL.

        // virtual istream&  ReadString (istream& is);

        // Encoding / Decoding is very handy when stream types might change -

        static const char*Encode(ZStr& str) {
            str.Replace("\n", "\\n");
            str.RemovePattern('\r');
            return str.c_str();
        }

        static const char*DecodeDOS(ZStr& str) {
            Encode(str);
            str.Replace("\\n", "\r\n");
            return str.c_str();
        }

        static const char*EncodeDOS(ZStr& str) {
            Encode(str);
            DecodeDOS(str);
            return str.c_str();
        }

        static const char*DecodeUNIX(ZStr& str) {
            Encode(str);
            str.Replace("\\n", "\n");
            return str.c_str();
        }

        static const char*EncodeUNIX(ZStr& str) {
            Encode(str);
            DecodeUNIX(str);
            return str.c_str();
        }
        static ZStr SetComma(int nelem);
        static ZStr SetComma(const ZStr& str);

        /**
         * Check to see if a character is either Alaphabetic or Numeric (ASCII)
         * @param ch - Character to test
         * @return True if a character is either alphabetic or numeric.
         */
        static bool IsAlNum(char ch) {
            if (ch >= 'a' && ch <= 'z')
                return true;
            if (ch >= 'A' && ch <= 'Z')
                return true;
            if (ch >= '0' && ch <= '9')
                return true;
            return false;
        }
    };

    class StreamZStr : public ZStr // DOC: Use this class to allow .Read() and .Write() to alias over to read/write _stream().
    {
    public:

        StreamZStr(void) {
        }

        StreamZStr(const ZStr& str) {
            *this = str;
        }

        StreamZStr(const StreamZStr& str) {
            *this = str;
        }

        virtual ~StreamZStr(void) {
        }

        int operator==(const StreamZStr& str) const {
            return (ZStr::operator==(str.c_str()));
        }

        int operator==(const ZStr& str) const {
            return (ZStr::operator==(str.c_str()));
        }

        StreamZStr& operator=(const StreamZStr& str) {
            if (this == &str)
                return *this;
            ZStr::operator=(str.c_str());
            return *this;
        }

        StreamZStr& operator=(const ZStr& str) {
            if (this == &str)
                return *this;
            ZStr::operator=(str.c_str());
            return *this;
        }

        virtual ostream& Write(ostream& os) const {
            return ZStr::WriteStream(os);
        }

        virtual istream& Read(istream& os) {
            return ZStr::ReadStream(os);
        }
    };


    size_t Strip(ZStr& str, char ch);
    size_t Clip(ZStr& str, char ch);
    int Getline(istream& is, ZStr& str);

    size_t Strip(ZStr& str, char ch);
    size_t Clip(ZStr& str, char ch);
    size_t Snip(const ZStr& str, ZStr& sLeft, ZStr& sRight, char ch);
    int Getline(istream& is, ZStr& str);
    size_t Rfind(const ZStr& sSrc, const ZStr& sPat, int ignore_case = 0);
    ZStr TagRemove(const ZStr& sSrc, char chOn = '<', char chOff = '>');

    ZStr Common(const ZStr& sC, const ZStr& sD); // Returns what to string have in common
    ZStr RCommon(const ZStr& s1, const ZStr& s2); // Returns what the END of two strings have in common

    void Clone(Array<ZStr>& array1, Array<StreamZStr>& array2);
    void Clone(Array<StreamZStr>& array1, Array<ZStr>& array2);

    void Convert(Array<ZStr>& a1, Array<StreamZStr>& a2);
    void Convert(Array<StreamZStr>& a1, Array<ZStr>& a2);
    wstring Convert(const string& str);
    string Convert(const wstring& wstr);

    ZStr operator +(const ZStr& str, const ZStr& cstr);
    ZStr& operator +=(ZStr& str, const ZStr& cstr);
    ZStr& operator >>(ZStr& str, size_t& sz);
    ZStr& operator <<(ZStr& str, size_t sz);
    ZStr& operator <<(ZStr& str, const ZStr& str2);
    ZStr& operator <<(ZStr& str, const char *psz);
    istream& operator >>(istream& is, ZStr& ss);
    ostream& operator <<(ostream& os, const ZStr& ss);

} // Able1

#endif

