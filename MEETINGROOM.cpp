#include <bits/stdc++.h>

using namespace std;

int N;
vector<vector<int>> adj;

bool disjoint(const pair<int, int>& p, const pair<int, int>& q)
{
	return p.second <= q.first || q.second <= p.first;
}

void makeGraph(const vector<pair<int, int>>& meetings)
{
	int vars = meetings.size();
	
	adj.clear();
	adj.resize(vars * 2);

	for(int i=0; i < vars; i += 2)
	{
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2);
		adj[j * 2 + 1].push_back(i * 2);
	}

	for(int i=0; i < vars; i++)
		for(int j=0; j < i; j++)
		{
			if(!disjoint(meetings[i], meetings[j]))
			{
				adj[i * 2].push_back(j * 2 + 1);
				adj[j * 2].push_back(i * 2 + 1);
			}
		}
}


vector<int> sccId, discovered, finished;
int sccCounter, vertexCounter;
stack<int> st;

vector<vector<int>> ans;

int scc(int here)
{
	int ret = discovered[here] = vertexCounter++;
	st.push(here);

	for(size_t i=0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];

		if(discovered[there] == -1)
			ret = min(ret, scc(there));
		else if(discovered[there] < discovered[here] && finished[there] != 1)
			ret = min(ret, discovered[there]);
	}

	if(ret == discovered[here])
	{
		ans.push_back(vector<int>());
		while(true)
		{
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			ans[sccCounter].push_back(t);
			finished[t] = 1;
			if(t == here)
				break;
		}
		sccCounter++;
	}

	return ret;
}

vector<int> tarjanSCC()
{
	sccId = discovered = finished = vector<int>(adj.size(), -1);
	sccCounter = vertexCounter = 0;

	for(int i=0; i < adj.size(); i++)
		if(discovered[i] == -1)
			scc(i);
	return sccId;
}



vector<int> solve2SAT()
{
	int n = adj.size() / 2;
	vector<int> label = tarjanSCC();

	for(int i=0; i < 2 * n; i+=2)
		if(label[i] == label[i+1])
			return vector<int>();

	vector<int> value(n, -1);

	vector<pair<int, int>> order;
	for(int i=0; i < 2 * n; i++)
		order.push_back({-label[i], i});

	sort(order.begin(), order.end());

	for(int i=0; i < 2 * n; i++)
	{
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex % 2 == 0;
		if(value[variable] != -1)
			continue;

		value[variable] = !isTrue;
	}
	return value;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d", &N);

		vector<pair<int, int>> a(N * 2);
		for(int i=0; i < N; i++)
			scanf("%d%d%d%d", &a[2 * i].first, &a[2 * i].second, &a[2 * i + 1].first, &a[2 * i + 1].second);

		makeGraph(a);

		vector<int> ans = solve2SAT();
		if(ans.empty())
			puts("IMPOSSIBLE");
		else
		{
			puts("POSSIBLE");
			for(size_t i=0; i < ans.size(); i+=2)
			{
				if(ans[i] == 1 || ans[i+1] == 0)
					printf("%d %d\n", a[i].first, a[i].second);
				else
					printf("%d %d\n", a[i + 1].first, a[i + 1].second);
			}
		}
	}

	return 0;
}