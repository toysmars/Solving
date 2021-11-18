// acmicpc 10254
//
// geometry
// convex hull
// rotating calipers
// 회전하는 캘리퍼스
// 볼록껍질
// 가장 먼 두 점

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 coord_t;

struct Point2D {
    coord_t x;
    coord_t y;
};

typedef Point2D Vec2D;

Vec2D vec(Point2D a, Point2D b) {
    return { b.x - a.x, b.y - a.y };
}

coord_t normSquare(Vec2D a) {
    return a.x * a.x + a.y * a.y;
}

coord_t cross(Vec2D a, Vec2D b) {
    return a.x * b.y - b.x * a.y;
}

int ccw(Vec2D a, Vec2D b) {
    coord_t c = cross(a, b);
    if (c == 0) return 0;
    return c > 0 ? 1 : -1;
}

coord_t ccw(Point2D p, Point2D a, Point2D b) {
    return ccw(vec(p, a), vec(b, p));
}

bool cmpX(const Point2D& a, const Point2D& b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

struct CcwComparator {
    Point2D base;
    bool operator()(const Point2D& a, const Point2D& b) {
        return ccw(base, a, b) > 0;
    }
};

vector<Point2D> convexHull(vector<Point2D>& p) {
    vector<Point2D> res;
    sort(p.begin(), p.end(), cmpX);
    CcwComparator ccwCmp = { p[0] };
    stable_sort(p.begin() + 1, p.end(), ccwCmp);
    res.push_back(p[0]);
    res.push_back(p[1]);
    for (int i = 2; i < p.size(); ++i) {
        int size = res.size();
        while (size >= 2 && ccw(p[i], res[size-2], res[size-1]) <= 0) {
            res.pop_back();
            size--;
        }
        res.push_back(p[i]);
    }
    return res;
}

// Find a pair of points that are farthest among the given points.
// Using rotating calipers algorithm.
pair<Point2D, Point2D> farthestPoints(vector<Point2D>& p) {
    auto h = convexHull(p);
    int n = h.size();
    int p1 = 0, p2 = 1;
    int ans1 = 0, ans2 = 1;
    auto maxR = normSquare(vec(h[p1], h[p2]));
    for (int i = 0; i < 2 * n; ++i) {
        int np1 = (p1 + 1) % n;
        int np2 = (p2 + 1) % n;
        int a = ccw(vec(h[p1], h[np1]), vec(h[p2], h[np2]));
        if (a >= 0) p1 = np1;
        if (a <= 0) p2 = np2;
        coord_t r = normSquare(vec(h[p1], h[p2]));
        if (maxR < r) {
            maxR = r;
            ans1 = p1;
            ans2 = p2;
        }
    }
    return make_pair(h[ans1], h[ans2]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        vector<Point2D> pt(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld", &pt[i].x, &pt[i].y);
        }
        auto hull = convexHull(pt);
        auto res = farthestPoints(pt);
        printf("%lld %lld %lld %lld\n", res.first.x, res.first.y, res.second.x, res.second.y);
    }
    return 0;
}
