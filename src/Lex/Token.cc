//===--- Token.cc ---------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>

using namespace C4;
using namespace Lex;


std::ostream & Lex::operator<<( std::ostream &out, TK tk )
{
  switch ( tk )
  {
    case TK::IDENTIFIER:      out << "identifier";      break;
    case TK::CONSTANT:        out << "constant";        break;
    case TK::STRING_LITERAL:  out << "string-literal";  break;
    case TK::END_OF_FILE:     out << "end-of-file";     break;

                              // Keywords
    case TK::Auto:            out << "auto";            break;
    case TK::Break:           out << "break";           break;
    case TK::Case:            out << "case";            break;
    case TK::Char:            out << "char";            break;
    case TK::Const:           out << "const";           break;
    case TK::Continue:        out << "continute";       break;
    case TK::Default:         out << "default";         break;
    case TK::Do:              out << "do";              break;
    case TK::Double:          out << "double";          break;
    case TK::Else:            out << "else";            break;
    case TK::Enum:            out << "enum";            break;
    case TK::Extern:          out << "extern";          break;
    case TK::Float:           out << "float";           break;
    case TK::For:             out << "for";             break;
    case TK::Goto:            out << "goto";            break;
    case TK::If:              out << "if";              break;
    case TK::Inline:          out << "inline";          break;
    case TK::Int:             out << "int";             break;
    case TK::Long:            out << "long";            break;
    case TK::Register:        out << "register";        break;
    case TK::Restrict:        out << "restrict";        break;
    case TK::Return:          out << "return";          break;
    case TK::Short:           out << "short";           break;
    case TK::Signed:          out << "signed";          break;
    case TK::Sizeof:          out << "sizeof";          break;
    case TK::Static:          out << "static";          break;
    case TK::Struct:          out << "struct";          break;
    case TK::Switch:          out << "switch";          break;
    case TK::Typedef:         out << "typedef";         break;
    case TK::Union:           out << "union";           break;
    case TK::Unsigned:        out << "unsigned";        break;
    case TK::Void:            out << "void";            break;
    case TK::Volatile:        out << "volatile";        break;
    case TK::While:           out << "while";           break;
    case TK::Alignas:         out << "_Alignas";        break;
    case TK::Alignof:         out << "_Alignof";        break;
    case TK::Atomic:          out << "_Atomic";         break;
    case TK::Bool:            out << "_Bool";           break;
    case TK::Complex:         out << "_Complex";        break;
    case TK::Generic:         out << "_Generic";        break;
    case TK::Imaginary:       out << "_Imaginary";      break;
    case TK::Noreturn:        out << "_Noreturn";       break;
    case TK::Static_assert:   out << "_Static_assert";  break;
    case TK::Thread_local:    out << "_Thread_local";   break;

                              // Punctuators
    case TK::LBracket:        out << "[";               break;
    case TK::RBracket:        out << "]";               break;
    case TK::LPar:            out << "(";               break;
    case TK::RPar:            out << ")";               break;
    case TK::LBrace:          out << "{";               break;
    case TK::RBrace:          out << "}";               break;
    case TK::Dot:             out << ".";               break;
    case TK::PtrOp:           out << "->";              break;
    case TK::IncOp:           out << "++";              break;
    case TK::DecOp:           out << "--";              break;
    case TK::And:             out << "&";               break;
    case TK::Mul:             out << "*";               break;
    case TK::Plus:            out << "+";               break;
    case TK::Minus:           out << "-";               break;
    case TK::Neg:             out << "~";               break;
    case TK::Not:             out << "!";               break;
    case TK::Div:             out << "/";               break;
    case TK::Mod:             out << "%";               break;
    case TK::LShift:          out << "<<";              break;
    case TK::RShift:          out << ">>";              break;
    case TK::Le:              out << "<";               break;
    case TK::Gr:              out << ">";               break;
    case TK::LEq:             out << "<=";              break;
    case TK::GEq:             out << ">=";              break;
    case TK::Eq:              out << "==";              break;
    case TK::NE:              out << "!=";              break;
    case TK::Xor:             out << "^";               break;
    case TK::Or:              out << "|";               break;
    case TK::LAnd:            out << "&&";              break;
    case TK::LOr:             out << "||";              break;
    case TK::QMark:           out << "?";               break;
    case TK::Col:             out << ":";               break;
    case TK::SCol:            out << ";";               break;
    case TK::Ellipsis:        out << "...";             break;
    case TK::Assign:          out << "=";               break;
    case TK::MulAssign:       out << "*=";              break;
    case TK::DivAssign:       out << "/=";              break;
    case TK::ModAssign:       out << "%=";              break;
    case TK::AddAssign:       out << "+=";              break;
    case TK::SubAssign:       out << "-=";              break;
    case TK::LShiftAssign:    out << "<<=";             break;
    case TK::RShiftAssign:    out << ">>=";             break;
    case TK::AndAssign:       out << "&=";              break;
    case TK::XorAssign:       out << "^=";              break;
    case TK::OrAssign:        out << "|=";              break;
    case TK::Comma:           out << ",";               break;
    case TK::Hash:            out << "#";               break;
    case TK::DHash:           out << "##";              break;

    default: out << "unknown token-kind";
  }
  return out;
}

std::unordered_map< Symbol, TK > Token::KeywordsTable;

void Token::INIT_KEYWORDS_TABLE()
{
  Token::KeywordsTable[ Symbol( "auto" ) ]            = TK::Auto;
  Token::KeywordsTable[ Symbol( "break" ) ]           = TK::Break;
  Token::KeywordsTable[ Symbol( "case" ) ]            = TK::Case;
  Token::KeywordsTable[ Symbol( "char" ) ]            = TK::Char;
  Token::KeywordsTable[ Symbol( "const" ) ]           = TK::Const;
  Token::KeywordsTable[ Symbol( "continue" ) ]        = TK::Continue;
  Token::KeywordsTable[ Symbol( "default" ) ]         = TK::Default;
  Token::KeywordsTable[ Symbol( "do" ) ]              = TK::Do;
  Token::KeywordsTable[ Symbol( "double" ) ]          = TK::Double;
  Token::KeywordsTable[ Symbol( "else" ) ]            = TK::Else;
  Token::KeywordsTable[ Symbol( "enum" ) ]            = TK::Enum;
  Token::KeywordsTable[ Symbol( "extern" ) ]          = TK::Extern;
  Token::KeywordsTable[ Symbol( "float" ) ]           = TK::Float;
  Token::KeywordsTable[ Symbol( "for" ) ]             = TK::For;
  Token::KeywordsTable[ Symbol( "goto" ) ]            = TK::Goto;
  Token::KeywordsTable[ Symbol( "if" ) ]              = TK::If;
  Token::KeywordsTable[ Symbol( "inline" ) ]          = TK::Inline;
  Token::KeywordsTable[ Symbol( "int" ) ]             = TK::Int;
  Token::KeywordsTable[ Symbol( "long" ) ]            = TK::Long;
  Token::KeywordsTable[ Symbol( "register" ) ]        = TK::Register;
  Token::KeywordsTable[ Symbol( "restrict" ) ]        = TK::Restrict;
  Token::KeywordsTable[ Symbol( "return" ) ]          = TK::Return;
  Token::KeywordsTable[ Symbol( "short" ) ]           = TK::Short;
  Token::KeywordsTable[ Symbol( "signed" ) ]          = TK::Signed;
  Token::KeywordsTable[ Symbol( "sizeof" ) ]          = TK::Sizeof;
  Token::KeywordsTable[ Symbol( "static" ) ]          = TK::Static;
  Token::KeywordsTable[ Symbol( "struct" ) ]          = TK::Struct;
  Token::KeywordsTable[ Symbol( "switch" ) ]          = TK::Switch;
  Token::KeywordsTable[ Symbol( "typedef" ) ]         = TK::Typedef;
  Token::KeywordsTable[ Symbol( "union" ) ]           = TK::Union;
  Token::KeywordsTable[ Symbol( "unsigned" ) ]        = TK::Unsigned;
  Token::KeywordsTable[ Symbol( "void" ) ]            = TK::Void;
  Token::KeywordsTable[ Symbol( "volatile" ) ]        = TK::Volatile;
  Token::KeywordsTable[ Symbol( "while" ) ]           = TK::While;
  Token::KeywordsTable[ Symbol( "_Alignas" ) ]        = TK::Alignas;
  Token::KeywordsTable[ Symbol( "_Alignof" ) ]        = TK::Alignof;
  Token::KeywordsTable[ Symbol( "_Atomic" ) ]         = TK::Atomic;
  Token::KeywordsTable[ Symbol( "_Bool" ) ]           = TK::Bool;
  Token::KeywordsTable[ Symbol( "_Complex" ) ]        = TK::Complex;
  Token::KeywordsTable[ Symbol( "_Generic" ) ]        = TK::Generic;
  Token::KeywordsTable[ Symbol( "_Imaginary" ) ]      = TK::Imaginary;
  Token::KeywordsTable[ Symbol( "_Noreturn" ) ]       = TK::Noreturn;
  Token::KeywordsTable[ Symbol( "_Static_assert" ) ]  = TK::Static_assert;
  Token::KeywordsTable[ Symbol( "_Thread_local" ) ]   = TK::Thread_local;
}

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  switch ( tok.kind )
  {
    case TK::IDENTIFIER:      out << "identifier"; break;
    case TK::CONSTANT:        out << "constant"; break;
    case TK::STRING_LITERAL:  out << "string-literal"; break;
    case TK::END_OF_FILE:     out << "end-of-file"; return out;

    default:
      if ( tok.isKeyword() )
        out << "keyword";
      else
        out << "punctuator";
  }
  out << " " << tok.sym;
  return out;
}

std::ostream & Lex::operator<<( std::ostream &out, Token const * const tok )
{
  switch ( tok->kind )
  {
    case TK::IDENTIFIER:      out << "identifier"; break;
    case TK::CONSTANT:        out << "constant"; break;
    case TK::STRING_LITERAL:  out << "string-literal"; break;
    case TK::END_OF_FILE:     out << "end-of-file"; return out;

    default:
      if ( tok->isKeyword() )
        out << "keyword";
      else
        out << "punctuator";
  }
  out << " " << tok->sym;
  return out;
}

void Token::dump() const
{
  std::cout << this << std::endl;
}
