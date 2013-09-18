#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "pos.h"

void errorf(Pos const&, char const* fmt, ...);

void errorf(char const* fmt, ...);

void errorErrno(Pos const& pos);

bool hasNewErrors();

int printDiagnosticSummary();

#endif
