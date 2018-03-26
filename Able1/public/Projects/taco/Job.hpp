#ifndef tacoJob_hpp
#define tacoJob_hpp

#include "taco.hpp"

namespace Taco
{

// SIMPLE RULES: 
// (1) CodeToTaco REMOVES source code documentation to TACO doc files in TACO folder.
// (2) TacoToCode REMOVES TACO doc files after moving same into source code.
// (3) Errors leave project in pre-call state.
//
class Job
{
   private:
      Directory    dirSource;
      LanguageInfo lang;

   protected:
      static ZStr ExtractDeffBlock(istream& is, const Job& job);
      static void Extract(const File& file, const Job& job, Array<Entry>& aResult); 

   public:
      Array<Entry> aDoc;
      Array<File>  aFiles;

      static bool Load(const Directory& dirSource, const LanguageInfo& lang, Job& job);
      static bool Save(const Job& job);

      static bool HeaderFunList(Job& job);
      static bool CodeToTaco(Job& job);
      static bool TacoToCode(Job& job);
};


}

#endif
