// acmicpc 13034
//
// game theory
// nim game
// grundy number
// mex

#include <bits/stdc++.h>
using namespace std;

int dp[1001];
int mex(int x) {
    int a = 0;
    int b = x - 2;
    bool have[16] = {0};
    while (a <= b) {
        // grundy numbe G(g) of game g = {a, b, c} is G(g) = G(a)^G(b)^G(c)
        int g = dp[a] ^ dp[b];
        have[g] = true;
        a++;
        b--;
    }
    // mex of game g is a smallest number (>=0) that is not included in G of possible next states.
    for (int i = 0; i < 16; ++i) {
        if (!have[i]) {
            return i;
        }
    }
    return -1;
}

int main() {
    dp[0] = dp[1] = 0;
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        dp[i] = mex(i);
    }
    printf("%d\n", dp[n] ? 1 : 2);
    return 0;
}
