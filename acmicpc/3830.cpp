// acmicpc 3830
//
// disjoint set with diff / distance / weight

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

class DisjointSet {
public:
	DisjointSet(int size) : p(size), diff(size) {
		for (int i = 0; i < size; ++i) p[i] = i;
	}

	pair<int, i64> find(int x) {
		if (p[x] != x) {
            auto res = find(p[x]);
            p[x] = res.first;
            diff[x] += res.second;
        }
		return make_pair(p[x], diff[x]);
	}

	void join(int x, int y, int w) {
		int xp = find(x).first;
		int yp = find(y).first;
		if (xp != yp) {
            p[yp] = xp;
            diff[yp] = diff[x] - diff[y] + w;
		}
	}

	vector<int> p;
    vector<i64> diff;
};

void solve(int n, int m) {
    DisjointSet ds(n);
    while (m--) {
        char cmd[2];
        int a, b, w;
        scanf("%s", cmd);
        if (*cmd == '!') {
            scanf("%d%d%d", &a, &b, &w);
            ds.join(a-1, b-1, w);
        } else {
            scanf("%d%d", &a, &b);
            auto resA = ds.find(a-1);
            auto resB = ds.find(b-1);
            if (resA.first != resB.first) {
                printf("UNKNOWN\n");
            } else {
                printf("%lld\n", -resA.second + resB.second);
            }
        }
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m)) {
        if (n == 0 && m == 0) {
            break;
        }
        solve(n, m);
    }
    return 0;
}
