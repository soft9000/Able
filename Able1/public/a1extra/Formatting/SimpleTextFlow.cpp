#include <a1extra/Formatting/SimpleTextFlow.hpp>

SimpleTextFlow::SimpleTextFlow(void) : iLineWidth(40), bCenter(false), bJustify(false) {
}

SimpleTextFlow::SimpleTextFlow(const SimpleTextFlow& ref) {
    *this = ref;
}

bool SimpleTextFlow::Encode(const ZStr& str, int width) {
    iLineWidth = width;
    sText = str;
    ReEncode();
    return true;
}

ZStr SimpleTextFlow::Query(void) const {
    ZStr sResult = sText;
    return sResult;
}

SimpleTextFlow& SimpleTextFlow::operator=(const SimpleTextFlow& ref) {
    bCenter = ref.bCenter;
    bJustify = ref.bJustify;
    sText = ref.sText;
    sError = ref.sError;
    return *this;
}
// Query / set properties;

size_t SimpleTextFlow::Width(void) const {
    return iLineWidth;
}

void SimpleTextFlow::Width(size_t iw) {
    iLineWidth = iw;
}

size_t SimpleTextFlow::Extract(Array<ZStr>& ary) {
    size_t result = NULL;
    size_t ssStart = NULL;
    size_t whence = NULL;
    // If it does not end in a newline, it still is a line;
    if (sText[sText.Length() - 1] != '\n')
        sText.Append("\n");
    whence = sText.Find('\n');
    while (whence != NPOS) {
        size_t tmp = whence - ssStart;
        if (result < tmp)
            result = tmp;
        ZStr sLine;
        sText.CopyPos(sLine, ssStart, whence + 1);
        ary[ary.Nelem()] = sLine;
        ssStart = whence + 1;
        whence = sText.Find('\n', ssStart);
    }
    return result;
}

size_t SimpleTextFlow::Lines(void) const {
    size_t result = NULL;
    size_t whence = NULL;
    whence = sText.Find('\n');
    while (whence != NPOS) {
        result++;
        whence = sText.Find('\n', whence + 1);
    }
    return result;
}

size_t SimpleTextFlow::WidestLine(void) const {
    size_t result = NULL;
    size_t ssStart = NULL;
    size_t whence = NULL;
    whence = sText.Find('\n');
    while (whence != NPOS) {
        size_t tmp = whence - ssStart;
        if (result < tmp)
            result = tmp;
        ssStart = whence + 1;
        whence = sText.Find('\n', ssStart);
    }
    return result;
}
/*
void      SimpleTextFlow::SetBox(char l = '+', char r = '+', char horiz = '-', char vert = '|') 
   {
   L = l; R = r; H = horiz; V = vert;
   }
void      SimpleTextFlow::SetBox(char chAll) 
   {
   L = R = H = V = chAll;
   }
void      SimpleTextFlow::Center(bool b = true) 
   {
   bCenter = b;
   }
void      SimpleTextFlow::Justify(bool b = true) 
   {
   bJustify = b;
   }
ZStr SimpleTextFlow::Error(void)         
   {
   ZStr se = sError; return se;
   }
 */

// Individual processes available;

ZStr SimpleTextFlow::ReEncode(void) {
    sError = "";
    size_t whence = NULL;
    whence = sText.Find("\r\n");
    while (whence != NPOS) {
        sText.RemoveBytes(whence, 1);
        whence = sText.Find("\r\n", whence);
    }
    whence = sText.Find("\n\r");
    while (whence != NPOS) {
        sText.RemoveBytes(whence + 1, 1);
        whence = sText.Find("\n\r", whence);
    }
    whence = sText.Find('\r');
    while (whence != NPOS) {
        sText[whence] = '\n';
        whence = sText.Find('\r', whence);
    }
    ZStr sResult = sText;
    return sResult;
}

ZStr SimpleTextFlow::UserExpand(size_t itab) {
    size_t whence = sText.Find("\\n"); // 2 bytes
    while (whence != NPOS) {
        sText.RemoveBytes(whence, 1);
        sText[whence] = '\n';
        whence = sText.Find("\\n", whence);
    }
    ZStr tabs;
    for (size_t ss = 0L; ss < itab; ss++)
        tabs.Append(' ');
    whence = sText.Find("\\t"); // 2 bytes
    while (whence != NPOS) {
        // Since the items are space-delimited, this usage will 
        // effectively expand to " \tTHREE" or " \t FOUR" spaces;
        sText.RemoveBytes(whence, 2);
        sText.Insert(whence, tabs);
        whence = sText.Find("\\t", whence);
    }
    ZStr& sResult = sText;
    return sResult;
}

ZStr SimpleTextFlow::ReflowLines(void) {
    sText.Replace(" \n", '\n');
    sText.Replace("\n ", '\n');
    ZStr sResult;
    size_t LinePos = NULL;
    size_t ssBreak = NPOS;
    size_t ssStart = false;
    bool buffered = false;
    for (size_t ss = NULL; ss < sText.Length(); ss++) {
        buffered = true;
        LinePos++;
        switch (sText[ss]) {
            case('\n'):
                LinePos = iLineWidth + 1; // mark the advance
                ssBreak = ss;
                break;
            case(' '):
                ssBreak = ss;
                break;
            default:
                break;
        }
        if (LinePos > iLineWidth) {
            if (ssBreak == NPOS)
                ssBreak = ss;
            ZStr sLine;
            sText.CopyPos(sLine, ssStart, ssBreak + 1);
            if (sText[ssBreak] != '\n')
                sLine.Append('\n');
            sResult.Append(sLine);
            LinePos = ss - ssBreak;
            ssStart = ssBreak + 1;
            ssBreak = NPOS;
            buffered = false;
        }
    }
    if (buffered == true) {
        ZStr sLine;
        sText.CopyPos(sLine, ssStart, sText.Length());
        if (sText[sText.Length() - 1] != '\n')
            sLine.Append('\n');
        sResult.Append(sLine);
    }
    sText = sResult;
    return sResult;
}

ZStr SimpleTextFlow::ReflowParagraphs(void) {
    sText.Replace("\n\n", "\r\r"); // encode paragraphs
    for (size_t ss = NULL; ss < sText.Length(); ss++) {
        switch (sText[ss]) {
            case ('\n'):
            {
                if (sText[ss + 1] == ' ') {
                    sText.RemoveBytes(ss, 1);
                    continue;
                }
                if (ss && sText[ss - 1] == ' ') {
                    sText.RemoveBytes(ss, 1);
                    continue;
                }
                sText[ss] = ' ';
            }
            default:
                break;
        }
    }
    sText.Replace("\r\r", "\n\n"); // encode paragraphs
    return ReflowLines();
}


#include <ctime>

char rchar[] ={
    '~', '!', '\\', '@', '#', '$', '%', '*', '+', '=', ':', '/', NULL
};

char RandomBorder(void) {
    static time_t tt = time(NULL);
    srand(tt);
    int ss = Random::RandRange(0, 10);
    if (ss >= 11)
        return 'E'; // for 'Error'
    return rchar[ss];
}

