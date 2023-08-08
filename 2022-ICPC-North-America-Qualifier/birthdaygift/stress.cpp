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
    auto a = in.ni();
    auto r = in.ni();
    auto res = stupidSolve(a, r);
    out(res);
}

void getInput(ostream& outStream) {
    Output out(outStream);
    auto age = rnd.next(1, 20);
    auto reminder = rnd.next(0, 224);
    out(age, reminder);
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
