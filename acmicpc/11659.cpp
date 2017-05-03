// https://www.acmicpc.net/problem/11659
// * fenwick tree
// * partial sum

#include <cstdio>
#include <vector>
using namespace std;

template<typename T>
class Fenwick {
  public:
    Fenwick(int n) : n(n), f(n + 1) {}

    // [i] += x
    void increase(int i, T x) {
        for (; i <= n; i += (i & -i)) f[i] += x;
    }

    // sum [1..i]
    T sum(int i) {
        T res = 0;
        for (; i > 0; i -= (i & -i)) res += f[i];
        return res;
    }

    // sum [l..r)
    T sum(int l, int r) {
        return sum(r - 1) - sum(l - 1);
    }

  private:
    int n;
    vector<T> f;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Fenwick<int> fw(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        fw.increase(i, x);
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", fw.sum(a, b + 1));
    }
    return 0;
}
