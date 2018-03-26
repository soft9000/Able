#ifndef LanguageInfo_hpp
#define LanguageInfo_hpp

namespace Taco
{

struct LanguageInfo
{
   ZStr sType;
   ZStr sKeyNamespace;
   ZStr sKeyClass;
   ZStr sKeyStruct;
   ZStr sKeyUsing;

   char chBlockStart, chBlockEnd, chStatememt, chParamStart, chParamEnd;

   LanguageInfo(void) : 
         sKeyNamespace("namespace"), sKeyClass("class"),    sKeyStruct("struct"),   sKeyUsing("using"),
         chBlockStart('{'),          chBlockEnd('}'),       chStatememt(';'),
         chParamStart('('),          chParamEnd(')'),       sType(".hpp")
      {
      }
};


}

#endif
