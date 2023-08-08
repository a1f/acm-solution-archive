#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma once

#include "prelude.h"
#include "input.h"
#include "output.h"
#include "dbg.h"
#include "nt/nt.h"
#include "nt/mod_new.h"
#include <matrix_utils.h>

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

md stupidSolve3(int age, int r) {
    vec2d<md> dp = makeVec2d<md>(9, 10);
    FORA(i, 1, 10) {
        FOR(j, 10) {
            if (j != i) {
                dp[(i * 10 + j) % 9][j] += 1;
            }
        }
    }
    FOR(i, age-3) {
        vec2d<md> nxt = makeVec2d<md>(9, 10);
        FOR(j9, 9) {
            FOR(d, 10) {
                FOR(d2, 10) {
                    if (d2 != d) {
                        auto nr = (j9 * 10 + d2) % 9;
                        nxt[nr][d2] += dp[j9][d];
                    }
                }
            }
        }
        dp = nxt;
    }
    md res = 0;
    FOR(j9, 9) {
        FOR(d, 10) {
            FOR(d2, 10) {
                if (d == d2) continue;
                if ((d * 10 + d2) % 25 == r % 25 && r % 9 == (j9 * 10 + d2) % 9) {
                    res += dp[j9][d];
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

md stupidSolve(int age, int r) {
    vec2d<md> dp = makeVec2d<md>(225, 10);
    FORA(i, 1, 10) {
        dp[i][i] = 1;
    }
    FOR(i, age-1) {
        vec2d<md> nxt = makeVec2d<md>(225, 10);
        FOR(j, 225) {
            FOR(d, 10) {
                FOR(d2, 10) {
                    if (d2 != d) {
                        auto nr = (j * 10 + d2) % 225;
                        nxt[nr][d2] += dp[j][d];
                    }
                }
            }
        }
        dp = nxt;
        vec<md> modVal(225);
        FOR(j, 225) {
            FOR(d, 10) {
                modVal[j] += dp[j][d];
            }
        }
        dbg(i + 2, modVal);
    }
    vec<md> modVal(225);
    FOR(j, 225) {
        FOR(d, 10) {
            modVal[j] += dp[j][d];
        }
    }
    return modVal[r];
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
