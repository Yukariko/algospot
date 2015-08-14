#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 987654321;
const int MAX_N = 15;

vector<string> a;
int dp[MAX_N+1][MAX_N+1];
int N;

bool pass(string &p, string &q, int pos)
{
	for(int i=0; p[i+pos] && q[i]; i++)
		if(p[i+pos] != q[i])
			return false;
	return true;
}

int cache[MAX_N+1][1<<MAX_N];
int choose[MAX_N+1][1<<MAX_N];

int solve(int last, int used)
{
	if(used == (1 << N) - 1)
		return 0;

	int& ret = cache[last][used];
	if(ret != -1)
		return ret;

	ret = 0;
	for(int next = 0; next < N; next++)
	{
		if((used & (1 << next)) == 0)
		{
			int cand = dp[last][next] + solve(next, used | (1 << next));
			if(ret <= cand)
			{
				ret = cand;
				choose[last][used] = next;
			}
		}
	}

	return ret;
}

string construct(int last, int used)
{
	if(used == (1 << N) - 1)
		return "";
	int sel = choose[last][used];
	return a[sel].substr(dp[last][sel]) + construct(sel, used | (1 << sel));
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		memset(dp, 0, sizeof(dp));
		memset(cache, -1, sizeof(cache));
		memset(choose, -1, sizeof(choose));
		a.clear();

		cin >> N;

		string b[MAX_N];
		for(int i=0; i < N; i++)
			cin >> b[i];

		for(int i=0; i < N; i++)
		{
			bool overlap = false;
			for(int j=0; j < N; j++)
			{
				if(i != j && b[j].find(b[i]) != -1)
				{
					overlap = true;
					b[i][0] = 0;
					break;
				}
			}
			if(overlap == false)
				a.push_back(b[i]);
		}

		N = a.size();
		for(int i=0; i < N; i++)
		{
			for(int j=0; j < N; j++)
			{
				if(i==j)
					continue;
				for(int k=0; a[i][k]; k++)
				{
					if(pass(a[i], a[j], k))
					{
						dp[i][j] = a[i].length() - k;
						break;
					}
				}
			}
		}
		
		int sum = 0;
		for(int i=0; i < N; i++)
			sum += a[i].length();

		int len = solve(15, 0);
		cout << construct(15, 0) << '\n';
	}
	return 0;
}