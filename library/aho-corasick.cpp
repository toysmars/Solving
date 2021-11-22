#include <bits/stdc++.h>
using namespace std;

typedef char trie_val_t;
typedef string val_t;
typedef int trie_node_id_t;

struct TrieNode {
    TrieNode(trie_val_t val, trie_node_id_t parent) : val(val), parent(parent) {}
    trie_val_t val;
    trie_node_id_t parent;
    bool complete = false;
    trie_node_id_t suffix_link = 0;
    map<trie_val_t, int> children_at;
};

struct AhoCorasic {
    AhoCorasic() {
        trie.push_back(TrieNode(0, -1));
    }
    void insert(const val_t& pattern) {
        trie_node_id_t curr = 0;
        for (auto p: pattern) {
            if (trie[curr].children_at[p] == 0) {
                trie[curr].children_at[p] = trie.size();
                trie.push_back(TrieNode(p, curr));
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
                if (trie[trie[next].suffix_link].complete) {
                    trie[next].complete = true;
                }
                q.push(next);
            }
        }
    }

    vector<pair<int, int>> findMatch(const val_t& text) {
        vector<pair<int, int>> ans;
        trie_node_id_t curr = 0;
        int n = text.length();
        for (int i = 0; i < text.size(); ++i) {
            auto t = text[i];
            while (curr > 0 && trie[curr].children_at[t] == 0)
                curr = trie[curr].suffix_link;
            curr = trie[curr].children_at[t];
            if (trie[curr].complete) {
                ans.push_back({ curr, i });
            }
        }
        return ans;
    }

    val_t value_of(trie_node_id_t idx) {
        val_t ans;
        while (idx > 0) {
            ans.push_back(trie[idx].val);
            idx = trie[idx].parent;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    vector<TrieNode> trie;
};
