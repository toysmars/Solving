// www.acmicpc.net/problem/2043
// * fenwick tree
// * partial sum
#include <cstdio>

typedef long long i64;

int N, M, K;
i64 fw[1000002];

void increase(int i, i64 delta) {
	for (; i <= N; i += (i & -i)) fw[i] += delta;
}

i64 sum(int i) {
	i64 res = 0;
	for (; i > 0; i -= (i & -i)) res += fw[i];
	return res;
}

i64 sum(int l, int r) {
	return sum(r - 1) - sum(l - 1);
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; ++i) {
		i64 x;
		scanf("%lld", &x);
		increase(i, x);
	}
	for (int i = 0; i < M + K; ++i) {
		i64 a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if (a == 1) {
			increase(b, c - sum(b, b + 1));
		} else {
			printf("%lld\n", sum(b, c + 1));
		}
	}
	return 0;
}

