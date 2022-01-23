// acmicpc 11717
//
// Game Theory
// Grundy Numbers
// Mex

#include <bits/stdc++.h>
using namespace std;

int H, W;
char B[21][21];
int dp[21][21][21][21];

int mex(int y1, int x1, int y2, int x2) {
    int h = y2 - y1 + 1;
    int w = x2 - x1 + 1;
    if (h <= 0 || w <= 0) return 0;
    int& res = dp[y1][x1][y2][x2];
    if (res != -1) return res;

    bool have[64] = {0};
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            if (B[y][x] == 'X') continue;
            int g = mex(y1, x1, y-1, x-1) ^ mex(y1, x+1, y-1, x2) ^ mex(y+1, x1, y2, x-1) ^ mex(y+1, x+1, y2, x2);
            have[g] = true;
        }
    }
    for (int i = 0; i < 64; ++i) {
        if (!have[i]) {
            res = i;
            return i;
        }
    }
    exit(1);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int H, W;
    scanf("%d%d", &H, &W);
    for (int i = 0; i < H; ++i) {
        scanf("%s", B[i]);
    }
    int ans = mex(0, 0, H-1, W-1);
    printf("%s\n", ans ? "First" : "Second");
    return 0;
}
