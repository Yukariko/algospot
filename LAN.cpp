#include <bits/stdc++.h>

using namespace std;

const double INF = 1e10;

int N, M;

pair<int, int> a[501];
double d[501][501];

double getDist(const pair<int, int>& p, const pair<int, int>& q)
{
	return sqrt((p.first - q.first) * (p.first - q.first) + (p.second - q.second) * (p.second - q.second));
}

double prim()
{
	int V = N;
	double ans = 0;

	vector<bool> added(V, false);

	vector<double> minWeight(V, INF);
	vector<int> parent(V, -1);

	minWeight[0] = parent[0] = 0;

	for(int iter = 0; iter < V; ++iter)
	{
		int u = -1;
		for(int v = 0; v < V; ++v)
			if(!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;

		ans += minWeight[u];
		added[u] = true;

		for(int i=0; i < V; ++i)
		{
			int v = i;
			double weight = d[u][i];
			if(!added[v] && minWeight[v] > weight)
			{
				minWeight[v] = weight;
				parent[v] = u;
			}
		}
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d%d", &N, &M);
		for(int i=0; i < N; i++)
			scanf("%d", &a[i].first);
		for(int i=0; i < N; i++)
			scanf("%d", &a[i].second);

		for(int i=0; i < N; i++)
			for(int j=0; j < N; j++)
				d[i][j] = getDist(a[i], a[j]);

		for(int i=0; i < M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			d[u][v] = 0;
			d[v][u] = 0;
		}

		printf("%.10f\n", prim());
	}
	return 0;
}