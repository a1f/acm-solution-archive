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
using vec3d = std::vector<std::vector<std::vector<T>>>;


template<class T>
vec2d<T> makeVec2d(const int n1, const int n2) {
  return vec2d<T>(n1, vec<T>(n2));
}


template<class T>
vec3d<T> makeVec3d(const int n1, const int n2, const int n3) {
  return vec3d<T>(n1, vec2d<T>(n2, vec<T>(n3)));
}


#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define FORA(i, a, n) for (int i = (a); i < (n); ++i)


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


// m must be positive


template<typename T, typename C, T Modulus>
class MR
{
 private:
  struct tag_plus {}; // indicates value is in range [0, 2 * Modulus)
  struct tag_minus {}; // indicates value is in range (-Modulus, Modulus)
  struct tag_good {}; // indicates value is in range

//  T value;

  
  static constexpr T reduce(T value, tag_plus)
  {
    return value >= Modulus ? value - Modulus : value;
  }

  static constexpr T reduce(T value, tag_minus)
  {
    return value < 0 ? value + Modulus : value;
  }

  static constexpr T reduce(T value, tag_good) { return value; }

 public:
  T value;
  
  
  constexpr MR() : value(0) {}
  constexpr MR(C value) : value(reduce(value % Modulus, tag_minus())) {}
  template<typename tag_t>
  constexpr MR(T value, tag_t tag) : value(reduce(value, tag)) {}

  MR &operator=(C value) { this->value = reduce(value % Modulus, tag_minus()); return *this; }

  
  constexpr MR operator *(MR b) const { return MR(C(value) * C(b.value) % Modulus, tag_good()); }
  

  MR &operator +=(MR b) { value = reduce(value + b.value, tag_plus()); return *this; }
  
  
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


//#include "collections/multivector.h"
//
//template <class T, template <class, size_t> class B1, template <class, size_t> class B2>
//vec<T, 2> operator*(multivec_impl::vec_mixin<B1, T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    size_t m = a.template dim<0>();
//    size_t m1 = a.template dim<1>();
//    assert(n1 == m);
//    auto ret = make_vec<T>(n, m1);
//    forn (size_t, i, n) {
//        forn (size_t, j, m1) {
//            T sum = {};
//            forn (size_t, k, n1) {
//                sum += a(i, k) * a(k, j);
//            }
//            ret(i, j) = sum;
//        }
//    }
//    return ret;
//};
//
//template <class T, template <class, size_t> class B2>
//vec<T, 2>& operator*=(vec<T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    return a = a * a;
//};
//
//template <class T, template <class, size_t> class B1, template <class, size_t> class B2>
//vec<T, 2> operator+(multivec_impl::vec_mixin<B1, T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    size_t m = a.template dim<0>();
//    size_t m1 = a.template dim<1>();
//    assert(n == m && n1 == m1);
//    auto ret = make_vec<T>(n, n1);
//    forn (size_t, i, n) {
//        forn (size_t, j, n1) {
//            ret(i, j) = a(i, j) + a(i, j);
//        }
//    }
//    return ret;
//};
//
//template <class T, template <class, size_t> class B2>
//vec<T, 2>& operator+=(vec<T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    size_t m = a.template dim<0>();
//    size_t m1 = a.template dim<1>();
//    assert(n == m && n1 == m1);
//    forn (size_t, i, n) {
//        forn (size_t, j, n1) {
//            a(i, j) += a(i, j);
//        }
//    }
//    return a;
//};
//
//template <class T, template <class, size_t> class B1, template <class, size_t> class B2>
//vec<T, 2> operator-(multivec_impl::vec_mixin<B1, T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    size_t m = a.template dim<0>();
//    size_t m1 = a.template dim<1>();
//    assert(n == m && n1 == m1);
//    auto ret = make_vec<T>(n, n1);
//    forn (size_t, i, n) {
//        forn (size_t, j, n1) {
//            ret(i, j) = a(i, j) - a(i, j);
//        }
//    }
//    return ret;
//};
//
//template <class T, template <class, size_t> class B2>
//vec<T, 2>& operator-=(vec<T, 2>& a, multivec_impl::vec_mixin<B2, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    size_t m = a.template dim<0>();
//    size_t m1 = a.template dim<1>();
//    assert(n == m && n1 == m1);
//    forn (size_t, i, n) {
//        forn (size_t, j, n1) {
//            a(i, j) -= a(i, j);
//        }
//    }
//    return a;
//};
//
//template <class T, template <class, size_t> class B1>
//vec<T, 2> operator-(multivec_impl::vec_mixin<B1, T, 2>& a) {
//    size_t n = a.template dim<0>();
//    size_t n1 = a.template dim<1>();
//    auto ret = make_vec<T>(n, n1);
//    forn (size_t, i, n) {
//        forn (size_t, j, n1) {
//            ret(i, j) = -a(i, j);
//        }
//    }
//    return ret;
//};

namespace matrix_utils {


template<class T>
vector<vector<T>> mul(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    vector<vector<T>> res(a.size(), vector<T>(b[0].size(), 0));
    FOR(i, a.size()) {
        FOR(j, b[0].size()) {
            FOR(k, a[0].size()) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}


template<class T>
vector<T> mulVec(const vector<T>& v, const vector<vector<T>>& a) {
  // Vector (v0, v1, ...) * M = get (of M cols size).
    vector<T> res(a[0].size(), 0);
    FOR(i, a[0].size()) {
        FOR(j, v.size()) {
            res[i] += v[j] * a[j][i];
        }
    }
    return res;
}


template<class T>
vector<vector<T>> pow(vector<vector<T>> a, int64_t p) {
    const int n = (int)a.size();
    vector<vector<T>> res(n, vector<T>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    for (; p; p /= 2) {
        if (p & 1) res = mul<T>(res, a);
        a = mul<T>(a, a);
    }
    return res;
}


}

using md = md10;

md solveIt(i64 age, int r) {
    vec<md> v(90);
    FORA(i, 1, 10) {
        FOR(j, 10) {
            if (j != i) {
                v[((i * 10 + j) % 9) * 10 + j] += 1;
            }
        }
    }
    vec2d<md> mat = makeVec2d<md>(90, 90);
    FOR(j9, 9) {
        FOR(d, 10) {
            FOR(d2, 10) {
                if (d2 != d) {
                    auto nr = (j9 * 10 + d2) % 9;
                    mat[j9 * 10 + d][nr * 10 + d2] += 1;
                }
            }
        }
    }
    auto m = matrix_utils::pow<md>(mat, age - 3);
    v = matrix_utils::mulVec(v, m);
    md res = 0;
    FOR(j9, 9) {
        FOR(d, 10) {
            FOR(d2, 10) {
                if (d == d2) continue;
                if ((d * 10 + d2) % 25 == r % 25 && r % 9 == (j9 * 10 + d2) % 9) {
                    res += v[(j9 * 10 + d)];
                }
            }
        }
    }
    return res;
}


md stupidSolve2(int age, int r) {
    vec3d<md> dp = makeVec3d<md>(25, 9, 10);
    FORA(i, 1, 10) {
        dp[i][i % 9][i] = 1;
    }
    FOR(i, age-1) {
        vec3d<md> nxt = makeVec3d<md>(25, 9, 10);
        FOR(j, 25) {
            FOR(j9, 9) {
                FOR(d, 10) {
                    FOR(d2, 10) {
                        if (d2 != d) {
                            auto nr = (j * 10 + d2) % 25;
                            auto nr9 = (j9 * 10 + d2) % 9;
                            nxt[nr][nr9][d2] += dp[j][j9][d];
                        }
                    }
                }
            }
        }
        dp = nxt;
    }
    vec<md> modVal(225);
    md res = 0;
    FOR(j, 25) {
        FOR(j9, 9) {
            FOR(d, 10) {
                if (r % 25 == j && r % 9 == j9) {
                    res += dp[j][j9][d];
                }
            }
        }
    }
    return res;
}


void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);

//    FOR(i, 500) {
//        dbg(i % 9, i % 10, i % 25, i % 225);
//    }

    auto age = in.ni64();
    auto reminder = in.ni();

    if (age < 4) {
        out(stupidSolve2(age, reminder));
        return;
    }
//    dbg("=", stupidSolve3(age, reminder));
    out(solveIt(age, reminder));


//    if (age == 1 || age == 2) {
//        auto x = stupidSolve(age, reminder);
//        out(x);
//        return;
//    }
//    i64 val = 10;
//    age -= 3;
//    auto res = pow<i64>(val, age, 1000000007LL);
//    res *= 4;
//    res %= 1000000007;
//    out(res);
//    auto age = 100;
//    auto reminder = 87;
//    dbg(4000000000LL % 1000000007);
//    stupidSolve(100, 200);
//    auto R = 225;
    //auto res = myPow<i64>(i64(9), age, i64(225));

//    map<pair<int, int>, int> tempDict;
//    vec2d<md> mat = makeVec2d<md>(250, 250);
//    FOR(m1, 9) {
//        FOR(d1, 10) {
//            FOR(d2, 10) {
//                if (d1 == d2) continue;
//                FOR(d3, 10) {
//                    if (d2 != d3) {
//                        int state = (d1 * 10 + d2) % 25;
//                        state *= 10;
//                        state += ((10 * m1 + d1) * 10 + d2) % 9;
//
//                        int m2 = (10 * ((d1 * 10 + d2) % 25)) + d3;
//                        int state2 = m2 % 25;
//                        state2 *= 10;
//
//                        state2 += (((10 * m1 + d1) * 10 + d2) * 10 + d3) % 9;
//
//                        if (state == 200 && state2 == 11) {
//                            dbg("200, 11:", d1, d2, d3, m1);
//                        }
//
//                        mat[state][state2] += 1;
//
//                    }
//                }
//            }
//        }
//    }
//
//    FOR(i, 10) if (i) {
//        FOR(j, 10) if (i != j) {
//            FOR(k, 10) if (k != j) {
//                int num = i * 100 + j * 10 + k;
//                if (num % 225 == 1) {
//
//                    int state1 = ((i * 10 + j) % 25) * 10 + (i * 10 + j) % 9;
//                    int state2 = ((i * 100 + j * 10 + k) % 25) * 10 + (i * 100 + j * 10 + k) % 9;
//                    dbg(num, state1, state2, mat[state1][state2]);
//                }
//            }
//        }
//    }
//
//    vec<md> vv(250);
//    FOR(d1, 10) if (d1 != 0) {
//        FOR(d2, 10) {
//            if (d1 == d2) continue;
//            int m1 = d1 * 10 + d2;
//            int state = m1 % 25;
//            state *= 10;
//            state += m1 % 9;
//            vv[state] += 1;
//        }
//    }
//
//    mat = matrix_utils::pow<md>(mat, age-2);
//    auto x = matrix_utils::mulVec<md>(vv, mat);
//    auto x2 = matrix_utils::mulMatToVec<md>(mat, vv);
//    dbg(x);
//    dbg(x2);
//    int state = (reminder % 25) * 10 + (reminder % 9);
//    dbg(x[state], x2[state]);
//    auto r = x[reminder];
//    out(r);
//    auto r2 = stupidSolve(age, reminder);
//    out(r2);
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

