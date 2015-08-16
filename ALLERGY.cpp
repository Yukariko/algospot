#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

const int INF = 987654321;

int N, M;
vector<long long> eatperson;

int minimum;

void solve(long long eat, long long who, int cnt)
{
	if(cnt >= minimum)
		return;

	if(who == (1LL << N) - 1)
	{
		minimum = min(minimum,cnt);
		return;
	}

	int find = -1;
	for(int i=0; i < N; i++)
	{
		if((who & (1LL << i)) == 0)
		{
			find = i;
			break;
		}
	}



	for(int i=0; i < M; i++)
		if((eat & (1LL << i)) == 0 && (eatperson[i] & (1LL << find)))
			solve(eat | (1LL << i), who | eatperson[i], cnt+1);
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		cin >> N >> M;
		
		map<string,int> names;
		for(int i=0; i < N; i++)
		{
			string name;
			cin >> name;
			names[name] = i;
		}


		eatperson.resize(M);
		for(int i=0; i < M; i++)
		{
			int cnt;
			cin >> cnt;

			eatperson[i] = 0;

			for(int j=0; j < cnt; j++)
			{
				string name;
				cin >> name;

				eatperson[i] |= 1LL << names[name];
			}
		}

		minimum = INF;
		solve(0,0,0);
		cout << minimum << '\n';
	}
	return 0;
}