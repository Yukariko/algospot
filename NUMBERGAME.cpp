#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = -987654321;
int cache[51][51];

int solve(const vector<int>& a, int left, int right)
{
	if(left > right)
		return 0;

	if(left == right)
		return a[left];

	int& ret = cache[left][right];
	if(ret != INF)
		return ret;

	ret = max(ret, a[left] - solve(a, left+1, right));
	ret = max(ret, a[right] - solve(a, left, right-1));
	ret = max(ret, -solve(a, left+2, right));
	ret = max(ret, -solve(a, left, right-2));
	
	return ret;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N;
		cin >> N;

		for(int i=0; i < N; i++)
			for(int j=i; j < N; j++)
				cache[i][j] = INF;

		vector<int> a(N);
		for(int i=0; i < N; i++)
			cin >> a[i];

		cout << solve(a, 0, N-1) << '\n';
	}
	return 0;
}