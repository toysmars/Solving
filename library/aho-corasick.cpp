// aho-corasick solver
// Examples:
//  * https://www.acmicpc.net/problem/2809
//  * https://www.acmicpc.net/problem/9250
//  * https://www.acmicpc.net/problem/10256

#include <bits/stdc++.h>
using namespace std;

typedef char trie_val_t;
typedef string val_t;
typedef int trie_node_id_t;

struct TrieNode {
    int depth = 0;
    bool complete = false;
    trie_node_id_t suffix_link = 0;
    trie_node_id_t output_link = 0;
    map<trie_val_t, int> children_at;
};

struct AhoCorasic {
    AhoCorasic() {
        trie.push_back({ 0 });
    }
    void insert(const val_t& pattern) {
        trie_node_id_t curr = 0;
        for (auto p: pattern) {
            if (trie[curr].children_at[p] == 0) {
                trie[curr].children_at[p] = trie.size();
                trie.push_back({ trie[curr].depth + 1 });
            }
            curr = trie[curr].children_at[p];
        }
        trie[curr].complete = true;
    }

    void build() {
        queue<trie_node_id_t> q;
        q.push(0);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            for (auto item: trie[curr].children_at) {
                auto letter = item.first;
                auto next = item.second;
                if (curr == 0) {
                    trie[next].suffix_link = 0;
                } else {
                    auto prev = trie[curr].suffix_link;
                    while (prev > 0 && trie[prev].children_at[letter] == 0) {
                        prev = trie[prev].suffix_link;
                    }
                    if (trie[prev].children_at[letter]) {
                        prev = trie[prev].children_at[letter];
                    }
                    trie[next].suffix_link = prev;
                }
                int suffix = trie[next].suffix_link;
                if (!trie[next].complete && trie[suffix].complete) {
                    trie[next].complete = true;
                    trie[next].output_link = trie[suffix].output_link == 0 ? suffix : trie[suffix].output_link;
                }
                q.push(next);
            }
        }
    }

    vector<pair<int, int>> findMatch(const val_t& text) {
        vector<pair<int, int>> ans;
        trie_node_id_t curr = 0;
        for (int i = 0; i < text.size(); ++i) {
            auto t = text[i];
            while (curr > 0 && trie[curr].children_at[t] == 0)
                curr = trie[curr].suffix_link;
            curr = trie[curr].children_at[t];
            if (trie[curr].complete) {
                trie_node_id_t output = trie[curr].output_link == 0 ? curr : trie[curr].output_link;
                ans.push_back({ i - trie[output].depth + 1, i });
            }
        }
        return ans;
    }

    vector<TrieNode> trie;
};
