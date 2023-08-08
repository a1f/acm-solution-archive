#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"
#include "nt/nt.h"
#include "nt/mod_new.h"
#include "dsu.h"

using md = md10;

enum VColor {
    UNKNOWN = -1,
    CYCLE = 0,
    TAIL = 1,
    MARK = 2,
};

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    vec<int> p(n);
    dsu::DSU disjointSet(n);
    vec2d<int> g(n);

    FOR(i, n) {
        auto x = in.ni() - 1;
        p[i] = x;
        g[x].push_back(i);
        disjointSet.unite(i, x);
    }
    vec<int> color(n, VColor::UNKNOWN);
    int countCycles = 0;
    vec<int> parent(n, -1);
    
    auto traverseAndMark = [&] (int v) -> int {
        color[v] = VColor::MARK;
        int pv = v;
        v = p[v];
        while (true) {
            if (color[v] == VColor::TAIL || color[v] == VColor::CYCLE) {
                v = pv;
                while (v != -1) {
                    color[v] = VColor::TAIL;
                    v = parent[v];
                }
                return 0;
            } else if (color[v] == VColor::UNKNOWN) {
                color[v] = VColor::MARK;
                parent[v] = pv;
                pv = v;
                v = p[v];
            } else if (color[v] == VColor::MARK) {
                // found cycle started from v
                while (pv != v) {
                    color[pv] = VColor::CYCLE;
                    pv = parent[pv];
                }
                color[v] = VColor::CYCLE;
                v = parent[v];
                while (v != -1) {
                    color[v] = VColor::TAIL;
                    v = parent[v];
                }
                return 1;
            } else {
                throw 42;
            }
        }
    };

    dbg("traverse");
    FOR(i, n) {
        if (color[i] == VColor::UNKNOWN) {
            countCycles += traverseAndMark(i);
        }
    }
    
    vec<md> dp(n), value(n, 1);

    function<void(int, int)> dfs = [&] (int v, int p) {
        dp[v] = 1;
        for (auto to : g[v]) {
            if (to == p) continue;
            if (color[to] == VColor::CYCLE) {
                continue;
            }
            dfs(to, v);
            dp[v] *= (dp[to] + 1);
        }
    };

    set<int> resValues;
    FOR(i, n) {
        if (color[i] == VColor::CYCLE) {
            auto val = disjointSet.findSet(i);
            resValues.insert(val);
            dfs(i, -1);
            value[val] *= dp[i];
        }
    }
    md result = 1;
    for (auto i : resValues) {
        result *= (value[i] + 1);
    }
    result -= 1;
    out(result);
}
