#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int N;
		cin >> N;

		int a[101];
		priority_queue<int> pq;

		for(int i=0; i < N; i++)
		{
			cin >> a[i];
			pq.push(-a[i]);
		}

		int ans = 0;
		int cat = 0;
		while(pq.size() > 1)
		{
			int p, q;
			p = -pq.top();
			pq.pop();

			q = -pq.top();
			pq.pop();

			ans += p+q;

			pq.push(-p-q);
		}
		cout << ans << '\n';
	}
	return 0;
}