#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		char a[11];
		int N, M;
		scanf("%s%d%d", a, &N, &M);

		int len = strlen(a);
		sort(a, a + len);

		bool find = false;

		static pair<int, int> parent[2][10000];
		static char choice[2][10000];
		fill(&parent[0][0], &parent[2][0], pair<int,int>(-1, -1));

		queue<pair<int, bool>> bfs;
		for(int i=0; a[i]; i++)
		{
			if(a[i] != '0')
			{
				int u = a[i] - '0' >= N;
				int n = (a[i] - '0') % N;
				bfs.push({n, u});
				choice[u][n] = a[i];
			}
		}

		while(!bfs.empty())
		{
			int m = bfs.front().first;
			bool u = bfs.front().second;
			bfs.pop();

			if(m == M && u)
			{
				find = true;
				break;
			}

			for(int i=0; a[i]; i++)
			{
				int nm = (m * 10 + a[i] - '0');
				bool nu = u || nm >= N;
				nm %= N;
				if(parent[nu][nm].first == -1)
				{
					parent[nu][nm] = {u, m};
					choice[nu][nm] = a[i];
					bfs.push({nm % N, nu});
				}
			}
		}

		if(!find)
			puts("IMPOSSIBLE");
		else
		{
			string ans;
			int u = 1;
			int n = M;
			while(parent[u][n].first != -1)
			{
				ans += choice[u][n];
				int nu = parent[u][n].first;
				int nm = parent[u][n].second;
				u = nu;
				n = nm;
			}
			ans += choice[u][n];

			reverse(ans.begin(), ans.end());
			puts(ans.c_str());
		}
	}
	return 0;
}