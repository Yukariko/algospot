#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

const int MAX_N = 10000001;

int minFactor[MAX_N];

void eratos()
{
	for(int i=2; i <= MAX_N; i++)
		minFactor[i] = i;

	for(int i=2; i*i <= MAX_N; i++)
		if(minFactor[i] == i)
			for(int j=i*i; j <= MAX_N; j+=i)
				if(minFactor[j] == j)
					minFactor[j] = i;
}

int main()
{
	eratos();

	int T;
	cin >> T;

	while(T--)
	{
		int N, lo, hi;
		cin >> N >> lo >> hi;

		int ans = 0;
		while(lo <= hi)
		{
			int nFactor = 1;
			int nowFactor = 0;
			int nowCnt = 0;
			for(int n = lo; n > 1; n /= minFactor[n])
			{
				if(nowFactor != minFactor[n])
				{
					nFactor *= nowCnt + 1;
					nowFactor = minFactor[n];
					nowCnt = 1;
				}
				else
					nowCnt++;
			}
			nFactor *= nowCnt + 1;

			if(nFactor == N)
				ans++;
			lo++;
		}


		cout << ans << '\n';
	}
	return 0;
}