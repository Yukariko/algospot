#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

long long E;
int M;
int len;
char b[15];
char a[11];

#define CUT 7

int cnt;
short IDX[10000001];
short dp[CUT][2][20][11441];

int getIndex()
{
	int ret = 0;
	for(int i=0; i < 10; i++)
		for(int j=0; j < a[i]; j++)
			ret = ret * 10 + i;

	return IDX[ret];
}

void setIndex(int pos, int depth, int num)
{
	if(depth == CUT)
	{
		IDX[num] = cnt++;
		return;
	}

	for(int i=pos; i < 10; i++)
		setIndex(i, depth+1, num * 10 + i);
}

int solve(int pos, int same, int mod)
{
	if(pos == len)
		return mod == 0;

	short *idx;
	if(pos + CUT >= len)
	{
		idx = &dp[len-pos-1][same][mod][getIndex()];
		if(*idx != -1)
			return *idx;

		*idx = 0;
	}

	int ret = 0;

	int limit = 9;
	if(same == 1)
		limit = b[pos];

	for(int i=0; i <= limit; i++)
	{
		if(a[i])
		{
			a[i]--;
			ret = (ret + solve(pos+1, same & i==limit, (mod * 10 + i) % M)) % 1000000007;
			a[i]++;
		}
	}

	if(pos + CUT >= len)
		*idx = ret;

	return ret;
}

int main()
{
	setIndex(0,0,0);

	int T;
	cin >> T;
	while(T--)
	{
		memset(dp,-1,sizeof(dp));
		memset(a,0,sizeof(a));

		cin >> E >> M;
		len = sprintf(b, "%lld", E);

		for(int i=0; i < len; i++)
		{
			b[i] -= '0';
			a[b[i]]++;
		}

		cout << solve(0, 1, 0) - (E % M == 0) << "\n";
	}

	return 0;
}