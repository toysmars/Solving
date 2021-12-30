// Matrix multiplication and power
// 행렬 거듭제곱
//
// Examples
// * https://www.acmicpc.net/problem/11444

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

typedef vector<i64> Vector;
typedef vector<Vector> Matrix;

Matrix identical(int n) {
    Matrix I(n, Vector(n));
    for (int i = 0; i < n; ++i) I[i][i] = 1;
    return I;
}

Matrix matrix_mul(Matrix& a, Matrix& b, int mod) {
    int n = a.size();
    Matrix r(n, Vector(n));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            for (int k = 0; k < a.size(); ++k) {
                r[i][j] += (a[i][k] * b[k][j]) % mod;
                r[i][j] %= mod;
            }
        }
    }
    return r;
}

Matrix matrix_pow(Matrix& m, i64 p, int mod) {
    static Matrix I = identical(m.size());
    if (p == 0) return I;
    if (p == 1) return m;
    Matrix r = matrix_pow(m, p / 2, mod);
    r = matrix_mul(r, r, mod);
    if (p % 2) {
        r = matrix_mul(r, m, mod);
    }
    return r;
}
