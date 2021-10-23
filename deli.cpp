#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

const int MAX_N = 500 * 1000;

// Fenwick tree -- computes cumulative sums
struct Fenwick
{    
    Fenwick(int buckets = MAX_N)
    {
	// nb buckets+1 because this algorithm is 1 based
	subfreq.assign(buckets + 1, 0);
    }

    void clear()
    {
	std::fill(subfreq.begin(), subfreq.end(), 0);
    }

    // add `value' to the array slot i
    void add(int i, uint64_t value)
    {
	while (i < subfreq.size())
	{
	    subfreq.at(i) += value;
	    i += (i & -i);
	}
    }

    // what's the cumulative sum at i
    uint64_t query(int i)
    {
	uint64_t sum = 0;
	while (i > 0)
	{
	    sum += subfreq.at(i);
	    i -= (i & -i);
	}
	return sum;
    }

    // what's an index of the greatest cumulative sum in
    // the tree <= n
    int search(uint64_t n)
    {
	int idx = 0;
	unsigned bitmask = (1ull << 31);

	uint64_t prev = 0;	
	while (bitmask)
	{
	    int tidx = idx + bitmask;
	    bitmask >>= 1;

	    if (tidx >= subfreq.size())
	    {
		continue;
	    }
	    
	    if (prev + subfreq[tidx] <= n)
	    {
		idx = tidx;
		prev += subfreq[tidx];
	    }	    
	}

	return idx;
    }

    std::vector<uint64_t> subfreq;
};

// There are only 31 possible price values: 2^0, 2^1, ..., 2^29, 2^30
// For each price 'p', we keep
// - the cumulative sum of the price of all toppings that cost 'p' or less up to a given index
// - the cumulative count of toppings that cost 'p' or less up to a given index
//
// The idea is we'll figure out how many items we can get using all prices. At that point,
// the budget remaining must be less than the largest price, because if the next item was
// that price and the budget was >= the largest price, we would include.
//
// So, if we haven't spent the whole budget, we start looking at the next smallest price,
// and see if we can buy more items starting at the index we just stopped at for the
// higher price. It's here that the counts come into play; items that can't be purchased at
// this price or below must be skipped, so we can't just subtract indices.
//
// We continue down this path until we either run out of budget or get to the cheapest
// items.
// 
Fenwick cumPrices[31];
Fenwick cumCounts[31];

// price is <= 2^30 here so it's ok in an int
void addItem(int n, int price)
{
    for (int pi = 30; pi >= 0; pi--)
    {
	int pp = (1 << pi);
	if (price <= pp)
	{
	    cumPrices[pi].add(n, price);
	    cumCounts[pi].add(n, 1);
	}	
    }
}

void updateItem(int n, int oldPrice, int newPrice)
{
    for (int pi = 30; pi >= 0; pi--)
    {
	int pp = (1 << pi);
	if (oldPrice <= pp)
	{
	    cumPrices[pi].add(n, -oldPrice);
	    cumCounts[pi].add(n, -1);
	}	
    }
    addItem(n, newPrice);
}

int main()
{
    int cases;
    std::cin >> cases;

    for (int cs = 1; cs <= cases; cs++)
    {
 	int n, m;
	std::cin >> n >> m;

	std::vector<int> prices {};
	prices.assign(n+1, 0);

	for (int i = 0; i < 31; i++)
	{
	    cumPrices[i].clear();
	    cumCounts[i].clear();
	}

	for (int i = 1; i <= n; i++)
	{
	    std::cin >> prices[i];
	    addItem(i, prices[i]);
	}

	std::cout << "Scenario #" << cs << ":" <<  std::endl;

	for (int i = 0; i < m; i++)
	{
	    int flag;
	    
	    std::cin >> flag;

	    if (flag == 1)
	    {
		uint64_t budget;
		std::cin >> budget;
		
		int idx = 0;
		int bin = 30;
		int tops = 0;

		while (budget && bin >= 0)
		{
		    uint64_t cp = cumPrices[bin].query(idx);
		    uint64_t cc = cumCounts[bin].query(idx);

		    budget += cp;
		    tops -= cc;

		    idx = cumPrices[bin].search(budget);

		    cp = cumPrices[bin].query(idx);
		    cc = cumCounts[bin].query(idx);

		    budget -= cp;
		    tops += cc;
		    
		    bin--;		    
		}

		std::cout
		    << "David can get "
		    << tops
		    << " toppings"
		    << std::endl;
		
	    }	    
	    else
	    {
		int n, p;
		std::cin >> n >> p;
		updateItem(n, prices[n], p);
		prices[n] = p;
	    }
	}

	std::cout << std::endl;
    }

    return 0;
}

