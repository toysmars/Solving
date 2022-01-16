// Parallel Binary Search
// pbs
//
// Examples:
// * https://www.acmicpc.net/problem/16074

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> query_t;
typedef int idx_t;
typedef int ans_t;

struct DecisionMaker {
    virtual void Init() = 0;
    virtual void PrepareTo(idx_t to) = 0;
    virtual bool Decide(query_t q) = 0;
};

struct ParallelBinarySearch {
    ParallelBinarySearch(vector<query_t>& qs, idx_t lb, idx_t ub, DecisionMaker* dm) : qs(qs), lbs(qs.size()), ubs(qs.size()), as(qs.size()), dm(dm) {
        for (int qi = 0; qi < qs.size(); ++qi) {
            lbs[qi] = lb;
            ubs[qi] = ub;
        }
    }

    vector<ans_t> Solve(int no_answer = -1) {
        for (int i = 0; i < as.size(); ++i) as[i] = no_answer;

        while (true) {
            bool solved = true;
            map<idx_t, vector<int>> qm;
            for (int qi = 0; qi < qs.size(); ++qi) {
                int lb = lbs[qi];
                int ub = ubs[qi];
                if (lb <= ub) {
                    solved = false;
                    int mid = (lb + ub) / 2;
                    qm[mid].push_back(qi);
                }
            }
            if (solved) break;

            dm->Init();

            for (auto& [tidx, qis]: qm) {
                dm->PrepareTo(tidx);
                for (auto qi: qis) {
                    auto& q = qs[qi];
                    if (dm->Decide(q)) {
                        as[qi] = tidx;
                        ubs[qi] = tidx - 1;
                    } else {
                        lbs[qi] = tidx + 1;
                    }
                }
            }
        }
        return as;
    }

    vector<query_t> qs;
    vector<idx_t> lbs;
    vector<idx_t> ubs;
    vector<ans_t> as;
    DecisionMaker* dm;
};
