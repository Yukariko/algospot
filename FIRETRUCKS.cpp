#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int V, E;
int N, M;

int a[1001];
int b[1001];

vector<vector<pair<int, int>>> adj;

int dijkstra(int S)
{
	vector<int> d(V+1, INF);

	d[S] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push({0, S});

	while(!pq.empty())
	{
		int w = -pq.top().first;
		int here = pq.top().second;

		pq.pop();

		if(d[here] < w)
			continue;

		for(size_t i=0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			int w = adj[here][i].second;
			if(d[there] > d[here] + w)
			{
				d[there] = d[here] + w;
				pq.push({-d[there], there});
			}
		}
	}

	int ans = INF;
	for(int i=0; i < M; i++)
		ans = min(ans, d[b[i]]);

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d%d%d%d", &V, &E, &N, &M);

		adj.clear();
		adj.resize(V+1);

		for(int i=0; i < E; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);

			adj[u].push_back({v, w});
			adj[v].push_back({u, w});
		}

		for(int i=0; i < N; i++)
			scanf("%d", &a[i]);

		for(int i=0; i < M; i++)
			scanf("%d", &b[i]);

		int ans = 0;
		for(int i=0; i < N; i++)
			ans += dijkstra(a[i]);

		printf("%d\n", ans);
	}
	return 0;
}