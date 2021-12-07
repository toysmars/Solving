// line segment
// line intersection
// 선분 교차 판정
//
// Example:
// * https://www.acmicpc.net/problem/2162
// * https://www.acmicpc.net/problem/2519

#include <bits/stdc++.h>
using namespace std;

struct Point2D {
    int x, y;
};

struct LineSegment2D {
    Point2D p1, p2;
};

// counter clockwise
int ccw(Point2D a, Point2D b, Point2D c) {
    int x = (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

bool lessThan(Point2D a, Point2D b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool lessThanOrEqualTo(Point2D a, Point2D b) {
    return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

// See if two line segments are intersect to each other.
bool isIntersect(LineSegment2D a, LineSegment2D b) {
    int ccwA = ccw(a.p1, a.p2, b.p1) * ccw(a.p1, a.p2, b.p2);
    int ccwB = ccw(b.p1, b.p2, a.p1) * ccw(b.p1, b.p2, a.p2);
    if (ccwA == 0 && ccwB == 0) {
        if (lessThan(a.p2, a.p1)) swap(a.p1, a.p2);
        if (lessThan(b.p2, b.p1)) swap(b.p1, b.p2);
        return lessThanOrEqualTo(b.p1, a.p2) && lessThanOrEqualTo(a.p1, b.p2);
    }
    return ccwA <= 0 && ccwB <= 0;
}
