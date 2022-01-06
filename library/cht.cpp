// CHT
// convex hull trick
// convec hull optimization
// 볼록 껍질 최적화
//
// Examples
// * https://www.acmicpc.net/problem/13263

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 coeff_t;
typedef i64 coord_t;
const coord_t MIN_X =  numeric_limits<i64>::min();

// LinearFunction represents a linear function f(x) = ax + b
struct LinearFunction {
    coeff_t a;
    coeff_t b;
};

coord_t solveLinearEquations(LinearFunction f, LinearFunction g) {
    return (g.b - f.b) / (f.a - g.a);
}

// CHT(Convex Hull Trick) solver.
//  Applicable recurrence relations:
//   * dp[i] = min { a[i]b[j] + c[j] } + d[i] when b[j] is monotonically decreasing
//   * dp[i] = max { a[i]b[j] + c[j] } + d[i] when b[j] is monotonically increasing
//    * f(x) = b[j]x + c[j] where x = a[i]
//  Time complexity
//   * O(n log n)
//   * O(n) when a[i] is monotocially increasing. (is_x_increasing = true)
struct ConvexHullTrickSolver {

    ConvexHullTrickSolver(bool is_x_increasing = false) : is_x_increasing(is_x_increasing), curr_ls_idx(0) {}

    coord_t Add(LinearFunction f) {
        coord_t x = MIN_X;
        while (st.size() > 0) {
            auto last_f = st.back().first;
            auto last_x = st.back().second;
            x = solveLinearEquations(last_f, f);
            if (last_x < x) break;
            st.pop_back();
        }
        st.emplace_back(f, x);
        return x;
    }

    coord_t Query(coord_t x) {
        if (is_x_increasing) {
            return linearSearchQuery(x);
        }
        return binarySearchQuery(x);
    }

    coord_t binarySearchQuery(coord_t x) {
        int lb = 0;
        int ub = st.size() - 1;
        int idx = 0;
        while (lb <= ub) {
            int t = (lb + ub) / 2;
            if (x >= st[t].second) {
                lb = t + 1;
                idx = t;
            } else {
                ub = t - 1;
            }
        }
        auto f = st[idx].first;
        return f.a * x + f.b;
    }

    coord_t linearSearchQuery(coord_t x) {
        while (curr_ls_idx + 1 < st.size() && st[curr_ls_idx + 1].second < x) {
            curr_ls_idx++;
        }
        auto f = st[curr_ls_idx].first;
        return f.a * x + f.b;
    }

    vector<pair<LinearFunction, coord_t>> st;
    bool is_x_increasing;
    int curr_ls_idx;
};
