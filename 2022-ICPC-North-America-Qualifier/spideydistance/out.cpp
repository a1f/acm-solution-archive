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

template<typename T>
ostream& operator<< (const T& x) {
    *out << x;
    return *out;
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


template<typename T> static constexpr T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }


// m must be positive


//template <class T>
//T gcd(T a, T b) {
//    return b == 0 ? a : gcd(b, a % b);
//}

//TODO extended gcd


// MD implementation of factorials and binomial


// TODO(alf): Tests


//
//int64_t lcm(const vector<int64_t>& a) {
//    int64_t res = a[0];
//    for (int i = 1; i < (int)a.size(); ++i) {
//        int64_t g = gcd(res, a[i]);
//        res *= a[i];
//        res /= g;
//    }
//    return res;
//}
//
//int64_t lcm(int64_t a, int64_t b) {
//    return (a * b / gcd(a, b));
//}


// Algorithms


int getMaxForTaxi(int x, int t) {
    int y = t - x;
    return max(-1, y);
}

bool debug;

int getMaxForSpidy(int x, int s) {
//    if (debug) {
//        int bestY = 0;
//        FOR(i, x + 1) {
//            int cst = (i * 3 + 1) / 2;
//            int ss = s - cst;
//            int nx = x - i;
//            ss -= nx;
//            int cy = i;
//            if (ss < 0) continue;
//            cy += ss;
//            bestY = max(bestY, cy);
//        }
//        dbg("x = ", x, "y=", bestY);
//        return bestY;
//    }
    if (s * 2 >= 3 * x) {
        s -= (3 * x) / 2;
        int cy = x;
        if (x % 2 == 1) {
            --s;
        }
        cy += s;
        dbg("x=", x, "v1 y:", cy);
        return cy;
    } else {
        int v = (s - x) * 2;
        dbg("x=", x, "v2 y:", v);

        return max(-1, v);
    }
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);

    debug = true;
    auto t = in.ni();
    auto s = in.ni();

    int maxX = max(t, s);
    i64 sumSpidy = 0;
    i64 sumTaxy = 0;
    for (int i = 1; i <= maxX; ++i) {
        int yt = getMaxForTaxi(i, t) + 1;
        int ys = getMaxForSpidy(i, s) + 1;
//        dbg("->", i, yt);
        yt = min(yt, ys);
        sumSpidy += ys;
        sumTaxy += yt;
    }
    sumSpidy *= 4;
    sumTaxy *= 4;
    ++sumSpidy;
    ++sumTaxy;
    dbg(sumTaxy, sumSpidy);
    i64 g = gcd(sumSpidy, sumTaxy);
    sumSpidy /= g;
    sumTaxy /= g;
    if (sumSpidy == 1) {
        out(sumTaxy);
    } else {
        out << sumTaxy << "/" << sumSpidy << "\n";
    }

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

