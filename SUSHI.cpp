#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N, M;
		cin >> N >> M;

		int a[21], b[21];
		for(int i=0; i < N; i++)
			cin >> a[i] >> b[i];

		int window[40001]={};
		int visit[40001]={};

		int ans = 0;
		for(int money=0, t=2; money < M; money += 40000, t++)
		{
			int size = min(M - money, 40000);

			for(int i=0; i <= size; i+=100)
			{
				for(int j=0; j < N; j++)
				{
					if(a[j] <= size)
					{
						if(i >= a[j])
						{
							visit[i] = t;
							window[i] = max(window[i], window[i-a[j]] + b[j]);
							ans = max(ans, window[i]);
						}
						else if(visit[i - a[j] + 40000])
						{
							visit[i-a[j]+40000] = t;
							window[i] = max(window[i], window[i-a[j]+40000] + b[j]);
							ans = max(ans, window[i]);
						}
					}
				}
			}
		}

		cout << ans << '\n';
	}
	return 0;	
}