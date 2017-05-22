// https://www.hackerrank.com/contests/w32/challenges/geometric-trick
// prime number
// sieve
// factors
// factorize
// divisors

#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long i64;

const int MAXN = 500000;

char S[MAXN + 1];

vector<pair<i64, i64>> factorize(int n, const vector<i64>& factors) {
    vector<pair<i64, i64>> res;
    while (n > 1) {
        i64 factor = factors[n];
        i64 count = 0;
        while (n % factor == 0) {
            n /= factor;
            count += 1;
        }
        res.push_back(make_pair(factor, count));
    }
    return res;
}

void divisors(int k, i64 x, const vector<pair<i64, i64>>& fp, vector<i64>& res) {
    if (k == fp.size()) {
        res.push_back(x);
    } else {
        i64 m = 1;
        for (int i = 0; i <= 2 * fp[k].second; ++i) {
            divisors(k + 1, x * m, fp, res);
            m *= fp[k].first;
        }
    }
}
vector<i64> divisors(int n, const vector<i64>& factors) {
    vector<i64> res;
    divisors(0, 1, factorize(n, factors), res);
    return res;
}

int main() {
    int n;
    scanf("%d%s", &n, S);
    vector<i64> factors(n + 1);
    factors[0] = factors[1] = 1;
    for (i64 i = 2; i <= n; ++i) {
        if (factors[i] == 0) {
            factors[i] = i;
            for (i64 j = i * i; j <= n; j += i) {
                if (factors[j] == 0) {
                    factors[j] = i;  
                }
            }
        }
    }
    int ans = 0;
    for (i64 b = 1; b < n; ++b) {
        if (S[b] == 'b') {
            i64 b1 = b + 1;
            auto ds = divisors(b1, factors);
            for (i64 a1 : ds) {
                i64 c1 = b1 * b1 / a1;
                i64 a = a1 - 1;
                i64 c = c1 - 1;
                if (a < n && c < n && S[a] == 'a' && S[c] == 'c') {
                    ans += 1;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
