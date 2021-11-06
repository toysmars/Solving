// acmicpc 9252
//
// lcs
// longest common subsequence

#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001];
int p[1001][1001];
string lcs(string& a, string& b) {
    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            dp[i][j] = max({dp[i][j-1], dp[i-1][j], dp[i-1][j-1] + (a[i-1]==b[j-1])});
        }
    }
    string ans;
    int i = a.size();
    int j = b.size();
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            ans += a[i-1];
            i -= 1;
            j -= 1;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i -= 1;
        } else {
            j -= 1;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    string a, b;
    cin >> a >> b;
    string ans = lcs(a, b);
    cout << ans.size() << endl;
    if (ans.size() > 0) {
        cout << ans << endl;
    }
    return 0;
}
