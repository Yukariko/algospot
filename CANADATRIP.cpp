#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

int N, K;

struct city {
	int L,M,G;
};

int decision(const vector<city>& a, int dist)
{
	int ans = 0;

	for(vector<city>::const_iterator it = a.begin(); it != a.end(); ++it)
	{
		int startPoint = it->L - it->M;
		if(startPoint > dist)
			continue;

		int remainDist = min(dist, it->L) - startPoint;
		ans += remainDist / it->G + 1;
	}
	return ans - K;
}


int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		cin >> N >> K;

		vector<city> a(N);
		for(int i=0; i < N; i++)
			cin >> a[i].L >> a[i].M >> a[i].G;

		int start = 0, end = 8030000;
		while(start <= end)
		{
			int mid = (start + end) / 2;

			int ans = decision(a, mid);
			if(ans < 0)
				start = mid + 1;
			else
				end = mid - 1;
		}
		cout << start << '\n';
	}
	return 0;
}