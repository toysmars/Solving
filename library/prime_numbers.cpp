#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef __int128_t i128;

i64 modPower(i64 x, i64 y, i64 mod) {
    i128 res = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) {
            res = res * x % mod;
        }
        x = (i128)x * x % mod;
        y >>= 1;
    }
    return res;
}

struct MillerRabin {
    bool isPrime(i64 x) {
        if (x < 2) {
            return false;
        }
        int r = 0;
        i64 d = x - 1;
        while ((d & 1) == 0) {
            d >>= 1;
            r += 1;
        }
        for (int a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (x == a) {
                return true;
            }
            if (check(x, a, d, r)) {
                return false;
            }
        }
        return true;
    }
private:
    bool check(i64 x, i64 a, i64 d, i64 r) {
        i64 t = modPower(a, d, x);
        if (t == 1 || t == x - 1) {
            return false;
        }
        for (int i = 1; i < r; ++i) {
            t = (i128)t * t % x;
            if (t == x - 1) {
                return false;
            }
        }
        return true;
    }
};

struct PollardRho {
    vector<i64> factorize(i64 x) {
        factors.clear();
        go(x);
        return factors;
    }

private:
    void go(i64 x) {
       if (x == 1) {
           return;
       }
       if (x % 2 == 0) {
           factors.push_back(2);
           go(x / 2);
           return;
       }

       MillerRabin mr;
       if (mr.isPrime(x)) {
           factors.push_back(x);
           return;
       }
       i64 a, b, c, g = x;
       auto f = [&](i64 n) {
           return ((i128)n * n % x + c) % x;
       };
       do {
           if (g == x) {
               a = b = rand() % (x - 2) + 2;
               c = rand() % 10 + 1;
               g = 1;
           }
           a = f(a);
           b = f(f(b));
           g = gcd(abs(a - b), x);
       } while (g == 1);
       go(g);
       go(x / g);
    }

    vector<i64> factors;
};

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

i64 phi(i64 x) {
    i64 ans = x;
    i64 r = x;
    PollardRho pr;
    for (i64 f: pr.factorize(x)) {
        if (r % f == 0) {
            ans = ans / f * (f - 1);
            while (r % f == 0) {
                r /= f;
            }
        }
    }
    if (r != 1) {
        ans = ans / r * (r - 1);
    }
    return ans;
}
