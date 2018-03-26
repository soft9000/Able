#include "CheesyPaginator.hpp"

int CheesyPaginator::CheesyBook::CheesyPage::pageWidthDefault(void)    
   {
   return 50;
   }
int CheesyPaginator::CheesyBook::CheesyPage::pageHeightDefault(void)   
   {
   return 20;
   }
int CheesyPaginator::CheesyBook::CheesyPage::pageWidth(void)    
   {
   return pageWidthDefault();
   }
bool CheesyPaginator::CheesyBook::CheesyPage::append(Line& refLine)
   {
   bool br = false;
   if(aLines.Nelem())
      {
      // Check to see if we have room to word-wrap this into the page
      size_t newhit = refLine.sSentance.Find(' ');
      Line& hang = aLines[aLines.Nelem() -1];
      int avail = int(pageWidth()) - int(hang.sSentance.Length());
      if(avail >= newhit)
         {
         // wrap it into the last line
         ZStr sUnify = hang.sSentance + " " + refLine.sSentance;
         hang.sSentance = StdReadable::mkSegment(sUnify, pageWidth());
         refLine.sSentance = sUnify;
         br = true;
         }
      }

   Line actual = refLine;
   while(isFull() == false)
      {
      actual.sSentance = StdReadable::mkSegment(refLine.sSentance, pageWidth());
      aLines.Append(actual);
      br = true;
      }
   return br;
   }
bool CheesyPaginator::CheesyBook::CheesyPage::isFull(void)
   {
   if(aLines.Nelem() >= pageHeight())
      return true;
   return false;
   }
int CheesyPaginator::CheesyBook::CheesyPage::pageHeight(void)   
   {
   return pageHeightDefault();
   }
size_t  CheesyPaginator::CheesyBook::GetPages(void)
   {
   return pwBook.Nelem();
   }
bool CheesyPaginator::CheesyBook::GetPage(size_t ss, CheesyPage& result)
   {
   if(ss >= pwBook.Nelem())
      return false;
   pwBook.At(ss, result);
   return true;
   }
bool CheesyPaginator::Paginate(File& fileIn, CheesyBook& book, ostream& os)
   {
   size_t lines = 0L;
      {
   // <<<WIP>>> IsTextFile() ?
   istream& is = fileIn.OpenRead();
   ZStr sLine;
   
   // STEP: Pre-allocate the array ...
   while(StdReadable::getSentance(is, sLine) == true)
      lines++;
   book.pwBook.AddZombies(lines);
   fileIn.Close();
      }
   
   // STEP: Add-in the lines
   lines = 0L;
   Line line;
   istream& is = fileIn.OpenRead();
   CheesyBook::CheesyPage page;
   while(StdReadable::getSentance(is, line.sSentance) == true)
      {
      line.lineId = lines;
      while(!line.IsNull())
         {
         page.Append(line);
         if(page.isFull())
            {
            book.pwBook.Append(page);
            book.pwBook.Empty();
            }
         }
      lines++;
      }

   // STEP: Don't forget to save the page-in-progress!
   if(page.isFull() == false)
      book.pwBook.Append(page);
   return true;
   }

