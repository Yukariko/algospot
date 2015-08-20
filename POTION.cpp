#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

int gcd(int p, int q)
{
	return q?gcd(q,p%q):p;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N;
		cin >> N;

		int r[201];
		for(int i=0; i < N; i++)
			cin >> r[i];

		int g = r[0];
		for(int i=1; i < N; i++)
			g = gcd(g, r[i]);

		int nr[201];
		for(int i=0; i < N; i++)
			nr[i] = r[i] / g;

		int p[201];
		for(int i=0; i < N; i++)
			cin >> p[i];

		for(int i=0; i < N; i++)
			g = max(g, (p[i] + nr[i]-1) / nr[i]);
		
		for(int i=0; i < N; i++)
			cout << nr[i] * g - p[i] << " ";
		cout << '\n';
	}
	return 0;
}