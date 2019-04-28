class RMQ {
  public:
    RMQ(int _n) {
        n = _n;
        for (int i = 0; i <= 4 * n; ++i) {
            t.push_back(-1);
        }
    }
    void update(int i, int x) {
        update(i, x, 1, 1, n + 1);
    }
    int update(int i, int x, int idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return -1;
        }
        int len = r - l;
        if (len == 1) {
            t[idx] = x;
            return t[idx];
        }
        int res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        int res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = max(t[idx], max(res1, res2));
        return t[idx];
    }
    int query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    int query(int ql, int qr, int idx, int l, int r) {
        if (l >= qr || r <= ql || l >= r) {
            return -1;
        }
        if (ql <= l && qr >= r) {
            return t[idx];
        }
        int len = r - l;
        int res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        int res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return max(res1, res2);
    }
    int n;
    vector<int> t;
};
