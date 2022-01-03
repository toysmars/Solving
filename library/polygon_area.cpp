// Polygon area
// 다각형 넓이
//
// Examples:
// * https://www.acmicpc.net/problem/2166

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

coord_t cross(Vec2D a, Vec2D b) {
    return a.x * b.y - b.x * a.y;
}

double area(vector<Point2D>& points) {
    int n = points.size();
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += cross(vec({0, 0}, points[i]), vec({0, 0}, points[(i+1)%n]));
    }
    return abs(sum) / 2.0;
}
