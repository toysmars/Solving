// merge sort tree
// 머지 소트 트리

#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    MergeSortTree(const vector<int>& arr) {
        sz = arr.size();
        tree.resize(4 * sz);
        init(1, 1, sz, arr);
    }

    // queryKind: 1 => get the number of elements > k in [ql, qr).
    // queryKind: 2 => get the number of elements >= k in [ql, qr).
    // queryKind: 3 => get the number of elements <= k in [ql, qr).
    // queryKind: 4 => get the number of elements < k in [ql, qr).
    int query(int ql, int qr, int k, int queryKind) {
        return query(1, ql, qr, 1, sz, k, queryKind);
    }

    int sz;
    vector<vector<int>> tree;

private:
    vector<int>& init(int idx, int l, int r, const vector<int>& arr) {
        vector<int>& cur = tree[idx];
        int len = r - l;
        if (len == 1) {
            cur.push_back(arr[l]);
            return cur;
        }
        auto& lt = init(idx * 2, l, l + len / 2, arr);
        auto& rt = init(idx * 2 + 1, l + len / 2, r, arr);
        cur.resize(lt.size() + rt.size());
        merge(lt.begin(), lt.end(), rt.begin(), rt.end(), cur.begin());
        return cur;
    }

    int query(int idx, int ql, int qr, int l, int r, int k, int queryKind) {
        if (l >= qr || r <= ql || l >= r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            switch (queryKind) {
                case 1: return tree[idx].end() - upper_bound(tree[idx].begin(), tree[idx].end(), k);
                case 2: return tree[idx].end() - lower_bound(tree[idx].begin(), tree[idx].end(), k);
                case 3: return upper_bound(tree[idx].begin(), tree[idx].end(), k) - tree[idx].begin();
                case 4: return lower_bound(tree[idx].begin(), tree[idx].end(), k) - tree[idx].begin();
                default: return 0;
            }

        }
        int len = r - l;
        int res1 = query(idx * 2, ql, qr, l, l + len / 2, k, queryKind);
        int res2 = query(idx * 2 + 1, ql, qr, l + len / 2, r, k, queryKind);
        return res1 + res2;
    }
};

int findKth(int a, int b, int k, MergeSortTree& mst) {
    int lb = 1;
    int ub = 10000;
    int ans = 1;
    while (lb <= ub) {
        int t = (lb + ub) / 2;
        int lessThanT = mst.query(a, b, t, 4);
        if (lessThanT < k) {
            ans = t;
            lb = t + 1;
        } else {
            ub = t - 1;
        }
    }
    return ans;
}

int count(int a, int b, int x, MergeSortTree& mst) {
    return b - a - mst.query(a, b, x, 1) - mst.query(a, b, x, 4);
}
