// acmicpc 1657
//
// minimum spanning tree
// mst
// kruskal

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
	DisjointSet(int size) : p(size), r(size) {
		for (int i = 0; i < size; ++i) p[i] = i;
	}

	int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}

	void join(int x, int y) {
		int xp = find(x);
		int yp = find(y);
		if (xp != yp) {
			if (r[xp] < r[yp]) p[xp] = yp;
			else if (r[xp] > r[yp]) p[yp] = xp;
			else { p[yp] = xp; r[xp]++; }
		}
	}

	vector<int> p;
	vector<int> r;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<tuple<int, int, int>> es;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        es.emplace_back(w, u-1, v-1);
    }
    sort(es.begin(), es.end());
    DisjointSet ds(n);
    int sum = 0;
    int max_w = 0;
    for (auto e: es) {
        int w = get<0>(e);
        int u = get<1>(e);
        int v = get<2>(e);
        if (ds.find(u) != ds.find(v)) {
            ds.join(u, v);
            sum += w;
            max_w = max(max_w, w);
        }
    }
    printf("%d\n", sum - max_w);
    return 0;
}
