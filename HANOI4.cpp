#include <bits/stdc++.h>

using namespace std;

vector<char> visit[12];

int setRing(int state, int n, int v)
{
	state &= ~(3 << (n * 2));
	state |= v << (n * 2);
	return state;
}

void precalc(int state, int N)
{
	queue<int> bfs;

	bfs.push(state);
	visit[N-1][state] = 0;

	int ans = 1;
	while(!bfs.empty())
	{
		int size = bfs.size();
		while(size--)
		{
			int s = bfs.front();
			bfs.pop();

			int top[4] = {-1, -1, -1, -1};
			for(int i=0, n = s; i < N; i++, n >>= 2)
				if(top[n & 3] == -1)
					top[n & 3] = i;

			for(int i=0; i < 4; i++)
				if(top[i] != -1)
					for(int j=0; j < 4; j++)
						if(i != j && (top[i] < top[j] || top[j] == -1)) 
						{
							int next = setRing(s, top[i], j);

							if(visit[N-1][next] == -1 || visit[N-1][next] > ans)
							{
								visit[N-1][next] = ans;
								bfs.push(next);
							}
						}
		}
		ans++;
	}
}

int main()
{
	for(int i=0; i < 12; i++)
		visit[i].resize(1 << ((i+1) * 2), -1);
	for(int i=1; i <= 12; i++)
		precalc((1 << (i * 2)) - 1, i);

	int T;
	scanf("%d", &T);

	while(T--)
	{
		int N;
		scanf("%d", &N);

		int state = 0;
		for(int i=0; i < 4; i++)
		{
			int l;
			scanf("%d", &l);
			while(l--)
			{
				int n;
				scanf("%d", &n);
				n--;
				state = setRing(state, n, i);
			}
		}

		printf("%d\n", visit[N-1][state]);
	}
	return 0;
}