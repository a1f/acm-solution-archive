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

    
    template<class T>
    vec<T> nVec(int n) const {
        vec<T> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = next<T>();
        }
        return v;
    }

    vec<int> nvi(int n) const {
        return nVec<int>(n);
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


const int INF = numeric_limits<int>::max();

int evaluateOrFail2(int x, int y, int s) {
    if (s == 3) {
        if (x % y) {
            return INF;
        }
        return x / y;
    }
    if (s == 0) {
        return x + y;
    }
    if (s == 1) {
        return x - y;
    }
    if (s == 2) {
        return x * y;
    }
    dbg("here2");
    throw 42;
}

int evaluateOrFail(const vec<int>& x, int s1, int s2) {
    if (s1 == 3) {
        if (x[0] % x[1]) {
            return INF;
        }
        return evaluateOrFail2(x[0] / x[1], x[2], s2);
    }
    if (s1 == 2) {
        return evaluateOrFail2(x[0] * x[1], x[2], s2);
    }
    // if (s2 >= 2) {
    //     if (s2 == 3) {
    //         if (x[1] % x[2]) {
    //             return INF;
    //         }
    //         return evaluateOrFail2(x[0], x[1] / x[2], s1);
    //     } 
    //     return evaluateOrFail2(x[0], x[1] * x[2], s1);
    // }
    if (s1 == 0) {
        return evaluateOrFail2(x[0] + x[1], x[2], s2);
    }
    if (s1 == 1) {
        return evaluateOrFail2(x[0] - x[1], x[2], s2);
    }
    dbg("here");
    throw 42;
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto x = in.nvi(3);
    auto res = INF;
    evaluateOrFail(x, 1, 2);
    FOR(i, 4) {
        FOR(j, 4) {
            auto cres = evaluateOrFail(x, i, j);
            dbg(i, j, cres);
            if (cres >= 0) {
                res = min(res, cres);
            }
        }
    }
    out(res);
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

