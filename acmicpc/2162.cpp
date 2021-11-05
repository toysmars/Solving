// acmicpc 2162
//
// line segment
// 선분교차
// ccw
// disjoint set size
// union find size

#include<bits/stdc++.h>
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

class DisjointSet {
public:
	DisjointSet(int size) : p(size), r(size), c(size) {
		for (int i = 0; i < size; ++i) {
            p[i] = i;
            c[i] = 1;
        }
	}

	int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}

	void join(int x, int y) {
		int xp = find(x);
		int yp = find(y);
        if (xp == yp) return;
        if (r[xp] < r[yp]) swap(xp, yp);
        p[yp] = xp;
        r[xp] += r[xp] == r[yp];
        c[xp] += c[yp];
	}

    int size(int x) {
        return c[find(x)];
    }

	vector<int> p;
	vector<int> r;
    vector<int> c;
};

int main() {
    int n;
    scanf("%d", &n);
    vector<LineSegment2D> lines;
    for (int i = 0; i < n; ++i) {
        LineSegment2D line;
        scanf("%d%d%d%d", &line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y);
        lines.push_back(line);
    }
    DisjointSet ds(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (isIntersect(lines[i], lines[j])) {
                ds.join(i, j);
            }
        }
    }
    int count = 0;
    int maxSize = 0;
    for (int i = 0; i < n; ++i) {
        if (ds.find(i) == i) {
            count += 1;
            if (maxSize < ds.size(i)) {
                maxSize = ds.size(i);
            }
        }
    }
    printf("%d\n", count);
    printf("%d\n", maxSize);

    return 0;
}

