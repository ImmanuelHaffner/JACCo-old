//===--- AST.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_AST_H
#define C4_AST_H

//
//  Expression
//
#include "Expr.h"
#include "IllegalExpr.h"
#include "Variable.h"
#include "Constant.h"
#include "StringLiteral.h"
#include "ExprList.h"
#include "ConditionalExpr.h"
#include "CastExpr.h"

#include "BinaryExpr.h"
#include "AssignmentExpr.h"

#include "UnaryExpr.h"
#include "PreIncExpr.h"
#include "PreDecExpr.h"
#include "SizeofExpr.h"
#include "SizeofTypeExpr.h"

#include "PostfixExpr.h"
#include "SubscriptExpr.h"
#include "FunctionCall.h"
#include "PostIncExpr.h"
#include "PostDecExpr.h"
#include "DotExpr.h"
#include "ArrowExpr.h"

//
//  Statement
//
#include "Stmt.h"
#include "IllegalStmt.h"

//
//  Declaration
//
#include "Declaration.h"
#include "IllegalDeclaration.h"

//
//  Type
//
#include "Type.h"
#include "IllegalType.h"

#endif
