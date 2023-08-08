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
    auto minLen = in.ni64();
    auto maxLen = in.ni64();
    auto xs = in.nvi64(n);
    sort(all(xs));
    if (n == 1) {
        out(maxLen);
        return;
    }

    FOR(i, n) if (i) {
        if (xs[i] - xs[i-1] < minLen) {
            out(-1);
            return;
        }
    }
    FOR(i, n) {
        xs[i] *= 2;
    }
    const i64 INF = numeric_limits<i64>::max();

    auto extendOne = [&] (int i, vec<i64>& lens) -> void {
        i64 leftNeiDst = INF;
        i64 rightNeiDst = INF;
        if (i > 0) {
            leftNeiDst = (xs[i] - lens[i] / 2) - (xs[i-1] + lens[i-1] / 2);
        }
        if (i < n - 1) {
            rightNeiDst = (xs[i+1] - lens[i+1] / 2) - (xs[i] + lens[i] / 2);
        }
        i64 r = min(leftNeiDst, rightNeiDst);
        lens[i] += r * 2;
        lens[i] = min(lens[i], maxLen * 2);
    };

    vec<i64> lens(n, minLen * 2);
    FOR(i, n) {
        extendOne(i, lens);
    }
    i64 res = accumulate(all(lens), i64(0));
    out(res / 2);
}
