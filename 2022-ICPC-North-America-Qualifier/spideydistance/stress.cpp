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
int delta;

void dfs1(int x, int y, vec2d<bool>& u, int t) {
    if (x + delta < 0 || y + delta < 0 || x + delta >= u.size() || y + delta > u[0].size()) {
        return;
    }
    if (t < 0) {
        return;
    }
    u[x + delta][y + delta] = true;
    dfs1(x + 1, y, u, t - 1);
    dfs1(x - 1, y, u, t - 1);
    dfs1(x, y + 1, u, t - 1);
    dfs1(x, y - 1, u, t - 1);
}

void dfs2(int x, int y, vec2d<bool>& u, int t) {
    if (x + delta < 0 || y + delta < 0 || x + delta >= u.size() || y + delta > u[0].size()) {
        return;
    }
    if (t < 0) {
        return;
    }
    u[x + delta][y + delta] = true;
    dfs2(x + 1, y, u, t - 2);
    dfs2(x - 1, y, u, t - 2);
    dfs2(x, y + 1, u, t - 2);
    dfs2(x, y - 1, u, t - 2);

    dfs2(x + 1, y + 1, u, t - 3);
    dfs2(x - 1, y + 1, u, t - 3);
    dfs2(x + 1, y - 1, u, t - 3);
    dfs2(x - 1, y - 1, u, t - 3);
}

void stressSolve(istream& inStream, ostream& outStream) {
    Input in(inStream);
    Output out(outStream);
    auto t = in.ni();
    auto s = in.ni();
    delta = max(t, s) + 2;
    vec2d<bool> u = makeVec2d<bool>(2 * delta + 1, 2 * delta + 1, false);
    dfs1(0, 0, u, t);
    int sumT = 0, sumS = 0;
    auto u2 = makeVec2d<bool>(2 * delta + 1, 2 * delta + 1, false);
    dfs2(0, 0, u2, 2 * s);
    vec<str> f1(u.size());
    vec<str> f2(u.size());
    vec<str> f(u.size());
    FR(i, -delta, delta) {
        FR(j, -delta, delta) {
            int x = i + delta;
            int y = j + delta;
            char c = '.';
            if (!u[x][y]) {
                f1[x].push_back('.');
            } else {
                c = 't';
                f1[x].push_back('T');
            }
            if (!u2[x][y]) {
                f[x].push_back(c);
                f2[x].push_back('.');
                continue;
            }
            if (c == 't') {
                c = 'X';
            } else {
                c = 's';
            }
            f[x].push_back(c);
            f2[x].push_back('X');
            if (u[x][y]) {
                ++sumT;
            }
            ++sumS;
        }
    }

    dbg("taxi");
    FOR(i, f1.size()) {
        dbg(f1[i]);
    }
    dbg("spider");
    FOR(i, f2.size()) {
        dbg(f2[i]);
    }
    dbg("both");
    FOR(i, f.size()) {
        dbg(f[i]);
    }
    int g = gcd(sumT, sumS);
    sumT /= g;
    sumS /= g;
    if (sumS == 1) {
        out(sumT);
    } else {
        out << sumT << "/" << sumS << "\n";
    }
}

void getInput(ostream& outStream) {
    Output out(outStream);
    auto t = rnd.next(0, 10);
    auto s = rnd.next(0, 10);
    out(t, s);
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
