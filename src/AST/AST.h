//===--- AST.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_AST_H
#define C4_AST_H

#include "Expr.h"

//
//  Statement
//
#include "Stmt.h"
#include "IllegalStmt.h"
#include "IfStmt.h"

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
