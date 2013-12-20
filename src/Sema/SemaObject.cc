//===--- SemaObject.cc-----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the SemaObject interface.
//
//===----------------------------------------------------------------------===//

#include "Sema.h"
#include "../AST/AST.h"

using namespace C4;
using namespace AST;
using namespace Sema;

#define RET return SemaResult( Valueness::RLValue, 0 )


//===----------------------------------------------------------------------===//
//
//  Translation Unit
//
//===----------------------------------------------------------------------===//

SemaResult TranslationUnit::analyze( Env &env ) const
{
  for ( auto it : *this );
  // TODO analyze
    //it->analyze( env );
}

//===----------------------------------------------------------------------===//
//
//  Expressions
//
//===----------------------------------------------------------------------===//

//SemaResult IllegalExpr::anaylze( Env &env ) const
//{
  //p.out << "illegal expression " << this->tok << " ";
//}

SemaResult Variable::analyze( Env &env ) const
{
  return SemaResult( Valueness::RLValue, 0 );
}

//SemaResult Constant::anaylze( Env &env ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult StringLiteral::anaylze( Env &env ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult BinaryExpr::anaylze( Env &env ) const
//{
  //p.out << "(" << this->lhs << " " << this->tok.sym << " "
    //<< this->rhs << ")";
//}

//SemaResult PostIncExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->expr.anaylze( p );
  //p.out << "++)";
//}

//SemaResult PostDecExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->expr.anaylze( p );
  //p.out << "--)";
//}

//SemaResult DotExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->expr->anaylze( p ); // lhs
  //p.out << "." << this->id.sym << ")";
//}

//SemaResult ArrowExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->expr->anaylze( p ); // lhs
  //p.out << "->" << this->id.sym << ")";
//}

//SemaResult AssignmentExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->lhs->anaylze( p ); // lhs
  //p.out << " " << this->tok.sym << " "; // assignment operator
  //this->rhs->anaylze( p ); // rhs
  //p.out << ")";
//}

//SemaResult ConditionalExpr::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->cond->anaylze( p );
  //p.out << " ? ";
  //this->lhs->anaylze( p );
  //p.out << " : ";
  //this->rhs->print ( p );
  //p.out << ")";
//}

//SemaResult PreDecExpr::anaylze( Env &env ) const
//{
  //p.out << "(--";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult PreIncExpr::anaylze( Env &env ) const
//{
  //p.out << "(++";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult FunctionCall::anaylze( Env &env ) const
//{
  //p.out << "(";
  //this->fun->anaylze( p );
  //// print the arguments
  //if ( this->args )
    //this->args->anaylze( p );
  //p.out << ")";
//}

//SemaResult UnaryOperation::anaylze( Env &env ) const
//{
  //p.out << "(" << this->tok.sym;
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult SizeofExpr::anaylze( Env &env ) const
//{
  //p.out << "(" << this->tok.sym << " ";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult SizeofTypeExpr::anaylze( Env &env ) const
//{
  //p.out << "(" << this->tok.sym << "(";
  //this->typeName->anaylze( p );
  //p.out << "))";
//}

//SemaResult SubscriptExpr::anaylze( Env &env ) const
//{
  //p.out << "(" << this->expr << "[";
  //this->index->anaylze( p );
  //p.out << "])";
//}

//SemaResult ExprList::anaylze( Env &env ) const
//{
  //p.out << "(";
  //auto it = this->begin();

  //if ( it != this->end() )
  //{
    //(*it)->anaylze( p );
    //++it;

    //for ( ; it != this->end(); ++it )
    //{
      //p.out << ", ";
      //(*it)->anaylze( p );
    //}
  //}
  //p.out << ")";
//}


////===----------------------------------------------------------------------===//
////
////  Statements
////
////===----------------------------------------------------------------------===//

SemaResult IllegalStmt::anaylze( Env &env ) const
{
  RET;
}

SemaResult CompoundStmt::anaylze( Env &env ) const
{
  env->pushScope();
  for ( auto it : *this )
  {
    it->analyze( env );
  }
  env->popScope();
  RET;
}

SemaResult LabelStmt::anaylze( Env &env ) const
{
  this->stmt->anaylze( env );
  RET;
}

SemaResult CaseStmt::anaylze( Env &env ) const
{
  this->expr->analyze( env );
  this->stmt->anaylze( env );
  RET;
}

SemaResult ExprStmt::anaylze( Env &env ) const
{
  if ( this->expr )
    return this->expr->anaylze( env );
  RET;
}

SemaResult IfStmt::anaylze( Env &env, bool const elseIf /*= false*/ ) const
{
  Cond->anaylze( env );
  Then->analyze( env );
  if ( Else )
    Else->analyze( env );
  RET;
}

//SemaResult ForStmt::anaylze( Env &env ) const
//{
  ///*
   //*  for (;;)
   //*/
  //p.iout() << "for (";
  //if ( this->Init )
    //this->Init->anaylze( p );
  //else if ( this->InitDecl )
    //this->InitDecl->anaylze( p );
  //p.out << ";";
  //if ( this->Cond )
    //this->Cond->anaylze( p );
  //p.out << ";";
  //if ( this->Step )
    //this->Step->anaylze( p );
  //p.out << ")";

  //Env &env_rec( p.out, p.indent + 1 );

  ///*
   //*  for (;;) {
   //*  }
   //*/
  //if ( auto compStmt =
      //dynamic_cast< CompoundStmt const * const >( this->Body ) )
  //{
    //p.out << " {\n";

    //for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
    //{
      //if ( (*it)->stmt )
        //(*it)->stmt->anaylze( p_rec );
      //else
      //{
        //p_rec.iout();
        //(*it)->decl->anaylze( p_rec );
      //}
      //p.out << "\n";
    //}

    //p.iout() << "}";
  //}

  ///*
   //*  for (;;)
   //*    ;
   //*/
  //else
  //{
    //p.out << "\n";
    //this->Body->anaylze( p_rec );
  //}
//}

//SemaResult SwitchStmt::anaylze( Env &env ) const
//{
  //// switch (a)
  //p.iout() << "switch (";
  //Cond->anaylze( p );
  //p.out << ")";

  //// Printer for the Body
  //Env &env_rec( p.out, p.indent + 1 );

  ///*
   //*  switch (a) {
   //*  }
   //*/
  //if ( auto compStmt = dynamic_cast< CompoundStmt const * const >( Body ) )
  //{
    //p.out << " {\n";

    //for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
    //{
      //if ( (*it)->stmt )
        //(*it)->stmt->anaylze( p_rec );
      //else
      //{
        //p_rec.iout();
        //(*it)->decl->anaylze( p_rec );
      //}
      //p.out << "\n";
    //}

    //p.iout() << "}";
  //}

  ///*
   //*  switch (a)
   //*    ;
   //*/
  //else
  //{
    //p.out << "\n";
    //this->Body->anaylze( p_rec );
  //}
//}

//SemaResult WhileStmt::anaylze( Env &env ) const
//{
  ///*
   //*  while (a)
   //*/
  //p.iout() << "while (";
  //this->Cond->anaylze( p );
  //p.out << ")";

  //Env &env_rec( p.out, p.indent + 1 );

  ///*
   //*  while (a) {
   //*  }
   //*/
  //if ( auto compStmt =
      //dynamic_cast< CompoundStmt const * const >( this->Body ) )
  //{
    //p.out << " {\n";

    //for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
    //{
      //if ( (*it)->stmt )
        //(*it)->stmt->anaylze( p_rec );
      //else
      //{
        //p_rec.iout();
        //(*it)->decl->anaylze( p_rec );
      //}
      //p.out << "\n";
    //}

    //p.iout() << "}";
  //}

  ///*
   //*  while (a)
   //*    ;
   //*/
  //else
  //{
    //p.out << "\n";
    //this->Body->anaylze( p_rec );
  //}
//}

//SemaResult DoStmt::anaylze( Env &env ) const
//{
  //p.iout() << "do";

  //Env &env_rec( p.out, p.indent + 1 );

  ///*
   //*  do {
   //*    a;
   //*  } while(a);
   //*/
  //if ( auto compStmt =
      //dynamic_cast< CompoundStmt const * const >( this->Body ) )
  //{
    //p.out << " {\n";

    //for ( auto it = compStmt->begin(); it != compStmt->end(); ++it )
    //{
      //if ( (*it)->stmt )
        //(*it)->stmt->anaylze( p_rec );
      //else
      //{
        //p_rec.iout();
        //(*it)->decl->anaylze( p_rec );
      //}

      //p.out << "\n";
    //}

    //// prepare cursor for 'while'
    //p.iout() << "} ";
  //}

  ///*
   //*  do
   //*    a;
   //*  while(a);
   //*/
  //else
  //{
    //p.out << "\n";
    //this->Body->anaylze( p_rec );

    //// prepare cursor for 'while'
    //p.out << "\n";
    //p.iout();
  //}

  //p.out << "while (";
  //this->Cond->anaylze( p );
  //p.out << ");";
//}

//SemaResult GotoStmt::anaylze( Env &env ) const
//{
  //p.iout() << "goto " << tok.sym << ";";
//}

//SemaResult ContinueStmt::anaylze( Env &env ) const
//{
  //p.iout() << "continue;";
//}

//SemaResult BreakStmt::anaylze( Env &env ) const
//{
  //p.iout() << "break;";
//}

//SemaResult ReturnStmt::anaylze( Env &env ) const
//{
  //p.iout() << "return";
  //if ( this->expr )
  //{
    //p.out << " ";
    //this->expr->anaylze( p );
  //}
  //p.out << ";";
//}


////===----------------------------------------------------------------------===//
////
////  Declaration
////
////===----------------------------------------------------------------------===//

//SemaResult IllegalExtDecl::anaylze( Env &env ) const
//{
  //p.out << "illegal external declaration " << this->tok << " ";
//}

//SemaResult IllegalDecl::anaylze( Env &env ) const
//{
  //p.out << "illegal declaration " << this->tok << " ";
//}

//SemaResult Declarator::anaylze( Env &env ) const
//{
  //// print the pointer by iterating over its count
  //for ( size_t i = 0; i < this->pointerCount; ++i )
    //p.out << "(*";
  //if ( this->directDeclarator )
    //this->directDeclarator->anaylze( p );
  //for ( size_t i = 0; i < this->pointerCount; ++i )
    //p.out << ")";
//}

//SemaResult IllegalDeclarator::anaylze( Env &env ) const
//{
  //p.out << "illegal declaration " << this->tok << " ";
//}

//SemaResult DirectDeclarator::anaylze( Env &env ) const
//{
  //if ( ! ( this->declarator || this->directDeclarator || this->params ) )
    //p.out << this->tok.sym;
  //else
  //{
    ///*
     //* If this direct declarator has a LHS and a RHS, print a parenthesis around
     //* them, e.g.:
     //*
     //*    (foo(int))
     //*/
    //if ( this->params )
      //p.out << "(";

    //if ( this->declarator )
      //this->declarator->print ( p );
    //else if ( this->directDeclarator )
      //this->directDeclarator->anaylze( p );
    //else if ( ! this->params )
      //p.out << this->tok; // IDENTIFIER

    //if ( this->params )
    //{
      //if ( this->declarator || this->directDeclarator )
        //p.out << "(";
      //this->params->anaylze( p );
      //if ( this->declarator || this->directDeclarator )
        //p.out << ")";
    //}

    //// close parenthesis
    //if ( this->params )
      //p.out << ")";
  //}
//}

//SemaResult FunctionDef::anaylze( Env &env ) const
//{
  //this->typeSpec->anaylze( p );
  //p.out << " ";
  //this->declarator->anaylze( p );
  //if ( this->decls )
    //p.out << " " << this->decls;
  //// static cast, to resolve multiple-inheritance ambiguity
  //p.out << "\n";
  //this->compStmt->anaylze( p );
//}

//SemaResult DeclList::anaylze( Env &env ) const
//{
  //for ( auto it = this->begin(); it != this->end(); ++it )
    //(*it)->anaylze( p );
//}

//SemaResult StructDeclList::anaylze( Env &env ) const
//{
  //for ( auto it = begin(); it != end(); ++it )
  //{
    //(*it)->anaylze( p );
    //p.out << "\n";
  //}
//}

//SemaResult StructDecl::anaylze( Env &env ) const
//{
  //p.iout();
  //this->typeSpec->anaylze( p );
  //if ( this->structDeclarators )
  //{
    //p.out << " ";
    //this->structDeclarators->anaylze( p );
  //}
  //p.out << ";";
//}

//SemaResult StructDeclaratorList::anaylze( Env &env ) const
//{
  //auto it = begin();
  //if ( it !=end() )
  //{
    //(*it)->anaylze( p );
    //++it;

    //for ( ; it != end(); ++it )
    //{
      //p.out << ", ";
      //(*it)->anaylze( p );
    //}
  //}
//}

//SemaResult ParamDecl::anaylze( Env &env ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
//}

//SemaResult ParamList::anaylze( Env &env ) const
//{
  //auto it = begin();
  //if ( it != end() )
  //{
    //(*it)->anaylze( p );
    //++it;

    //for ( ; it != end(); ++it )
    //{
      //p.out << ", ";
      //(*it)->anaylze( p );
    //}
  //}
//}


////===----------------------------------------------------------------------===//
////
////  Type
////
////===----------------------------------------------------------------------===//

//SemaResult TypeName::anaylze( Env &env ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
//}

//SemaResult StructSpecifier::anaylze( Env &env ) const
//{
  //p.out << "struct";

  ///*
   //* struct S
   //*/
  //if ( this->name )
    //p.out << " " << this->name->sym;

  ///*
   //* struct [S]
   //* {
   //* }
   //*/
  //if ( this->structDecls )
  //{
    //p.out << "\n";
    //p.iout() << "{\n";
    //this->structDecls->anaylze( Printer ( p.out, p.indent + 1) );
    //p.iout() << "}";
  //}
//}

//SemaResult TypeSpecifier::anaylze( Env &env ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult IllegalTypeSpecifier::anaylze( Env &env ) const
//{
  //p.out << "illegal type specifier " << this->tok << " ";
//}

//SemaResult Decl::anaylze( Env &env ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
  //p.out << ";";
//}
