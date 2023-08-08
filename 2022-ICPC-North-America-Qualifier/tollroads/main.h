#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"
#include "graph/graph.h"
#include "dsu.h"

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
