// acmicpc 1786
//
// string matching
// kmp

#include <bits/stdc++.h>
using namespace std;

vector<int> kmpPrefixSufix(const string& str)
{
    int n = str.size();
    vector<int> pi(n, 0);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && str[i] != str[j]) {
            j = pi[j-1];
        }
        if (str[i] == str[j]) {
            pi[i] = ++j;
        } else {
            pi[i] = j;
        }
    }
    return pi;
}

vector<int> kmpMatch(const string& str, const string& pattern)
{
    int n = str.size();
    int m = pattern.size();
    vector<int> pi = kmpPrefixSufix(pattern);
    vector<int> res;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && str[i] != pattern[j]) {
            j = pi[j-1];
        }
        if (str[i] == pattern[j]) {
            ++j;
            if (j == m) {
                res.push_back(i-m+1);
                j = pi[j-1];
            }
        }
    }
    return res;
}

int main() {
    string T, P;
    getline(cin, T);
    getline(cin, P);
    auto matches = kmpMatch(T, P);
    cout << matches.size() << endl;
    for (int idx: matches) {
        cout << idx + 1 << " ";
    }
    cout << endl;
    return 0;
}
