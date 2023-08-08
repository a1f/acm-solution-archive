#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto s1 = in.ns();
    auto s2 = in.ns();
    s1 += s2;
    sort(all(s1));
    out(s1);
}
