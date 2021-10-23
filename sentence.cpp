#include <cctype>
#include <iostream>

int main()
{
    int cases;

    std::cin >> cases;

    for (int cas = 1; cas <= cases; cas++)
    {
	int n;
	std::cin >> n;

	int upper = 0, lower = 0;
	while (n--)
	{
	    std::string word {};
	    std::cin >> word;

	    for (char ch : word)
	    {
		if (isupper(ch))
		{
		    upper++;
		}
		else 
		{
		    lower++;
		}
	    }
	}

	std::cout
	    << "Sentence #"
	    << cas
	    << ": "
	    << (upper == lower ? "Yes" : "No")
	    << std::endl;
    }    
    return 0;
}
