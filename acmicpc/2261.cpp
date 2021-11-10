// acmicpc 2261
//
// sweep line
// Euclidean space

#include <bits/stdc++.h>
using namespace std;

struct Point { int x; int y; };

bool compXY(const Point& a, const Point& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

struct CompYX {
    bool operator() (const Point& a, const Point& b) const {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    }
};

int dist(const Point a, const Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int main() {
    int n;
    scanf("%d", &n);
    vector<Point> A(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &A[i].x, &A[i].y);
    }
    sort(A.begin(), A.end(), compXY);

    int d = dist(A[0], A[1]);
    set<Point, CompYX> s;
    s.insert(A[0]);
    s.insert(A[1]);
    for (int i = 2, j = 0; i < n; ++i) {
        while (j < i && (A[i].x - A[j].x) * (A[i].x - A[j].x) >= d) {
            s.erase(A[j]);
            j++;
        }
        auto lit = s.lower_bound({A[i].x-d, A[i].y-d-1});
        auto uit = s.upper_bound({A[i].x+d, A[i].y+d+1});
        while (lit != uit) {
            d = min(d, dist(A[i], *lit));
            lit++;
        };
        s.insert(A[i]);
    }
    printf("%d\n", d);

    return 0;
}
