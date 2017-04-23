// http://codeforces.com/contest/793/problem/C
// * geometry
// * line

#include <cstdio>
#include <vector>
using namespace std;

const double INF = 1e15;
const double EPS = 1e-12;

int N;
int x1;
int y1;
int x2;
int y2;

double min(double a, double b) { return a < b ? a : b;}
double max(double a, double b) { return a > b ? a : b;}

pair<double, double> time(int x1, int x2, int p, int v) {
	if (v == 0) {
		if (x1 < p && p < x2) {
			return make_pair(0, INF);
		} else {
			return make_pair(-1, -1);
		}
	}
	double t1 = 1.0 * (x1 - p) / v;
	double t2 = 1.0 * (x2 - p) / v;
	return make_pair(min(t1, t2), max(t1, t2));
}


int main() {
	scanf("%d", &N);
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	double tmin = 0;
	double tmax = 1e15;
	for (int i = 0; i < N; ++i) {
		int x, y, vx, vy;
		scanf("%d%d%d%d", &x, &y, &vx, &vy);
		auto xr = time(x1, x2, x, vx);
		auto yr = time(y1, y2, y, vy);
		tmin = max(tmin, max(xr.first, yr.first));
		tmax = min(tmax, min(xr.second, yr.second));
	}
	if (tmax < 0 || tmin + EPS >= tmax) {
		printf("-1\n");
	} else {
		printf("%.15lf\n", tmin);
	}

	return 0;
}
