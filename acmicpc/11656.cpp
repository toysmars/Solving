// https://www.acmicpc.net/problem/11656
// * string
// * suffix array
// * Manber myers

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Comparator {
    const string& str;
    Comparator(const string& s) : str(s) {}
    bool operator()(int a, int b) {
        return str[a] < str[b];
    }
};

struct ManberMyers {
  	vector<int> solve(const string& str) {
	    int n = str.size();
	    pos = vector<int>(n);
	    prm = vector<int>(n);
	    vector<int> cnt(n), next(n);
	    vector<bool> bh(n), b2h(n);

	    // Sort suffixes according to their first characters.
	    for (int i = 0; i < n; ++i) {
	        pos[i] = i;
	    }
	    Comparator comp(str);
	    sort(pos.begin(), pos.end(), comp);

	    // Initial value for bh and bh2.
	    for (int i = 0; i < n; ++i) {
	        bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
	        b2h[i] = false;
	    }

	    // Iterate for h = 1, 2, 4, 8, ...
	    for (int h = 1; h < n; h <<= 1) {
	        // Calculate buckets.
	        int i = 0, j = 0, buckets = 0;
	        while (i < n) {
	            j = i + 1;
	            while (j < n && !bh[j]) ++j;
	            i = next[i] = j;
	            ++buckets;
	        }
	        // If we got n buckets then we are done.
	        if (buckets == n) break;
	        // Calculate prms.
	        for (int i = 0; i < n; i = next[i]) {
	            cnt[i] = 0;
	            for (int j = i; j < next[i]; ++j) {
	                prm[pos[j]] = i;
	            }
	        }
	        // Calculate values for 2h based on h.
	        cnt[prm[n-h]] += 1;
	        b2h[prm[n-h]] = true;
	        for (int i = 0; i < n; i = next[i]) {
	            for (int j = i; j < next[i]; ++j) {
	                int d = pos[j] - h;
	                if (d >= 0) {
	                    prm[d] += cnt[prm[d]]++;
	                    b2h[prm[d]] = true;
	                }
	            }
	            for (int j = i; j < next[i]; ++j) {
	                int d = pos[j] - h;
	                if (d >= 0 && b2h[prm[d]]) {
	                    for (int k = prm[d] + 1; !bh[k] && b2h[k]; ++k) {
	                        b2h[k] = false;
	                    }
	                }
	            }
	        }
	        for (int i = 0; i < n; ++i) {
	            pos[prm[i]] = i;
	            bh[i] = bh[i] || b2h[i];
	        }
	    }
	    for (int i = 0; i < n; ++i) {
	        prm[pos[i]] = i;
	    }
	    return pos;
	}

	vector<int> suffixArray() {
	    return pos;
	}

	vector<int> rank() {
	    return prm;
	}

	// s[pos[i]...] is ith suffix
    vector<int> pos;
	// s[i...] is prm[i]th suffix
    vector<int> prm;
};


int main() {
	ManberMyers mm;
	string s;
	cin >> s;
	vector<int> suffixArray = mm.solve(s);
	for (int i : suffixArray) {
		cout << &s[i] << endl;
	}
	return 0;
}
