// acmicpc 16367
//
// two-sat
// 2-sat

#include <bits/stdc++.h>
using namespace std;

struct SCC
{
    // Solve SCC problem by Tarjan's algorithm.
    vector<int> Solve(const vector<vector<int>>& g) {
        int n = g.size();

        di = 0;
        scc_count = 0;
        scc_ids = vector<int>(n);
        discovers = vector<int>(n, -1);
        is_in_stack = vector<bool>(n);

        for (int u = 0; u < n; ++u) {
            if (discovers[u] == -1) {
                solve(g, u);
            }
        }
        return scc_ids;
    }

    int solve(const vector<vector<int>>& g, int u) {
        int low = discovers[u] = di++;
        st.push(u);
        is_in_stack[u] = true;
        for (auto v: g[u]) {
            if (discovers[v] == -1) {
                low = min(low, solve(g, v));
            } else if (is_in_stack[v]) {
                low = min(low, discovers[v]);
            }
        }
        if (low == discovers[u]) {
            while (true) {
                int v = st.top();
                st.pop();
                is_in_stack[v] = false;
                scc_ids[v] = scc_count;
                if (u == v) {
                    break;
                }
            }
            ++scc_count;
        }
        return low;
    }

	int di;
	int scc_count;
	vector<int> scc_ids;
	vector<int> discovers;
	vector<bool> is_in_stack;
    stack<int> st;
};

struct TwoSAT
{
    TwoSAT(int n): g(2*n) {}

    void UorV(int u, int v) {
        NotUtoV(u, v);
        NotUtoV(v, u);
    }
    void NotUorV(int u, int v) {
        UtoV(u, v);
        NotUtoNotV(v, u);
    }
    void UorNotV(int u, int v) {
        NotUorV(v, u);
    }
    void NotUorNotV(int u, int v) {
        UtoNotV(u, v);
        UtoNotV(v, u);
    }
    void UtoV(int u, int v) {
        g[2*u].push_back(2*v);
    }
    void NotUtoV(int u, int v) {
        g[2*u+1].push_back(2*v);
    }
    void UtoNotV(int u, int v) {
        g[2*u].push_back(2*v+1);
    }
    void NotUtoNotV(int u, int v) {
        g[2*u+1].push_back(2*v+1);
    }

    vector<bool> Solve() {
        // Find SCC of given graph.
        SCC scc;
        vector<int> sccId = scc.Solve(g);

        // number of variables.
        int n = g.size() / 2;

        // if a variable and its complement are in the same component,
        // than there is no solution.
        for (int i = 0; i < 2*n; i += 2) {
            if (sccId[i] == sccId[i+1]) {
                return vector<bool>();
            }
        }
        // Topological order of the SCC.
        vector<pair<int, int> > torder;
        for (int i = 0; i < 2*n; ++i) {
            torder.push_back(make_pair(sccId[i], i));
        }
        // Topological order is inverse of scc id.
        sort(torder.rbegin(), torder.rend());

        // Assign
        vector<bool> res(n);
        vector<bool> visit(n, false);
        for (int i = 0; i < 2*n; ++i) {
            int u = torder[i].second;
            int v = u / 2;
            bool is = u % 2;
            if (visit[v]) {
                continue;
            }
            res[v] = is;
            visit[v] = true;
        }
        return res;
    }

    vector<vector<int>> g;
};

void add(TwoSAT& twoSat, int u, bool isu, int v, bool isv) {
    if (isu) {
        if (isv) twoSat.UorV(u, v);
        else twoSat.UorNotV(u, v);
    } else {
        if (isv) twoSat.NotUorV(u, v);
        else twoSat.NotUorNotV(u, v);
    }
}

// (A && B) || (B && C) || (C && A) == (A || B) && (B || C) && (C || A)
int main() {
    int K, N;
    scanf("%d%d", &K, &N);
    TwoSAT twoSat(K);
    for (int i = 0; i < N; ++i) {
        int k1, k2 ,k3;
        char c1[2], c2[2], c3[2];
        scanf("%d%s%d%s%d%s", &k1, c1, &k2, c2, &k3, c3);
        k1--; k2--; k3--;
        add(twoSat, k1, *c1 == 'R', k2, *c2 == 'R');
        add(twoSat, k2, *c2 == 'R', k3, *c3 == 'R');
        add(twoSat, k3, *c3 == 'R', k1, *c1 == 'R');
    }
    auto res = twoSat.Solve();
    if (res.size() == 0) {
        printf("-1\n");
        return 0;
    }
    for (auto r: res) {
        printf("%c", r ? 'R' : 'B');
    }
    printf("\n");
    return 0;
}
