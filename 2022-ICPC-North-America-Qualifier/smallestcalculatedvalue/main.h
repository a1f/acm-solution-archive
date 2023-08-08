#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"

const int INF = numeric_limits<int>::max();

int evaluateOrFail2(int x, int y, int s) {
    if (s == 3) {
        if (x % y) {
            return INF;
        }
        return x / y;
    }
    if (s == 0) {
        return x + y;
    }
    if (s == 1) {
        return x - y;
    }
    if (s == 2) {
        return x * y;
    }
    dbg("here2");
    throw 42;
}

int evaluateOrFail(const vec<int>& x, int s1, int s2) {
    if (s1 == 3) {
        if (x[0] % x[1]) {
            return INF;
        }
        return evaluateOrFail2(x[0] / x[1], x[2], s2);
    }
    if (s1 == 2) {
        return evaluateOrFail2(x[0] * x[1], x[2], s2);
    }
    // if (s2 >= 2) {
    //     if (s2 == 3) {
    //         if (x[1] % x[2]) {
    //             return INF;
    //         }
    //         return evaluateOrFail2(x[0], x[1] / x[2], s1);
    //     } 
    //     return evaluateOrFail2(x[0], x[1] * x[2], s1);
    // }
    if (s1 == 0) {
        return evaluateOrFail2(x[0] + x[1], x[2], s2);
    }
    if (s1 == 1) {
        return evaluateOrFail2(x[0] - x[1], x[2], s2);
    }
    dbg("here");
    throw 42;
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto x = in.nvi(3);
    auto res = INF;
    evaluateOrFail(x, 1, 2);
    FOR(i, 4) {
        FOR(j, 4) {
            auto cres = evaluateOrFail(x, i, j);
            dbg(i, j, cres);
            if (cres >= 0) {
                res = min(res, cres);
            }
        }
    }
    out(res);
}
