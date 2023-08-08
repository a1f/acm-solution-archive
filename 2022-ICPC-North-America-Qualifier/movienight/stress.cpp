#pragma once

#include "main.h"
// #include "test.h"
#include "rand.h"
#include "test_util.h"
#include "checker.h"
#include "input.h"
#include "output.h"
#include "bit_util.h"

Random rnd;

const int ITERS = 1000;

void stressSolve(istream& inStream, ostream& outStream) {
    Input in(inStream);
    Output out(outStream);
    auto n = in.ni();
    vec<int> p = in.nvi(n);
    subOne(p);
    int res = 0;
    FOR(mask, 1 << n) if (mask) {
        auto ok = true;
        FOR(i, n) {
            if (getBit(mask, i)) {
                if (!getBit(mask, p[i])) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            ++res;
        }
    }
    out(res);
}

void getInput(ostream& outStream) {
    Output out(outStream);
    auto n = rnd.next(2, 8);
    out(n);
    FOR(i, n) {
        while (true) {
            auto x = rnd.next(1, n);
            if (x == i + 1) continue;
            out(x);
            break;
        }
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
