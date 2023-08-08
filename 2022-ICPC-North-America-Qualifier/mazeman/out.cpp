//#include "input.h"
//#include "output.h"
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")


#define NDEBUG
NDEBUG


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <queue>
#include <random>
#include <chrono>


using namespace std;

template<class T>
using vec = std::vector<T>;

template<class T>
using vec2d = std::vector<std::vector<T>>;


template<class T>
vec2d<T> makeVec2d(const int n1, const int n2, const T initValue) {
  return vec2d<T>(n1, vec<T>(n2, initValue));
}


#define FOR(i, n) for (int i = 0; i < (n); ++i)


#define all(c) c.begin(), c.end()


typedef string str;


// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END


// Section with adoption of array and vector algorithms.


//#include <ext/pb_ds/tree_policy.hpp>
//#include <ext/pb_ds/assoc_container.hpp>
//
//template <class T> using StdTree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;


//bool __hack = std::ios::sync_with_stdio(false);
//auto __hack1 = cin.tie(nullptr);

struct Input {

    Input(istream &in) : in(&in) {}

    template<class T>
    T next() const {
        T x;
        *in >> x;
        return x;
    }

    int ni() const {
        return next<int>();
    }

    
    istream *in;
};

Input in(cin);


class Output {

private:
ostream *out;

template<typename T>
void printSingle(const T &value) {
    *out << value;
}


public:
Output(ostream &out) : out(&out) {}


inline void print() {}

template<typename T, typename...Ts>
inline void print(const T &f, const Ts&... args) {
    printSingle(f);
    if (sizeof...(args) != 0) {
        *out << ' ';
        print(args...);
    }
}

template<typename...Ts>
inline void println(const Ts&... args) {
    print(args...);
    (*out) << '\n';
}

template<typename...Ts>
inline void operator() (const Ts&... args) {
    println(args...);
}


};

Output out(cout);


namespace template_util {
    

    constexpr int bytecount(uint64_t x) {
        return x ? 1 + bytecount(x >> 8) : 0;
    }

    template<int N>
    struct bytetype {
        
    };

    
    /// caide keep
    template<uint64_t N>
    struct minimal_uint : bytetype<bytecount(N)> {
    };
}


#define dbg(...) ;


void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    auto m = in.ni();
    vec<str> f(n);
    str s;
    getline(*in.in, s);
    FOR(i, n) {
        getline(*in.in, s);
        dbg(i, s);
        f[i] = s;
    }
    vec2d<bool> used = makeVec2d<bool>(n, m, false);
    vec2d<int> zones(30);
    int countDots = 0;
    bool foundLetters;
    set<int> letters;

    function<void(int, int, int)> dfs = [&] (int x, int y, int zoneId) {
        if (x < 0 || y < 0 || x >= n || y >= m) {
            return;
        }
        if (used[x][y]) return;
        used[x][y] = true;
        if (f[x][y] == 'X') {
            return;
        }
        if (f[x][y] == '.') {
            ++countDots;
        }
        if (isupper(f[x][y])) {
            zones[f[x][y] - 'A'].push_back(zoneId);
            letters.insert(f[x][y] - 'A');
            foundLetters = true;
            return;
        }
        dfs(x + 1, y, zoneId);
        dfs(x - 1, y, zoneId);
        dfs(x, y + 1, zoneId);
        dfs(x, y - 1, zoneId);
    };
    int zoneCount = 0;
    int notCoveredDots = 0;
    FOR(i, n) {
        FOR(j, m) {
            if (f[i][j] == '.') {
                if (!used[i][j]) {
                    countDots = 0;
                    foundLetters = false;
                    dfs(i, j, zoneCount);
                    if (!foundLetters) {
                        notCoveredDots += countDots;
                    } else {
                        ++zoneCount;
                    }
                }
            }
        }
    }
    dbg("zoneCount", zoneCount);
    dbg("notCoveredDots", notCoveredDots);
    dbg(zones);

    vec<int> lets(all(letters));
    int minLetters = (int)lets.size();
    vec<int> countZoneCoverage(zoneCount);
    int coveredZones = 0, turnedOneLetters = 0;

    function<void(int)> rec = [&] (int letId) {
        if (letId == (int)lets.size()) {
            if (coveredZones == zoneCount) {
                minLetters = min(minLetters, turnedOneLetters);
            }
            return;
        }
        rec(letId + 1);
        ++turnedOneLetters;
        for(auto z : zones[lets[letId]]) {
            countZoneCoverage[z]++;
            if (countZoneCoverage[z] == 1) {
                ++coveredZones;
            }
        }
        rec(letId + 1);
        --turnedOneLetters;
        for(auto z : zones[lets[letId]]) {
            countZoneCoverage[z]--;
            if (countZoneCoverage[z] == 0) {
                --coveredZones;
            }
        }
    };
    rec(0);
    out(minLetters, notCoveredDots);
}

//#include <fstream>


int main() {
//  ifstream fin("input.txt");
//  ofstream fout("output.txt");
//    Input in(in);
//    Output out(out);
    solve(cin, cout);
//  solve(fin, fout);
    return 0;
}

