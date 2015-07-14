#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N, Q;
char a[501][11];
double prob_first[501];
double prob_next[501][501];
double prob_trans[501][501];

int M;
char b[101][11];
int idx[101];

int res[101][501];

double dp[101][501];

double solve(int pos, int prev)
{
	if(pos == M)
		return 0.0;

	double &ret = dp[pos][prev];
	if(ret != 1.0)
		return ret;

	ret = -1e200;

	for(int i=0; i < N; i++)
	{
		double prob_now = prob_trans[i][idx[pos]] + prob_next[prev][i];
		prob_now += solve(pos+1, i);

		if(ret < prob_now)
		{
			ret = prob_now;
			res[pos][prev] = i;
		}
	}

	return ret;
}

void pre_solve()
{
	double &ret = dp[0][0];

	for(int i=0; i < M; i++)
		for(int j=0; j < N; j++)
			dp[i][j] = 1.0;

	ret = -1e200;

	for(int i=0; i < N; i++)
	{
		double prob_now = prob_trans[i][idx[0]] + prob_first[i] + solve(1, i);
		if(ret < prob_now)
		{
			ret = prob_now;
			res[0][0] = i;
		}
	}
}

void print(int pos, int prev)
{
	if(pos == M)
		return;

	printf("%s ", a[res[pos][prev]]);
	print(pos+1, res[pos][prev]);
}

int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=0; i < N; i++)
		scanf("%s",a[i]);

	for(int i=0; i < N; i++)
	{
		scanf("%lf",&prob_first[i]);
		prob_first[i] = log(prob_first[i]);
	}

	for(int i=0; i < N; i++)
	{
		for(int j=0; j < N; j++)
		{
			scanf("%lf",&prob_next[i][j]);
			prob_next[i][j] = log(prob_next[i][j]);
		}
	}

	for(int i=0; i < N; i++)
	{
		for(int j=0; j < N; j++)
		{
			scanf("%lf",&prob_trans[i][j]);
			prob_trans[i][j] = log(prob_trans[i][j]);
		}
	}

	while(Q--)
	{
		scanf("%d",&M);

		for(int i=0; i < M; i++)
		{
			scanf("%s",b[i]);
			for(int j=0; j < N; j++)
			{
				if(strcmp(b[i], a[j]) == 0)
				{
					idx[i] = j;
					break;
				}
			}
		}

		pre_solve();

		print(0,0);
		puts("");
	}
	return 0;
}