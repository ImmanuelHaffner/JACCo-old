def readGrammar():
    f = open("ANSI_C_Grammar.txt", "rt")
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
    f.close()
    return rules

def isTerminal(x):
    return not x.islower()

def first_old(grammar, lhs):
    F = set()
    for rhs in grammar[lhs]:
        if (isTerminal(rhs[0])):
            F.add(rhs[0])
        elif (rhs[0] != lhs):
            F = F.union(first(grammar, rhs[0]))
    return F


        

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


    

grammar = readGrammar()

F = firstk(grammar, 2)

for nt, first in F.items():
    print(nt)
    for f in sorted(first):
        print("\t", f)
    print()
