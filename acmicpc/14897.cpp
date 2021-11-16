// acmicpc 14897
//
// merge sort tree
// distinct elements

#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    // Construct merge sort segment tree based on the input `arr`.
    // Please note that the `arr` should be 1-based indexing.
    MergeSortTree(const vector<int>& arr) {
        sz = arr.size();
        tree.resize(4 * sz);
        init(1, 1, sz, arr);
    }

    // Executes the query in range [ql, qr) with given value `k`.
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

// Given arry arr, Let next[i] be the index where arr[i] appears again.
// The number of distinct element in arr[l..r) equals to the number of
//  elements in that range where the next[k] > r (l <= k < r)
int main() {
    int n;
    scanf("%d", &n);
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    map<int, int> mnext;
    vector<int> vnext(n + 1);
    for (int i = n; i > 0; --i) {
        vnext[i] = mnext[arr[i]];
        if (vnext[i] == 0) {
            vnext[i] = n + 2;
        }
        mnext[arr[i]] = i;
    }
    MergeSortTree mst(vnext);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", mst.query(a, b + 1, b));
    }
    return 0;
}
