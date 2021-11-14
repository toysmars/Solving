// acmicpc 11689
//
// Euler phi (totient) function
// 오일러 피 함수
// coprime
// 서로소
// sieve

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Sieve {
	Sieve(i64 n) {
		factor = vector<i64>(n + 1);
		factor[0] = factor[1] = 1;
		for (i64 i = 2; i <= n; ++i) factor[i] = i;
		for (i64 i = 2; i <= n; ++i) {
			if (isPrime(i)) {
				primes.push_back(i);
				for (i64 j = 1 * i * i; j <= n; j += i) {
					factor[j] = i;
				}
			}
		}
	}

	bool isPrime(int x) {
		if (x == 0 || x == 1) return false;
		return factor[x] == x;
	}

	vector<i64> primes;
	vector<i64> factor;
};

i64 phi(const vector<i64>& primes, i64 x) {
    i64 ans = x;
    i64 r = x;
	for (i64 p: primes) {
		if (p * p > x) break;
        if (r % p == 0) {
            ans = ans / p * (p - 1);
            while (r % p == 0) {
                r /= p;
            }
        }
    }
    if (r != 1) {
        ans = ans / r * (r - 1);
    }
    return ans;
}

int main() {
	Sieve sieve(100000);
	i64 x;
	while (scanf("%lld", &x)) {
		if (x == 0) break;
		printf("%lld\n", phi(sieve.primes, x));
	}
	return 0;
}
