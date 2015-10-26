#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

struct wTree
{
	bool end;
	int no;
	wTree *node[26];
	int first;

	wTree() : end(false), no(-1), first(-1)
	{
		memset(node, 0, sizeof(node));
	}

	~wTree()
	{
		for(int i=0; i < 26; i++)
			if(node[i])
				delete node[i];
	}

	void push(const char *str, int idx)
	{
		if(first == -1)
			first = idx;
		if(*str == 0)
		{
			no = idx;
			return;
		}

		wTree *&next = node[*str-'A'];
		if(next == 0)
			next = new wTree;

		return next->push(str+1, idx);
	}

	int find(const char *str)
	{
		if(*str == 0)
			return no;

		wTree *&next = node[*str-'A'];

		if(next == 0)
			return -2;

		return next->find(str+1);
	}

	int type(const char *str, int idx)
	{
		if(first == idx)
			return 1;
		if(*str == 0 || node[*str-'A'] == 0)
			return INF;
		return 1 + node[*str-'A']->type(str+1, idx);
	}
};

bool cmp(const pair<string,int>& p, const pair<string,int>& q)
{
	if(p.second != q.second)
		return p.second > q.second;
	return p.first < q.first;
}


int main()
{
	int T;
	scanf("%d",&T);

	while(T--)
	{
		int N, M;
		scanf("%d%d",&N,&M);

		vector<pair<string,int>> a(N);
		wTree trie;
		for(int i=0; i < N; i++)
			cin >> a[i].first >> a[i].second;

		sort(a.begin(), a.end(), cmp);
		for(int i=0; i < N; i++)
			trie.push(a[i].first.c_str(), i);

		int ans = 0;
		while(M--)
		{
			char a[11];
			scanf("%s",a);

			int len = strlen(a);
			int find = trie.find(a);
			if(find < 0)
			{
				ans += len;
				//printf("%d ", len);
			}
			else
			{
				int tab = trie.type(a, find) + (find == 0);
				ans += min(len, tab);
				//printf("%d ",tab);
			}
			ans++;
		}
		ans--;
		printf("%d\n", ans);
	}
	return 0;
}