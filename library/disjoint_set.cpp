#include <bits/stdc++.h>
using namespace std;

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
