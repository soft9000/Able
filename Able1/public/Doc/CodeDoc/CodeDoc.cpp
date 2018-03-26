#include "CodeDoc.hpp"

using namespace CodeDoc;

void CodeFormatter::ReadToken(istream& is, ZStr& str)
   {
   str.Read(is);
   }

CodeFormatter::BlockType CodeFormatter::GetBlockType(const ZStr& str)
   {
   int iTally = str.Tally('{');
   if(!iTally)
      return bt_Statement;
   if(iTally == 1)
      return bt_Simple;
   return bt_Complex;
   }

// A block of code is delimited by braces OR it is a simple semicolin statement
void CodeFormatter::ParseBlockOrStatement(istream& is, ZStr& str)
   {
   char ch;
   while(is)
      {
      is.read(&ch, 1);
      if(!is)
         return;
      switch(ch)
         {
         case('\r'):
         continue;

         case('\t'):
            str += ' ';
         continue;

         case('('):
         case('['):
         case('\"'):
         case('\''):
            {
            stringstream srm;
            srm << str;
            PassQuote(srm, is, ch);
            str = srm.str();
            }
         break;
         case('{'):
            {
            is.putback(ch);
            stringstream srm;
            srm << str;
            PassBlock(srm, is, '{', '}');
            str = srm.str();
            }
         return;
         case(';'):
            {
            str += ch;
            return;
            }
         break;
         default:
            str += ch;
         break;
         }
      }
   }

char CodeFormatter::Scroll(istream& is)
   {
   bool bNewline = false; bool bSpaces = false;
   char ch = 0;
   while(is)
      {
      is.read(&ch, 1);
      if(!is)
         return 0;
      switch(ch)
         {
         case('\n'):
            bNewline = true;
         continue;

         case(' '):
         case('\r'):
         case('\t'):
            bSpaces = true;
         continue;

         default:
            {
            if(bNewline)
               return ch;
            if(bSpaces)
              {
               is.putback(ch);
               return ' ';
               }
            return ch;
            }
         }
      }
   return 0;
   }

void CodeFormatter::PassBlock(ostream& os, istream& is, char chOn, char chOff)
   {
   int iLevel = 0;
   char ch;
   while(is)
      {
      is.read(&ch, 1);
      if(!is)
         return;
      os << ch;
      if(ch == chOn)
         {
         iLevel++;
         continue;
         }
      if(ch == chOff)
         {
         iLevel--;
         if(iLevel == 0)
            return;
         }
      }
   }

void CodeFormatter::PassQuote(ostream& os, istream& is, char chOff)
   {
   bool bEsc = false;
   char ch;
   while(is)
      {
      is.read(&ch, 1);
      if(!is)
         return;
      os << ch;
      if(bEsc == false)
         {
         if(ch == chOff)
            return;
         }
      if(bEsc == true)
         {
         bEsc = false;
         continue;
         }
      if(ch == '\\')
         bEsc = true;
      }
   }

void CodeFormatter::Newline(ostream& os, int iLevel)
   {
   os << endl;
   for(int ss = 0; ss < iLevel; ss++)
      for(int tt = 0; tt < iTab; tt++)
         os << ' ';
   }

bool CodeFormatter::Normalize(const File& fileIn, const File& fileOut)
   {
   File file = fileIn;
   istream& is = file.OpenRead(File::AT_BINARY);
   File oFile  = fileOut;
   ostream& os = oFile.OpenWrite(File::AT_BINARY);
   char ch;
   while(is)
      {
      is.read(&ch, 1);
      if(!is)
         continue;
      switch(ch)
         {
         case('\r'):
         continue;

         case('\''):
         case('\"'):
            {
            os << ch;
            PassQuote(os, is, ch);
            }
         continue;

         case(':'):
            {
            os << ch;
            os << " ";
            }
         continue;

         case('?'):
         case('('):
         case(')'):
         case('{'):
         case('}'):
         case(';'):
            {
            os << " ";
            os << ch;
            os << " ";
            }
         continue;

         case '\t':
         case ' ':
         case '\n':
            os << ' ';
         continue;

         default:
            os << ch;
         continue;
         }
      }
   return true;
   }

bool CodeFormatter::Normalize(const File& fff)
   {
   File file = fff;
   File fileDest;
   if(fileDest.Name(file.Name() + ".tmp") == false)
      return false;
   if(Normalize(file, fileDest) == false)
      return false;
   File fileTmp;
   if(fileTmp.Name(file.Name() + ".old") == false)
      return false;
   if(file.CopyTo(fileTmp) == false)
      return false;
   if(fileDest.CopyTo(file) == false)
      return false;
   fileDest.Remove();
   return true;
   }

CodeFormatter::CodeFormatter(void) : iTab(3)
   {
   }

bool CodeFormatter::NormalizeF(const File& fff, File& fileDest)
   {
   File file = fff;
   if(fileDest.Name(file.Name() + ".tmp") == false)
      return false;
   if(file.CopyTo(fileDest) == false)
      return false;
   if(Normalize(fileDest) == false)
      return false;
   return true;
   }

bool CodeFormatter::Beautify(const File& fff)
   {
   File file = fff;
   File fileNormal;
   if(NormalizeF(file, fileNormal) == false)
      return false;
   File fileDest;
   if(fileDest.Name(fileNormal.Name() + ".tmp") == false)
      return false;
   if(FormatCode(fileNormal, fileDest) == false)
      return false;
   File fileTmp;
   if(fileTmp.Name(file.Name() + ".old") == false)
      return false;
   if(file.CopyTo(fileTmp) == false)
      return false;
   if(fileDest.CopyTo(file) == false)
      return false;
   fileDest.Remove();
   fileNormal.Remove();
   return true;
   }

bool CodeFormatter::FormatCode0(const File& fileIn, const File& fileOut)
   {
   bool bIgnoreNext = false;
   int iLevel = 0;
   File file = fileIn;
   istream& is = file.OpenRead(File::AT_BINARY);
   File oFile = fileOut;
   ostream& os = oFile.OpenWrite();
   char ch;
   while(is)
      {
      ch = Scroll(is);
      if(!is)
         continue;

      if(bIgnoreNext)
         {
         os << ch;
         bIgnoreNext = false;
         continue;
         }

      if(ch == '\"' || ch == '\'')
         {
         os << ch;
         PassQuote(os, is, ch);
         continue;
         }

      switch(ch)
         {
         case('\n'):
            os << endl;
         break;

         case(':'):
            {
            os << ch;
            }
         break;

         case(';'):
            {
            os << ch;
            Newline(os, iLevel);
            }
         break;

         case('{'):
            {
            os << ch;
            iLevel++;
            Newline(os, iLevel);
            }
         break;

         case('}'):
            {
            iLevel--;
            os << ch;
            Newline(os, iLevel);
            }
         break;

         default:
            os << ch;
         break;
         }
      }
   return true;
   }


bool CodeFormatter::FormatCode1(const File& fileIn, const File& fileOut)
   {
   bool bNewline = false;
   int iLevel = 0;
   File file = fileIn;
   istream& is = file.OpenRead(File::AT_BINARY);
   File oFile = fileOut;
   ostream& os = oFile.OpenWrite();
   ZStr str;
   while(is)
      {
      ReadToken(is, str);
      if(!is)
         continue;
      switch(str[0])
         {
         case('{'):
            {
            iLevel++;
            os << str;
            Newline(os, iLevel);
            bNewline = true;
            continue;
            }
         case('}'):
            {
            iLevel--;
            os << str;
            Newline(os, iLevel);
            bNewline = true;
            continue;
            }
         case(':'):
         case(';'):
            {
            os << str;
            if(bNewline == false)
               Newline(os, iLevel);
            bNewline = true;
            continue;
            }
         default:
         break;
         }
      bNewline = false;
      os << " ";
      os << str;
      }
   return true;
   }

bool CodeFormatter::FormatCode(const File& fileIn, const File& fileOut)
   {
   int iLevel = 0;
   File file = fileIn;
   istream& is = file.OpenRead(File::AT_BINARY);
   File oFile  = fileOut;
   ostream& os = oFile.OpenWrite(File::AT_BINARY);
   ZStr sLine;
   while(is)
      {
      ParseBlockOrStatement(is, sLine);
      if(!is)
         continue;
      CodeFormatter::BlockType bt = GetBlockType(sLine);
      switch(bt)
         {
         case(bt_Statement):
         break;

         case(bt_Simple):
         break;

         case(bt_Complex):
         break;
         }
      }
   return true;
   }
