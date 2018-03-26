// Class File: Written to encapsulate all of those MS / ANSI stream differences.
// Also serves as a place to wrapper all of those FILE_FUN functions.
// 11/12/1998: Class written, R. Nagy.
// 04/02/1999: This thing could have only worked previously if file A/E and Name()
//    was FQ? --Now it handles the unknown much better, R. Nagy.
//       Fixed potential maintenance bugs by checking if FQFname was !NULL.
//       Rewrote Qualify().
//       Changed Create() from OPEN_EXISITING to CREATE_ALWAYS.
// 07/24/1999: Added Set/QueryScopeDestruct(), R. Nagy
// 10/16/1999: Finally unified the i/o streams by adding OpenReadWrite(), R. Nagy
// 12/13/1999: Added Resume(), R. Nagy
// 12/22/1999: Moved implementation over to File.Cpp so as to remove bleed-throughs 
//             to items in "File_Fun", R. Nagy
// 12/27/1999: Went over to the "xFile.Hpp" convention. Allows classes to be used
//             in external linkange, as well as inline (legacy), R. Nagy.
// 01/15/2000: NOTE: Remove() usage changed to now imply a "close", as first, R. Nagy
// 06/02/2001: Added IsNull(), R. Nagy
// 06/06/2001: Tested and fixed IsNull(), R. Nagy
// 11/22/2001: Added Time(time_t). Updated Time(void) to use same [Feliez de la estaci'on del gracias!], R. Nagy
// 06/11/2002: Time to add an operator ==(). Compares file NAMES, only (CASE SENSITIVE), R. Nagy
// 07/06/2002: Added QueryFileNode(), R. Nagy
// 07/22/2002: Added LoadTextFile(), R. Nagy
// 11/20/2002: Added LoadStreamBuffer(), R. Nagy
// 05/08/2003: Added CanRead() / CanWrite(), R. Nagy
// 10/30/2003: Added CopyTo(dir) and Query(dir), R. Nagy
// 10/30/2003: Added QueryNode() and QueryParent() [to complement Directory signature], R. Nagy
// 02/07/2004: Removed inline from standalone function definitions, R. Nagy.
// 11/13/2004: Lightly updated to support commmon usage, R. Nagy
// 11/24/2004: Re-arranging headers to better support G++, R. Nagy
// 05/25/2005: Added static LoadText(), R. Nagy
// 05/20/2005: Added SetNode() and SetParent(), R. Nagy
// 07/05/2005: Sped up the implementaiton of LoadText(). Converted to text file mode, too, R. Nagy
// 07/05/2005: Added LoadPureText(), R. Nagy
// 11/25/2006: Updated MkUniqueName() to use the default node folder instead of the pwd, R. Nagy
// 12/16/2006: Added MkUniqueName(sSuffix), R. Nagy
// 01/13/2007: Changed the default constructor + Qualify() to place an UNQUALIFIED file name
//             into the PROGRAM HOME DIR, not the pwd. That is what I always seem to expect, R. Nagy
// 01/24/2007: Added Here() so as to quickly place files into the PWD, R. Nagy
// 01/10/2008: Added MkGenerationName(), R. Nagy
// 01/11/2008: Updated MkUniqueName() to remove default P_tmpdir, if there, R. Nagy
//             Added MoveTo(Directory&), R. Nagy
// 01/17/2008: Added MkUniqueName(Directory&) duo. Updated MkUniqueName(void), R. Nagy
//             Updated File.Name() to favor strings with PathChar()s for ALL files, R. Nagy
//             Updated File.Name() to favor DYNAMIC PARENT for non-null files, R. Nagy
//             Updated File.Name(Dir) to use dir.Home(), R. Nagy
//             Added FQN(), R. Nagy
// 01/19/2008: Added NamePwd(), R. Nagy
// 06/13/2008: Updated IsNull() to work more as expected, R. Nagy
// 10/22/2008: Modified MoveTo() and CopyTo() to 100% const usage, R. Nagy
// 10/22/2008: Reverted - UN modified MoveTo() and CopyTo() to non-const usage (MSVC 6 - file might need to close!), R. Nagy
//
#ifndef xzFile_Hpp
#define xzFile_Hpp


namespace Able1 {

    /** File is a ShareableObject that manages file I/O.
     *
     */
    class File : public ShareableObject {
    private:
        bool _bDestructorDeletes;

        // Accept a path-char qualified name. Assigned varbatum. Path character IS required.
        // Should be a fully qualified name, but does not HAVE to be... (caveat developer!)
        bool FQN(const ZStr& sMondo);

    protected:
        fstream *pIOStream;

        ZStr sFQName;
        void _init(void);

        // Please use QueryPathTo, instead

        const char *PathTo(ZStr& str) const {
            return QueryPathTo(str);
        }

        // Retired on  10/30/2003, R. Nagy
        const char *QueryPathTo(ZStr& str) const; // ONLY the path to the file (no file name)
        const char *QueryFileNode(ZStr& str) const; // ONLY the name of the file (no path is included)

    public:

        enum TranslationModes {
            AT_TEXT,
            AT_BINARY,
            DEFAULT = AT_TEXT
        };

        File(void);
        File(const ZStr& stdName);
        File(const File&);
        virtual ~File(void);

        // CommonObject
        bool FromString(const ZStr&);
        const char *ToString(ZStr&) const;

        bool Here(void); // Place in the pwd -

        bool IsNull(void) const; // true if default file name Assign(ed, AND default file name does not exist. Otherwise false.

        bool Launch(void) const; // This opens or views a file, if possible.

        // Removes the `pw File` when class goes out-of-scopy (ONLY);

        void SetScopeDestruct(bool br) {
            _bDestructorDeletes = br;
        }

        bool QueryScopeDestruct(void) {
            return _bDestructorDeletes;
        }

        // NOTE: Name(ZStr&)
        //       ---- ==========
        // Contains PathChar?
        //    Applied varbaitum - used without ANY further testing
        // No PathChar?
        //    If pw file IsNull(), node-name is placed in ProgramId folder,
        //    If pw file !IsNull() then will be placed in ParentFolder.
        bool Name(const ZStr&);
        bool Name(const Directory& dir, const ZStr&);

        bool Name(const File& file) {
            return Name(file.Name());
        }
        ZStr Name(void) const;

        // Name the file in the Present Working Directory (PWD). Same as Name(Directory.Get(), Str).
        bool NamePwd(const ZStr&);

        bool Rename(const ZStr&);

        bool Rename(const File& file) {
            return Rename(file.Name());
        }

        bool MkUniqueName(const Directory&); // Create a temporary file in the folder
        bool MkUniqueName(const Directory& dir, const ZStr& sSuffix);

        bool MkUniqueName(void); // WAS MkUniqueName -
        bool MkUniqueName(const ZStr& sSuffix); // Create a temporary file

        ZStr Query(Directory& dir) const;

        const char *QueryNode(ZStr& str) const; // ONLY the name of the file (no path is included)
        const char *QueryParent(ZStr& str) const; // ONLY the path to the file (no file name)
        bool QueryParent(Directory& dir) const; // Parent directory

        bool SetNode(ZStr& str); // ONLY the name of the file (no path is included)
        bool SetParent(ZStr& str); // ONLY the path to the file (no file name)
        bool SetParent(Directory& dir); // ONLY the path to the file (no file name)

        ZStr QueryNode(void) const; // ONLY the name of the file (no path is included)
        ZStr QueryParent(void) const; // ONLY the path to the file (no file name)

        time_t GetTime(void) const; // Returns the time, in nearest seconds, of the referenced file
        bool Touch(void);
        bool Touch(time_t);

        bool Create(void);
        bool Exists(void) const;
        bool CanRead(void) const; // A file may exist, but we not have access to it (read  locked, security, etc).
        bool CanWrite(void) const; // A file may exist, but we not have access to it (write locked, security, etc).

        bool CopyTo(const File&);
        bool CopyTo(const Directory&);
        bool MoveTo(const Directory&);
        bool CopyTo(const ZStr&);
        bool Remove(void);
        bool Empty(void);

        bool Hide(void);
        bool UnHide(void);
        bool IsHidden(void);

        char Drive(void);
        int Device(void);

        istream& OpenRead(TranslationModes at = AT_TEXT);

        istream& OpenRead(const ZStr& sfn, TranslationModes at = AT_TEXT) {
            Name(sfn);
            return OpenRead(at);
        }
        ostream& OpenWrite(TranslationModes at = AT_TEXT);

        ostream& OpenWrite(const ZStr& sfn, TranslationModes at = AT_TEXT) {
            Name(sfn);
            return OpenWrite(at);
        }
        ostream& OpenAppend(TranslationModes at = AT_TEXT); // Only use this to append. Do not seek!
        iostream& OpenReadWrite(TranslationModes at = AT_TEXT); // Okay to seek using this, except has ios::end seeking problems under Microsoft VS??
        iostream& Resume(void);
        void Close(void);

        operator ostream&() {
            if (pIOStream) return *pIOStream;
            return OpenWrite();
        } // 04/03/2001

        File & operator=(const File&);

        int operator==(const File& file) {
            return (sFQName == file.sFQName);
        }
        ostream& Write(ostream& os) const;
        istream& Read(istream& is);

        bool DumpContents(ostream& os, TranslationModes at = AT_TEXT);
        bool DumpContents(long spStartAt, long spEndBefore, ostream& osDumpTo, TranslationModes at);

        static bool SaveText(const File& file, const ZStr& sResult); // DOC: Replaces file content with a TEXT MODE string.
        static bool LoadText(const File& file, ZStr& sResult); // DOC: Loads a file into a string.
        static bool LoadPureText(const File& file, ZStr& sResult, char chSkipStart = '<', char chSkipEnd = '>'); // DOC: Loads a file into a string. Ingores items between delimiters (inclusive)
        static bool Qualify(ZStr& sName); // DOC: Converts alien path chars. Then if no path char, place in program (Home()) dir. Else remains unchanged.

        // Prefix file name with a unique number. Based upon folder content.
        // File name will be placed into the folder (dir) specified. Defaults to
        // the unique name on overflow of 0L.
        static File MkGenerationName(const Directory& dir, const File& file);
    };

    inline bool LoadTextFile(ZStr& sResult, const File& file) {
        return File::LoadText(file, sResult);
    }

    // This is FAST - Massively F-A-S-T=E-R for LARGE HTML files! (no RAM SLAM!)

    inline File Html2TextFile(const File& fff) {
        File fileIN = fff;
        File file;
        file.Name(ZStr(fff.Name()) + ".txt");
        bool bSkip = false;
        istream& is = fileIN.OpenRead();
        ostream& os = file.OpenWrite();
        char ich = 0;
        while (is) {
            is.read(&ich, 1);
            if (!is)
                continue;
            if (ich == '<') {
                bSkip = true;
                continue;
            }
            if (ich == '>') {
                bSkip = false;
                continue;
            }
            if (bSkip)
                continue;
            os << ich;
        }
        file.Close();
        return file;
    }

    bool IsTextFile(const File&);
    bool IsTextFile(const ZStr& sFileName);
    void MkLocalFileName(ZStr& sFileNameCandidate, bool bSkipPathChar = false);


} // namespace Able1


#endif
