// acmicpc 2239
//
// sudoku

#include <bits/stdc++.h>
using namespace std;

char A[9][10];
int Y[81];
int X[81];
int N;
int Row[9];
int Col[9];
int Box[9];

int box_index(int y, int x) {
    return y / 3 * 3 + x / 3;
}

bool go(int k) {
    if (k == N) return true;
    int y = Y[k];
    int x = X[k];
    for (int i = 1; i <= 9; ++i) {
        int bit = (1<<i);
        if (Row[y] & bit) continue;
        if (Col[x] & bit) continue;
        if (Box[(box_index(y, x))] & bit) continue;
        Row[y] |= bit;
        Col[x] |= bit;
        Box[box_index(y, x)] |= bit;
        A[y][x] = '0' + i;
        if (go(k + 1)) return true;
        Row[y] &= ~bit;
        Col[x] &= ~bit;
        Box[box_index(y, x)] &= ~bit;
    }
    return false;
}

int main() {
    for (int i = 0; i < 9; ++i) {
        scanf("%s", A[i]);
        for (int j = 0; j < 9; ++j) {
            int n = A[i][j] - '0';
            if (n == 0) {
                Y[N] = i;
                X[N] = j;
                N++;
            }
            int bit = (1<<n);
            Row[i] |= bit;
            Col[j] |= bit;
            Box[box_index(i, j)] |= bit;
        }
    }
    go(0);
    for (int i = 0; i < 9; ++i) {
        printf("%s\n", A[i]);
    }
    return 0;
}
