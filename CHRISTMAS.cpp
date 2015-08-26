#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;

const int MOD = 20091101;

int waysToBuy(const vector<int>& psum, int K)
{
	vector<long long> count(K, 0);
	for(int i=0; i < psum.size(); i++)
		count[psum[i]]++;

	int ret = 0;
	for(int i=0; i < K; i++)
		ret = (ret + count[i] * (count[i] - 1) / 2) % MOD;
	return ret;
}

int maxBuys(const vector<int>& psum, int K)
{
	vector<int> mBuys(psum.size());
	vector<int> prev(K, -1);

	mBuys[0] = 0;
	for(int i=0; i < psum.size(); i++)
	{
		if(i > 0)
			mBuys[i] = mBuys[i-1];

		int j = prev[psum[i]];
		if(j != -1)
			mBuys[i] = max(mBuys[i], mBuys[j] + 1);
		prev[psum[i]] = i;
	}
	return mBuys.back();
}

int main()
{
	int T;
	scanf("%d",&T);

	while(T--)
	{
		int N, K;
		scanf("%d%d",&N,&K);

		vector<int> a(N);
		for(int i=0; i < N; i++)
			scanf("%d",&a[i]);

		vector<int> psum(N+1);
		psum[0] = 0;
		for(int i=0; i < N; i++)
			psum[i+1] = (a[i] + psum[i]) % K;

		printf("%d %d\n",waysToBuy(psum, K), maxBuys(psum, K));
	}
	return 0;
}