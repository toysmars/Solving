// acmicpc 19585
//
// trie

#include <bits/stdc++.h>
using namespace std;

char name[2001];
bool isColor[2001];
bool isNick[2001];

struct TrieNode {
    bool complete = false;
    map<char, int> childrenAt;
};

class Trie {
public:
    Trie() {
        nodes.push_back(TrieNode());
        nodes.push_back(TrieNode());
    }
    void add(int root, const char s[]) {
        int curr = root;
        for (int i = 0; s[i]; ++i) {
            if (nodes[curr].childrenAt[s[i]] == 0) {
                nodes[curr].childrenAt[s[i]] = nodes.size();
                nodes.push_back(TrieNode());
            }
            curr = nodes[curr].childrenAt[s[i]];
        }
        nodes[curr].complete = true;
    }
    vector<TrieNode> nodes;
};

bool isLegend(Trie& trie, char name[]) {
    memset(isColor, 0, sizeof(isColor));
    memset(isNick, 0, sizeof(isNick));
    int len = strlen(name);

    int curr = 0;
    for (int i = 0; i < len; ++i) {
        if (trie.nodes[curr].childrenAt[name[i] ] == 0) {
            break;
        }
        curr = trie.nodes[curr].childrenAt[name[i] ];
        isColor[i] = trie.nodes[curr].complete;
    }

    curr = 1;
    for (int i = len - 1 ; i >= 0; --i) {
        if (trie.nodes[curr].childrenAt[name[i] ] == 0) {
            break;
        }
        curr = trie.nodes[curr].childrenAt[name[i] ];
        isNick[i] = trie.nodes[curr].complete;
    }

    for (int i = 0; i < len; ++i) {
        if (isColor[i] && isNick[i + 1]) {
            return true;
        }
    }
    return false;
}


int main() {
    int C, N;
    scanf("%d%d", &C, &N);
    Trie trie;
    for (int i = 0; i < C; ++i) {
        scanf("%s", name);
        trie.add(0, name);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%s", name);
        int len = strlen(name);
        reverse(&name[0], &name[len]);
        trie.add(1, name);
    }
    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i) {
        scanf("%s", name);
        printf("%s\n", isLegend(trie, name) ? "Yes" : "No");
    }
    return 0;
}

