#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
pair <int, pair <int, int> > kadane_enhanced (T vec)
{
	pair <int, pair <int, int> > p;
	int max_here = 0, max_so_far = INT_MIN;
	int i = 0, j = 0;
	bool swtch = false;

	for (int k = 0; k < vec.size(); k++)
	{
		swtch = false;
		max_here += vec[k];
		if (max_so_far < max_here)
		{
			max_so_far = max_here;
			j = k;

			swtch = true;
		}
		if (max_here < 0)
		{
			max_here = 0;
			i = swtch ? (k + 1) : i;
		}
	}

	p = {max_so_far, {i, j}};
	return p;
}