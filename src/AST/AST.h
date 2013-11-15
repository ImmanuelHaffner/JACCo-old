//===--- AST.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_AST_H
#define C4_AST_H

#include <vector>
#include <iostream>
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    enum class ASTType
    {
      // the ILLEGAL type for ASTs where parsing failed
      ILLEGAL,

      IDENTIFIER,
      CONSTANT,
      STRING_LITERAL,

      PRIMARY_EXPRESSION,
      POSTFIX_EXPRESSION,
      ARGUMENT_EXPRESSION_LIST,
      UNARY_EXPRESSION,
      UNARY_OPERATOR,
      CAST_EXPRESSION,
      MULTIPLICATIVE_EXPRESSION,
      ADDITIVE_EXPRESSION,
      SHIFT_EXPRESSION,
      RELATIONAL_EXPRESSION,
      EQUALITY_EXPRESSION,
      AND_EXPRESSION,
      EXCLUSIVE_OR_EXPRESSION,
      INCLUSIVE_OR_EXPRESSION,
      LOGICAL_AND_EXPRESSION,
      LOGICAL_OR_EXPRESSION,
      CONDITIONAL_EXPRESSION,
      ASSIGNMENT_EXPRESSION,
      ASSIGNMENT_OPERATOR,
      EXPRESSION,
      CONSTANT_EXPRESSION,
      DECLARATION,
      DECLARATION_SPECIFIERS,
      INIT_DECLARATOR_LIST,
      INIT_DECLARATOR,
      STORAGE_CLASS_SPECIFIER,
      TYPE_SPECIFIER,
      STRUCT_OR_UNION_SPECIFIER,
      STRUCT_OR_UNION,
      STRCUT_DECLARATION_LIST,
      STRUCT_DECLARATION,
      SPECIFIER_QUALIFIER_LIST,
      STRUCT_DECLARATOR_LIST,
      STRUCT_DECLARATOR,
      ENUM_SPECIFIER,
      ENUMERATOR_LIST,
      ENUMERATOR,
      TYPE_QUALIFIER,
      DECLARATOR,
      DIRECT_DECLARATOR,
      POINTER,
      TYPE_QUALIFIER_LIST,
      PARAMETER_TYPE_LIST,
      PARAMETER_LIST,
      PARAMETER_DECLARATION,
      IDENTIFIER_LIST,
      TYPE_NAME,
      ABSTRACT_DECLARATOR,
      DIRECT_ABSTRACT_DECLARATOR,
      INITIALIZER,
      INITIALIZER_LIST,
      STATEMENT,
      LABELED_STATEMENT,
      COMPOUND_STATEMENT,
      DECLARATION_LIST,
      STATEMENT_LIST,
      EXPRESSION_STATEMENT,
      SELECTION_STATEMENT,
      ITERATION_STATEMENT,
      JUMP_STATEMENT,
      TRANSLATION_UNIT,
      EXTERNAL_DECLARATION,
      FUNCTION_DEFINITION
    };

    ///
    struct ASTNode
    {
      ASTNode( ASTType type, ASTNode * const parent = NULL );
      virtual ~ASTNode();

      ASTNode * getParent() const;
      void setParent( ASTNode * const p );
      ASTNode * getChild( int n ) const;
      void setChild( ASTNode * const c, int n );
      void append( ASTNode * const c );
      void append( ASTNode &c );
      ASTNode * operator[]( int n );
      std::vector< ASTNode * >::iterator begin();
      std::vector< ASTNode * >::const_iterator begin() const;
      std::vector< ASTNode * >::iterator end();
      std::vector< ASTNode * >::const_iterator end() const;

      friend std::ostream & operator<<( std::ostream &out,
          ASTNode const &node );
      virtual void dump( std::ostream &out = std::cout, int const n = 0 ) const;


      ASTType const type;

      private:
      ASTNode * parent;
      std::vector< ASTNode * > childs;
    };

    std::ostream & operator<<( std::ostream &out, ASTNode const &node );
  } // end namespace AST
} // end namespace C4

#endif
