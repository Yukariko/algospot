#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

class NetworkFlow
{
public:
	struct Edge 
	{
		int target, capacity, flow;
		Edge *reverse;

		int residualCapacity() const { return capacity - flow; }

		void push(int amt)
		{
			flow += amt;
			reverse->flow -= amt;
		}
	};

	NetworkFlow(int V) : V(V)
	{
		adj.resize(V);
	}

	~NetworkFlow()
	{
		for(int i=0; i < V; i++)
			for(size_t j=0; j < adj[i].size(); j++)
				delete adj[i][j];
	}

	void addEdge(int u, int v, int capacity)
	{
		Edge *uv = new Edge(), *vu = new Edge();

		uv->target = u;
		uv->capacity = capacity;
		uv->flow = 0;
		uv->reverse = vu;

		vu->target = v;
		vu->capacity = 0;
		vu->flow = 0;
		vu->reverse = uv;

		adj[u].push_back(uv);
		adj[v].push_back(vu);
	}

	int getMaximumFlow(int source, int sink)
	{
		int totalFlow = 0;

		while(true)
		{
			vector<pair<int, Edge*>> parent(V, {-1, nullptr});

			queue<int> q;
			parent[source].first = source;
			q.push(source);

			while(!q.empty() && parent[sink].first == -1)
			{
				int here = q.front();
				q.pop();

				for(size_t i=0; i < adj[here].size(); i++)
				{
					Edge *there = adj[here][i];
					int v = there->reverse->target;

					if(there->residualCapacity() > 0 && parent[v].first == -1)
					{
						q.push(v);
						parent[v] = {here, there};
					}
				}
			}

			if(parent[sink].first == -1)
				break;

			int amount = INF;
			for(int p = sink; p != source; p = parent[p].first)
				amount = min(amount, parent[p].second->residualCapacity());

			totalFlow += amount;
			for(int p = sink; p != source; p = parent[p].first)
			{
				Edge *uv = parent[p].second;
				uv->push(amount);
			}

		}

		return totalFlow;
	}

private:
	int V;
	vector<vector<Edge *>> adj;

};

const int dy[] = {1, 1};
const int dx[] = {1, -1};

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		int N;
		scanf("%d", &N);

		char a[8][9];
		for(int i=0; i < N; i++)
			scanf("%s", a[i]);

		int id[2][8][8];
		memset(id, -1, sizeof(id));

		int idx = 0;
		for(int d=0; d < 2; d++)
			for(int i=0; i < N; i++)
				for(int j=0; j < N; j++)
					if(a[i][j] == '.' && id[d][i][j] == -1)
					{
						int y = i, x = j;
						while(y >= 0 && y < N && x >= 0 && x < N && a[y][x] == '.')
						{
							id[d][y][x] = idx;
							y += dy[d];
							x += dx[d];
						}
						idx++;
					}

		NetworkFlow nf(idx + 2);

		int source = idx;
		int sink = idx+1;

		bool check[64][64] = {};
		bool check2[64] = {};
		for(int i=0; i < N; i++)
			for(int j=0; j < N; j++)
				if(id[0][i][j] != -1 && !check[id[0][i][j]][id[1][i][j]])
				{
					check[id[0][i][j]][id[1][i][j]] = true;
					if(!check2[id[0][i][j]])
					{
						check2[id[0][i][j]] = true;
						nf.addEdge(source, id[0][i][j], 1);
					}
					if(!check2[id[1][i][j]])
					{
						check2[id[1][i][j]] = true;
						nf.addEdge(id[1][i][j], sink, 1);
					}

					nf.addEdge(id[0][i][j], id[1][i][j], 1);
				}

		printf("%d\n", nf.getMaximumFlow(source, sink));
	}
	return 0;
}