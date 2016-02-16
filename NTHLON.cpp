#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int N;
pair<int, int> a[501];

const int START = 401;

int vertex(int delta)
{
	return delta + 200;
}

int dijkstra()
{
	vector<vector<pair<int, int>>> adj(410);
	int V = 402;

	for(int i=0; i < N; i++)
	{
		int delta = a[i].first - a[i].second;
		adj[START].push_back({vertex(delta), a[i].first});
	}

	for(int delta = -200; delta <= 200; delta++)
	{
		for(int i=0; i < N; i++)
		{
			int next = delta + a[i].first - a[i].second;
			if(abs(next) > 200)
				continue;

			adj[vertex(delta)].push_back({vertex(next), a[i].first});
		}
	}

	vector<int> d(V, INF);

	priority_queue<pair<int, int>> pq;
	pq.push({0, START});
	d[START] = 0;

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

	return d[vertex(0)];
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d", &N);
		for(int i=0; i < N; i++)
			scanf("%d%d", &a[i].first, &a[i].second);

		int ans = dijkstra();
		if(ans == INF)
			puts("IMPOSSIBLE");
		else
			printf("%d\n", ans);
	}
	return 0;
}