//
// Blurry
// UCF High School Programming Contest 2019
// Jim Geist jimg@knights.ucf.edu
//
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

struct Image
{
    int n; // images are always square n x n
    std::vector<int> pixels;

    Image(int n)
	: n(n)
    {
	pixels.resize(n * n);
    }

    void clear()
    {
	std::fill(pixels.begin(), pixels.end(), 0);
    }

    inline int &at(int x, int y)
    {
	return pixels[y*n+x];
    }

    void read()
    {
	int nn = n * n;
	for (int i = 0; i < nn; i++)
	{
	    int pix;
	    std::cin >> pix;
	    pixels[i] = pix;
	}
    }

    void print()
    {
	int nn = n * n;
	for (int i = 0; i < nn; i++)
	{
	    std::cout
		<< pixels[i]
		<< (((i % n) == n-1) ? "\n" : " ");	    
	}
    }
};

int main()
{
    int images;

    std::istream &in = std::cin;

    std::cin >> images;

    for (int image = 1; image <= images; image++)
    {
	std::cout << "Image #" << image << ":" << std::endl;

	int n, k;
	std::cin >> n >> k;
	int padding = k / 2;

//	assert((k % 2) == 1);

	Image in {n};
	in.read();

	Image interim {n};
	interim.clear();

	// basically we're trying to get the sum of every possible k x k square
	// inside the image. in the first pass we'll sum every k x 1 strip, which
	// we can do in O(n^2) time via incremental sums.
	//
	for (int y = 0; y < n; y++)
	{
	    int sum = 0;
	    for (int x = 0; x < k; x++)
	    {
		sum += in.at(x, y);
	    }

	    interim.at(padding, y) = sum;

	    for (int x = padding + 1; x < n - padding; x++)
	    {
		sum -= in.at(x - padding - 1, y);
		sum += in.at(x + padding, y);
		interim.at(x, y) = sum;
	    }
	}

	// now we'll add all the sums from the previous step in the y dimension,
	// which we can also do in O(n^2) via incremental sums of those sums.
	//
	// We also scale by 1/(k^2) and round to compute the blurred average.
	//
	Image blurred {n};
	blurred.clear();

	double scale = 1.0 / (k*k);

	for (int x = padding; x < n - padding; x++)
	{
	    int sum = 0;
	    for (int y = 0; y < k; y++)
	    {
		sum += interim.at(x, y);
	    }
	    blurred.at(x, padding) = (int)(sum * scale + 0.5);

	    for (int y = padding + 1; y < n - padding; y++)
	    {
		sum -= interim.at(x, y - padding - 1);
		sum += interim.at(x, y + padding);
		blurred.at(x, y) = (int)(sum * scale + 0.5);
	    }
	}

	blurred.print();
	std::cout << std::endl;
    }
    return 0;
}
