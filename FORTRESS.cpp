#include <iostream>
#include <algorithm>

using namespace std;

bool isIn(int x, int y, int r)
{
	return x * x + y * y <= r * r;
}

int solve2(const vector< vector<int> >& a, int pos)
{
	int ret = 0;
	for(int i=0; i < a[pos].size(); i++)
		ret = max(ret, 1 + solve2(a, a[pos][i]));
	return ret;
}

int solve(const vector< vector<int> >& a, int pos)
{
	int ret = 0;
	for(int i=0; i < a[pos].size(); i++)
	{
		int t = 1 + solve2(a, a[pos][i]);
		ret = max(ret, t);
		for(int j=i+1; j < a[pos].size(); j++)
			ret = max(ret, t + 1 + solve2(a, a[pos][j]));
	}
	return ret;
}

struct castle
{
	int x, y, r;
	bool operator < (const castle& p)
	{
		return r < p.r;
	}
};

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N;
		cin >> N;

		vector<castle> a(N);
		for(int i=0; i < N; i++)
			cin >> a[i].x >> a[i].y >> a[i].r;

		sort(a.begin(), a.end());

		vector< vector<int> > inCastle(N);
		vector<bool> check(N, 0);
		for(int i=0; i < N; i++)
		{
			for(int j=0; j < i; j++)
			{
				if(!check[j] && isIn(a[i].x - a[j].x, a[i].y - a[j].y, a[i].r))
				{
					check[j] = true;
					inCastle[i].push_back(j);
				}
			}
		}

		int ans = 0;
		for(int i=0; i < N; i++)
			ans = max(ans, solve(inCastle, i));

		cout << ans << '\n';
	}
	return 0;
}