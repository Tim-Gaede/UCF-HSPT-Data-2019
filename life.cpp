#include <bits/stdc++.h>

typedef long long ll;

const ll MAX_N = 1e5 + 7;
const ll MAX_W = 1e9 + 7;

struct bg_edge {
	ll a, b, c, id, take, leav;
	bool neg;
	bg_edge(void) : bg_edge(-1,-1,-1,-1,true) {}
	bg_edge(const ll& _a, const ll& _b, const ll& _c, const ll& _id, const bool& _neg)
	: a(_a), b(_b), c(_c), id(_id), take(MAX_N), leav(MAX_N), neg(_neg) {}
	bool operator<(const bg_edge& o) const {
		return c < o.c;
	}
} edges[MAX_N];

struct my_comp {
	bool operator()(const ll& a, const ll& b) const {
		return edges[a] < edges[b];
	}
};

ll t, n, m;
std::vector<ll> gr[2][MAX_N];
std::vector<ll> memo[2][MAX_N];

ll get_next(const bool& go_neg, const ll& new_node, const ll& edge_just_took) {
	auto it = std::upper_bound(gr[go_neg][new_node].begin(), gr[go_neg][new_node].end(), edge_just_took, my_comp());
	return std::distance(gr[go_neg][new_node].begin(), it);
}

ll go(const bool& only_neg, const ll& node, const ll& edge) {
	const ll sz = memo[only_neg][node].size();
	if (edge >= sz) return 0;

	ll& ret = memo[only_neg][node][edge];
	if (ret != -1) return ret;

	/* skip this edge */
	ret = go(only_neg, node, edge+1);

	/* can take positive */
	if (!only_neg) {
		ret = std::max(ret, 1 + go(only_neg, edges[gr[only_neg][node][edge]].b, get_next(only_neg, edges[gr[only_neg][node][edge]].b, gr[only_neg][node][edge])));
	}

	/* can always take a negative so long as it's an acceptable magnitude */
	ret = std::max(ret, 1 + go(true, edges[gr[only_neg][node][edge]].b, get_next(true, edges[gr[only_neg][node][edge]].b, gr[only_neg][node][edge])));

	return ret;
}

/* bb is function that finds what the longest path is. */
/*
ll prev = 0;
void bb(const bool& only_neg, const ll& node, const ll& edge) {
	const ll sz = memo[only_neg][node].size();
	if (edge >= sz) return;

	if (prev + go(only_neg, node, edge+1) == go(0, 0, 0)) {
		bb(only_neg, node, edge+1);
		return;
	}

	if (!only_neg) {
		if (prev + 1 + go(only_neg, edges[gr[only_neg][node][edge]].b, get_next(only_neg, edges[gr[only_neg][node][edge]].b, edge)) == go(0, 0, 0)) {
			++prev;
			std::cout << "took edge " << edges[gr[only_neg][node][edge]].id << "\n";
			bb(only_neg, edges[gr[only_neg][node][edge]].b, get_next(only_neg, edges[gr[only_neg][node][edge]].b, edge));
			return;
		}
	}
	if (prev + 1 + go(true, edges[gr[only_neg][node][edge]].b, get_next(true, edges[gr[only_neg][node][edge]].b, edge)) == go(0, 0, 0)) {
		++prev;
		std::cout << "took edge " << edges[gr[only_neg][node][edge]].id << "\n";
		bb(true, edges[gr[only_neg][node][edge]].b, get_next(true, edges[gr[only_neg][node][edge]].b, edge));
		return;
	}
}
*/

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		std::cin >> n >> m;

		for (ll i = 0; i < n; ++i) {
			gr[0][i].clear();
			gr[1][i].clear();
		}

		for (ll i = 0, a, b, c; i < m; ++i) {
			std::cin >> a >> b >> c; --a; --b;
			edges[i] = bg_edge(a, b, std::abs(c), i, c < 0);
			gr[c < 0][a].push_back(i);
		}

		/* sort edges for binary search and prepare memo */
		for (ll i = 0; i < n; ++i) {
			std::sort(gr[0][i].begin(), gr[0][i].end(), my_comp());
			std::sort(gr[1][i].begin(), gr[1][i].end(), my_comp());
			memo[0][i].assign(gr[0][i].size(), -1);
			memo[1][i].assign(gr[1][i].size(), -1);
		}

		/* we might wanna start off negative:  vvv */
		const ll ans = std::max(go(0, 0, 0), go(1, 0, 0));

		std::cout << "Scenario #" << tt << ": " << ans << "\n";

		// bb(0, 0, 0); prev = 0;
	}

	return 0;
}
