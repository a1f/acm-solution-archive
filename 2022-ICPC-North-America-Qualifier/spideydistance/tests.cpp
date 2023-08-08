#include "main.h"
#include "test_util.h"
#include "checker.h"

using namespace std;
using namespace testutil;

const string TEST_FILE = "/Users/alexfetisov/acm/alf/_/spideydistance/tests";

int main(int argc, char* argv[]) {
  auto testData = testReader(TEST_FILE);
  if (argc > 1) {
    // Override test to run if we run from python script
    testData.testToRun = atoi(argv[1]);
  }
  vec<pair<string, int>> summary;
  for (int testId = 1; testId <= testData.tests.size(); ++testId) {
    if (testData.testToRun != -1) {
      if (testData.testToRun != testId) {
        continue;
      }
    }
    auto res = test(testId, testData.tests[testId-1].first, testData.tests[testId-1].second, solve, checker);
    if (!res.empty()) {
      summary.push_back({"Test #" + to_string(testId) + ": " + res, res == "Accepted" ? 0 : 1});
    }
  }

  FOR(i, summary.size()) {
    if (summary[i].second) {
      cout << RED << summary[i].first << "\n";
    } else {
      cout << GREEN << summary[i].first << "\n";
    }
  }
  return 0;
}
