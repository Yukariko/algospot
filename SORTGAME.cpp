#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> toSort;

void precalc(int n)
{
	vector<int> perm(n);
	for(int i=0; i < n; i++)
		perm[i] = i;

	queue<vector<int>> q;
	q.push(perm);
	toSort[perm] = 0;

	int dist = 0;
	while(!q.empty())
	{
		int size = q.size();
		dist++;
		while(size--)
		{
			vector<int> here = q.front();
			q.pop();

			for(int i=0; i < n; i++)
			{
				for(int j=i+2; j <= n; j++)
				{
					reverse(here.begin() + i, here.begin() + j);
					if(toSort.count(here) == 0)
					{
						q.push(here);
						toSort[here] = dist;
					}
					reverse(here.begin() + i, here.begin() + j);
				}
			}
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for(int i=1; i <= 8; i++)
		precalc(i);

	while(T--)
	{
		int N;
		scanf("%d", &N);

		vector<int> a(N);
		for(int i=0; i < N; i++)
			scanf("%d", &a[i]);

		vector<int> b(N);
		for(int i=0; i < N; i++)
		{
			int small = 0;
			for(int j=0; j < N; j++)
				if(a[j] < a[i])
					small++;
			b[i] = small;
		}

		printf("%d\n", toSort[b]);
	}
	return 0;
}