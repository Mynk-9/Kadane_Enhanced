/**
  *		@brief		For knowledge about this algorithm,
  *					See: http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
  */

#include <iostream>
#include <chrono>
#include <random>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
int kadane (T vec)
{
	int max_here = 0, max_so_far = INT_MIN;

	for (auto i = vec.begin(); i != vec.end(); i++)
	{
		max_here += *i;
		if (max_so_far < max_here)
			max_so_far = max_here;
		max_here = max_here < 0 ? 0 : max_here;
	}

	return max_so_far;
}

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

void printVec (vector <int> v)
{
	cout << "The array: ";
	for (auto i = v.begin(); i != v.end(); i++)
		cout << *i << " ";
	cout << endl;
}

int main()
{
	vector <int> a;

	cout << "Generating 10000000 (1 Crore) random numbers...\n";
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 generator (seed);
	for (int i = 1; i <= 10000000; i++)
	{
		int tmp = generator();
		int sgn = generator() % 2 ? -1 : 1;
		a.push_back((tmp % 100) * sgn);
	}

	//printVec(a);
	cout << "\n";

	int kdn;
	pair <int, pair <int, int> > kdn_e;

	auto start = chrono::high_resolution_clock::now();
	kdn = kadane(a);
	auto stop = chrono::high_resolution_clock::now();
	auto duration_k = chrono::duration_cast <chrono::milliseconds> (stop - start);

	start = chrono::high_resolution_clock::now();
	kdn_e= kadane_enhanced(a);
	stop = chrono::high_resolution_clock::now();
	auto duration_k_e = chrono::duration_cast <chrono::milliseconds> (stop - start);

	cout << "Output with normal Kadane: " << kdn << ". Took " << duration_k.count() << " milliseconds to execute.\n";
	cout << "Output with enhanced Kadane: " << kdn_e.first
		 << " from range: [" << kdn_e.second.first << ", " << kdn_e.second.second << "]. "
		 << "Took " << duration_k_e.count() << " milliseconds to execute." << endl;

	cout << "\n\n Do you want to see the number list (bahot lambi hai rhendo)? (y/n)" << endl;
	string s;
	cin >> s;
	if (s == "y" || s == "Y")
		printVec(a);
	else
		cout << "Bye" << endl;

    return 0;
}
