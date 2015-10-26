#include <bits/stdc++.h>

using namespace std;

const int NUM = 26;
int toNum(char ch) {return ch - 'a';}

struct TrieNode
{
	int no;
	int terminal;
	TrieNode* children[NUM];
	TrieNode *fail;
	vector<int> output;

	TrieNode() : terminal(-1), fail(NULL)
	{
		memset(children, 0, sizeof(children));
	}

	~TrieNode()
	{
		for(int i=0; i < NUM; i++)
			if(children[i])
				delete children[i];
	}

	void insert(const char* key, int id)
	{
		if(*key == 0)
			terminal = id;
		else
		{
			int next = toNum(*key);
			if(children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(key+1, id);
		}
	}

	TrieNode* find(const char* key)
	{
		if(*key == 0)
			return this;
		int next = toNum(*key);
		if(children[next] == NULL)
			return NULL;
		return children[next]->find(key+1);
	}

	static void computeFailFunc(TrieNode *root)
	{
		queue<TrieNode*> q;
		root->fail = root;
		q.push(root);

		int num = 0;

		while(!q.empty())
		{
			TrieNode* here = q.front();
			q.pop();

			here->no = num++;

			for(int edge=0; edge < NUM; edge++)
			{
				TrieNode* child = here->children[edge];
				if(!child)
					continue;
				if(here == root)
					child->fail = root;
				else
				{
					TrieNode* t = here->fail;
					while(t != root && t->children[edge] == NULL)
						t = t->fail;
					if(t->children[edge])
						t = t->children[edge];
					child->fail = t;
				}

				child->output = child->fail->output;
				if(child->terminal != -1)
					child->output.push_back(child->terminal);
				q.push(child);
			}
		}
	}

	static vector<pair<int,int>> ahoCorasick(const char* s, TrieNode* root)
	{
		vector<pair<int,int>> ret;
		TrieNode* state = root;

		for(size_t i=0; s[i]; i++)
		{
			int chr = toNum(s[i]);
			while(state != root && state->children[chr] == NULL)
				state = state->fail;
			if(state->children[chr])
				state = state->children[chr];
			for(size_t j=0; j < state->output.size(); j++)
				ret.push_back(make_pair(i, state->output[j]));
		}
		return ret;
	}
};

const int MOD = 10007;

TrieNode *root;

int alphaPow[101];
int N, M;

int cache[101][1001];

int solve(TrieNode* trie, int pos)
{
	if(trie->output.size())
		return 0;
	if(pos == N)
		return 1;

	int& ret = cache[pos][trie->no];
	if(ret != -1)
		return ret;
	ret = 0;
	for(int i=0; i < 26; i++)
	{
		if(trie->children[i] == NULL)
		{
			TrieNode *state = trie;
			while(state != state->fail && state->children[i] == NULL)
				state = state->fail;
			if(state->children[i])
				state = state->children[i];
			ret = (ret + solve(state, pos+1)) % MOD;
		}
		else
			ret = (ret + solve(trie->children[i], pos+1)) % MOD;
	}

	return ret;
}

int main()
{
	alphaPow[0] = 26;
	for(int i=1; i < 100; i++)
		alphaPow[i] = (alphaPow[i] * 26) % MOD;

	int T;
	scanf("%d",&T);

	while(T--)
	{
		memset(cache, -1, sizeof(cache));
		scanf("%d%d",&N,&M);

		TrieNode trie;
		root = &trie;
		char a[11];
		while(M--)
		{
			scanf("%s",a);
			trie.insert(a, M);
		}

		TrieNode::computeFailFunc(&trie);

		printf("%d\n", solve(&trie,0));

	}
	return 0;
}