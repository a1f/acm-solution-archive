#pragma once

#include "main.h"
// #include "test.h"
#include "rand.h"
#include "test_util.h"
#include "checker.h"
#include "input.h"
#include "output.h"

Random rnd;

const int ITERS = 1000;

void stressSolve(istream& inStream, ostream& outStream) {
    Input in(inStream);
    Output out(outStream);
    auto n = in.ni();
    auto m = in.ni();
    auto q = in.ni();
    vec2d<int> ginit;
    FOR(i, m) {
        auto x = in.ni() - 1;
        auto y = in.ni() - 1;
        auto c = in.ni();
        ginit.push_back({x, y, c});
    }
    sort(all(ginit), [&](const vec<int>& v1, const vec<int>& v2) -> bool {
        return v1[2] < v2[2];
    });
    FOR(i, q) {
        auto a = in.ni() - 1;
        auto b = in.ni() - 1;
        Graph ng;
        auto ns = ng.addNodes(n);

        function<void(int, vec<bool>&)> dfs = [&] (int v, vec<bool>& mark) {
            mark[v] = true;
            for (auto a : ng.outArcs(ns[v])) {
                auto to = ng.to(a);
                if (!mark[to.id]) {
                    dfs(to.id, mark);
                }
            }
        };

        int resa = -1, resb = -1;
        FOR(j, m) {
            ng.addEdge(ns[ginit[j][0]], ns[ginit[j][1]]);
            if (j < m - 1 && ginit[j][2] == ginit[j+1][2]) {
                continue;
            }
            vec<bool> mark(n);
            dfs(a, mark);
            if (mark[b]) {
                resa = ginit[j][2];
                resb = 0;
                FOR(k, n) {
                    if (mark[k]) {
                        ++resb;
                    }
                }
                break;
            }
        }
        out(resa, resb);
    }

}

void getInput(ostream& outStream) {
    Output out(outStream);
    auto n = rnd.next(2, 6);
    auto g = rnd.genGraph(n);
    auto m = g.size();
    auto qq = rnd.next(1, n);
    out(n, m, qq);
    for (int i = 0; i < g.size(); ++i) {
        auto a = g[i].first + 1;
        auto b = g[i].second + 1;
        auto c = rnd.next(1, 5);
        out(a, b, c);
    }
    FOR(i, qq) {
        auto a = rnd.next(1, n-1);
        auto b = rnd.next(a + 1, n);
        out(a, b);
    }
}

int main() {
  // rnd.seed(3731);
  for (int testId = 1; testId <= ITERS; ++testId) {
    ostringstream outInput;
    getInput(outInput);
    if (!testutil::compareSolutions(stressSolve, solve, checker, outInput.str())) {
      break;
    }
  }
  cout << "All tests passed!\n";
  return 0;
}
