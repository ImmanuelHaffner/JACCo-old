//===--- Printable.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "AST.h"

using namespace C4;
using namespace AST;


std::ostream & Printer::iout() const
{
  for ( unsigned i = 0; i < indent; ++i )
    out << "\t";
  return out;
}

std::ostream & AST::operator<<( std::ostream &out, Printable const &p )
{
  p.print( Printer(out) );
  return out;
}

std::ostream & AST::operator<<( std::ostream &out, Printable const * const p )
{
  p->print( Printer(out) );
  return out;
}

std::ostream & AST::operator<<( std::ostream &out, Printer const &p )
{
  for ( unsigned i = 0; i < p.indent; ++i )
    out << "\t";
  return out;
}

void Printable::dump() const
{
  std::cout << this << std::endl;
}


//===----------------------------------------------------------------------===//
//
//  Translation Unit
//
//===----------------------------------------------------------------------===//

void TranslationUnit::print( Printer const p ) const
{
  for ( auto it = begin(); it != end(); ++it )
  {
    (*it)->print( p );
    p.out << "\n";
  }
}


//===----------------------------------------------------------------------===//
//
//  Expressions
//
//===----------------------------------------------------------------------===//

void IllegalExpr::print( Printer const p ) const
{
  p.out << "illegal expression " << this->tok << " ";
}

void Variable::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void Constant::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void StringLiteral::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void BinaryExpr::print( Printer const p ) const
{
  p.out << "(" << this->lhs << " " << this->tok.sym << " "
    << this->rhs << ")";
}

void PostIncExpr::print( Printer const p ) const
{
  p.out << "(";
  this->expr.print( p );
  p.out << "++)";
}

void PostDecExpr::print( Printer const p ) const
{
  p.out << "(";
  this->expr.print( p );
  p.out << "--)";
}

void DotExpr::print( Printer const p ) const
{
  p.out << "(";
  this->expr->print( p ); // lhs
  p.out << "." << this->id.sym << ")";
}

void ArrowExpr::print( Printer const p ) const
{
  p.out << "(";
  this->expr->print( p ); // lhs
  p.out << "->" << this->id.sym << ")";
}

void AssignmentExpr::print( Printer const p ) const
{
  p.out << "(";
  this->lhs->print( p ); // lhs
  p.out << " " << this->tok.sym << " "; // assignment operator
  this->rhs->print( p ); // rhs
  p.out << ")";
}

void ConditionalExpr::print( Printer const p ) const
{
  p.out << "(";
  this->cond->print( p );
  p.out << " ? ";
  this->lhs->print( p );
  p.out << " : ";
  this->rhs->print ( p );
  p.out << ")";
}

void PreDecExpr::print( Printer const p ) const
{
  p.out << "(--";
  this->expr->print( p );
  p.out << ")";
}

void PreIncExpr::print( Printer const p ) const
{
  p.out << "(++";
  this->expr->print( p );
  p.out << ")";
}

void FunctionCall::print( Printer const p ) const
{
  this->fun->print( p );
  p.out << "(";
  // print the arguments
  if ( this->args )
  {
    ExprList const * const args =
      static_cast< ExprList const * const >( this->args );
    for ( auto it = args->begin(); it != args->end(); ++it )
      (*it)->print( p );
  }
  p.out << ")";
}

void UnaryOperation::print( Printer const p ) const
{
  p.out << "(" << this->tok;
  this->expr->print( p );
  p.out << ")";
}

void SizeofExpr::print( Printer const p ) const
{
  p.out << "(" << this->tok.sym << " ";
  this->expr->print( p );
  p.out << ")";
}

void SizeofTypeExpr::print( Printer const p ) const
{
  p.out << "(" << this->tok.sym << "(";
  this->type->print( p );
  p.out << "))";
}

void SubscriptExpr::print( Printer const p ) const
{
  p.out << "(" << this->expr << "[";
  this->index->print( p );
  p.out << "])";
}

void ExprList::print( Printer const p ) const
{
  p.out << "(";
  auto it = this->begin();

  if ( it != this->end() )
  {
    (*it)->print( p );
    ++it;

    for ( ; it != this->end(); ++it )
    {
      p.out << ", ";
      (*it)->print( p );
    }
  }
  p.out << ")";
}


//===----------------------------------------------------------------------===//
//
//  Statements
//
//===----------------------------------------------------------------------===//

void IllegalStmt::print( Printer const p ) const
{
  p.out << "illegal statement " << this->tok << " ";
}

void CompoundStmt::print( Printer const p ) const
{
  p.iout() << "{\n";
  Printer const p_rec( p.out, p.indent + 1 );
  for ( auto it = begin(); it != end(); ++it )
  {
    if ( (*it)->stmt )
      (*it)->stmt->print( p_rec );
    else
    {
      p_rec.iout();
      (*it)->decl->print( p_rec );
    }
    p.out << "\n";
  } // end for
  p.iout() << "}";
}

void ReturnStmt::print( Printer const p ) const
{
  p.iout() << "return";
  if ( this->expr )
  {
    p.out << " ";
    this->expr->print( p );
  }
  p.out << ";";
}

void LabelStmt::print( Printer const p ) const
{
  p.out << this->tok << ":\n";
  this->stmt->print( p );
}

void CaseStmt::print( Printer const p ) const
{
  p.out << this->tok << " " << this->expr << ":\n" << this->stmt;
}

void ExprStmt::print( Printer const p ) const
{
  p.iout();
  if ( this->expr )
    this->expr->print( p );
  p.out << ";";
}

void IfStmt::print( Printer const p ) const
{
  _print( p );
}

void IfStmt::_print( Printer const p, bool const elseIf /*= false*/ ) const
{
  if ( ! elseIf )
    p.iout();

  // if (a)
  p.out << "if (";
  Cond->print( p );
  p.out << ")";

  // Printer for the Then and the Else block
  Printer const p_rec( p.out, p.indent + 1 );

  /*
   *  if (a) {
   *    a;
   *    b;
   *  }
   */
  if ( auto compStmt = dynamic_cast< CompoundStmt const * const >( Then ) )
  {
    p.out << " {\n";

    for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
    {
      if ( (*it)->stmt )
        (*it)->stmt->print( p_rec );
      else
      {
        p_rec.iout();
        (*it)->decl->print( p_rec );
      }
      p.out << "\n";
    }

    p.iout() << "}";

    if ( Else )
      p.out << " ";
  }

  /*
   *  if (a)
   *    a;
   */
  else
  {
    p.out << "\n";
    Then->print( p_rec );
    if ( Else )
    {
      p.out << "\n";
      p.iout();
    }
  }

  if ( Else )
  {
    p.out << "else";
    /*
     *  if (a)
     *    a;
     *  else if
     */
    if ( auto ifStmt = dynamic_cast< IfStmt const * const >( Else ) )
    {
      p.out << " ";
      ifStmt->_print( p, true );
    }

    /*
     *  if (a)
     *    a;
     *  else {
     *    b;
     *  }
     */
    else if ( auto compStmt =
        dynamic_cast< CompoundStmt const * const >( Else ) )
    {
      p.out << " {\n";

      for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
      {
        if ( (*it)->stmt )
          (*it)->stmt->print( p_rec );
        else
        {
          p_rec.iout();
          (*it)->decl->print( p_rec );
        }
        p.out << "\n";
      }

      p.iout() << "}";
    }

    /*
     *  if (a)
     *    a;
     *  else
     *    b;
     */
    else
    {
      p.out << "\n";
      Else->print( p_rec );
    }
  } // end Else
}

void ForStmt::print( Printer const p ) const
{
  //TODO but not important
  (void) p;
}

void SwitchStmt::print( Printer const p ) const
{
  //TODO but not important
  (void) p;
}

void WhileStmt::print( Printer const p ) const
{
  //TODO
  (void) p;
}

//===----------------------------------------------------------------------===//
//
//  Declaration
//
//===----------------------------------------------------------------------===//

void IllegalExtDecl::print( Printer const p ) const
{
  p.out << "illegal external declaration " << this->tok << " ";
}

void TypeSpecifier::print( Printer const p ) const
{
  p.out << this->tok.sym;
}

void StructSpecifier::print( Printer const p ) const
{
  p.out << "struct";
  if ( this->name )
    p.out << " " << this->name->sym;

  if ( this->structDecls )
  {
    p.out << p << "\n{";
    this->structDecls->print( Printer ( p.out, p.indent + 1) );
    p.out << p << "}";
  }
}

void IllegalTypeSpecifier::print( Printer const p ) const
{
  p.out << "illegal type specifier " << this->tok << " ";
}

void Decl::print( Printer const p ) const
{
  this->typeSpec->print( p );
  if ( this->declarator )
  {
    p.out << " ";
    this->declarator->print( p );
  }
  p.out << ";";
}

void IllegalDecl::print( Printer const p ) const
{
  p.out << "illegal declaration " << this->tok << " ";
}

void Declarator::print( Printer const p ) const
{
  // print the pointer by iterating over its count
  for ( size_t i = 0; i < this->pointerCount; ++i )
    p.out << "(*";
  if ( this->directDeclarator )
    this->directDeclarator->print( p );
  for ( size_t i = 0; i < this->pointerCount; ++i )
    p.out << ")";
}

void IllegalDeclarator::print( Printer const p ) const
{
  p.out << "illegal declaration " << this->tok << " ";
}

void DirectDeclarator::print( Printer const p ) const
{
  if ( ! ( this->declarator || this->directDeclarator || this->params ) )
    p.out << this->tok.sym;
  else
  {
    if ( this->declarator )
    {
      p.out << "(";
      this->declarator->print ( p );
      p.out << ")";
    }
    else if ( this->directDeclarator )
      this->directDeclarator->print( p );

    if ( this->params )
    {
      p.out << "(";
      this->params->print( p );
      p.out << ")";
    }
  }
}

void FunctionDef::print( Printer const p ) const
{
  p.out << this->typeSpec << " " << this->declarator;
  if ( this->decls )
    p.out << " " << this->decls;
  // static cast, to resolve multiple-inheritance ambiguity
  p.out << "\n" << (Stmt const * const) this->compStmt;
}

void DeclList::print( Printer const p ) const
{
  for ( auto it = this->begin(); it != this->end(); ++it )
    (*it)->print( p );
}

void StructDeclList::print( Printer const p ) const
{
  for ( auto const &it : *this )
  {
    p.out << p;
    it->print( p );
    p.out << ";\n";
  }
}

void StructDeclaratorList::print( Printer const p ) const
{
  for ( auto it = begin(); it != end(); ++it )
    (*it)->print( p );
}

void ParamDecl::print( Printer const p ) const
{
  this->typeSpec->print( p );
  if ( this->declarator )
  {
    p.out << " ";
    this->declarator->print( p );
  }
}

void ParamList::print( Printer const p ) const
{
  auto it = begin();
  if ( it != end() )
  {
    (*it)->print( p );
    ++it;

    for ( ; it != end(); ++it )
    {
      p.out << ", ";
      (*it)->print( p );
    }
  }
}


//===----------------------------------------------------------------------===//
//
//  Type
//
//===----------------------------------------------------------------------===//

void IllegalType::print( Printer const p ) const
{
  p.out << "illegal type " << this->tok.sym << " ";
}

void Type::print( Printer const p ) const
{
  this->typeSpec->print( p );
  if ( this->declarator )
  {
    p.out << " ";
    this->declarator->print( p );
  }
}
