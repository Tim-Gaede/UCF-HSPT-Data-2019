#include <bits/stdc++.h>

typedef int ll;

int main(void) {
	ll t; std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		/* read input */
		ll n; std::cin >> n;
		std::vector<ll> vec(n);
		for (auto& e : vec)
			std::cin >> e;

		/* if ever there is non-zero remainder, array is bad */
		bool ans = false;
		for (const auto& e : vec)
			for (const auto& f : vec)
				ans = ans || (f > e) * f % e;

		std::cout << "Array #" << tt << ": " << (ans ? "Go away" : "This array is bae") << "!\n";
	}

	return 0;
}
