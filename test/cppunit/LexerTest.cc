//===--- LexerTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerTest.h"

#include "../../src/Lex/Lexer.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( LexerTest );

using namespace C4;
using namespace Lex;

void LexerTest::setUp()
{
}

void LexerTest::tearDown()
{
}


void LexerTest::testConstructor()
{
  char const * const fileName = "resource/allowedCharacters.c";

  Lexer lexer( fileName );

  // check file name
  CPPUNIT_ASSERT( lexer.fileName.compare( fileName ) == 0 );

  // check pos
  CPPUNIT_ASSERT( strcmp( fileName, lexer.getPos().name ) == 0 );
  CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
  CPPUNIT_ASSERT_EQUAL( 0u, lexer.getPos().column );

  Lexer lexer2;
  // check file name
  CPPUNIT_ASSERT( lexer2.fileName.compare( "<stdin>" ) == 0 );

  // check pos
  CPPUNIT_ASSERT_EQUAL( 1u, lexer2.getPos().line );
  CPPUNIT_ASSERT_EQUAL( 0u, lexer2.getPos().column );
}

void LexerTest::testEof()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 0u, token.pos.column );
  }

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 0u, token.pos.column );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testEolStyles()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "a\nb\rc\r\nd" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // a
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "a" ) == 0 );
  }

  // b
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "b" ) == 0 );
  }

  // c
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "c" ) == 0 );
  }

  // d
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "d" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n/*\n\r\r\n*/a" );
  std::cin.rdbuf( stream.rdbuf() );


  // a
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "a" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadKeywords()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "auto break\nconst \n int\r\ncontinue while for" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // auto
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "auto" ) == 0 );
  }

  // break
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "break" ) == 0);
  }

  // const
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "const" ) == 0);
  }

  // int
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "int" ) == 0);
  }

  // continue
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "continue" ) == 0);
  }

  // while
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 10u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "while" ) == 0);
  }

  // for
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::KEYWORD );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 16u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "for" ) == 0);
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadIdentifier()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "a b\nc \n d\r\ne f1 _f2" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  // a
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "a" ) == 0 );
  }

  // b
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "b" ) == 0 );
  }

  // c
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "c" ) == 0 );
  }

  // d
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "d" ) == 0 );
  }

  // e
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "e" ) == 0 );
  }

  // f1
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "f1" ) == 0 );
  }

  // _f2
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "_f2" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadDecimalConstant()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "1 23\n4 \n 5\r\n67 8 90" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // 1
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "1" ) == 0 );
  }

  // 23
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "23" ) == 0 );
  }

  // 4
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "4" ) == 0 );
  }

  // 5
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "5" ) == 0 );
  }

  // 67
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "67" ) == 0 );
  }

  // 8
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "8" ) == 0 );
  }

  // 90
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "90" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadNumericalAndIdentifier()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "12a 1_" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // 12
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "12" ) == 0 );
  }

  // a
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "a" ) == 0 );
  }

  // 1
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "1" ) == 0 );
  }

  // _
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "_" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadCharacterConstant()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "'a' 'b'\n'c' \n 'd'\r\n'e' '\\n' '\\\\'" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // a
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'a'" ) == 0 );
  }

  // b
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'b'" ) == 0 );
  }

  // c
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'c'" ) == 0 );
  }

  // d
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'d'" ) == 0 );
  }

  // e
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'e'" ) == 0 );
  }

  // \n
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'\\n'" ) == 0 );
  }

  // \\ (sym.str() to avoid two-line comment)
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 10u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "'\\\\'" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadStringLiteral()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "\"a\" \n \"bc\"\r\n\"d e \" \"\\n bla\"" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // "a"
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::STRING_LITERAL );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "\"a\"" ) == 0 );
  }

  // "bc"
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::STRING_LITERAL );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "\"bc\"" ) == 0 );
  }

  // "d e "
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::STRING_LITERAL );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "\"d e \"" ) == 0 );
  }

  // "\n bla"
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::STRING_LITERAL );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "\"\\n bla\"" ) == 0 );
  }


  stream.str( "\n\"\"" );
  std::cin.rdbuf( stream.rdbuf() );


  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::STRING_LITERAL );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "\"\"" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuator()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "[->>>=....|||--=" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // [
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBracket );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "[" ) == 0 );
  }

  // .
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::PtrOp );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "->" ) == 0 );
  }

  // >>=
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::RShiftAssign );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ">>=" ) == 0 );
  }

  // ...
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Ellipsis );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "..." ) == 0 );
  }

  // .
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Dot );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 10u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "." ) == 0 );
  }

  // ||
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LOr );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 11u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "||" ) == 0 );
  }

  // |
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Or );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 13u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "|" ) == 0 );
  }

  // --
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::DecOp );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 14u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "--" ) == 0 );
  }

  // =
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Assign );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 16u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "=" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDigraph()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "<::><%%>%: %:%:" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );



  // <:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBracket );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<:" ) == 0 );
  }

  // :>
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::RBracket );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ":>" ) == 0 );
  }

  // <%
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBrace );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<%" ) == 0 );
  }

  // %>
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::RBrace );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%>" ) == 0 );
  }

  // %:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Hash );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 9u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%:" ) == 0 );
  }

  // %:%:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::DHash );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 12u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%:%:" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDots()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "........" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // ...
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Ellipsis );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "..." ) == 0 );
  }

  // ...
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Ellipsis );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "..." ) == 0 );
  }

  // .
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Dot );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "." ) == 0 );
  }

  // .
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Dot );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "." ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDigraphAmbiguity()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "<:>" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // <:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBracket );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<:" ) == 0 );
  }

  // >
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Gr );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ">" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n<%>" );
  std::cin.rdbuf( stream.rdbuf() );

  // <%
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBrace );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<%" ) == 0 );
  }

  // >
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Gr );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ">" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n%:%:%:%" );
  std::cin.rdbuf( stream.rdbuf() );

  // %:%:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::DHash );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%:%:" ) == 0 );
  }

  // %:
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Hash );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%:" ) == 0 );
  }

  // %
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Mod );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "%" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n<%:>" );
  std::cin.rdbuf( stream.rdbuf() );

  // <%
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LBrace );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<%" ) == 0 );
  }

  // :>
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::RBracket );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ":>" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n<<::>>" );
  std::cin.rdbuf( stream.rdbuf() );

  // <<
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::LShift );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<<" ) == 0 );
  }

  // :
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Col );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ":" ) == 0 );
  }

  // :>
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::RBracket );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ":>" ) == 0 );
  }

  // >
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::Gr );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), ">" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testComments()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "//" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
  }


  // redirect stdin
  stream.str( "\n//\\\n" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 0u, token.pos.column );
  }


  // redirect stdin
  stream.str( "\n/**/" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
  }


  // redirect stdin
  stream.str( "\n/*\n\\\n*/" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
  }


  // redirect stdin
  stream.str( "\n//*" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
  }


  // redirect stdin
  stream.str( "\n///*" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 9u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadCommentAsWhitespace()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "abc/**/def" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // abc
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "abc" ) == 0 );
  }

  // def
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "def" ) == 0 );
  }


  // redirect stdin
  stream.str( "\nau/**/to" );
  std::cin.rdbuf( stream.rdbuf() );


  // au
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "au" ) == 0 );
  }

  // to
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "to" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n123/**/456" );
  std::cin.rdbuf( stream.rdbuf() );


  // 123
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "123" ) == 0 );
  }

  // 456
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "456" ) == 0 );
  }


  // redirect stdin
  stream.str( "\n</**/<=" );
  std::cin.rdbuf( stream.rdbuf() );


  // <
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::Le );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<" ) == 0 );
  }

  // <=
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::LEq );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( strcmp( token.sym.str(), "<=" ) == 0 );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
