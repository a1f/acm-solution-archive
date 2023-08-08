#pragma once

#include "main.h"
// #include "test.h"
#include "rand.h"
#include "test_util.h"
#include "checker.h"
#include "input.h"
#include "output.h"

Random rnd;

const int ITERS = 10;

void stressSolve(istream& inStream, ostream& outStream) {
    Input in(inStream);
    Output out(outStream);
}

void getInput(ostream& outStream) {
    Output out(outStream);
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
