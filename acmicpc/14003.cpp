// acmicpc 14003
//
// lis
// longest increasing subsequence

#include<bits/stdc++.h>
using namespace std;

vector<int> lis(vector<int>& v) {
    vector<int> p(v.size());
    vector<int> m(v.size() + 1);
    int len = 0;
    for (int i = 0; i < v.size(); ++i) {
        int lb = 1;
        int ub = len;
        while (lb <= ub) {
            int t = (lb + ub) / 2;
            if (v[m[t]] < v[i]) {
                lb = t + 1;
            } else {
                ub = t - 1;
            }
        }
        p[i] = m[lb - 1];
        m[lb] = i;
        if (lb > len) {
            len = lb;
        }
    }
    vector<int> ans;
    for (int i = len - 1, k = m[len]; i >= 0; --i) {
        ans.push_back(v[k]);
        k = p[k];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> v;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    vector<int> res = lis(v);
    printf("%lu\n", res.size());
    for (int i = 0; i < res.size(); ++i) {
        if (i) printf(" ");
        printf("%d", res[i]);
    }
    printf("\n");
    return 0;
}
