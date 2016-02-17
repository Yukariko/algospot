#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int M = 98765432;

int V, E;

vector<vector<pair<int, int>>> adj;

bool reachable[101][101];

int bellmanford()
{
	for(int k=0; k < V; k++)
		for(int i=0; i < V; i++)
			for(int j=0; j < V; j++)
				reachable[i][j] |= reachable[i][k] && reachable[k][j];

	vector<int> upper(V, INF);

	upper[0] = 0;
	bool updated;

	bool cycle = false;

	for(int i=0; i < V; i++)
	{
		updated = false;

		for(int here = 0; here < V; here++)
		{
			for(size_t j=0; j < adj[here].size(); j++)
			{
				int there = adj[here][j].first;
				int w = adj[here][j].second;

				if(upper[there] > upper[here] + w)
				{
					if(i == V-1 && (reachable[there][1] || reachable[here][1]))
						cycle = true;
					upper[there] = upper[here] + w;
					updated = true;
				}
			}
		}

		if(!updated)
			break;
	}

	if(upper[1] >= INF-M)
		return -INF;

	if(cycle)
		return INF;
	
	return upper[1];
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d%d", &V, &E);

		adj.clear();
		adj.resize(V);

		memset(reachable, false, sizeof(reachable));
		for(int i=0; i < V; i++)
			reachable[i][i] = true;

		for(int i=0; i < E; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			adj[u].push_back({v, w});
			reachable[u][v] = true;
		}

		int past = bellmanford();

		if(past == -INF)
		{
			puts("UNREACHABLE");
			continue;
		}

		if(past == INF)
			printf("INFINITY ");
		else
			printf("%d ", past);

		for(size_t i=0; i < V; i++)
			for(size_t j=0; j < adj[i].size(); j++)
				adj[i][j].second = -adj[i][j].second;

		int present = bellmanford();
		if(present == INF)
			printf("INFINITY\n");
		else
			printf("%d\n", -present);

	}
	return 0;
}