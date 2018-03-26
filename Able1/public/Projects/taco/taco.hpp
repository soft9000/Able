// T.A.C.O - Transitive Associations for Codebase Organization
// =======   
// GOAL is to extract member definitions so a SINGLE set of external 
// documentation can be maintained between SEVERAL concurrent code bases.
//
// SIMPLE RULES:
// ~~~~~~~~~~~~ 
// (1) CodeToTaco REMOVES source code documentation to TACO doc files in TACO folder.
// (2) TacoToCode REMOVES TACO doc files after moving same into source code.
// (3) Errors between to above states leave project in pre-call state.
//
// TACO allows for the embedding, extraction, replacement, and stand-alone 
// maintenance of "chunk-style" ASCII information. 
//
// TACO will create a file that can be used with other stand-alone
// tools (e.g. asciidoc, spell checkers, databases.) 
//
// TACO features can be applied in such a way so as to move any updates 
// back into source code base(s)... or not... as your project preference 
// demands.
// -----
//
// 2008/07/26: Project created, R. A. Nagy
//
#ifndef taco_hpp
#define taco_hpp

#include <Able1.hpp>
using namespace Able1;

#include "Entry.hpp"
#include "Language.hpp"
#include "Job.hpp"


#endif
