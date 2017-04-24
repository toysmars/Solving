// https://www.acmicpc.net/problem/10942
// * palindrome
// * manacher

#include <vector>
#include <algorithm>
using namespace std;

// Manacher's algorithm
vector<int> manacher(const vector<int>& v)
{
	vector<int> s;
	if (v.size()) {
		s.push_back(-2);
		for_each(v.begin(), v.end(), [&s](int x) { s.push_back(-1); s.push_back(x); });
		s.push_back(-1);
		s.push_back(-3);
	} else {
		s.push_back(-2);
		s.push_back(-3);
	}
	int n = s.size();
	int c = 0, r = 0;
	vector<int> table(n);
	for (int i = 1; i < n-1; ++i) {
		int ii = 2 * c - i;
		table[i] = (r > i) ? min(r - i, table[ii]) : 0;
		while (s[i + 1 + table[i]] == s[i - 1 - table[i]]) {
			++table[i];
		}
		if (i + table[i] > r) {
			c = i;
			r = i + table[i];
		}
	}
	return table;
}

int main() {
	int n;
	scanf("%d", &n);
	vector<int> v;
	while (n--) {
		int x;
		scanf("%d", &x);
		v.push_back(x);
	}
	vector<int> t = manacher(v);
	int q;
	scanf("%d", &q);
	while (q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		int len = t[a + b];
		printf("%d\n", len > b - a);
	}
	return 0;
}
