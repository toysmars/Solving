// KMP
// Knuth Morris Pratt
// String matching
//
// Example
// * https://www.acmicpc.net/problem/14959

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
