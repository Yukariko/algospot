#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

int N, K;

bool decision(const vector< pair<int,int> >& a, double bound)
{
	vector<double> p(N);

	for(int i=0; i < N; i++)
		p[i] = bound * a[i].second - a[i].first;

	sort(p.begin(), p.end());

	double ans = 0;
	for(int i=N-K; i < N; i++)
		ans += p[i];

	return ans < 0;
}

int main()
{
	int T;
	cin >> T;

	cout.setf(ios::fixed);
	cout.precision(8);

	while(T--)
	{
		cin >> N >> K;

		vector< pair<int,int> > a(N);

		for(int i=0; i < N; i++)
			cin >> a[i].first >> a[i].second;

		double start = 0, end = 1;

		while(start + 1e-10 <= end)
		{
			double mid = (start + end) / 2;

			if(decision(a, mid))
				start = mid;
			else
				end = mid;
		}

		cout << start << '\n';
	}
	return 0;
}