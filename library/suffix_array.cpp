// Suffix Array
// LCP
// Longest Common Prefix
//
// Examples:
// * https://www.acmicpc.net/problem/13576

#include <bits/stdc++.h>
using namespace std;

struct SuffixArraySolver {
    SuffixArraySolver(const string& str): str(str), pos(str.size()), rank(str.size()), lcp(str.size()) {}

    // Builds suffix array of given string `str`.
    // pos[i] is the index of string s.t. str[pos[i]...] is i_th suffix in lexicographical order.
    // rank[i] is suffix rank of str[i..]
    void Solve() {
        int n = str.size();
        vector<int> ord(n + 1);
        vector<int> nord(n + 1);
        vector<int> cnt(max(256, n + 1));
        vector<int> r(n + 1);

        // initialize pos
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
            ord[i] = str[i];
        }

        int h = 1;
        int done = 1;
        while (true) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i) cnt[ord[min(i + h, n)]]++;
            for (int i = 1; i <= n || i <= 255; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) r[--cnt[ord[min(i + h, n)]]] = i;
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i) cnt[ord[i]]++;
            for (int i = 1; i <= n || i <= 255; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) pos[--cnt[ord[r[i]]]] = r[i];
            if (done == n) {
                break;
            }
            done = 1;
            nord[pos[0]] = 1;
            for (int i = 1; i < n; ++i) {
                done += (ord[pos[i - 1]] != ord[pos[i]] || ord[pos[i - 1] + h] != ord[pos[i] + h]);
                nord[pos[i]] = done;
            }
            for (int i = 0; i < n; ++i) {
                ord[i] = nord[i];
            }
            h *= 2;
        }
        for (int i = 0; i < n; ++i) {
            rank[pos[i]] = i;
        }
    }

    // Builds LCP array. This method must be called after `Solve()`.
    // Longest Common Prefix is the longest prefix between two consecutive suffixes in the suffix array.
    // lcp[i] (i >= 1) is the length of common prefix of i-1_th suffix and i_th suffex.
    void SolveLCP() {
        int n = str.size();
        int len = 0;
        for (int i = 0; i < n; ++i) {
            int k = rank[i];
            if (k > 0) {
                int j = pos[k - 1];
                while (str[j + len] == str[i + len]) {
                    len += 1;
                }
                lcp[k] = len;
                len -= len > 0;
            }
        }
    }

    vector<int> pos;
    vector<int> rank;
    vector<int> lcp;
    string str;
};

