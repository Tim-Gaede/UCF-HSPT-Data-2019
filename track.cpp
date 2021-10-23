#include <bits/stdc++.h>

typedef long long ll;

struct bg_p {
	double x, y;
	
	double dist(const bg_p& o) const {
		double dx = x - o.x;
		double dy = y - o.y;
		return std::sqrt(dx*dx + dy*dy);
	}
};

double w1, w2, w3, l;

double go1(const double& y, const double& w1, const double& w2) {
	bg_p right = {w2, y};
	double m = right.y / right.x;
	bg_p left = {w1 / m, w1};
	return left.dist(right);
}

double go2(const double& y, const double& w2, const double& w3) {
	bg_p left = {-w2, y};
	double m = left.y / left.x;
	bg_p right = {-w3 / m, -w3};
	return left.dist(right);
}

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(7);
	
	ll t; std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		std::cin >> w1 >> w2 >> w3 >> l;
		
		double min1 = std::numeric_limits<double>::infinity();
		double min2 = min1;
		
		{
			double lo = -l, hi = 0;
			for (ll loop = 200; loop--; ) {
				double delta = (hi - lo) / 3;
				double m1 = lo + delta;
				double m2 = hi - delta;
				double d1 = go1(m1, w1, w2);
				double d2 = go1(m2, w1, w2);
				if (d1 < d2)
					hi = m2;
				else lo = m1;
			}
			min1 = go1(lo, w1, w2);
		}
		
		{
			double lo = 0, hi = l;
			for (ll loop = 200; loop--; ) {
				double delta = (hi - lo) / 3;
				double m1 = lo + delta;
				double m2 = hi - delta;
				double d1 = go2(m1, w2, w3);
				double d2 = go2(m2, w2, w3);
				if (d1 < d2) hi = m2;
				else lo = m1;
			}
			min2 = go2(lo, w2, w3);
		}

		std::cout << "Track Blueprint #" << tt << ": " << std::min(min1, min2) << "\n";	
	}

	return 0;
}
