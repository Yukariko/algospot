#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 10;

int main()
{
	int T;
	cin >> T;

	cout.precision(8);
	while(T--)
	{
		int N, K, M;
		cin >> N >> K >> M;

		int mLen[51];
		for(int i=0; i < N; i++)
			cin >> mLen[i];

		double nextProb[51][51];
		for(int i=0; i < N; i++)
			for(int j=0; j < N; j++)
				cin >> nextProb[i][j];

		int favor[11];
		for(int i=0; i < M; i++)
			cin >> favor[i];

		double ans[MOD][51] = {};
		bool changed[MOD][51] = {};

		ans[0][0] = 1;
		changed[0][0] = true;

		for(int i=1; i <= K; i++)
		{
			for(int j=0; j < N; j++)
			{
				changed[i % MOD][j] = false;
				ans[i % MOD][j] = 0;
				for(int k=0; k < N; k++)
				{
					if(mLen[k] > i)
						continue;

					if(changed[(i-mLen[k]) % MOD][k])
					{
						changed[i % MOD][j] = true;
						ans[i % MOD][j] += ans[(i-mLen[k]) % MOD][k] * nextProb[k][j];
					}
				}
			}
		}

		for(int i=0; i < M; i++)
		{
			double ret = ans[K % MOD][favor[i]];
			for(int j=1; K-j >= 0 && j < mLen[favor[i]]; j++)
				ret += ans[(K-j) % MOD][favor[i]];
			cout << ret << " ";
		}
		cout << '\n';
	}
	return 0;
}