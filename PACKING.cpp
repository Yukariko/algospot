#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int N,W;

typedef struct PACK {
	char name[21];
	int weight;
	int count;
	int last;
} PACK;

PACK p[101];
int dp[101][1001];
int resN;
int res[101][1001];
int start;
int solve(int pos,int w)
{

	int& ret=dp[pos+1][w];
	if(ret!=-1)return ret;
	ret = 0;
	int sel = -1;
	for(int i=pos+1; i<N; i++)
	{
		if(p[i].weight <= w)
		{
			int t = p[i].count + solve(i, w - p[i].weight);
			if(ret < t)
			{
				ret = t;
				sel = i;
			}
		}
	}
	res[pos+1][w] = sel;
	return ret;
}

void build(int pos,int w,vector<int> &seq)
{
	if(pos!=-1) seq.push_back(pos);
	int next = res[pos+1][w];
	if(next != -1) build(next,w-p[next].weight,seq);
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		memset(dp,-1,sizeof(dp));
		memset(res,-1,sizeof(res));
		scanf("%d%d ",&N,&W);
		for(int i=0;i<N;i++)
		{
			scanf("%s%d%d ",p[i].name,&p[i].weight,&p[i].count);
		}
		printf("%d ",solve(-1,W));
		vector<int> ret;
		build(-1,W,ret);
		printf("%d\n",ret.size());
		for(int i=0;i<ret.size();i++)puts(p[ret[i]].name);
	}
}