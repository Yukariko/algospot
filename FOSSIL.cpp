#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

#define point pair<double, double>
#define x first
#define y second

vector< pair< point, point > > upper, lower;

void decompose(const vector< point >& hull)
{
	int N = hull.size();
	for(int i=0; i < N; i++)
	{
		if(hull[i].x < hull[(i+1) % N].x)
			lower.push_back(make_pair(hull[i], hull[(i+1) % N]));
		else if(hull[i].x > hull[(i+1) % N].x)
			upper.push_back(make_pair(hull[i], hull[(i+1) % N]));
	}
}

double minX(const vector< point >& hull)
{
	double ans = hull[0].x;
	for(int i=1; i < hull.size(); i++)
		ans = min(ans, hull[i].x);
	return ans;
}

double maxX(const vector< point >& hull)
{
	double ans = hull[0].x;
	for(int i=1; i < hull.size(); i++)
		ans = max(ans, hull[i].x);
	return ans;
}

double between(const point& p, const point& q, double x)
{
	return (p.x <= x && x <= q.x) || (q.x <= x && x <= p.x);
}

double at(const point& p, const point& q, double x)
{
	double dy = q.y - p.y, dx = q.x - p.x;
	return p.y + dy * (x - p.x) / dx;
}

double vertical(double x)
{
	double minUp = 1e20, maxLow = -1e20;

	for(int i=0; i < upper.size(); i++)
		if(between(upper[i].first, upper[i].second, x))
			minUp = min(minUp, at(upper[i].first, upper[i].second, x));

	for(int i=0; i < lower.size(); i++)
		if(between(lower[i].first, lower[i].second, x))
			maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));

	return minUp - maxLow;
}

int main()
{
	int T;
	cin >> T;

	cout.setf(ios::fixed);
	cout.precision(10);

	while(T--)
	{
		int N, M;
		cin >> N >> M;

		vector< point > hull1(N), hull2(M);

		for(int i=0; i < N; i++)
			cin >> hull1[i].first >> hull1[i].second;

		for(int i=0; i < M; i++)
			cin >> hull2[i].first >> hull2[i].second;

		upper.clear();
		lower.clear();

		decompose(hull1);
		decompose(hull2);

		double lo = max(minX(hull1), minX(hull2));
		double hi = min(maxX(hull1), maxX(hull2));

		if(hi < lo)
		{
			cout << 0 << '\n';
			continue;
		}

		for(int i=0; i < 100; i++)
		{
			double aab = (lo * 2 + hi) / 3.0;
			double abb = (lo + hi * 2) / 3.0;

			if(vertical(aab) < vertical(abb))
				lo = aab;
			else
				hi = abb;
		}

		cout << max(0.0, vertical(hi)) << '\n';
	}
	return 0;
}