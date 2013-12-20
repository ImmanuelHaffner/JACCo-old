//===--- SemaObject.cc-----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the SemaObject interface.
//
//===----------------------------------------------------------------------===//

#include "Sema.h"

using namespace C4;
using namespace AST;
using namespace Sema;


//===----------------------------------------------------------------------===//
//
//  Translation Unit
//
//===----------------------------------------------------------------------===//

SemaResult TranslationUnit::analyze( Env * const env ) const
{
  for ( auto it : *this )
  {
    it->analyze( env );
  }
}

//===----------------------------------------------------------------------===//
//
//  Expressions
//
//===----------------------------------------------------------------------===//

//SemaResult IllegalExpr::anaylze( Printer const p ) const
//{
  //p.out << "illegal expression " << this->tok << " ";
//}

//SemaResult Variable::anaylze( Printer const p ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult Constant::anaylze( Printer const p ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult StringLiteral::anaylze( Printer const p ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult BinaryExpr::anaylze( Printer const p ) const
//{
  //p.out << "(" << this->lhs << " " << this->tok.sym << " "
    //<< this->rhs << ")";
//}

//SemaResult PostIncExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->expr.anaylze( p );
  //p.out << "++)";
//}

//SemaResult PostDecExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->expr.anaylze( p );
  //p.out << "--)";
//}

//SemaResult DotExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->expr->anaylze( p ); // lhs
  //p.out << "." << this->id.sym << ")";
//}

//SemaResult ArrowExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->expr->anaylze( p ); // lhs
  //p.out << "->" << this->id.sym << ")";
//}

//SemaResult AssignmentExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->lhs->anaylze( p ); // lhs
  //p.out << " " << this->tok.sym << " "; // assignment operator
  //this->rhs->anaylze( p ); // rhs
  //p.out << ")";
//}

//SemaResult ConditionalExpr::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->cond->anaylze( p );
  //p.out << " ? ";
  //this->lhs->anaylze( p );
  //p.out << " : ";
  //this->rhs->print ( p );
  //p.out << ")";
//}

//SemaResult PreDecExpr::anaylze( Printer const p ) const
//{
  //p.out << "(--";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult PreIncExpr::anaylze( Printer const p ) const
//{
  //p.out << "(++";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult FunctionCall::anaylze( Printer const p ) const
//{
  //p.out << "(";
  //this->fun->anaylze( p );
  //// print the arguments
  //if ( this->args )
    //this->args->anaylze( p );
  //p.out << ")";
//}

//SemaResult UnaryOperation::anaylze( Printer const p ) const
//{
  //p.out << "(" << this->tok.sym;
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult SizeofExpr::anaylze( Printer const p ) const
//{
  //p.out << "(" << this->tok.sym << " ";
  //this->expr->anaylze( p );
  //p.out << ")";
//}

//SemaResult SizeofTypeExpr::anaylze( Printer const p ) const
//{
  //p.out << "(" << this->tok.sym << "(";
  //this->typeName->anaylze( p );
  //p.out << "))";
//}

//SemaResult SubscriptExpr::anaylze( Printer const p ) const
//{
  //p.out << "(" << this->expr << "[";
  //this->index->anaylze( p );
  //p.out << "])";
//}

//SemaResult ExprList::anaylze( Printer const p ) const
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

//SemaResult IllegalStmt::anaylze( Printer const p ) const
//{
  //p.out << "illegal statement " << this->tok << " ";
//}

//SemaResult CompoundStmt::anaylze( Printer const p ) const
//{
  //p.iout() << "{\n";
  //Printer const p_rec( p.out, p.indent + 1 );
  //for ( auto it = begin(); it != end(); ++it )
  //{
    //if ( (*it)->stmt )
      //(*it)->stmt->anaylze( p_rec );
    //else
    //{
      //p_rec.iout();
      //(*it)->decl->anaylze( p_rec );
    //}
    //p.out << "\n";
  //} // end for
  //p.iout() << "}";
//}

//SemaResult LabelStmt::anaylze( Printer const p ) const
//{
  //if ( tok.kind == TK::IDENTIFIER )
  //{
    //p.out << this->tok.sym << ":\n";
    //this->stmt->anaylze( Printer( p.out, p.indent ) );
  //}
  //else
  //{
    //p.iout() << this->tok.sym << ":\n";
    //this->stmt->anaylze( Printer( p.out, p.indent + 1 ) );
  //}
//}

//SemaResult CaseStmt::anaylze( Printer const p ) const
//{
  //p.iout() << this->tok.sym << " " << this->expr << ":\n";
  //if ( auto caseStmt = dynamic_cast< CaseStmt const * const >( stmt ) )
  //{
    //caseStmt->anaylze( p );
  //}
  //else
    //this->stmt->anaylze( Printer( p.out, p.indent + 1 ) );
//}

//SemaResult ExprStmt::anaylze( Printer const p ) const
//{
  //p.iout();
  //if ( this->expr )
    //this->expr->anaylze( p );
  //p.out << ";";
//}

//SemaResult IfStmt::anaylze( Printer const p ) const
//{
  //_anaylze( p );
//}

//SemaResult IfStmt::_anaylze( Printer const p, bool const elseIf /*= false*/ ) const
//{
  //if ( ! elseIf )
    //p.iout();

  //// if (a)
  //p.out << "if (";
  //Cond->anaylze( p );
  //p.out << ")";

  //// Printer for the Then and the Else block
  //Printer const p_rec( p.out, p.indent + 1 );

  ///*
   //*  if (a) {
   //*    a;
   //*    b;
   //*  }
   //*/
  //if ( auto compStmt = dynamic_cast< CompoundStmt const * const >( Then ) )
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

    //if ( Else )
      //p.out << " ";
  //}

  ///*
   //*  if (a)
   //*    a;
   //*/
  //else
  //{
    //p.out << "\n";
    //Then->anaylze( p_rec );
    //if ( Else )
    //{
      //p.out << "\n";
      //p.iout();
    //}
  //}

  //if ( Else )
  //{
    //p.out << "else";
    ///*
     //*  if (a)
     //*    a;
     //*  else if
     //*/
    //if ( auto ifStmt = dynamic_cast< IfStmt const * const >( Else ) )
    //{
      //p.out << " ";
      //ifStmt->_anaylze( p, true );
    //}

    ///*
     //*  if (a)
     //*    a;
     //*  else {
     //*    b;
     //*  }
     //*/
    //else if ( auto compStmt =
        //dynamic_cast< CompoundStmt const * const >( Else ) )
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
     //*  if (a)
     //*    a;
     //*  else
     //*    b;
     //*/
    //else
    //{
      //p.out << "\n";
      //Else->anaylze( p_rec );
    //}
  //} // end Else
//}

//SemaResult ForStmt::anaylze( Printer const p ) const
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

  //Printer const p_rec( p.out, p.indent + 1 );

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

//SemaResult SwitchStmt::anaylze( Printer const p ) const
//{
  //// switch (a)
  //p.iout() << "switch (";
  //Cond->anaylze( p );
  //p.out << ")";

  //// Printer for the Body
  //Printer const p_rec( p.out, p.indent + 1 );

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

//SemaResult WhileStmt::anaylze( Printer const p ) const
//{
  ///*
   //*  while (a)
   //*/
  //p.iout() << "while (";
  //this->Cond->anaylze( p );
  //p.out << ")";

  //Printer const p_rec( p.out, p.indent + 1 );

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

//SemaResult DoStmt::anaylze( Printer const p ) const
//{
  //p.iout() << "do";

  //Printer const p_rec( p.out, p.indent + 1 );

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

//SemaResult GotoStmt::anaylze( Printer const p ) const
//{
  //p.iout() << "goto " << tok.sym << ";";
//}

//SemaResult ContinueStmt::anaylze( Printer const p ) const
//{
  //p.iout() << "continue;";
//}

//SemaResult BreakStmt::anaylze( Printer const p ) const
//{
  //p.iout() << "break;";
//}

//SemaResult ReturnStmt::anaylze( Printer const p ) const
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

//SemaResult IllegalExtDecl::anaylze( Printer const p ) const
//{
  //p.out << "illegal external declaration " << this->tok << " ";
//}

//SemaResult IllegalDecl::anaylze( Printer const p ) const
//{
  //p.out << "illegal declaration " << this->tok << " ";
//}

//SemaResult Declarator::anaylze( Printer const p ) const
//{
  //// print the pointer by iterating over its count
  //for ( size_t i = 0; i < this->pointerCount; ++i )
    //p.out << "(*";
  //if ( this->directDeclarator )
    //this->directDeclarator->anaylze( p );
  //for ( size_t i = 0; i < this->pointerCount; ++i )
    //p.out << ")";
//}

//SemaResult IllegalDeclarator::anaylze( Printer const p ) const
//{
  //p.out << "illegal declaration " << this->tok << " ";
//}

//SemaResult DirectDeclarator::anaylze( Printer const p ) const
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

//SemaResult FunctionDef::anaylze( Printer const p ) const
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

//SemaResult DeclList::anaylze( Printer const p ) const
//{
  //for ( auto it = this->begin(); it != this->end(); ++it )
    //(*it)->anaylze( p );
//}

//SemaResult StructDeclList::anaylze( Printer const p ) const
//{
  //for ( auto it = begin(); it != end(); ++it )
  //{
    //(*it)->anaylze( p );
    //p.out << "\n";
  //}
//}

//SemaResult StructDecl::anaylze( Printer const p ) const
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

//SemaResult StructDeclaratorList::anaylze( Printer const p ) const
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

//SemaResult ParamDecl::anaylze( Printer const p ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
//}

//SemaResult ParamList::anaylze( Printer const p ) const
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

//SemaResult TypeName::anaylze( Printer const p ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
//}

//SemaResult StructSpecifier::anaylze( Printer const p ) const
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

//SemaResult TypeSpecifier::anaylze( Printer const p ) const
//{
  //p.out << this->tok.sym;
//}

//SemaResult IllegalTypeSpecifier::anaylze( Printer const p ) const
//{
  //p.out << "illegal type specifier " << this->tok << " ";
//}

//SemaResult Decl::anaylze( Printer const p ) const
//{
  //this->typeSpec->anaylze( p );
  //if ( this->declarator )
  //{
    //p.out << " ";
    //this->declarator->anaylze( p );
  //}
  //p.out << ";";
//}
