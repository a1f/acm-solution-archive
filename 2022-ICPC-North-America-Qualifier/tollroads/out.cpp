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


#define forn(t, i, n) for (t i = 0; i < (n); ++i)


#define all(c) c.begin(), c.end()


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


//TODO migrate iterators into iterator_utils
namespace graph_impl {

    
    template<class K, class V>
    struct GenMap {
        using Value = V;

        explicit GenMap(V v_ = V{}): v(v_) {
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

    
  };

  struct Arc {
    int id;

    explicit Arc(int id_ = -1) : id(id_) {}

    
  };

  struct Edge {
    int id;

    explicit Edge(int id_ = -1) : id(id_) {}

    
    template<class C>
    Edge& with(C& c, typename C::Value v) {
      c(*this) = v;
      return *this;
    };

    
  };

  
  template<class V>
  using EdgeMap = graph_impl::GenMap<Edge, V>;

  
  Graph& clear() {
    arcs_.clear();
    nodes_.clear();
    return *this;
  }

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

  
  Arc uv(Edge e) const {
    assert(valid(e));
    return Arc{e.id << 1};
  }

  
  Node u(Edge e) const {
    assert(valid(e));
    return from(uv(e));
  }

  Node v(Edge e) const {
    assert(valid(e));
    return to(uv(e));
  }

  
  Arc dual(Arc a) const {
    if (a.id == -1) {
      return a;
    }
    assert(valid(a));
    return Arc{a.id ^ 1};
  }

  
  Node from(Arc a) const {
    assert(valid(a));
    return Node{arcs_[dual(a).id].to};
  }

  Node to(Arc a) const {
    assert(valid(a));
    return Node{arcs_[a.id].to};
  }

  
 private:

  
 public:

  
 private:
  vector<graph_impl::NodeT> nodes_;
  vector<graph_impl::ArcT> arcs_;
};


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

    
    int getSize(int a) {
        return size[findSet(a)];
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

Graph g;
Graph::EdgeMap<int> edgeCost;
typedef Graph::Node Node;
typedef Graph::Edge Edge;

struct DSUMetadata {
    vec<int> s;
    DSUMetadata() {}
    DSUMetadata(int x) {
        s.clear();
        s.push_back(x);
    }

};

vec<DSUMetadata> dsuMetadataMemory;

struct Query {
    int a, b;
    int resA, resB;
    bool queryIsReady = false;

    Query() {}
    Query(int a_, int b_) : a(a_), b(b_), resA(-1), resB(-1) {}
};

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    g.clear();
    auto n = in.ni();
    auto m = in.ni();
    auto countQueries = in.ni();
    dsuMetadataMemory = vec<DSUMetadata>(n);
    vec<DSUMetadata*> dsuMetaPtrTable(n);
    FOR(i, n) {
        dsuMetadataMemory[i] = DSUMetadata(i);
        dsuMetaPtrTable[i] = &dsuMetadataMemory[i];
    }
    vec<Node> nodes = g.addNodes(n);
    vec<Edge> edges;
    edgeCost.clear();
    FOR(i, m) {
        auto a = in.ni() - 1;
        auto b = in.ni() - 1;
        auto cs = in.ni();
        edges.push_back(g.addEdge(nodes[a], nodes[b]).with(edgeCost, cs));
    }
    sort(all(edges), [&] (const Edge& e1, const Edge& e2) -> bool {
        return edgeCost(e1) < edgeCost(e2);
    });
    dsu::DSU disjointSet(n);

    vec<Query> queries(countQueries);
    vec2d<int> nodeToQueries(n);
    FOR(i, countQueries) {
        auto a = in.ni() - 1;
        auto b = in.ni() - 1;
        queries[i] = Query(a, b);
        nodeToQueries[a].push_back(i);
        nodeToQueries[b].push_back(i);
    }
    vec<int> queriesToUpdate;

    auto processAndMerge = [&] (int idA, int idB, int cst) {
        auto& ptrA = dsuMetaPtrTable[idA];
        auto& ptrB = dsuMetaPtrTable[idB];

        for (const auto v : ptrA->s) {
            ptrB->s.push_back(v);
            for (const auto qid : nodeToQueries[v]) {
                if (queries[qid].queryIsReady) {
                    continue;
                }
                int qa = queries[qid].a, qb = queries[qid].b;
                if (
                        (disjointSet.findSet(qa) == idA && disjointSet.findSet(qb) == idB) ||
                        (disjointSet.findSet(qa) == idB && disjointSet.findSet(qb) == idA)
                   ) {
                    queries[qid].queryIsReady = true;
                    queries[qid].resA = cst;
                    queriesToUpdate.push_back(qid);
                }
            }
        }

        disjointSet.unite(idA, idB);
        auto newId = disjointSet.findSet(idA);
        dsuMetaPtrTable[newId] = ptrB;
    };

    int prevEdgeCost = -1;
    for (const auto& e : edges) {
        if (edgeCost(e) != prevEdgeCost) {
            if (prevEdgeCost != -1) {
                for (auto qid : queriesToUpdate) {
                    queries[qid].resB = disjointSet.getSize(queries[qid].a);
                }
                queriesToUpdate.clear();
            }
            prevEdgeCost = edgeCost(e);
        }
        int a = g.v(e).id;
        int b = g.u(e).id;
        auto idA = disjointSet.findSet(a);
        auto idB = disjointSet.findSet(b);
        if (idA == idB) {
            continue;
        }
        auto aSetSize = disjointSet.getSize(idA);
        auto bSetSize = disjointSet.getSize(idB);
        if (aSetSize < bSetSize) {
            processAndMerge(idA, idB, edgeCost(e));
        } else {
            processAndMerge(idB, idA, edgeCost(e));
        }
    }
    for (auto qid : queriesToUpdate) {
        queries[qid].resB = disjointSet.getSize(queries[qid].a);
    }
    FOR(i, countQueries) {
        if (queries[i].resA == -1 || queries[i].resB == -1) {
            throw 42;
        }
        out(queries[i].resA, queries[i].resB);
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

