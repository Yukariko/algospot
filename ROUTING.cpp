#include <bits/stdc++.h>

using namespace std;

int V, E;
vector<vector<pair<int, double>>> adj;

double dijkstra()
{
	vector<double> d(V+1, 0.0);

	d[0] = 1.0;

	priority_queue<pair<double, int>> pq;
	pq.push({-1.0, 0});

	while(!pq.empty())
	{
		double w = -pq.top().first;
		int here = pq.top().second;

		pq.pop();

		if(d[here] < w)
			continue;

		for(size_t i=0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			double w = adj[here][i].second;
			if(d[there] == 0.0 || d[there] > d[here] * w)
			{
				d[there] = d[here] * w;
				pq.push({-d[there], there});
			}
		}
	}


	return d[V-1];
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d%d", &V, &E);

		adj.clear();
		adj.resize(V+1);

		for(int i=0; i < E; i++)
		{
			int u, v;
			double w;
			scanf("%d%d%lf", &u, &v, &w);

			adj[u].push_back({v, w});
			adj[v].push_back({u, w});
		}

		printf("%.10f\n", dijkstra());
	}
	return 0;
}