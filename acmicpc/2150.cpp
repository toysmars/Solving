// acmicpc 2150
//
// scc
// strongly connected component

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

int main() {
    int V, E;
    scanf("%d%d", &V, &E);
    vector<vector<int>> g(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u-1].push_back(v-1);
    }
    SCC sccSolver;
    auto scc = sccSolver.Solve(g);
    vector<vector<int>> res(sccSolver.scc_count);
    for (int u = 0; u < V; ++u) {
        res[scc[u]].push_back(u+1);
    }
    for (auto x: res) {
        sort(x.begin(), x.end());
    }
    sort(res.begin(), res.end());
    printf("%lu\n", res.size());
    for (auto x: res) {
        for (int u: x) {
            printf("%d ", u);
        }
        printf("-1\n");
    }
    return 0;
}
