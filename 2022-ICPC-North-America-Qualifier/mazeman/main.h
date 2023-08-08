#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    auto m = in.ni();
    vec<str> f(n);
    str s;
    getline(*in.in, s);
    FOR(i, n) {
        getline(*in.in, s);
        dbg(i, s);
        f[i] = s;
    }
    vec2d<bool> used = makeVec2d<bool>(n, m, false);
    vec2d<int> zones(30);
    int countDots = 0;
    bool foundLetters;
    set<int> letters;

    function<void(int, int, int)> dfs = [&] (int x, int y, int zoneId) {
        if (x < 0 || y < 0 || x >= n || y >= m) {
            return;
        }
        if (used[x][y]) return;
        used[x][y] = true;
        if (f[x][y] == 'X') {
            return;
        }
        if (f[x][y] == '.') {
            ++countDots;
        }
        if (isupper(f[x][y])) {
            zones[f[x][y] - 'A'].push_back(zoneId);
            letters.insert(f[x][y] - 'A');
            foundLetters = true;
            return;
        }
        dfs(x + 1, y, zoneId);
        dfs(x - 1, y, zoneId);
        dfs(x, y + 1, zoneId);
        dfs(x, y - 1, zoneId);
    };
    int zoneCount = 0;
    int notCoveredDots = 0;
    FOR(i, n) {
        FOR(j, m) {
            if (f[i][j] == '.') {
                if (!used[i][j]) {
                    countDots = 0;
                    foundLetters = false;
                    dfs(i, j, zoneCount);
                    if (!foundLetters) {
                        notCoveredDots += countDots;
                    } else {
                        ++zoneCount;
                    }
                }
            }
        }
    }
    dbg("zoneCount", zoneCount);
    dbg("notCoveredDots", notCoveredDots);
    dbg(zones);

    vec<int> lets(all(letters));
    int minLetters = (int)lets.size();
    vec<int> countZoneCoverage(zoneCount);
    int coveredZones = 0, turnedOneLetters = 0;

    function<void(int)> rec = [&] (int letId) {
        if (letId == (int)lets.size()) {
            if (coveredZones == zoneCount) {
                minLetters = min(minLetters, turnedOneLetters);
            }
            return;
        }
        rec(letId + 1);
        ++turnedOneLetters;
        for(auto z : zones[lets[letId]]) {
            countZoneCoverage[z]++;
            if (countZoneCoverage[z] == 1) {
                ++coveredZones;
            }
        }
        rec(letId + 1);
        --turnedOneLetters;
        for(auto z : zones[lets[letId]]) {
            countZoneCoverage[z]--;
            if (countZoneCoverage[z] == 0) {
                --coveredZones;
            }
        }
    };
    rec(0);
    out(minLetters, notCoveredDots);
}
