/*
CheesyPaginator was written to allows me to Read, bookmark,
and extract quotations from text files. Just like a
book.

"Just like a book" means that text is formatted into
pages. Pages that allow us to track Reading progress, 
as well as to exchange book references with others.

Why Bother?
-----------
Because I use everything from desktops to PDAs 
(-that span 20 years of technology - HP 100/200LX, 
Zaurus 5600,Jornada 720...) the Reader is designed 
to work using plain old ASCII - no kerned fonts, no 
graphical support - deliciously cheesy!

Because WIN32 is very popular, a graphical interface
is included. Because console applications are more 
portable (especially when you have a DOS emulator), 
a DOS Reading utility is also provided.

Whats Next?
-----------
I will be converting hundreds of public domain tomes 
and electronic texts for us to Read. If you are a 
civic minded sort of person, then you can share the
cheesy books that you create with this program 
family, too.

*/
// 04/16/2005 - Class created, R. Nagy
#ifndef CheesyPaginator_Hpp
#define CheesyPaginator_Hpp

#include "AbsoluteBookReferences.hpp"
using namespace AbsoluteBookReferences;

class CheesyPaginator
{
   public:
      class CheesyBook
         {
         public:
            class CheesyPage
               {
               // A page is simply an array of lines
               Array<Line> aLines;
               public:
                  int pageWidth(void);
                  int pageHeight(void);
                  bool isFull(void);
                  // Append will fill up a page. If anything is left over,
                  // it will be returned so you can append it to the *next*
                  // page. Return of true means that something was appended.
                  // Line will be null (ty_null) when is has all be Inserted.
                  bool        append(Line& ioLine);

                  static int pageWidthDefault(void);
                  static int pageHeightDefault(void);
               };
               
            size_t  GetPages(void);    // Nelem() of pages in the book
            bool    GetPage(size_t, CheesyPage& result);            
            
         protected:
            // A book is simply an array of pages
            Array<CheesyPage> pwBook;
            
         friend CheesyPaginator;            
         };
         
      // Detect sentances and paragraph marks - put them into an array of lines, then paginate them.
      static bool Paginate(File& fileIn, CheesyBook& book, ostream& os);
};


#endif
