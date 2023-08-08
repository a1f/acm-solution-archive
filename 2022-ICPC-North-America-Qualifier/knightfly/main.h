#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"

const auto DELTA_DIR = vec<pair<int, int>>{
    {1, 2},
    {2, 1},
    {-1, 2},
    {2, -1},
    {1, -2},
    {-2, 1},
    {-1, -2},
    {-2, -1},
};

pair<int, int> operator + (const pair<int, int>& p1, const pair<int, int>& p2) {
    return make_pair(
        p1.first + p2.first,
        p1.second + p2.second
    );
}

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    pair<int, int> startPoint, endPoint;
    auto x = in.ni();
    auto y = in.ni();
    startPoint = make_pair(x, y);

    x = in.ni();
    y = in.ni();
    endPoint = make_pair(x, y);

    vec<pair<int, int>> openPointsSortedX(n), openPointsSortedY(n);
    FOR(i, n) {
        x = in.ni();
        y = in.ni();
        openPointsSortedX[i] = {x, y};
        openPointsSortedY[i] = {y, x};
    }
    sort(all(openPointsSortedX));
    sort(all(openPointsSortedY));

    auto findPointInVec = [] (const vec<pair<int, int>>& v, const pair<int, int>& p) -> int {
        return (int)(lower_bound(all(v), p) - v.begin());
    };

    vec<pair<int, int>> q;
    q.push_back(startPoint);
    map<pair<int, int>, int> optimal;
    optimal[startPoint] = 0;

    auto getNewPos = [&] (pair<int, int> p, const pair<int, int>& delta) -> pair<int, int> {
        int dx, dy, dx1, dy1;
        if (abs(delta.first) == 2) {
            dx = delta.first / 2;
            dy = 0;
            dx1 = 0;
            dy1 = delta.second;
        } else {
            dx = 0;
            dy = delta.second / 2;
            dx1 = delta.first;
            dy1 = 0;
        }
        for (int i = 0; i < 2; ++i) {
            p = p + make_pair(dx, dy);
            if (openPoints.find(p) != openPoints.end()) {
                return p;
            }
        }
        p = p + make_pair(dx1, dy1);
        if (openPoints.find(p) != openPoints.end()) {
            return p;
        }
        return {-1, -1};
    };

    for (int i = 0; i < q.size(); ++i) {
        auto top = q[i];
        for (const auto& dd : DELTA_DIR) {
            auto newPos = getNewPos(top, dd);
            if (openPoints.find(newPos) != openPoints.end()) {
                auto it = optimal.find(newPos);
                if (it == optimal.end() || it->second > optimal[top] + 1) {
                    optimal[newPos] = optimal[top] + 1;
                    q.push_back(newPos);
                }
            }
        }
    }
    auto it = optimal.find(endPoint);
    if (it == optimal.end()) {
        out(-1);
        return;
    }
    out(it->second);
}
