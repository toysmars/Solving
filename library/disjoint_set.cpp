class DisjointSet {
public:
    DisjointSet(int n) {
        for (int i = 0; i < n; ++i) {
            s.push_back(i);
            r.push_back(0);
        }
    }
    int findSet(int x) {
        if (s[x] != x) {
            s[x] = findSet(s[x]);
        }
        return s[x];
    }
    void unionSet(int x, int y) {
        int sx = findSet(x);
        int sy = findSet(y);
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
private:
    vector<int> s;
    vector<int> r;
};
