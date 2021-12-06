// acmicpc 14959
//
// KMP
// Repeating string
// 반복 문자열

#include <bits/stdc++.h>
using namespace std;

vector<int> prefixSufix(const vector<int>& pattern)
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

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    reverse(a.begin(), a.end());
    auto p = prefixSufix(a);
    int mink = n - 1;
    int minp = 1;
    for (int k = 0; k < n; ++k) {
        int tk = (n - k - 1);
        int tp = (k - p[k] + 1);
        if (mink + minp > tk + tp) {
            mink = tk;
            minp = tp;
        }
        if (mink + minp == tk + tp && minp > tp) {
            mink = tk;
            minp = tp;
        }
    }
    printf("%d %d\n", mink, minp);
    return 0;
}
