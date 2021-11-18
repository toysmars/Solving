// acmicpc 1708
//
// geometry
// convex hull
// Graham scan

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Point {
    i64 x;
    i64 y;
};

i64 ccw(const Point& a, const Point& b, const Point& c)
{
    return a.x * b.y + b.x * c.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y;
}

bool cmpX(const Point& a, const Point& b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

struct CcwComparator {
    Point base;
    bool operator()(const Point& a, const Point& b) {
        return ccw(base, a, b) > 0;
    }

};

vector<Point> convexHull(vector<Point>& p) {
    vector<Point> res;
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
