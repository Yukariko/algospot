#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const long long MOD = 1LL << 32;

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int K, N;
		cin >> K >> N;

		long long a = 1983;

		queue<long long> last_signal;

		int ans = 0;
		long long current_sum = 0;
		for(int i=0; i < N; i++)
		{
			current_sum += a % 10000 + 1;
			while(!last_signal.empty() && current_sum > K)
			{
				current_sum -= last_signal.front();
				last_signal.pop();
			}

			if(current_sum == K)
				ans++;

			last_signal.push(a % 10000 + 1);
			a = (a * 214013 + 2531011) % MOD;
		}

		cout << ans << '\n';
	}
	return 0;
}