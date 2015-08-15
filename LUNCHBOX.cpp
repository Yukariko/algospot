#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(const pair<int,int>& p, const pair<int,int>& q)
{
	return p.second > q.second;
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int N;
		cin >> N;

		int warm[10001];
		int eat[10001];

		for(int i=0; i < N; i++)
			cin >> warm[i];

		for(int i=0; i < N; i++)
			cin >> eat[i];

		vector<pair<int, int> > a;
		for(int i=0; i < N; i++)
			a.push_back(make_pair(warm[i],eat[i]));

		sort(a.begin(), a.end(), cmp);

		int ans = 0;
		int modTime = 0;

		for(int i=0; i < N; i++)
		{
			modTime += a[i].first;
			ans = max(ans, modTime + a[i].second);
		}

		cout << ans << '\n';
	}
	return 0;
}