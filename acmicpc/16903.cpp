// acmicpc 16903
//
// trie
// xor 최적화

#include <bits/stdc++.h>
using namespace std;

typedef int node_id_t;
struct Node {
    int x;
    int cnt;
    node_id_t l;
    node_id_t r;
};

struct Trie {
    Trie() {
        trie.push_back({-1, 0, -1, -1});
    }
    void add(int x, int inc) {
        node_id_t nid = 0;
        for (int b = 31; b >= 0; --b) {
            int v = x & (1<<b);
            if (v == 0) {
                if (trie[nid].l == -1) {
                    trie[nid].l = trie.size();
                    trie.push_back({0, 0, -1, -1});
                }
                nid = trie[nid].l;
                trie[nid].cnt += inc;
            } else {
               if (trie[nid].r == -1) {
                    trie[nid].r = trie.size();
                    trie.push_back({1, 0, -1, -1});
                }
                nid = trie[nid].r;
                trie[nid].cnt += inc;
            }
        }
    }
    int query(int x) {
        node_id_t nid = 0;
        int ans = 0;
        for (int b = 31; b >= 0; --b) {
            int v = (x & (1<<b)) > 0;
            ans <<= 1;
            if (trie[nid].r == -1 || trie[trie[nid].r].cnt <= 0) {
                nid = trie[nid].l;
                ans |= v;
            } else if (trie[nid].l == -1 || trie[trie[nid].l].cnt <= 0) {
                nid = trie[nid].r;
                ans |= v^1;
            } else if (v == 0) {
                nid = trie[nid].r;
                ans |= 1;
            } else {
                nid = trie[nid].l;
                ans |= 1;
            }
        }
        return ans;
    }

    vector<Node> trie;
};

int main() {
    int m;
    scanf("%d", &m);
    Trie trie;
    trie.add(0, 1);
    for (int i = 0; i < m; ++i) {
        int q, x;
        scanf("%d%d", &q, &x);
        switch (q) {
            case 1: trie.add(x, 1); break;
            case 2: trie.add(x, -1); break;
            case 3: printf("%d\n", trie.query(x));
        }
    }
    return 0;
}
