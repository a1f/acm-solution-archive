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
    auto n = in.ni();
    auto m = in.ni();
    vec<int> p(n);
    FOR(i, n) {
        p[i] = i;
    }
    FOR(i, m) {
        auto x = in.ni() - 1;
        swap(p[x], p[x + 1]);
    }
    addOne(p);
    out(p);
}
