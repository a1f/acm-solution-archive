#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"
#include "nt/nt.h"


int getMaxForTaxi(int x, int t) {
    int y = t - x;
    return max(-1, y);
}

bool debug;

int getMaxForSpidy(int x, int s) {
//    if (debug) {
//        int bestY = 0;
//        FOR(i, x + 1) {
//            int cst = (i * 3 + 1) / 2;
//            int ss = s - cst;
//            int nx = x - i;
//            ss -= nx;
//            int cy = i;
//            if (ss < 0) continue;
//            cy += ss;
//            bestY = max(bestY, cy);
//        }
//        dbg("x = ", x, "y=", bestY);
//        return bestY;
//    }
    if (s * 2 >= 3 * x) {
        s -= (3 * x) / 2;
        int cy = x;
        if (x % 2 == 1) {
            --s;
        }
        cy += s;
        dbg("x=", x, "v1 y:", cy);
        return cy;
    } else {
        int v = (s - x) * 2;
        dbg("x=", x, "v2 y:", v);

        return max(-1, v);
    }
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);

    debug = true;
    auto t = in.ni();
    auto s = in.ni();

    int maxX = max(t, s);
    i64 sumSpidy = 0;
    i64 sumTaxy = 0;
    for (int i = 1; i <= maxX; ++i) {
        int yt = getMaxForTaxi(i, t) + 1;
        int ys = getMaxForSpidy(i, s) + 1;
//        dbg("->", i, yt);
        yt = min(yt, ys);
        sumSpidy += ys;
        sumTaxy += yt;
    }
    sumSpidy *= 4;
    sumTaxy *= 4;
    ++sumSpidy;
    ++sumTaxy;
    dbg(sumTaxy, sumSpidy);
    i64 g = gcd(sumSpidy, sumTaxy);
    sumSpidy /= g;
    sumTaxy /= g;
    if (sumSpidy == 1) {
        out(sumTaxy);
    } else {
        out << sumTaxy << "/" << sumSpidy << "\n";
    }

}
