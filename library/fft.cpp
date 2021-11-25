// FFT
// Convolution
// polynomial multiplication
// Examples:
//  * https://www.acmicpc.net/problem/1067
//  * https://www.acmicpc.net/problem/17134

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// https://www.codetd.com/en/article/6915059
// MOD, G
// 469762049, 3
// 998244353, 3
// 1004535809, 3
// 2013265921, 31
// 2281701377, 3

const i64 MOD = 469762049;
const int G = 3;

int mpow(int a, int r) {
    if (r == 0) return 1;
    if (r == 1) return a;
    i64 res = mpow(a, r / 2);
    res = (res * res) % MOD;
    if (r & 1) res = (res * a) % MOD;
    return (int)res;
}

void trim(vector<int>& a) {
    while (a.size() > 0 && a.back() == 0) a.pop_back();
}

struct FFT {
    FFT(int n) : n(n), l(n) {
        int lg = 0;
        for (int i = 1; i < n; i <<= 1) {
            lg++;
        }
        for(int i = 0; i < n; i++) {
            l[i] = (l[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        }
    }

    vector<int> fft(const vector<int>& a, bool inverse = false) {
        vector<int> r(n);
        for (int i = 0; i < a.size(); ++i) {
            r[i] = (a[i] + MOD) % MOD;
        }
        for(int i = 0 ; i < n; ++i) {
            if (i < l[i]) {
                swap(r[i], r[l[i]]);
            }
        }
        int base = inverse ? mpow(G, MOD - 2) : G;
        for (int len = 1; len < n; len <<= 1) {
            i64 p = mpow(base, (MOD / len) >> 1);
            for (int i = 0; i < n; i += len << 1) {
                i64 w = 1;
                for (int j = 0; j < len; ++j) {
                    i64 L = r[i + j];
                    i64 R = r[i + j + len] * w % MOD;
                    r[i + j] = (L + R) % MOD;
                    r[i + j + len] = (L - R + MOD) % MOD;
                    w = w * p % MOD;
                }
            }
        }
        if (inverse) {
            i64 inv = mpow(n, MOD - 2);
            for (int i = 0; i < n; i++) r[i] = (r[i] * inv) % MOD;
        }
        return r;
    }

    int n;
    vector<int> l;
};

// (f*g)(m) = sigma (1 <= k <= m) f(k)g(m-k)
struct FFTMultiplier {    
    vector<int> multiply(vector<int>& a, vector<int>& b) {
        int n = 1;
        int len = max(a.size(), b.size());
        while (n <= len) n *= 2;
        n *= 2;

        FFT fft(n);
        vector<int> u = fft.fft(a);
        vector<int> v = fft.fft(b);

        vector<int> y(n);
        for (int i = 0; i < n; i++) {
            y[i] = ((i64)u[i] * v[i]) % MOD;
        }

        vector<int> ans = fft.fft(y, true);
        trim(ans);
        return ans;
    }
};
