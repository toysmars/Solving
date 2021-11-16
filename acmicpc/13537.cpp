// acmicpc 13537
//
// merge sort tree

#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    MergeSortTree(const vector<int>& arr) {
        sz = arr.size();
        tree.resize(4 * sz);
        init(1, 1, sz, arr);
    }

    int query(int ql, int qr, int k) {
        return query(1, ql, qr, 1, sz, k);
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

    int query(int idx, int ql, int qr, int l, int r, int k) {
        if (l >= qr || r <= ql || l >= r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[idx].end() - upper_bound(tree[idx].begin(), tree[idx].end(), k);
        }
        int len = r - l;
        int res1 = query(idx * 2, ql, qr, l, l + len / 2, k);
        int res2 = query(idx * 2 + 1, ql, qr, l + len / 2, r, k);
        return res1 + res2;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    MergeSortTree msst(arr);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", msst.query(l, r + 1, k));
    }
    return 0;
}
