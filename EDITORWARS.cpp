#include <bits/stdc++.h>

using namespace std;

struct DisjointSet
{
	vector<int> parent, rank, size, enemy;
	DisjointSet(int n) : parent(n), rank(n, 1), enemy(n, -1), size(n, 1)
	{
		for(int i=0; i < n; i++)
			parent[i] = i;
	}

	int findSize(int u)
	{
		u = find(u);
		return size[u];
	}

	int find(int u)
	{
		if(u == parent[u])
			return u;
		return parent[u] = find(parent[u]);
	}

	int merge(int u, int v)
	{
		if(u == -1 || v == -1)
			return max(u, v);
		u = find(u);
		v = find(v);
		if(u == v)
			return u;
		if(rank[u] > rank[v])
			swap(u, v);

		parent[u] = v;
		size[v] += size[u];
		if(rank[u] == rank[v])
			++rank[v];
		return v;
	}

	bool dis(int u, int v)
	{
		u = find(u);
		v = find(v);
		if(u == v)
			return false;

		int a = merge(u, enemy[v]);
		int b = merge(v, enemy[u]);
		enemy[a] = b;
		enemy[b] = a;
		return true;
	}
	bool ack(int u, int v)
	{
		u = find(u);
		v = find(v);
		if(enemy[u] == v)
			return false;

		int a = merge(u, v);
		int b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		if(b != -1)
			enemy[b] = a;
		return true;
	}
};

int main()
{
	int T;
	scanf("%d",&T);

	while(T--)
	{
		int N, M;
		scanf("%d%d",&N,&M);

		DisjointSet djs(N);

		bool contradict = false;
		int ans = 0;

		for(int i=1; i <= M; i++)
		{
			char m[4];
			int a, b;
			scanf("%s%d%d",m,&a,&b);

			if(contradict)
				continue;

			if(string(m) == "ACK")
			{
				if(!djs.ack(a, b))
					contradict = true;
			}
			else
			{
				if(!djs.dis(a, b))
					contradict = true;
			}

			if(contradict)
				ans = i;
		}
	
		if(contradict)
			printf("CONTRADICTION AT %d\n", ans);
		else
		{
			for(int node=0; node < N; node++)
			{
				if(djs.find(node) == node)
				{
					int enemy = djs.enemy[node];
					if(enemy > node)
						continue;
					int mySize = djs.size[node];
					int enemySize = (enemy == -1? 0 : djs.size[enemy]);
					ans += max(mySize, enemySize);
				}
			}
			printf("MAX PARTY SIZE IS %d\n", ans);
		}
	}
	return 0;
}