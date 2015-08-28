#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main()
{
	int T;
	scanf("%d",&T);

	while(T--)
	{
		int N;
		scanf("%d",&N);

		map<int, int> nerd;
		int ans=0;
		for(int i=0; i < N; i++)
		{
			int problem, ramen;
			scanf("%d%d", &problem, &ramen);

			map<int,int>::iterator it = nerd.lower_bound(problem);
			if(it != nerd.end() && it->second > ramen)
			{
				ans += nerd.size();
				continue;
			}
			if(it != nerd.begin())
			{
				--it;
				while(true)
				{
					if(it->second > ramen)
						break;
					if(it == nerd.begin())
					{
						nerd.erase(it);
						break;
					}
					else
					{
						map<int, int>::iterator jt = it;
						--jt;
						nerd.erase(it);
						it = jt;
					}
				}
			}
			nerd[problem] = ramen;
			ans += nerd.size();
		}

		cout << ans << '\n';
	}

	return 0;
}