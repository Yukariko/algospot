#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

vector<int> getPartialMatch(const string& N)
{
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1, matched = 0;
	while(begin + matched < m)
	{
		if(N[begin + matched] == N[matched])
		{
			++matched;
			pi[begin+matched-1] = matched;
		}
		else
		{
			if(matched == 0)
				++begin;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int kmpSearch(const string& H, const string& N)
{
	int n = H.size(), m = N.size();

	vector<int> pi = getPartialMatch(N);

	int matched = 0;
	for(int i=0; i < n; i++)
	{
		while(matched > 0 && H[i] != N[matched])
			matched = pi[matched - 1];

		if(H[i] == N[matched])
		{
			++matched;
			if(matched == m)
				return i - m + 1;
		}
	}
	return -1;
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int N;
		cin >> N;

		N++;
		vector<string> dial(N);

		cin >> dial[0];
		int len = dial[0].size();

		int ans = 0;
		for(int i=1; i < N; i++)
		{
			cin >> dial[i];

			int turn = i % 2;
			int search;
			if(turn)
			  search = kmpSearch(dial[i] + dial[i], dial[i-1]);
			else
				search = kmpSearch(dial[i-1] + dial[i-1], dial[i]);

			ans += search;
		}
		cout << ans << '\n';
	}
	return 0;
}