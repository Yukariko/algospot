#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

const int INF = 87654321;
char S[10001];
int dp[10001];

int solve(int pos)
{
	// Base
	if(!S[pos]) return 0;
	if(!S[pos+1]||!S[pos+2]) return INF;

	int& ret=dp[pos];
	if(ret != INF) return ret;

	// Level 1
	for(int i=1;i<5 && S[pos+i];i++)
	{
		if(S[pos+i-1] != S[pos+i])
			break;
		if(i>=2)
		{
			ret = min(ret,1+solve(pos+i+1));
		}
	}
	// Level 2
	int count = S[pos+1] - S[pos];
	if(count == 1 || count == -1)
	{
		for(int i=1;i<5 && S[pos+i];i++)
		{
			if(S[pos+i] - S[pos+i-1] != count)
				break;
			if(i >= 2)
			{
				ret = min(ret,2+solve(pos+i+1));
			}
		}
	}
	// Level 3
	int p=S[pos],q=S[pos+1];
	for(int i=0;i<5 && S[pos+i];i++)
	{
		if((i&1)==0 && p != S[pos+i])
			break;
		else if((i&1) && q != S[pos+i])
			break;
		if(i>=2)
		{
			ret = min(ret,4+solve(pos+i+1));
		}
	}
	// Level 4
	if(count != 1 && count != -1)
	{
		for(int i=1;i<5 && S[pos+i];i++)
		{
			if(S[pos+i] - S[pos+i-1] != count)
				break;
			if(i >= 2)
			{
				ret = min(ret,5+solve(pos+i+1));
			}
		}
	}
	// Level 5
	for(int i=2;i<5 && S[pos+i];i++)
	{
		ret = min(ret, 10+solve(pos+i+1));
	}
	return ret;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		gets(S);
		for(int i=0;S[i];i++)dp[i]=INF;
		printf("%d\n",solve(0));
	}
}