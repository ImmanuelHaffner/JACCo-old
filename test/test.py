from os import listdir
from os.path import isdir, splitext, split
from subprocess import check_output, CalledProcessError
from itertools import count



verbose = False
stopOnFailure = False


class Test:
    def __init__(self, name):
        self.name = name
        self.cfile = self.name + ".c"
        expected = open(self.name + ".tok", "rt").readlines()
        self.expectedExitCode = int(expected[0])
        self.expectedLines = list(map(str.strip, expected[1:]))

    def runC4(self):
        try:
            out = check_output("../build/default/c4 --tokenize --haffner " + self.cfile, shell = True)
            ret = 0
        except CalledProcessError as e:
            out = e.output
            ret = e.returncode
        def processLine(l):
            l = l.strip()
            l = l.split(":", 1)
            l = split(l[0])[1] + ":" + l[1]
            return l
        return (ret, list(map(processLine, out.decode().splitlines())))

    def run(self):
        try:
            ret, out = self.runC4()
        except UnicodeDecodeError:
            return False
        if (verbose):
            print("Running test:", self.name)
        if (ret != self.expectedExitCode):
            if (verbose):
                print("Expected exit code %d, but got %d" % (self.expectedExitCode, ret))
            return False
        if (self.expectedExitCode == 0):
            passed = True
            for i, lg, le in zip(count(), out, self.expectedLines):
                if (lg != le):
                    if (verbose):
                        print("Line %d: Expected '%s', but got '%s'" % (i, le, lg))
                    passed = False
            return passed
        else:
            return True


def findTests(dir = "resource"):
    tests = []
    for file in listdir(dir):
        if (isdir(dir + "/" + file)):
            tests.extend(findTests(dir + "/" + file))
        else:
            name, ext = splitext(file)
            if (ext == ".c"):
                try:
                    tests.append(Test(dir + "/" + name))
                except UnicodeDecodeError:
                    pass
    return tests


tests = findTests()
passed = 0
numTests = len(tests)
for test in tests:
    if (test.run()):
        passed += 1
    else:
        print(test.name, "failed")
        if (stopOnFailure):
            break

    
print("Passed %d of %d tests" % (passed, numTests))
    
