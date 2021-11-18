// https://www.acmicpc.net/problem/14216
//
// complete bipartite assignment
// hungarian

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <queue>
#include <algorithm>
#include <memory.h>
using namespace std;

const int INF = 1000000000;
int n;
int cost[501][501];

int solve() {
    int res = 0;
    vector<int> um(n, -1);
    vector<int> vm(n, -1);
    for (int s = 0; s < n; ++s) {
        vector<int> udist(n, INF);
        vector<int> vdist(n, INF);
        vector<int> up(n, -1);
        vector<int> vp(n, -1);
        vector<bool> inqueue(n);
        queue<int> q;
        udist[s] = 0;
        q.push(s);
        inqueue[s] = true;
        int minv = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inqueue[u] = false;
            for (int v = 0; v < n; ++v) {
                if (um[u] == v) continue;
                if (vdist[v] > udist[u] + cost[u][v]) {
                    vdist[v] = udist[u] + cost[u][v];
                    vp[v] = u;
                    if (vm[v] == -1) {
                        if (minv == -1 || vdist[v] < vdist[minv]) {
                            minv = v;
                        }
                    } else {
                        if (udist[vm[v]] > vdist[v] - cost[vm[v]][v]) {
                            udist[vm[v]] = vdist[v] - cost[vm[v]][v];
                            up[vm[v]] = v;
                            if (!inqueue[vm[v]]) {
                                q.push(vm[v]);
                                inqueue[vm[v]] = true;
                            }
                        }
                    }
                }
            }
        }
        int tv = minv;
        res += vdist[minv];
        while (true) {
            int tu = vp[tv];
            um[tu] = tv;
            vm[tv] = tu;
            if (tu == s) break;
            tv = up[tu];
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }
    printf("%d\n", solve());
    return 0;
}

