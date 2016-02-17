#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		int V, E, N;
		scanf("%d%d%d", &V, &E, &N);

		int d[201][201];
		for(int i=0; i < V; i++)
		{
			for(int j=0; j < V; j++)
				d[i][j] = INF;
			d[i][i] = 0;
		}

		for(int i=0; i < E; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			d[u][v] = d[v][u] = w;
		}

		for(int k=0; k < V; k++)
			for(int i=0; i < V; i++)
				for(int j=0; j < V; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		int ans = 0;
		for(int i=0; i < N; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);

			if(d[u][v] <= w)
			{
				ans++;
				continue;
			}

			d[u][v] = d[v][u] = w;
			for(int i=0; i < V; i++)
			{
				d[i][v] = min(d[i][v], d[i][u] + d[u][v]);
				d[v][i] = min(d[v][i], d[v][u] + d[u][i]);
			}
			
			for(int i=0; i < V; i++)
			{
				d[u][i] = min(d[u][i], d[u][v] + d[v][i]);
				d[i][u] = min(d[i][u], d[v][u] + d[u][i]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}