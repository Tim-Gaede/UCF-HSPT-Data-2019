#include <bits/stdc++.h>

typedef long long ll;

const ll MAX_R = 107;

ll w, r, c, k;
std::string grid[MAX_R];
ll a[2][MAX_R];

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> w;
	for (ll tt = 1; tt <= w; ++tt) {
		std::cin >> r >> c >> k;
		for (ll i = 0; i < r; ++i)
			std::cin >> grid[i];

		/* get the column heights */
		for (ll j = 0; j < c; ++j) {
			a[0][j] = 0;
			for (ll i = 0; i < r; ++i)
				a[0][j] += (grid[i][j] == '#');

			/* when flipped, the col has a complementary height. */
			a[1][j] = r - a[0][j];
		}

		/* answer is simply to flip whenever
		invertomancer cannot climb high enough. */

		ll ans = 0;
		for (ll j = 0, flip = 0; j + 1 < c; ++j)
			if (a[flip][j] + k < a[flip][j+1]) {
				++ans; flip ^= 1;
			}

		std::cout << "World #" << tt << ": " << ans << "\n";
	}

	return 0;
}
