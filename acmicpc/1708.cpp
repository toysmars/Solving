// acmicpc 1708
//
// geometry
// convex hull
// Graham scan

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
    return ccw(vec(p, a), vec(p, b));
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
        while (size >= 2 && ccw(p[i], res[size-1], res[size-2]) >= 0) {
            res.pop_back();
            size--;
        }
        res.push_back(p[i]);
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<Point> p(n);

    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    auto ch = convexHull(p);
    printf("%lu\n", ch.size());
    return 0;
}
