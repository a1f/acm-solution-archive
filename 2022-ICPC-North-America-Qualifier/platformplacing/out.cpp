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


#define FOR(i, n) for (int i = 0; i < (n); ++i)


#define all(c) c.begin(), c.end()


typedef int64_t i64;


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

    i64 ni64() const {
        return next<i64>();
    }

    
    template<class T>
    vec<T> nVec(int n) const {
        vec<T> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = next<T>();
        }
        return v;
    }

    
    vec<i64> nvi64(int n) const {
        return nVec<i64>(n);
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


void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    auto minLen = in.ni64();
    auto maxLen = in.ni64();
    auto xs = in.nvi64(n);
    sort(all(xs));
    if (n == 1) {
        out(maxLen);
        return;
    }

    FOR(i, n) if (i) {
        if (xs[i] - xs[i-1] < minLen) {
            out(-1);
            return;
        }
    }
    FOR(i, n) {
        xs[i] *= 2;
    }
    const i64 INF = numeric_limits<i64>::max();

    auto extendOne = [&] (int i, vec<i64>& lens) -> void {
        i64 leftNeiDst = INF;
        i64 rightNeiDst = INF;
        if (i > 0) {
            leftNeiDst = (xs[i] - lens[i] / 2) - (xs[i-1] + lens[i-1] / 2);
        }
        if (i < n - 1) {
            rightNeiDst = (xs[i+1] - lens[i+1] / 2) - (xs[i] + lens[i] / 2);
        }
        i64 r = min(leftNeiDst, rightNeiDst);
        lens[i] += r * 2;
        lens[i] = min(lens[i], maxLen * 2);
    };

    vec<i64> lens(n, minLen * 2);
    FOR(i, n) {
        extendOne(i, lens);
    }
    i64 res = accumulate(all(lens), i64(0));
    out(res / 2);
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

