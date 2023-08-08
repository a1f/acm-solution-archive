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
    auto a = in.nvi(n);
    sort(all(a));
    i64 sum = 0;
    int cnt = 0;
    i64 sumLeft = a.back();
    int cntLeft = 1;
    for (int i = (int)a.size() - 2; i >= 0; --i) {
        sum += a[i];
        ++cnt;
        if (sum >= sumLeft) {
            sumLeft += sum;
            cntLeft += cnt;
            sum = 0;
            cnt = 0;
        }
    }
    out(cntLeft);
}
