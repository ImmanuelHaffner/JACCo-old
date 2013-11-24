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
#include "Expression.h"
#include "IllegalExpression.h"
#include "Variable.h"
#include "Constant.h"
#include "StringLiteral.h"
#include "PostfixExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

//
//  Statement
//
#include "Statement.h"

//
//  Declaration
//
#include "Declaration.h"

//
//  Type
//
#include "Type.h"

#endif
