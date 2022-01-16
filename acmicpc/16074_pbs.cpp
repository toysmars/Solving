// acmicpc 16074
//
// Parallel Binary Search (PBS)
// Minimul Spanning Tree
// Kruskal

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

struct DisjointSet {
    DisjointSet(int n) {
        for (int i = 0; i < n; ++i) {
            s.push_back(i);
            r.push_back(0);
        }
    }
    int find(int x) {
        if (s[x] != x) {
            s[x] = find(s[x]);
        }
        return s[x];
    }
    void join(int x, int y) {
        int sx = find(x);
        int sy = find(y);
        if (sx == sy) {
            return;
        }
        if (r[sx] < r[sy]) {
            swap(sx, sy);
        }
        s[sy] = sx;
        if (r[sx] == r[sy]) {
            r[sx] += 1;
        }
    }
    vector<int> s;
    vector<int> r;
};

struct Edge {
	int u;
	int v;
	int w;
	bool operator<(const Edge& rhs) const {
		return w < rhs.w;
	}
};

struct KrusukalDecisionMaker : DecisionMaker {
    KrusukalDecisionMaker(vector<Edge>& es) : es(es), ds(0), cur(0) {
        sort(es.begin(), es.end());
    }

    void Init() {
        ds = DisjointSet(es.size() + 2);
        cur = 0;
    }

    void PrepareTo(idx_t to) {
        while (cur < es.size() && es[cur].w <= to) {
            ds.join(es[cur].u, es[cur].v);
            cur++;
        }
    }

    bool Decide(query_t q) {
        return ds.find(q.first) == ds.find(q.second);
    }

    vector<Edge>& es;
    DisjointSet ds;
    int cur;
};

int R, C, Q;
int H[501][501];

int point_to_idx(int y, int x) {
    return y * C + x + 1;
}

pair<int, int> idx_to_point(int idx) {
    idx--;
    return make_pair(idx / C, idx % C);
}

int main() {
    scanf("%d%d%d", &R, &C, &Q);
    vector<Edge> es;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            scanf("%d", &H[i][j]);
            if (i > 0) es.push_back({point_to_idx(i, j), point_to_idx(i-1, j), max(H[i][j], H[i-1][j])});
            if (j > 0) es.push_back({point_to_idx(i, j), point_to_idx(i, j-1), max(H[i][j], H[i][j-1])});
        }
    }

    vector<query_t> qs;
    for (int i = 0; i < Q; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
        int u = point_to_idx(y1-1, x1-1);
        int v = point_to_idx(y2-1, x2-1);
        qs.emplace_back(u, v);
    }

    DecisionMaker* dm = new KrusukalDecisionMaker(es);
    ParallelBinarySearch pbs(qs, 1, 1000000, dm);

    auto as = pbs.Solve();

    for (int i = 0; i < qs.size(); ++i) {
        auto [y1, x1] = idx_to_point(qs[i].first);
        auto [y2, x2] = idx_to_point(qs[i].second);
        printf("%d\n", max({H[y1][x1], H[y2][x2], as[i]}));
    }

    return 0;
}
