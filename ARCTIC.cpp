#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int N;
vector<pair<double,double> > a;
double dist[101][101];

bool decision(double d)
{
	bool visit[101] = {};

	queue<int> q;
	visit[0] = true;
	q.push(0);

	while(!q.empty())
	{
		int current = q.front();
		q.pop();

		for(int next=0; next < N; next++)
		{
			if(!visit[next] && dist[current][next] <= d)
			{
				visit[next] = true;
				q.push(next);
			}
		}
	}

	for(int i=0; i < N; i++)
		if(!visit[i])
			return false;
	return true;
}

int main()
{
	int T;
	cin >> T;
	
	cout.setf(ios::fixed);
	cout.precision(2);
	while(T--)
	{
		cin >> N;

		a.clear();
		a.resize(N);
		for(int i=0; i < N; i++)
			cin >> a[i].first >> a[i].second;

		for(int i=0; i < N; i++)
			for(int j=i+1; j < N; j++)
				dist[i][j] = dist[j][i] = sqrt( (a[i].first-a[j].first) * (a[i].first-a[j].first) + (a[i].second-a[j].second) * (a[i].second-a[j].second));

		double start = 0, end = sqrt(2.0*1000*1000);

		while(start + 1e-6 <= end)
		{
			double d = (start + end) / 2;
			if(!decision(d))
				start = d;
			else
				end = d;
		}


		cout << start << '\n';
	}
	return 0;
}