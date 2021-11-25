#include <bits/stdc++.h>
using namespace std;

struct Sieve {
	Sieve(int n) {
		factor = vector<int>(n + 1);
		factor[0] = factor[1] = 1;
		for (int i = 2; i <= n; ++i) factor[i] = i;
		for (int i = 2; i <= n; ++i) {
			if (isPrime(i)) {
				primes.push_back(i);
				for (long long j = 1ll * i * i; j <= n; j += i) {
					factor[j] = i;
				}
			}
		}
	}

	bool isPrime(int x) {
		if (x == 0 || x == 1) return false;
		return factor[x] == x;
	}

	vector<int> primes;
	vector<int> factor;
};
