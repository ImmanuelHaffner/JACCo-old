<<<<<<< HEAD
//===--- Printable.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Printable.h"
#include "AST.h"


using namespace C4;
using namespace AST;


void Variable::print( Printer const p )
{
  p.out << this->tok.sym;
}
||||||| merged common ancestors
=======
//===--- Printable.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Printable.h"
#include "AST.h"


using namespace C4;
using namespace AST;


void Variable::print( Printer const p )
{
  p.out << this->tok.sym;
}

void BinaryExpr::print( Printer const p )
{
    this->lhs.print();
    p.out << " " << this->tok.sym << " "; 
    this->rhs.print();
}

>>>>>>> moved print method of binary expression to printable.cc
