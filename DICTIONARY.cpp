#include <bits/stdc++.h>

using namespace std;

bool graph[26][26];
bool visit[26];
int trans[26];

bool dfs(int pos, vector<int>& order)
{
	visit[pos] = true;
	for(int i=0; i < 26; i++)
		if(graph[pos][i] && visit[i] == false)
			dfs(i, order);
	order.push_back(pos);
	return true;
}

vector<int> topologySort()
{
	vector<int> order;

	memset(visit, false, sizeof(visit));
	for(int i=0; i < 26; i++)
		if(visit[i] == false)
			dfs(i, order);
	reverse(order.begin(), order.end());
	for(int i=0; i < 26; i++)
		for(int j=i+1; j < 26; j++)
			if(graph[order[j]][order[i]])
				return vector<int>();
	return order;
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int N;
		cin >> N;

		vector<string> a(N);
		for(int i=0; i < N; i++)
			cin >> a[i];

		memset(graph, false, sizeof(graph));
		
		for(int i=1; i < N; i++)
		{
			int pos = 0;
			while(a[i-1][pos] && a[i][pos] && a[i-1][pos] == a[i][pos])
				pos++;

			if(a[i-1][pos] == 0 || a[i][pos] == 0)
				continue;

			graph[a[i-1][pos]-'a'][a[i][pos]-'a'] = true;
		}

		vector<int> ans = topologySort();
		if(ans.empty())
		{
			cout << "INVALID HYPOTHESIS\n";
			continue;
		}
		for(auto p : ans)
			cout << (char)(p + 'a');
		cout << "\n";
	}

	return 0;
}