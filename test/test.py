from os import listdir
from os.path import isdir, splitext, split, abspath
from subprocess import check_output, CalledProcessError
from itertools import count, chain
from optparse import OptionParser



class Test:
    def __init__(self, testFile, cFile, c4Path):
        self.name = testFile
        self.cFile = split(cFile)[1]
        self.cwd, self.testFile = split(testFile)
        expected = open(testFile, "rt").readlines()
        try:
            self.expectedExitCode = int(expected[0])
        except ValueError:
            raise SyntaxError("Invalid syntax in token-file: %s" % testFile)
        self.expectedLines = list(map(str.strip, expected[1:]))
        self.errors = []
        self.c4Path = abspath(c4Path)

    def runC4(self):
        try:
            out = check_output([self.c4Path] + self.c4Args + [self.cFile], cwd = self.cwd)
            ret = 0
        except CalledProcessError as e:
            out = e.output
            ret = e.returncode
        return (ret, out.decode().splitlines())

    def logError(self, msg):
        self.errors.append(msg)

    def printErrors(self):
        for err in self.errors:
            print("%s: %s" % (self.name, err))

    def __hash__(self):
        return hash(self.testFile)

    def __eq__(self, t):
        return self.testFile == t.testFile


class LexerTest(Test):
    c4Args = ["--tokenize"]

    def run(self):
        try:
            ret, out = self.runC4()
        except UnicodeDecodeError:
            return False
        if (ret != self.expectedExitCode):
            self.logError("Expected exit code %d, but got %d" % (self.expectedExitCode, ret))
            return False
        if (self.expectedExitCode == 0):
            passed = True
            for i, lg, le in zip(count(), out, self.expectedLines):
                if (lg != le):
                    self.logError("Line %d: Expected '%s', but got '%s'" % (i, le, lg))
                    passed = False
            return passed
        else:
            return True


class ParserTest:
    c4Args = ["--parser"]

    def run(self):
        return False # TODO: implement


cats = {
    ".tok": LexerTest,
    ".ast": ParserTest
}


def createTest(testFile, c4Path):
    dir, file = split(testFile)
    name, ext = splitext(file)
    cFile = "%s/%s.c" % (dir, name)
    return cats[ext](testFile, cFile, c4Path)


def findTests(exts, c4Path, dir = "resource"):
    for file in listdir(dir):
        if (isdir(dir + "/" + file)):
            for test in findTests(exts, c4Path, dir + "/" + file):
                yield test
        else:
            name, ext = splitext(file)
            if (ext in exts):
                try:
                    yield createTest(dir + "/" + file, c4Path)
                except UnicodeDecodeError:
                    pass


if (__name__ == "__main__"):
    # parse command line
    parser = OptionParser(usage = "Usage: %prog [OPTIONS] [TESTS]")
    parser.add_option("-t", "--test", dest = "test",
                      metavar = "TEST", default = "all",
                      help = "Run a specified test")
    parser.add_option("-c", "--c4", dest = "c4Path",
                      metavar = "COMPILER", default = "../build/default/c4",
                      help = "Specify the path to your compiler")
    parser.add_option("-n", "--max-errors", dest = "maxErrors",
                      metavar = "NUM", default = "20",
                      help = "Abort after NUM failed tests")
    parser.add_option("-o", "--html", dest = "html",
                      metavar = "FILE", default = None,
                      help = "Output results into HTML file")
    parser.add_option("-q", "--quiet", dest = "verbose", default = True,
                      action = "store_false",
                      help = "Print out more information")
    parser.add_option("-l", "--lexer", dest = "lexer", default = False,
                      action = "store_true",
                      help = "Run all lexer tests")
    parser.add_option("-p", "--parser", dest = "parser", default = False,
                      action = "store_true",
                      help = "Run all parser tests")
    (options, args) = parser.parse_args()
    c4Path = options.c4Path
    verbose = options.verbose
    maxErrors = int(options.maxErrors)
    exts = []
    catFlags = {
        "lexer": ".tok",
        "parser": ".ast"
    }
    for k, v in catFlags.items():
        if (getattr(options, k)):
            exts.append(v)
    if (args == [] and exts == []):
        # in this case run all tests
        exts = list(cats.keys())
    catTests = [] if (exts == []) else findTests(exts, c4Path)
    selectedTests = [createTest(path, c4Path) for path in args]
    tests = chain(selectedTests, catTests)

    results = {}
    passed = 0
    failed = 0
    numTests = 0
    for test in tests:
        if (test not in results):
            results[test] = res = test.run()
            numTests += 1
            if (res):
                passed += 1
            else:
                failed += 1
                print("Failed " + test.testFile)
                if (verbose):
                    test.printErrors()
                if (failed >= maxErrors):
                    break
    print("Passed %d of %d tests" % (passed, numTests))

    if (options.html != None):
        htmloutput.generate(results, options.html)
