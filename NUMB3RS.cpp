#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int N,D,P,T,Q;
char map[51][51];
double dp[101][51];
int numPass[51];

double solve(int day,int state)
{
  if(!day) return state == Q? 1.0: 0.0;
  double& ret = dp[day][state];
  if(ret) return ret;
  int count = numPass[state];

  for(int i=0;i<N;i++)
  {
    if(map[state][i])
    {
      ret += solve(day-1,i) / count;
    }
  }

  return ret;
}

int main()
{
  int C;
  for(scanf("%d",&C);C--;)
  {
    scanf("%d%d%d",&N,&D,&P);
    for(int i=0;i<N;i++)
    {
      numPass[i] = 0;
      for(int j=0;j<N;j++)
      {
        scanf("%1d",&map[i][j]);
        if(map[i][j]) numPass[i]++;
      }
    }

    for(scanf("%d",&T);T--;)
    {
      scanf("%d",&Q);
      memset(dp,0,sizeof(dp));
      printf("%.8f ",solve(D,P));
    }
    puts("");
  }
}