// acmicpc 11689
//
// Euler phi (totient) function
// 오일러 피 함수
// coprime
// 서로소

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 phi(i64 x) {
    i64 ans = x;
    i64 r = x;
    for (i64 i = 2; i * i <= x; ++i) {
        if (r % i == 0) {
            ans = ans / i * (i - 1);
            while (r % i == 0) {
                r /= i;
            }
        }
    }
    if (r != 1) {
        ans = ans / r * (r - 1);
    }
    return ans;
}

int main() {
    i64 x;
    scanf("%lld", &x);
    printf("%lld\n", phi(x));
    return 0;
}
