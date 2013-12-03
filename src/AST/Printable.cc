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


std::ostream & AST::operator<<( std::ostream &out, Printable const &p )
{
  p.print( Printer(out) );
  return out;
}


//===----------------------------------------------------------------------===//
//
//  Expressions
//
//===----------------------------------------------------------------------===//

void IllegalExpr::print( Printer const p ) const
{
  p.out << "illegal expression " << this->tok.sym;
}

void Variable::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void BinaryExpr::print( Printer const p ) const
{
  this->lhs->print( p );
  p.out << " " << this->tok.sym << " "; 
  this->rhs->print( p );
}

void PostIncExpr::print( Printer const p ) const
{
  this->expr.print( p );
  p.out << "++";
}

void PostDecExpr::print( Printer const p ) const
{
  this->expr.print( p );
  p.out << "--";
}

void ArrowExpr::print( Printer const p ) const
{
  this->lhs.print( p ); // lhs
  p.out << "->" << this->rhs.sym; // -> IDENTIFIER
}

void DotExpr::print( Printer const p ) const
{
  this->lhs.print( p ); // lhs
  p.out << "." << this->rhs.sym; // . IDENTIFIER
}

void AssignmentExpr::print( Printer const p ) const
{
  this->lhs->print( p ); // lhs
  p.out << " " << this->tok.sym << " "; // assignment operator
  this->rhs->print( p ); // rhs
}

void ConditionalExpr::print( Printer const p ) const
{
  this->cond->print( p );
  p.out << " ? ";
  this->lhs->print( p );
  p.out << " : ";
  this->rhs->print ( p );
}

void Constant::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void StringLiteral::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void PreDecExpr::print( Printer const p ) const
{
  p.out << "--";
  this->expr->print( p );
}

void PreIncExpr::print( Printer const p ) const
{
  p.out << "++";
  this->expr->print( p );
}

void FunctionCall::print( Printer const p ) const
{
  //TODO 
  (void) p;
}

void SizeofExpr::print( Printer const p ) const
{
  p.out << this->tok.sym << " ";
  this->expr->print( p );
}

void SizeofTypeExpr::print( Printer const p ) const
{
  //TODO: Missing << / print() for types
  /*p.out << this->tok.sym << "(";
    this->type.print( p );
    p.out << ")";*/
  (void) p;

}

void SubscriptExpr::print( Printer const p ) const
{
  p.out << this->expr << "[";
  this->index->print( p );
  p.out << "]";
}

void CastExpr::print( Printer const p ) const
{
  p.out << this->tok.sym;
}


//===----------------------------------------------------------------------===//
//
//  Statements
//
//===----------------------------------------------------------------------===//

void IllegalStmt::print( Printer const p ) const
{
  p.out << this->tok.sym;
}


//===----------------------------------------------------------------------===//
//
//  Declaration
//
//===----------------------------------------------------------------------===//

/*Lazyness void IllegalDecl::print( Printer const p ) const
{
  p.out << this->tok.sym;
}*/


//===----------------------------------------------------------------------===//
//
//  Type
//
//===----------------------------------------------------------------------===//

void IllegalType::print( Printer const p ) const
{
  p.out << this->tok.sym;
}
