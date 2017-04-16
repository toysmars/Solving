// Codeforces 801 D
// Category: Geometry vector distance

#include <cstdio>
#include <cmath>

struct Vector {
	Vector() : x(0), y(0) {}
	Vector(double _x, double _y) : x(_x), y(_y) {}

	Vector sub(Vector v) {
		return Vector(x - v.x , y - v.y);
	}

	double dot(Vector v) {
		return x * v.x + y * v.y;
	}

	double cross(Vector v) {
		return x * v.y - y * v.x;
	}

	double norm() {
		return sqrt(x * x + y * y);
	}

	double x;
	double y;
};

int N;
Vector pt[1001];

double dist_to_line(Vector p, Vector p1, Vector p2) {
	Vector d = p2.sub(p1);
	Vector x = p.sub(p1);

	return fabs(x.cross(d) / d.norm());
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		pt[i].x = x;
		pt[i].y = y;
	}
	double ans = 1e18;
	for (int i = 0; i < N; ++i) {
		int p = (i - 1 + N) % N;
		int q = (i + 1 + N) % N;
		double dist = dist_to_line(pt[i], pt[p], pt[q]) / 2.0;
		ans = ans < dist ? ans : dist;
	}
	printf("%.10lf\n", ans);
	return 0;
}
