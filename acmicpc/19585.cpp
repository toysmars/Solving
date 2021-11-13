// acmicpc 19585
//
// trie

#include <bits/stdc++.h>
using namespace std;

char name[2001];
bool isColor[2001];
bool isNick[2001];

struct TrieNode {
    bool complete;
    map<char, TrieNode*> children;
};

class Trie {
public:
    Trie() {
        root = new TrieNode;
    }
    void add(const char s[]) {
        TrieNode* curr = root;
        for (int i = 0; s[i]; ++i) {
            if (curr->children.find(s[i]) == curr->children.end())  {
                curr->children[s[i]] = new TrieNode;
            }
            curr = curr->children[s[i]];
        }
        curr->complete = true;
    }
    TrieNode *root;
};

bool isLegend(Trie& colorTrie, Trie& nickTrie, char name[]) {
    memset(isColor, 0, sizeof(isColor));
    memset(isNick, 0, sizeof(isNick));

    int len = strlen(name);
    TrieNode* curr = colorTrie.root;
    for (int i = 0; i < len; ++i) {
        if (curr->children.find(name[i]) == curr->children.end()) {
            break;
        }
        curr = curr->children[name[i]];
        isColor[i] = curr->complete;
    }

    curr = nickTrie.root;
    for (int i = len - 1 ; i >= 0; --i) {
        if (curr->children.find(name[i]) == curr->children.end()) {
            break;
        }
        curr = curr->children[name[i]];
        isNick[i] = curr->complete;
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
    Trie colorTrie;
    for (int i = 0; i < C; ++i) {
        scanf("%s", name);
        colorTrie.add(name);
    }
    Trie nickTrie;
    for (int i = 0; i < N; ++i) {
        scanf("%s", name);
        int len = strlen(name);
        reverse(&name[0], &name[len]);
        nickTrie.add(name);
    }
    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i) {
        scanf("%s", name);
        printf("%s\n", isLegend(colorTrie, nickTrie, name) ? "Yes" : "No");
    }
    return 0;
}
