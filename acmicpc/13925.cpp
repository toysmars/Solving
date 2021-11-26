// acmicpc 13925
// segment tree with lazy propagation

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 val_t;

const int MOD = 1000000007;

const int OpAdd = 1;
const int OpMul = 2;
const int OpSet = 3;

val_t modpow(val_t a, int r, int mod) {
    if (r == 0) return 1;
    if (r == 1) return a;
    val_t res = modpow(a, r / 2, mod);
    if (r & 1) {
        res = res * a % mod;
    }
    res = res * res % mod;
    return res;
}

struct SegmentTree {
    SegmentTree(int n) : n(n), t(4 * n + 1, 0), lz_sum(4 * n + 1), lz_mul(4 * n + 1, 1) {}

    // update the segment tree with value x for range [ul, ur)
    void update(int ul, int ur, val_t x, int op) {
        update(ul, ur, x, 1, 1, n + 1, op);
    }
    val_t update(int ul, int ur, val_t x, int idx, int l, int r, int op) {
        propagate(idx, l, r);
        if (l >= ur || r <= ul || l >= r) {
            return t[idx];
        }
        if (ul <= l && r <= ur) {
            if (op == OpAdd) lz_sum[idx] += x;
            if (op == OpMul) lz_sum[idx] = (lz_sum[idx] * x) % MOD, lz_mul[idx] = (lz_mul[idx] * x) % MOD;
            if (op == OpSet) lz_sum[idx] = x, lz_mul[idx] = 0;
            propagate(idx, l, r);
            return t[idx];
        }
        int len = r - l;
        val_t res1 = update(ul, ur, x, idx * 2 + 0, l, l + len / 2, op);
        val_t res2 = update(ul, ur, x, idx * 2 + 1, l + len / 2, r, op);
        t[idx] = (res1 + res2) % MOD;
        return t[idx];
    }

    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        propagate(idx, l, r);
        if (l >= qr || r <= ql || l >= r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return (res1 + res2) % MOD;
    }

    void propagate(int idx, int l, int r) {
        if (lz_mul[idx] == 1 && lz_sum[idx] == 0) {
            return;
        }
        int len = r - l;
        if (len > 1) {
            lz_mul[idx * 2] = (lz_mul[idx * 2] * lz_mul[idx]) % MOD;
            lz_mul[idx * 2 + 1] = (lz_mul[idx * 2 + 1] * lz_mul[idx]) % MOD;
            lz_sum[idx * 2] = (lz_sum[idx * 2] * lz_mul[idx] + lz_sum[idx]) % MOD;
            lz_sum[idx * 2 + 1] = (lz_sum[idx * 2 + 1] * lz_mul[idx] + lz_sum[idx]) % MOD;
        }
        t[idx] = (t[idx] * lz_mul[idx] + len * lz_sum[idx]) % MOD;
        lz_mul[idx] = 1;
        lz_sum[idx] = 0;
    }

    int n;
    vector<val_t> t;
    vector<val_t> lz_sum;
    vector<val_t> lz_mul;
};

int main() {
    int n, m;
    scanf("%d", &n);
    SegmentTree st(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        st.update(i, i + 1, x, OpSet);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int q, l, r, x;
        scanf("%d%d%d", &q, &l, &r);
        if (q <= 3) {
            scanf("%d", &x);
            st.update(l, r + 1, x, q);
        } else {
            printf("%lld\n", st.query(l, r + 1));
        }
    }
    return 0;
}
