#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int V, E;
int a[501];
int d[501][501][2];

int main()
{
	scanf("%d%d", &V, &E);
	for(int i=1; i <= V; i++)
		scanf("%d", &a[i]);

	for(int i=1; i <= V; i++)
	{
		for(int j=1; j <= V; j++)
			d[i][j][0] = d[i][j][1] = INF;
		d[i][i][0] = d[i][i][1] = 0;
	}

	for(int i=0; i < E; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		d[u][v][0] = d[v][u][0] = d[u][v][1] = d[v][u][1] = w;
	}

	vector<pair<int, int>> order(V+1);
	for(int i=1; i <= V; i++)
		order[i].first = a[i], order[i].second = i;

	sort(order.begin()+1, order.end());

	for(int k=1; k <= V; k++)
	{
		int w = order[k].second;
		for(int i=1; i <= V; i++)
			for(int j=1; j <= V; j++)
			{
				d[i][j][0] = min(d[i][j][0], d[i][w][0] + d[w][j][0]);
				d[i][j][1] = min(d[i][j][1], d[i][w][0] + a[w] + d[w][j][0]);
			}
	}

	int T;
	scanf("%d", &T);

	while(T--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", d[u][v][1]);
	}

	return 0;
}