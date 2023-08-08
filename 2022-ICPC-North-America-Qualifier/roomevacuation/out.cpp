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
vec3d<T> makeVec3d(const int n1, const int n2, const int n3) {
  return vec3d<T>(n1, vec2d<T>(n2, vec<T>(n3)));
}


#define FOR(i, n) for (int i = 0; i < (n); ++i)


#define forn(t, i, n) for (t i = 0; i < (n); ++i)


typedef string str;


// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END

template<class T>
inline T mn(T arg) {
    return arg;
}

template<class T, class... Ts>
inline typename common_type<T, Ts...>::type mn(T arg, Ts... args) {
    auto arg1 = mn(args...);
    return arg < arg1 ? arg : arg1;
}


template <class T>
T pop(queue<T>& v) {
    T ret = v.front();
    v.pop();
    return ret;
}


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

    
    template<class T>
    vec<T> nVec(int n) const {
        vec<T> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = next<T>();
        }
        return v;
    }

    
    vec<string> nvs(int n) const {
        return nVec<string>(n);
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


//TODO migrate iterators into iterator_utils
namespace graph_impl {

    template<class T, class G, T next(const G&, T)>
    struct GenListIterator {
        GenListIterator(const G& g_, T t_): g(g_), t(t_) {}

        T operator*() const {
            return t;
        }

        GenListIterator& operator++() {
            t = next(g, t);
            return *this;
        }

        
        bool operator!=(const GenListIterator& o) const {
            assert(&g == &o.g);
            return t != o.t;
        }
    private:
        const G& g;
        T t;
    };

    template<class T, class G, T next(const G&, T)>
    struct GenListIterable {
        GenListIterable(const G& g_, T from_, T to_): g(g_), from(from_), to(to_) {}

        GenListIterator<T, G, next> begin() {
            return {g, from};
        };

        GenListIterator<T, G, next> end() {
            return {g, to};
        };
    private:
        const G& g;
        T from, to;
    };

    template<class T>
    struct GenRangeIterator {
        explicit GenRangeIterator(int at_): at(at_) {}

        T operator*() const {
            return T{at};
        }

        GenRangeIterator& operator++() {
            at++;
            return *this;
        }

        
        bool operator!=(const GenRangeIterator& o) const {
            return at != o.at;
        }
    private:
        int at;
    };

    template<class T>
    struct GenRangeIterable {
        GenRangeIterable(int from_, int to_):  from(from_), to(to_) {}

        GenRangeIterator<T> begin() {
            return GenRangeIterator<T>{from};
        };

        GenRangeIterator<T> end() {
            return GenRangeIterator<T>{to};
        };
    private:
        int from, to;
    };

    template<class K, class V>
    struct GenMap {
        using Value = V;

        explicit GenMap(V v_ = V{}): v(v_) {
        }

        GenMap& reserve(int n) {
            impl_.reserve(n);
            return *this;
        }

        GenMap& clear() {
            impl_.clear();
            return *this;
        }

        V& operator()(K k) {
            if (impl_.size() <= k.id) {
                impl_.resize(k.id + 1, v);
            }
            return impl_[k.id];
        }

        const V& operator()(K k) const {
            if (impl_.size() <= k.id) {
                return v;
            }
            return impl_[k.id];
        }
        vector<V> impl_;
    private:
        V v;
    };


struct NodeT {
  int firstOut = -1;
  int degree = 0;
};

struct ArcT {
  int to, nextOut;
};
}
struct Graph {
  struct Node {
    int id;

    explicit Node(int id_ = -1) : id(id_) {}

    bool operator==(const Node o) const { return id == o.id; }

    
  };

  struct Arc {
    int id;

    explicit Arc(int id_ = -1) : id(id_) {}

    
    bool operator!=(const Arc o) const { return id != o.id; }

    
  };

  struct Edge {
    int id;

    explicit Edge(int id_ = -1) : id(id_) {}

    
    template<class C>
    Edge& withUV(C& c, typename C::Value v) {
      c(Arc{2 * id}) = v;
      return *this;
    };

    template<class C>
    Edge& withVU(C& c, typename C::Value v) {
      c(Arc{2 * id + 1}) = v;
      return *this;
    };

    
  };

  template<class V>
  using NodeMap = graph_impl::GenMap<Node, V>;

  template<class V>
  using ArcMap = graph_impl::GenMap<Arc, V>;

  
  Node addNode() {
    int n = (int) nodes_.size();
    nodes_.push_back({});
    return Node{n};
  }

  vector<Node> addNodes(int count) {
    vector<Node> ret(count);
    forn (int, i, count) {
      ret[i] = addNode();
    }
    return ret;
  }

  Edge addEdge(Node u, Node v) {
    assert(valid(u));
    assert(valid(v));
    int n = (int) arcs_.size();
    arcs_.push_back({});
    arcs_[n].to = v.id;
    arcs_[n].nextOut = nodes_[u.id].firstOut;
    nodes_[u.id].firstOut = n;
    arcs_.push_back({});
    arcs_[n + 1].to = u.id;
    arcs_[n + 1].nextOut = nodes_[v.id].firstOut;
    nodes_[v.id].firstOut = n + 1;
    nodes_[u.id].degree++;
    nodes_[v.id].degree++;
    return Edge{n >> 1};
  }

  
  int nodesCount() const {
    return (int) nodes_.size();
  }

  int arcsCount() const {
    return (int) arcs_.size();
  }

  
  Arc dual(Arc a) const {
    if (a.id == -1) {
      return a;
    }
    assert(valid(a));
    return Arc{a.id ^ 1};
  }

  Arc firstInArc(Node a) const {
    assert(valid(a));
    return dual(Arc{nodes_[a.id].firstOut});
  }

  Arc firstOutArc(Node a) const {
    assert(valid(a));
    return Arc{nodes_[a.id].firstOut};
  }

  Arc nextInArc(Arc a) const {
    assert(valid(a));
    return dual(Arc{arcs_[dual(a).id].nextOut});
  }

  Arc nextOutArc(Arc a) const {
    assert(valid(a));
    return Arc{arcs_[a.id].nextOut};
  }

  Node from(Arc a) const {
    assert(valid(a));
    return Node{arcs_[dual(a).id].to};
  }

  Node to(Arc a) const {
    assert(valid(a));
    return Node{arcs_[a.id].to};
  }

  
  template<class T>
  NodeMap<T> nodeMap(T v0 = T{}) const {
    NodeMap<T> ret(v0);
    ret.reserve(nodesCount());
    return ret;
  }

  template<class T>
  ArcMap<T> arcMap(T v0 = T{}) const {
    ArcMap<T> ret(v0);
    ret.reserve(arcsCount());
    return ret;
  }

  
 private:

  static Arc nextInArc_(const Graph& g, Arc a) {
    return g.nextInArc(a);
  }

  
 public:

  graph_impl::GenListIterable<Arc, Graph, &Graph::nextInArc_> inArcs(Node a) const {
    assert(valid(a));
    return graph_impl::GenListIterable<Arc, Graph, &Graph::nextInArc_>(*this,
                                                                       firstInArc(a),
                                                                       Arc{});
  }

  
  graph_impl::GenRangeIterable<Arc> arcs() const {
    return graph_impl::GenRangeIterable<Arc>(0, arcsCount());
  }

  
 private:
  vector<graph_impl::NodeT> nodes_;
  vector<graph_impl::ArcT> arcs_;
};


// Highest-label variation of Karzanov's algorithm
template <class Cap = int32_t, class Excess = int64_t>
struct DinicFlow {
    using Node = Graph::Node;
    using Arc = Graph::Arc;
    

    DinicFlow(const Graph& g_, const Graph::ArcMap<Cap>& cap_): g(g_), cap(cap_) {}

    Excess run(Node s, Node t) {
        residual = cap;
        label = g.nodeMap<int>(g.nodesCount());
        currentArc = g.nodeMap<Arc>();
        value = 0;
        while (buildNet(s, t)) {
            Cap inf = numeric_limits<Cap>::max();
            Cap cur;
            while ((cur = flowDfs(s, t, inf)) > 0) {
                value += cur;
            }
        }
        flow = g.arcMap<Cap>();
        for (auto a : g.arcs()) {
            flow(a) = cap(a) - residual(a);
        }
        return value;
    }

    bool buildNet(Node s, Node t) {
        label.clear();
        label(t) = 0;
        queue<Node> q;
        q.push(t);
        while (!q.empty()) {
            auto u = pop(q);
            currentArc(u) = g.firstOutArc(u);
            if (u == s) {
                break;
            }
            for (auto a : g.inArcs(u)) {
                auto v = g.from(a);
                if (residual(a) > 0 && label(v) == g.nodesCount()) {
                    label(v) = label(u) + 1;
                    q.push(v);
                }
            }
        }
        if (label(s) == g.nodesCount()) {
            return false;
        }
        return true;
    }

    Cap flowDfs(Node u, Node t, Cap max) {
        if (u == t) {
            return max;
        }
        Cap ret = 0;
        auto& a = currentArc(u);
        for (; a != Arc{}; a = g.nextOutArc(a)) {
            auto v = g.to(a);
            Cap cur;
            if (label(u) == label(v) + 1 && residual(a) > 0 && (cur = flowDfs(v, t, mn(residual(a), max))) > 0) {
                ret += cur;
                max -= cur;
                residual(a) -= cur;
                residual(g.dual(a)) += cur;
                if (max == 0) {
                    break;
                }
            }
        }
        return ret;
    }

    // outputs
    Excess value;
    Graph::ArcMap<Cap> flow, residual;

private:
    // inputs
    const Graph& g;
    const Graph::ArcMap<Cap>& cap;

    // temp
    Graph::NodeMap<int> label;
    Graph::NodeMap<Arc> currentArc;
};

Graph g;
vec<Graph::Node> nodes;
vec3d<pair<int, int>> nodeRefs;
Graph::ArcMap<int> cap;

void addEdgeBase(const Graph::Node& n1, const Graph::Node& n2, int c) {
    g.addEdge(n1, n2).withUV(cap, c).withVU(cap, 0);
}

void addEdge(int x1, int y1, int z1, int c) {
    addEdgeBase(nodes[nodeRefs[x1][y1][z1].first], nodes[nodeRefs[x1][y1][z1].second], c);
}

void addEdge(int x1, int y1, int z1, int x2, int y2, int z2, int c) {
    addEdgeBase(nodes[nodeRefs[x1][y1][z1].second], nodes[nodeRefs[x2][y2][z2].first], c);
}

void addEdge(int x2, int y2, int z2, Graph::Node nn, int c) {
    addEdgeBase(nodes[nodeRefs[x2][y2][z2].second], nn, c);
}

void addEdge(Graph::Node nn, int x2, int y2, int z2, int c) {
    addEdgeBase(nn, nodes[nodeRefs[x2][y2][z2].first], c);
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);

    auto n = in.ni();
    auto m = in.ni();
    auto t = in.ni();
    vec<str> f = in.nvs(n);


    nodes = g.addNodes(n * m * 2 * (t + 1) + 2);
    nodeRefs = makeVec3d<pair<int, int>>(t + 1, n, m);
    vec2d<int> revRef(n * m * 2 * (t + 1) + 2);
    int cnt = 0;
    auto S = nodes.end()[-2];
    auto T = nodes.end()[-1];

    FOR(i, t + 1) {
        FOR(j, n) {
            FOR(k, m) {
                nodeRefs[i][j][k] = {cnt, cnt + 1};
                revRef[cnt] = {i, j, k};
                revRef[cnt+1] = {i, j, k};
                cnt += 2;
            }
        }
    }

    dbg("building graph");

    const int dj[] = {1, 0, -1, 0};
    const int dk[] = {0, 1, 0, -1};
    FOR(i, t + 1) {
        FOR(j, n) {
            FOR(k, m) {
                if (f[j][k] == '#') continue;
                if (i < t) {
                    // Edge between layers
                    addEdge(i, j, k, i + 1, j, k, 1);
                    FOR(d, 4) {
                        int nj = j + dj[d];
                        int nk = k + dk[d];
                        if (nj >= 0 && nk >= 0 && nj < n && nk < m) {
                            if (f[nj][nk] != '#') {
                                addEdge(i, j, k, i + 1, nj, nk, 1);
                            }
                        }
                    }
                }
                addEdge(i, j, k, 1);
                if (f[j][k] == 'E') {
                    addEdge(i, j, k, T, 1);
                }
                if (i == 0 && f[j][k] == 'P') {
                    addEdge(S, i, j, k, 1);
                }
            }
        }
    }
    dbg("running flow");

    DinicFlow<int> maxFlow(g, cap);
    auto flow = maxFlow.run(S, T);
    out(flow);

//    FOR(i, t + 1) {
//        FOR(j, n) {
//            FOR(k, m) {
//                for (auto ta : g.outArcs(nodes[nodeRefs[i][j][k].first])) {
//                    if (maxFlow.flow(ta) > 0) {
//                        dbg("[", i, j, k, "] cell with flow", maxFlow.flow(ta));
//                    }
//                }
//            }
//        }
//    }
//    dbg("");
//    FOR(i, t + 1) {
//        FOR(j, n) {
//            FOR(k, m) {
//                for (auto ta : g.outArcs(nodes[nodeRefs[i][j][k].second])) {
//                    if (maxFlow.flow(ta) > 0) {
//                        dbg("[", i, j, k, "] out cell flow", maxFlow.flow(ta), "to", revRef[g.to(ta).id]);
//                    }
//                }
//            }
//        }
//    }
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

