// acmicpc 10266
//
// kmp

#include <bits/stdc++.h>
using namespace std;

typedef int elem_t;
struct KMP {
    vector<int> prefixSufix(const vector<elem_t>& pattern)
    {
        int n = pattern.size();
        vector<int> pi(n, 0);
        for (int i = 1, j = 0; i < n; ++i) {
            while (j > 0 && pattern[i] != pattern[j]) {
                j = pi[j-1];
            }
            if (pattern[i] == pattern[j]) {
                pi[i] = ++j;
            } else {
                pi[i] = j;
            }
        }
        return pi;
    }

    vector<int> match(const vector<elem_t>& source, const vector<elem_t>& pattern)
    {
        int n = source.size();
        int m = pattern.size();
        vector<int> pi = prefixSufix(pattern);
        vector<int> res;
        for (int i = 0, j = 0; i < n; ++i) {
            while (j > 0 && source[i] != pattern[j]) {
                j = pi[j-1];
            }
            if (source[i] == pattern[j]) {
                ++j;
                if (j == m) {
                    res.push_back(i-m+1);
                    j = pi[j-1];
                }
            }
        }
        return res;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    vector<int> b(n);
    vector<int> p(n);
    vector<int> s(2*n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 1; i < n; ++i) {
        p[i] = a[i] - a[i - 1];
        s[i] = s[i + n] = b[i] - b[i - 1];

    }
    p[0] = 360000 + a[0] - a[n - 1];
    s[0] = s[n] = 360000 + b[0] - b[n - 1];

    KMP kmp;
    auto res = kmp.match(s, p);
    printf("%s\n", res.size() > 0 ? "possible" : "impossible");
    return 0;
}
