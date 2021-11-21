// manacher's algorithm
// length of palindrome
//
// Examples
//  https://www.acmicpc.net/problem/16163
//  https://www.acmicpc.net/problem/19492

#include <bits/stdc++.h>
using namespace std;

// Manacher's algorithm
// Returns the length of longest palindorme substring centered at each index.
// The size of index space is 2 * v.size() + 1 (it includes the point between two characters)
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
