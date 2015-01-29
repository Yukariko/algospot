#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 10000000;

int N;
int dp[101][101];

int solve(int pos, int lastPutCount)
{
	if(!pos) return 1;
	int& ret = dp[pos][lastPutCount];

	if(ret) return ret;
	for(int i=1;i<=pos;i++)
	{
		ret = (ret + ((i + lastPutCount - 1) * solve(pos-i,i)) % MOD ) % MOD;
	}

	return ret % MOD;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		scanf("%d",&N);
		int ret = 0;
		for(int i=1;i<=N;i++)
		{
			ret = (ret + solve(N-i,i)) % MOD;
		}
		printf("%d\n",ret);
	}
}