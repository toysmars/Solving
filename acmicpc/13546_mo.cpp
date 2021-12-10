// acmicpc 13546
//
// mo's 
// square root decomposition

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;
const int MAX_K = 100000;
const int MAX_M = 100000;
const int RT = 700;

struct Query {
    int id, l, r;
    bool operator<(const Query &b) const {
        int arb = r / RT;
        int brb = b.r / RT;
        return arb == brb ? l < b.l : arb < brb;
    }
};

int N, K, M;
int A[MAX_N + 1];
Query Q[MAX_M];
int Ans[MAX_M];
list<int> S[MAX_K + 1];

const int BSIZE = MAX_N / RT + 10;
int C[MAX_N + 1];
int B[BSIZE];

void push(int d) {
    C[d]++;
    B[d/RT]++;
}
void pop(int d) {
    C[d]--;
    B[d/RT]--;
}
int query() {
    for (int i = BSIZE - 1; i >= 0; --i) {
        if (B[i] == 0) continue;
        for (int j = 0, k = min(MAX_N, i * RT + RT - 1); j < RT; --j, --k) {
            if (C[k] > 0) {
                return k;
            }
        }
    }
    return 0;
}

void push_front(int x, int pos) {
    if (!S[x].empty()) {
        pop(S[x].back() - S[x].front());
    }
    S[x].push_front(pos);
    push(S[x].back() - S[x].front());
}
void pop_front(int x, int pos) {
    auto& s = S[x];
    pop(S[x].back() - S[x].front());
    S[x].pop_front();
    if (!S[x].empty()) {
        push(S[x].back() - S[x].front());
    }
}
void push_back(int x, int pos) {
    if (!S[x].empty()) {
        pop(S[x].back() - S[x].front());
    }
    S[x].push_back(pos);
    push(S[x].back() - S[x].front());
}
void pop_back(int x, int pos) {
    pop(S[x].back() - S[x].front());
    S[x].pop_back();
    if (!S[x].empty()) {
        push(S[x].back() - S[x].front());
    }
}

int main() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
        Q[i].r += 1;
    }
    sort(&Q[0], &Q[M]);
    int i = 0;
    int j = 0;
    for (int qi = 0; qi < M; ++qi) {
        int id = Q[qi].id;
        int l = Q[qi].l;
        int r = Q[qi].r;
        while (j < r) { push_back(A[j], j); j++; }
        while (j > r) { --j; pop_back(A[j], j); }
        while (i < l) { pop_front(A[i], i); i++; }
        while (i > l) { --i; push_front(A[i], i); }
        Ans[id] = query();
    }
    for (int i = 0; i < M; ++i) {
        printf("%d\n", Ans[i]);
    }
    return 0;
}
