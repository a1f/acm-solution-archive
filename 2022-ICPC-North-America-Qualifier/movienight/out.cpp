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


// m must be positive


template<typename T, typename C, T Modulus>
class MR
{
 private:
  struct tag_plus {}; // indicates value is in range [0, 2 * Modulus)
  struct tag_minus {}; // indicates value is in range (-Modulus, Modulus)
   // indicates value is in range

//  T value;

  
  static constexpr T reduce(T value, tag_plus)
  {
    return value >= Modulus ? value - Modulus : value;
  }

  static constexpr T reduce(T value, tag_minus)
  {
    return value < 0 ? value + Modulus : value;
  }

  
 public:
  T value;
  
  
  constexpr MR() : value(0) {}
  constexpr MR(C value) : value(reduce(value % Modulus, tag_minus())) {}
  template<typename tag_t>
  constexpr MR(T value, tag_t tag) : value(reduce(value, tag)) {}

  MR &operator=(C value) { this->value = reduce(value % Modulus, tag_minus()); return *this; }

  constexpr MR operator +(MR b) const { return MR(value + b.value, tag_plus()); }
  
  
  MR &operator -=(MR b) { value = reduce(value - b.value, tag_minus()); return *this; }
  MR &operator *=(MR b) { value = C(value) * C(b.value) % Modulus; return *this; }

  
  constexpr T get() const { return value; }

  // These are only valid if the dividend is relatively prime to the modulus
  
  
};

template<typename T, typename C, T Modulus>
static inline std::ostream &operator<<(std::ostream &o, MR<T, C, Modulus> mr)
{
  return o << mr.get();
}


typedef MR<int, int64_t, 1000000007> md10;


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


#include <type_traits>


namespace dsu {

struct DSU {
    vector<int> parent;
    vector<int> rank;
    vector<int> size;

    DSU(int n) {
        parent = vector<int>(n, 0);
        rank = vector<int>(n, 0);
        size = vector<int>(n, 1);
        FOR(i, n) {
            parent[i] = i;
        }
    }

    
    bool unite(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a == b) {
            return false;
        }
        int size_a = size[a];
        int size_b = size[b];
        if (rank[a] >= rank[b]) {
            ++rank[b];
            parent[b] = a;
        } else {
            parent[a] = b;
        }
        size[findSet(a)] = size_a + size_b;
        return true;
    }

    int findSet(int v) {
        return (v == parent[v]) ? v : (parent[v] = findSet(parent[v]));
    }
};

}

using md = md10;

enum VColor {
    UNKNOWN = -1,
    CYCLE = 0,
    TAIL = 1,
    MARK = 2,
};

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    vec<int> p(n);
    dsu::DSU disjointSet(n);
    vec2d<int> g(n);

    FOR(i, n) {
        auto x = in.ni() - 1;
        p[i] = x;
        g[x].push_back(i);
        disjointSet.unite(i, x);
    }
    vec<int> color(n, VColor::UNKNOWN);
    int countCycles = 0;
    vec<int> parent(n, -1);
    
    auto traverseAndMark = [&] (int v) -> int {
        color[v] = VColor::MARK;
        int pv = v;
        v = p[v];
        while (true) {
            if (color[v] == VColor::TAIL || color[v] == VColor::CYCLE) {
                v = pv;
                while (v != -1) {
                    color[v] = VColor::TAIL;
                    v = parent[v];
                }
                return 0;
            } else if (color[v] == VColor::UNKNOWN) {
                color[v] = VColor::MARK;
                parent[v] = pv;
                pv = v;
                v = p[v];
            } else if (color[v] == VColor::MARK) {
                // found cycle started from v
                while (pv != v) {
                    color[pv] = VColor::CYCLE;
                    pv = parent[pv];
                }
                color[v] = VColor::CYCLE;
                v = parent[v];
                while (v != -1) {
                    color[v] = VColor::TAIL;
                    v = parent[v];
                }
                return 1;
            } else {
                throw 42;
            }
        }
    };

    dbg("traverse");
    FOR(i, n) {
        if (color[i] == VColor::UNKNOWN) {
            countCycles += traverseAndMark(i);
        }
    }
    
    vec<md> dp(n), value(n, 1);

    function<void(int, int)> dfs = [&] (int v, int p) {
        dp[v] = 1;
        for (auto to : g[v]) {
            if (to == p) continue;
            if (color[to] == VColor::CYCLE) {
                continue;
            }
            dfs(to, v);
            dp[v] *= (dp[to] + 1);
        }
    };

    set<int> resValues;
    FOR(i, n) {
        if (color[i] == VColor::CYCLE) {
            auto val = disjointSet.findSet(i);
            resValues.insert(val);
            dfs(i, -1);
            value[val] *= dp[i];
        }
    }
    md result = 1;
    for (auto i : resValues) {
        result *= (value[i] + 1);
    }
    result -= 1;
    out(result);
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

