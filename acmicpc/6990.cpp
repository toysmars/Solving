// acmicpc 6990
//
// Geometry
// 기하
// 선분 교차 판정

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e15;
const double EPS = 1e-8;
typedef double coord_t;

struct Point2D {
    coord_t x, y;
};

bool lessThan(Point2D a, Point2D b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool lessThanOrEqualTo(Point2D a, Point2D b) {
    return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

typedef Point2D Vec2D;

Vec2D vec(Point2D a, Point2D b) {
    return { b.x - a.x, b.y - a.y };
}

Vec2D normalize(Vec2D v) {
    double norm = sqrt(v.x * v.x + v.y * v.y);
    return { v.x / norm, v.y / norm };
}

coord_t cross(Vec2D a, Vec2D b) {
    return a.x * b.y - b.x * a.y;
}

int ccw(Vec2D a, Vec2D b) {
    coord_t c = cross(a, b);
    if (abs(c) < EPS) return 0;
    return c > 0 ? 1 : -1;
}

coord_t ccw(Point2D p, Point2D a, Point2D b) {
    return ccw(vec(p, a), vec(p, b));
}

struct Snail {
    Point2D p0, p1;
    Vec2D v;
};

double updateHitPoint(Snail& s, int L) {
    if (s.v.x == 0) {
        s.p1 = { s.p0.x, s.v.y > 0 ? L : 0.0 };
        return s.v.y > 0 ? L - s.p0.y : s.p0.y;
    }
    if (s.v.y == 0) {
        s.p1 = { s.v.x > 0 ? L : 0.0, s.p0.y };
        return s.v.x > 0 ? L - s.p0.x : s.p0.x;
    }
    double tx = max(-s.p0.x / s.v.x, (L - s.p0.x) / s.v.x);
    double ty = max(-s.p0.y / s.v.y, (L - s.p0.y) / s.v.y);
    double t = min(tx, ty);
    s.p1 = { s.p0.x + t * s.v.x, s.p0.y + t * s.v.y };
    return t;
}

bool isIntersect(Snail a, Snail b) {
    int ccwA = ccw(a.p0, a.p1, b.p0) * ccw(a.p0, a.p1, b.p1);
    int ccwB = ccw(b.p0, b.p1, a.p0) * ccw(b.p0, b.p1, a.p1);
    if (ccwA == 0 && ccwB == 0) {
        if (lessThan(a.p1, a.p0)) swap(a.p0, a.p1);
        if (lessThan(b.p1, b.p0)) swap(b.p0, b.p1);
        return lessThanOrEqualTo(b.p0, a.p1) && lessThanOrEqualTo(a.p0, b.p1);
    }
    return ccwA <= 0 && ccwB <= 0;
}

bool isParallel(Snail a, Snail b) {
    return ccw(vec(a.p0, a.p1), vec(b.p0, b.p1)) == 0;
}

double getParallelMeetTime(Snail a, Snail b) {
    if (a.v.x == 0) {
        if (a.p0.y > b.p0.y == a.v.y > 0) {
            return INF;
        }
        if (a.p0.y > b.p0.y) swap(a, b);
        if (a.v.y < 0 && b.v.y > 0) {
            return INF;
        } else if (a.v.y > 0 && b.v.y < 0) {
            return (b.p0.y - a.p0.y) / 2;
        } else {
            return (b.p0.y - a.p0.y);
        }
    } else if (a.v.y == 0) {
        if (a.p0.x > b.p0.x == a.v.x > 0) {
            return INF;
        }
        if (a.p0.x > b.p0.x) swap(a, b);
        if (a.v.x < 0 && b.v.x > 0) {
            return INF;
        } else if (a.v.x > 0 && b.v.x < 0) {
            return (b.p0.x - a.p0.x) / 2;
        } else  {
            return (b.p0.x - a.p0.x);
        }
    } else {
        if (a.p0.x > b.p0.x == a.v.x > 0) {
            return INF;
        }
        if (a.p0.x > b.p0.x) swap(a, b);
        if (a.v.x < 0 && b.v.x > 0) {
            return INF;
        } else if (a.v.x > 0 && b.v.x < 0) {
            return hypot(b.p0.x - a.p0.x, b.p0.y - a.p0.y) / 2;
        } else  {
            return hypot(b.p0.x - a.p0.x, b.p0.y - a.p0.y);
        }
    }
}

double getMeetTime(Snail a, Snail b) {
    if (a.p0.x == b.p0.x && a.p0.y == b.p0.y) {
        return 0.0;
    }
    if (!isIntersect(a, b)) {
        return INF;
    }
    if (isParallel(a, b)) {
        return getParallelMeetTime(a, b);
    }
    double d = cross(vec(a.p0, a.p1), vec(b.p0, b.p1));
    double pa = cross(a.p0, a.p1);
    double pb = cross(b.p0, b.p1);
    double x = (pa * (b.p0.x - b.p1.x) - pb * (a.p0.x - a.p1.x)) / d;
    double y = (pa * (b.p0.y - b.p1.y) - pb * (a.p0.y - a.p1.y)) / d;
    double ad = hypot(x - a.p0.x, y - a.p0.y);
    double bd = hypot(x - b.p0.x, y - b.p0.y);
    return ad + EPS >= bd ? ad : INF;
}

int main() {
    int N, L;
    scanf("%d%d", &N, &L);

    vector<Snail> snails;
    vector<pair<double, pair<int, int>>> ht;
    for (int i = 0; i < N; ++i) {
        double x, y, p, q;
        scanf("%lf%lf%lf%lf", &x, &y, &p, &q);
        Snail snail = { .p0 = { x, y }, .v = { p - x, q - y } };
        snail.v = normalize(snail.v);
        double t = updateHitPoint(snail, L);
        //printf("snail %d hits wall (%.02lf, %.02lf)at %lf\n", i, snail.p1.x, snail.p1.y, t);
        snails.push_back(snail);
        ht.emplace_back(t, make_pair(i, -1));
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            double t = getMeetTime(snails[i], snails[j]);
            if (t < INF) {
                //printf("snail %d meets %d at %lf\n", i, j, t);
                ht.emplace_back(t, make_pair(i, j));
            }
        }
    }
    sort(ht.begin(), ht.end());
    vector<bool> stop(N);
    double ans = 0;
    for (auto hit: ht) {
        double t = hit.first;
        int who = hit.second.first;
        int to = hit.second.second;
        if (stop[who]) continue;
        auto& s1 = snails[who];
        s1.p1 = { s1.p0.x + t * s1.v.x, s1.p0.y + t * s1.v.y };
        if (to == -1) {
            ans = t;
            stop[who] = true;
            //printf("snail %d stops at %lf hitting %d\n", who, t, to);
            continue;
        }
        auto& s2 = snails[to];
        if (!stop[to]) {
            s2.p1 = { s2.p0.x + t * s2.v.x, s2.p0.y + t * s2.v.y };
        }
        double mt = getMeetTime(s1, s2);
        if (abs(t - mt) < EPS) {
            ans = t;
            stop[who] = true;
            //printf("snail %d stops at %lf (%lf, %lf) hitting %d\n", who, t, s1.p1.x, s1.p1.y, to);
            continue;
        }
    }
    printf("%.02f\n", ans);
    return 0;
}
