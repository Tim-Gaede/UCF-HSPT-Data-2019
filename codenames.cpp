#include <bits/stdc++.h>

typedef int ll;

const ll MAX_N = 107;

/*
	This problem can probably be
	done with greedy but it is
	just easier to run HopcroftKarp
	a few times.

	HopcroftKarp solves the unit
	bipartite matching problem in
	O(E * sqrt(V)).
*/

struct HopcroftKarp {
	struct Node {
		ll id;
		ll level;

		Node* pair;
		std::vector<Node*> adj;

		bool used;

		Node(const ll& ii)
			: id(ii), level(-1), pair(nullptr), used(false) {}
	};

	ll n;
	std::vector<Node*> graph;

	HopcroftKarp(const ll& nn) {
		n = nn;
		graph.resize(n);
		for (ll i = 0; i < n; ++i)
			graph[i] = new Node(i);
	}

	~HopcroftKarp(void) {
		for (Node* e : graph)
			delete e;
	}

	void add_edge(const ll& a, const ll& b) {
		if (!graph[a] || !graph[b]) return;
		graph[a]->adj.push_back(graph[b]);
		graph[b]->adj.push_back(graph[a]);
	}

	/* matches the graph. */
	ll match(void) {
		for (ll match = 0; ;) {
			std::queue<Node*> order;
			for (auto& node : graph) {
				node->level = -1;
				if (node->pair == nullptr) {
					node->level = 0;
					order.push(node);
				}
			}

			while (!order.empty()) {
				Node* curr = order.front(); order.pop();
				for (auto& neigh : curr->adj) {
					Node* w = neigh->pair;
					if (w != nullptr && w->level < 0) {
						w->level = curr->level + 1;
						order.push(w);
					}
				}
			}

			for (auto& node : graph)
				node->used = false;

			ll d = 0;
			for (auto& node : graph)
				d += node->pair == nullptr && dfs(node);

			match += d;

			/* the end */
			if (d == 0) return match;
		}
	}

	bool dfs(Node* curr) {
		curr->used = true;
		for (auto& neigh : curr->adj) {
			Node* w = graph[neigh->id]->pair;
			if (w == nullptr || (!w->used && curr->level < w->level && dfs(w))) {
				curr->pair = neigh;
				neigh->pair = curr;
				return true;
			}
		}
		return false;
	}
};

struct bg_p {
	std::string s; ll id;
};

ll t, n;
std::string ans[MAX_N];

ll read_num(void) {
	std::string s;
	std::getline(std::cin, s);
	std::stringstream ss(s);
	ll ret; ss >> ret;
	return ret;
}

int main(void) {
	t = read_num();
	for (ll tt = 1; tt <= t; ++tt, std::cout << "\n") {
		std::cout << "Event #" << tt << ":\n";

		n = read_num();

		/* we will bucket the words by first character */
		std::vector<std::vector<bg_p>> buck(26);

		for (ll i = 0; i < n; ++i) {

			/* get string and strip it, convert to uppercase */
			std::string s; std::getline(std::cin, s);
			s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
			std::transform(s.begin(), s.end(), s.begin(), ::toupper);

			buck[s.front() - 'A'].push_back({s, i});
		}

		/* track if it's good or not. */
		bool good = true;

		for (ll letter = 0; letter < 26; ++letter) {
			const ll num_words = buck[letter].size();
			HopcroftKarp hoppy(n + 26 * 26);

			/* now we have to match things */
			for (const auto& e : buck[letter]) {
				const ll sz = e.s.length();
				for (char first_letter = 'A'; first_letter <= 'Z'; ++first_letter) {
					ll first_occ = 1, secon_occ;
					for (; first_occ < sz && e.s[first_occ] != first_letter; ++first_occ);
					if (first_occ >= sz) continue;

					for (char secon_letter = 'A'; secon_letter <= 'Z'; ++secon_letter) {
						for (secon_occ = first_occ+1; secon_occ < sz && e.s[secon_occ] != secon_letter; ++secon_occ);
						if (secon_occ < sz)
							hoppy.add_edge(e.id, n + 26 * (first_letter - 'A') + (secon_letter - 'A'));
					}
				}
			}

			/*  we are good if we can match each word
			    in the bucket with a unique three-letter
				codename. */
			good = good && hoppy.match() == num_words;

			/* recover the matching. */
			for (const auto& e : buck[letter]) {
				if (hoppy.graph[e.id]->pair == nullptr)
					break;

				const ll match_id = hoppy.graph[e.id]->pair->id - n;
				ans[e.id] = std::string(3, e.s.front());
				ans[e.id][1] = 'A' + match_id/26;
				ans[e.id][2] = 'A' + match_id%26;
			}
		}

		if (good)
			for (ll i = 0; i < n; ++i)
				std::cout << ans[i] << "\n";
		else std::cout << "Not Possible\n";
	}
	return 0;
}
