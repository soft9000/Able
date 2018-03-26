
#include <a1extra/StdLog/EzLog.hpp>
#include <a1extra/Formatting/WordWrap.hpp>
#include <a1extra/Disclaimer.hpp>

const char *DEFAULT_LOG_FILE_NAME = ".ezlog";

struct HtmlLog {

    static void Start(ostream & os) {
        File file;
        ProgramId pid;
        pid.GetProgram(file);
        os << "<html>" << endl;
        os << "<title>" << file.Name() << "</title>";

        os << "<body LINK=\"#0000ff\" VLINK=\"#800080\" BGCOLOR=\"#00ffff\">" << endl;

        File file2;
        file2.Name("Soft9000.gif");
        pid.PutInDirectory(file2);
        os << "<a href=\"http://www.soft9000.com\"><img src=\"";
        os << file2.Name();
        os << "\" alt=\"About the author\" border=\"0\" width=\"309\" height=\"42\"></a>";
        os << endl;

        os << "<FONT SIZE=2 FACE=\"Courier New\" COLOR=\"#800000\">";
        os << "<br>" << endl;
        os << "<p><i>These data have been brought to you by </i>";
        os << file.Name();
        os << "<i>, which is part of the <b>Stdnoj Project</b>.</i>";
        os << "</p></FONT>" << endl;

        StdDateTime sdt;
        os << "<FONT SIZE=1 FACE=\"Courier New\"> <p>";
        os << "Logging report generated on: <i>" << AsMDYHMS(sdt) << "</i>" << endl;
        os << "<br>" << endl;
        os << "</p></FONT>" << endl;
    }

    static void Stop(ostream & os) {
        os << "<br><hr>" << endl;
        os << "</body>" << endl;
        os << "</html>" << endl;
    }

    static void Write(ZStr& sTime, ZStr& sPayload, ostream & os) {
        ZStr str;
        os << "<hr>";
        os << "<b>" << sTime << "</b><br>";
        os << "<p><FONT SIZE=3 FACE=\"Courier New\" COLOR=\"#008000\">";
        os << sPayload;
        os << "</p></FONT>" << endl;
        os << "<br>";
        os << endl;
    }

};

EzLog::EzLog(void) {
    SetDefault();
    std::cout << "Name is " << this->pwFile.Name();
}

void EzLog::SetDefault(void) {
    Directory dir;
    if (dir.Get() == true) {
        ProgramId pid;
        pid.GetProgram(dir);
        if (SetDefaultLog(dir) == false)
            pwFile.Name(DEFAULT_LOG_FILE_NAME);
    }
}

bool EzLog::SetDefaultLog(Directory& dir) {
    stringstream srm;
    srm << dir.Name() << PathChar() << DEFAULT_LOG_FILE_NAME << ends;
    return pwFile.Name(PRESTO(srm));
}

bool EzLog::SetDerivedLog(File& file) {
    stringstream srm;
    srm << file.Name() << DEFAULT_LOG_FILE_NAME << ends;
    return pwFile.Name(PRESTO(srm));
}

bool EzLog::HasDefaultLog(Directory& dir) {
    ZStr str;
    Array<File> aFiles;
    dir.Query(aFiles);
    for (size_t ss = 0L; ss < aFiles.Nelem(); ss++) {
        str = aFiles[ss].QueryNode();
        if (str == DEFAULT_LOG_FILE_NAME)
            return true;
    }
    return false;
}

void EzLog::LocateDefaultLog(void) {
    Directory dir;
    if (dir.Get() == true) {
        if (HasDefaultLog(dir) == true) {
            SetDefaultLog(dir);
            return;
        }

        ZStr sDir = dir.QueryParent();
        while (1) {
            if (dir.Name(sDir) == true) {
                if (HasDefaultLog(dir)) {
                    SetDefaultLog(dir);
                    return;
                }
            }
            ZStr sHold = dir.QueryParent();
            if (sDir == sHold) {
                SetDefault();
                return;
            }
            sDir = sHold;
        }
    }

    SetDefault();
}

bool EzLog::WriteLog(const ZStr& message) {
    ZStr sResult;
    return WriteLog(message, sResult);
}

bool EzLog::WriteLog(const ZStr& message, ZStr& sResult) {
    bool br = false;
    ostream& os = pwFile.OpenAppend();
    sResult = StdLog::LogFormat(message);
    os << sResult << endl;
    if (os)
        br = true;
    pwFile.Close();
    return br;
}

void EzLog::Usage(ostream& os) {
    File file;
    ProgramId pid;
    pid.GetProgram(file);

    ZStr str = file.QueryNode();
    os << endl;
    os << str << " -by rnagy@Soft9000.com, " << __DATE__ << endl;
    for (size_t ss = 0L; ss < str.Length(); ss++)
        os << '-';
    os << endl << endl;

    os << "Time stamp or list log messages into either the present folder (.) or" << endl;
    os << "to a dynamically located parental log else " << EzLog::LogDefaultName(str) << " (=) " << endl;
    os << endl;
    os << "Usage:" << endl;
    os << "-----" << endl;

    os << file.QueryNode() << " . message" << endl;
    os << "   -Log the message to an " << DEFAULT_LOG_FILE_NAME << " in the current folder." << endl;

    os << endl << "or " << endl << endl;
    os << file.QueryNode() << " $ message" << endl;
    os << "   -Log the message to the default (EzLog.exe) program folder." << endl;

    os << endl << "or " << endl << endl;
    os << file.QueryNode() << " = message" << endl;
    os << "   -Log the message to an " << DEFAULT_LOG_FILE_NAME << " in the ancestor OR default program folder." << endl;

    os << endl << "or " << endl << endl;
    os << file.QueryNode() << " @" << endl;
    os << "   -Format and display the log file." << endl;
    os << endl;
    Disclaimer::Header(os);
    os << endl;
}

bool EzLog::ShowLog(ostream& os) {
    return ShowLog(pwFile, os);
}

bool EzLog::ShowLog(const File& file, ostream& os) {
    bool br = ShowHtmlLog(file);
    if (br)
        return br;
    return ShowTextLog(file, os);
}

bool EzLog::ShowHtmlLog(const File& fff) {
    ZStr sTime, sPayload, sLine;

    File fnOut = ZStr(fff.Name()) + ".html";
    ostream& os = fnOut.OpenWrite();
    HtmlLog::Start(os);

    File file = fff;
    istream& is = file.OpenRead();
    while (is) {
        sLine.Readline(is);
        if (!is)
            continue;
        size_t pos = sLine.Find("-");
        if (pos == npos) {
            sTime = "";
            sPayload = sLine;
        } else {
            sTime = sLine.Subpos(0, pos);
            sPayload = sLine.Subpos(pos, NPOS);
        }
        HtmlLog::Write(sTime, sPayload, os);
    }

    HtmlLog::Stop(os);
    fnOut.Close();
    file.Close();
    return fnOut.Launch();
}

bool EzLog::ShowTextLog(const File& file, ostream& os) {
    File f2 = file;
    bool br = file.Exists();
    cout << file.Name() << endl;
    if (br) {
        Array<ZStr> aLines;
        ZStr sLine;
        istream& is = f2.OpenRead();
        while (is) {
            sLine.Readline(is);
            if (!is)
                continue;
            aLines = TextFormatting::WordWrap::Wrap(sLine, 0, 0, 77);
            for (size_t ss = 0L; ss < aLines.Nelem(); ss++)
                os << aLines[ss] << endl;
            os << "-----" << endl;
        }
    }
    return br;
}

const char *EzLog::LogDefaultName(ZStr& str) {
    EzLog log;
    log.SetDefault();
    str = log.pwFile.Name();
    return str.c_str();
}

bool EzLog::Main(int argc, char *argv[], ostream& os) {
    ZStr str;
    Array<ZStr> array;
    for (size_t ss = 0L; ss < argc; ss++) {
        str = argv[ss];
        array.Append(str);
    }
    return Main(array, os);
}

bool EzLog::Main(Array<ZStr>& array, ostream& os) {
    bool bHelp = true;

    EzLog log;

    if (array[1] == "@") {
        log.LocateDefaultLog();
        return log.ShowLog(cout);
    }

    if (array[1] == ".") {
        Directory dir;
        dir.Get();
        if (log.SetDefaultLog(dir) == false) {
            os << "Waring: Unable to Set log file to " << dir.Name() << ". Using default." << endl;
            log.LocateDefaultLog();
        }
        bHelp = false;
    }

    if (array[1] == "$") // default - as used
    {
        log.SetDefault();
        bHelp = false;
    }

    if (array[1] == "=") // locate the default - in the tree or otherwise
    {
        log.LocateDefaultLog();
        bHelp = false;
    }

    if (bHelp) {
        Usage(os);
        if (array.Nelem() <= 2)
            return true;
        return false;
    }

    // Adjust for WIN32 command shell idosyncracies
    stringstream srm;
    for (size_t ss = 2; ss < array.Nelem(); ss++)
        srm << array[ss] << " " << endl;
    ZStr str = PRESTO(srm);
    str.Strip();
    ZStr sResult;
    bool br = log.WriteLog(str, sResult);
    if (br == false)
        os << "Error: Unable to log message to file." << endl;
    else
        os << log.pwFile.Name() << ":" << endl;
    os << sResult;
    return br;
}


