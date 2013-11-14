
def readGrammar(f):
    rhs = None
    lhs = None
    rules = {}
    for l in f.readlines():
        l = l.strip()
        if (l.startswith(":") or l.startswith("|")):
            rhs.add(tuple(l[1:].split()))
        elif (l.startswith(";")):
            rules[lhs] = rhs
            lhs = rhs = None
        else:
            lhs = l
            rhs = set()
    return rules

def isTerminal(x):
    return not x.islower()

def firstk(G, k = 1):
    F = {}

    def concat(A, B):
        X = set()
        for a in A:
            if (len(a) < k):
                for b in B:
                    X.add((a + b)[:k])
            else:
                X.add(a[:k])
        return X

    def first(x):
        M = set()
        for rhs in G[x]:
            S = set([tuple()])
            for y in rhs:
                if (isTerminal(y)):
                    S = concat(S, set(((y,),)))
                else:
                    S = concat(S, F[y])
            M.update(S)
        return M

    for nt in G.keys():
        F[nt] = set()

    while (True):
        F_ = F.copy()
        for nt in F_:
            F_[nt] = first(nt)
        if (F == F_):
            break
        F = F_

    return F


    

if (__name__ == "__main__"):
    from optparse import OptionParser
    from sys import stdout

    parser = OptionParser(usage = "Usage: %prog [OPTIONS]")
    parser.add_option("-g", "--grammar", dest = "grammar",
                      metavar = "FILE", default = "grammar_stripped.txt",
                      help = "Select a specific grammar file.")
    parser.add_option("-k", dest = "k",
                      metavar = "NUMBER", default = "1",
                      help = "Specify k parameter.")
    parser.add_option("-o", "--output", dest = "output",
                      metavar = "FILE", default = "-",
                      help = "Write output to specified FILE.")
    (options, args) = parser.parse_args()

    k = int(options.k)
    f = open(options.grammar, "rt")
    grammar = readGrammar(f)
    f.close()

    F = firstk(grammar, k)

    if (options.output == "-"):
        o = stdout
    else:
        o = open(options.output, "wt")

    for nt, first in F.items():
        print(nt + ":", file = o)
        for f in sorted(first):
            print("\t", " ".join(f), file = o)
        print(file = o)

    if (o != stdout):
        o.close()
