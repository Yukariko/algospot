#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
const int MOD = 1000000007;

int dp[101];

int solve(int n)
{
	if(n <= 1) return 1;
	int& ret = dp[n];
	if(ret) return ret;
	return ret = (solve(n-1) + solve(n-2)) % MOD;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		scanf("%d",&N);
		int ret = N%2==0?(solve(N) - solve(N/2) - solve(N/2-1)) % MOD:(solve(N) - solve(N/2)) % MOD;
		if(ret < 0) ret += MOD;
		printf("%d\n",ret);
	}
}