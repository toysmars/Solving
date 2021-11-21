// acmicpc 16877
//
// game theory
// nim game
// grundy number
// mex

#include <bits/stdc++.h>
using namespace std;

const int N_FIBS = 31;
const int MAX_P = 3000000;
const int MAX_N = 100000;

int fibs[N_FIBS];
int mex[MAX_P + 1];

int main() {
    fibs[0] = 1;
    fibs[1] = 2;
    for (int fi = 2; fi < N_FIBS; ++fi) {
        fibs[fi] = fibs[fi-1] + fibs[fi-2];
    }
    mex[0] = 0;
    for (int p = 1; p <= MAX_P; ++p) {
        bool have[16] = {false};
        for (int fi = 0; fi < N_FIBS && fibs[fi] <= p; ++fi) {
            have[mex[p - fibs[fi]]] = true;
        }
        for (int i = 0; i < 16; ++i) {
            if (!have[i]) {
                mex[p] = i;
                break;
            }
        }
    }
    int n, gn = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        gn ^= mex[x];
    }
    printf("%s\n", gn ? "koosaga" : "cubelover");

    return 0;
}
