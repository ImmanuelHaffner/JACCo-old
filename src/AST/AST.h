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
#include "PostfixExpr.h"
#include "UnaryExpr.h"
#include "BinaryExpr.h"

//
//  Statement
//
#include "Statement.h"
#include "IllegalStatement.h"

//
//  Declaration
//
#include "Declaration.h"
#include "IllegalDeclaration.h"

//
//  Type
//
#include "Type.h"

#endif
