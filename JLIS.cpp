#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

int N,M;
int A[101],B[101];
int dp[101][101];

int solve(int aPos, int bPos, int last)
{
	if(aPos == N && bPos == M) return 0;

	int& ret=dp[aPos][bPos];
	if(ret) return ret;

	for(int i=aPos;i<N;i++)
	{
		if(last < A[i])
		{
			ret = max(ret,1 + solve(i+1, bPos, A[i]));
		}
	}
	for(int i=bPos;i<M;i++)
	{
		if(last < B[i])
		{
			ret = max(ret,1 + solve(aPos, i+1, B[i]));
		}
	}
	return ret;
}

int main()
{
	int C;
	scanf("%d",&C);
	for(;C--;)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",A+i);
		for(int i=0;i<M;i++)scanf("%d",B+i);
		memset(dp,0,sizeof(dp));
		printf("%d\n",solve(0,0,INT_MIN));
	}
}