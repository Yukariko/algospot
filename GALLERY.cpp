#include <bits/stdc++.h>

using namespace std;

int G, H;
vector<vector<int>> adj;
vector<bool> visit;

const int WATCHED = 0;
const int UNWATCHED = 1;
const int INSTALLED = 2;

int installed;

int dfs(int here)
{
	visit[here] = true;
	bool children[3] = {};

	for(size_t i=0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];
		if(!visit[there])
			children[dfs(there)] = true;
	}

	if(children[UNWATCHED])
	{
		installed++;
		return INSTALLED;
	}

	if(children[INSTALLED])
		return WATCHED;

	return UNWATCHED;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d%d", &G, &H);

		adj = vector<vector<int>>(G + 1);
		visit = vector<bool>(G+1, false);

		for(int i=0; i < H; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		installed = 0;
		for(int i=0; i < G; i++)
			if(!visit[i] && dfs(i) == UNWATCHED)
				installed++;

		printf("%d\n", installed);
	}
	return 0;
}