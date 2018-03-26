#if 0
#include <a1extra/Formatting/SimpleTextFlow.hpp>

int main(int argc, char* argv[]) {
    SimpleTextFlow r1;
    r1.Encode("This\rshould be no\nLess than four\r\nlines");
    ZStr str;
#if 1
    str = r1.ReflowLines();
    cout << "~~~~~~~~~~" << endl;
    cout << str;
    cout << "~~~~~~~~~~" << endl;
#endif
    r1.Encode("This is a very long line with absolutely no breakage therein. We are checking the auto-wrapping feature here, so good luck!");
    str = r1.ReflowLines();
    cout << str;
    cout << "~~~~~~~~~~" << endl;
    r1.Encode("This is a very long line with absolutely ONE breakage\r herein. We are checking the auto-wrapping feature here, so good luck!");
    str = r1.ReflowLines();
    cout << str;
    cout << "Longest:" << r1.WidestLine() << endl;
    cout << "~~~~~~~~~~" << endl;

    str.Assign("This is a very long line with absolutely a few odd breakages\r herein. We are checking the auto-wrapping feature here, so good luck!");
    str.Append("This is a very long line with absolutely a few odd breakages\r herein. We are checking the auto-wrapping feature here, so good luck!");
    str.Append(" This is a very long line with absolutely a few odd breakages\r herein. We are checking the auto-wrapping feature here, so good luck!");
    str.Append("This is a very long line with absolutely a few odd breakages\r herein. We are checking the auto-wrapping feature here, so good luck!");
    r1.Encode(str);
    str = r1.ReflowLines();
    cout << str;
    cout << "Longest:" << r1.WidestLine() << endl;
    cout << "~~~~~~~~~~" << endl;
    str = r1.ReflowParagraphs();
    cout << str;
    cout << "Longest:" << r1.WidestLine() << endl;
    cout << "~~~~~~~~~~" << endl;
    BoxedText box;
    str = box.Box(r1, 3);
    cout << str;
    cout << "~~~~~~~~~~" << endl;
    str = box.TitleBox("Cool Beans", r1, 3);
    cout << str;
    cout << "~~~~~~~~~~" << endl;
    cout << "(neoj)" << endl;
    return 1;
}

#endif