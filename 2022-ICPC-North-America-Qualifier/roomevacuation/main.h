#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"
#include "graph/graph.h"
#include "graph/dinic_flow.h"

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
