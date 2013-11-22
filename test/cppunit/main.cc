//===--- main.cc ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include <iostream>

#include "../../src/Lex/Token.h"

int main()
{
	std::cout << "Start Unit Tests:" << std::endl;

  C4::Lex::Token::INIT_KEYWORDS_TABLE();

	// informs the test listener about test results
	CPPUNIT_NS :: TestResult TestResult;

	// registers the listener for collecting test results
	CPPUNIT_NS :: TestResultCollector CollectedResults;
	TestResult.addListener (&CollectedResults);

	// listener for output of results of single tests
	CPPUNIT_NS :: BriefTestProgressListener progress;
	TestResult.addListener (&progress);

	// insert test suite via registry into test runner
	CPPUNIT_NS :: TestRunner TestRunner;
	TestRunner.addTest (CPPUNIT_NS :: TestFactoryRegistry :: getRegistry ().makeTest ());
	TestRunner.run (TestResult);

	// print results in compiler format
	CPPUNIT_NS :: CompilerOutputter compileroutputter (&CollectedResults, std::cerr);
	compileroutputter.write ();

	// return whether tests succeeded
	return CollectedResults.wasSuccessful () ? 0 : 1;
}
