#include <bits/stdc++.h>

typedef long long ll;

int main(void) {

	ll t; std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		ll num, k; std::cin >> num >> k;
		std::vector<ll> perm(19), number(19);
		for (ll j = 0; j < 18; ++j) {
			number[18-j] = num % 10;
			num /= 10;
		}
		ll j = 0;
		for (; number[j] == 0 && j < static_cast<ll>(number.size()); ++j);

		std::vector<ll> num_digits(10);

		std::function<bool(const ll&, const ll&, const bool&, const bool&)>
		permute = [&](const ll& pos, const ll& max, const bool& bounded, const bool& first) {
			if (pos == static_cast<ll>(number.size())) //reached end of number while still being valid, so return
				return true;
			ll i = number[pos]; //get current digit
			if (!bounded) i = 0; //if the current digit does not have to be greater than the original digit
                            //i.e at least one digit before it in the current number is different from the original number, let it be whatever
			for (; i <= 9; ++i) { //try all posible digits
				if (num_digits[i] == max) continue; //if the limit on the digit we are trying is reached, continue
            	//else, set perm array and increment the number of times the current digit has appeared
				perm[pos] = i;
				if (!(first && i == 0)) num_digits[i]++;
				if (permute(pos+1, max, bounded && i == number[pos], false))
					return true; //if the current permutation works, return true
				if (!(first && i == 0)) num_digits[i]--; //reset number of times the digit has appeared
			}
			return false; //nothing works, so return :(
		};

		if (!permute(j-1, k, true, true)) {
			std::cout << "Find a different k\n";
		} else {
			j = 0;
			for (; perm[j] == 0; ++j);
			for (; j < 19; ++j)
				std::cout << perm[j];
			std::cout << "\n";
		}
	}

	return 0;
}
