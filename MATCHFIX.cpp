#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

class NetworkFlow
{
public:

	NetworkFlow(int V) : V(V)
	{
		memset(capacity, 0, sizeof(capacity));
		memset(flow, 0, sizeof(flow));
	}

	void clearFlow()
	{
		memset(flow, 0, sizeof(flow));	
	}

	void addEdge(int u, int v, int cap)
	{
		capacity[u][v] = cap;
	}

	void subEdge(int u, int v)
	{
		capacity[u][v] = 0;
	}

	int getMaximumFlow(int source, int sink)
	{
		memset(flow, 0, sizeof(flow));

		int totalFlow = 0;
		while(true)
		{
			vector<int> parent(V, -1);

			queue<int> q;
			parent[source] = source;
			q.push(source);
			int here;

			while(!q.empty() && parent[sink] == -1)
			{
				here = q.front();
				q.pop();

				for(int there = 0; there < V; there++)
				{
					if(capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
					{
						q.push(there);
						parent[there] = here;
					}
				}
			}

			if(parent[sink] == -1)
			{
				break;
			}

			int amount = INF;
			for(int p = sink; p != source; p = parent[p])
				amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

			totalFlow += amount;
			for(int p = sink; p != source; p = parent[p])
			{
				flow[parent[p]][p] += amount;
				flow[p][parent[p]] -= amount;
			}
		}

		return totalFlow;
	}

private:
	int V;
	int capacity[101][101];
	int flow[101][101];
};

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		int N, M;
		scanf("%d%d", &N, &M);

		vector<int> win(N);
		for(int i=0; i < N; i++)
			scanf("%d", &win[i]);

		vector<pair<int, int>> a(M);

		int canWin = 0;
		for(int i=0; i < M; i++)
		{
			scanf("%d%d", &a[i].first, &a[i].second);
			if(a[i].first == 0 || a[i].second == 0)
				canWin++;
		}

		NetworkFlow nf(1 + M + N + 1);

		int source = N + M;
		int sink = N + M + 1;

		for(int i=0; i < M; i++)
		{
			nf.addEdge(source, i, 1);
			nf.addEdge(i, M + a[i].first, 1);
			nf.addEdge(i, M + a[i].second, 1);
		}


		bool find = false;

		for(int totalWin = win[0]; totalWin <= win[0] + canWin; totalWin++)
		{
			if(*max_element(win.begin() + 1, win.end()) >= totalWin)
				continue;

			for(int i=0; i < N; i++)
			{
				int maxWin = (i == 0? totalWin: totalWin - 1);
				nf.addEdge(M + i, sink, maxWin - win[i]);
			}

			if(nf.getMaximumFlow(source, sink) == M)
			{
				find = true;
				printf("%d\n", totalWin);
				break;
			}
		}

		if(!find)
			puts("-1");
	}
	return 0;
}