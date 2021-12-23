// acmicpc 13977
//
// 정수론
// 모듈로 곱셈 역원 (페르마 소정리)
// 이항계수

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int MOD = 1000000007;
const int MAX_N = 4000000;

// Calculates a^r mod m
int mod_pow(int a, int r, int m) {
    if (r == 0) return 1;
    if (r == 1) return a;
    i64 x = mod_pow(a, r / 2, m);
    x = x * x % m;
    if (r % 2) {
        x = x * a % m;
    }
    return x;
}

// Calculates n! mod m
int Fac[MAX_N + 1];
int mod_fac(int n, int m) {
    int& f = Fac[n];
    if (f != -1) return f;
    if (n == 0 || n == 1) return f = 1;
    return f = (i64)n * mod_fac(n - 1, m) % m;
}

// Calculates n choose k (binomial coefficient) mod m
// This function works only when the given m is a prime number.
int mod_nCk(int n, int k, int m) {
    i64 nu = mod_fac(n, m);
    i64 de = (i64)mod_fac(n - k, m) * mod_fac(k, m) % m;
    i64 de_inv = mod_pow(de, m - 2, m);
    return nu * de_inv % m;
}

int main() {
    int m;
    scanf("%d", &m);
    memset(Fac, -1, sizeof(Fac));
    for (int i = 0; i < m; ++i) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", mod_nCk(n, k, MOD));
    }
    return 0;
}
