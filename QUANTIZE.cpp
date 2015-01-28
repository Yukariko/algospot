#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF=987654321;

int N,S;
int A[101];
int dp[101][11];
int avg(int p,int q)
{
	int avg=0;
	for(int i=p;i<q;i++)
	{
		avg+=A[i];
	}
	avg /= q-p;

	int ret=INF;
	for(int i=-1;i<=1;i++)
	{
		int temp=0;
		for(int j=p;j<q;j++)
		{
			temp+=(A[j] - (avg+i)) * (A[j] - (avg+i));
		}
		ret = min(ret, temp);
	}
	return ret;
}

int solve(int pos,int chance)
{
	if(pos == N) return 0;
	if(!chance) return INF;

	int& ret=dp[pos][chance];
	if(ret != INF) return ret;

	for(int i=pos+1;i<=N;i++)
	{
		ret = min(ret, avg(pos,i) + solve(i,chance-1));
	}
	return ret;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		scanf("%d%d",&N,&S);
		for(int i=0;i<N;scanf("%d",A+i++));
		for(int i=0;i<N;i++)
		{
			for(int j=1;j<=S;j++)
			{
				dp[i][j]=INF;
			}
		}
		sort(A,A+N);
		printf("%d\n",solve(0,S));
	}
}