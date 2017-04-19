// https://www.acmicpc.net/problem/6588
// * sieve
// * prime number
// * factor

#include <cstdio>
#include <vector>
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

int main() {
	Sieve sieve(1000000);
	auto& primes = sieve.primes;
	while (true) {
		int x;
		scanf("%d", &x);
		if (x == 0) break;
		for (int i = 1; i < primes.size(); ++i) {
			if (sieve.isPrime(x - primes[i])) {
				printf("%d = %d + %d\n", x, primes[i], x - primes[i]);
				break;
			}
		}
	}
	return 0;
}
