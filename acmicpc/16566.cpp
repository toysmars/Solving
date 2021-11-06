// acmicpc 16566
//
// disjoint set and binary search

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
	DisjointSet(int size) : p(size) {
		for (int i = 0; i < size; ++i) p[i] = i;
	}

	int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}

    // Does not apply rank optimization for using disjoint set with binary search.
	void join(int x, int y) {
		int px = find(x);
		int py = find(y);
		if (px != py) {
            p[py] = px;
		}
	}

	vector<int> p;
};

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<int> deck;
    deck.push_back(0);
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        deck.push_back(x);
    }
    sort(deck.begin(), deck.end());
    DisjointSet ds(n + 1);

    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        int lb = 1;
        int ub = m;
        int pos = 0;
        while (lb <= ub) {
            int t = (lb + ub) / 2;
            if (x < ds.find(deck[t])) {
                ub = t - 1;
                pos = t;
            } else {
                lb = t + 1;
            }
        }
        printf("%d\n", ds.find(deck[pos]));
        ds.join(deck[pos - 1], deck[pos]);
    }
    return 0;
}
