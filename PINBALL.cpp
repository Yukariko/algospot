#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2
{
	double x, y;

	explicit vector2(double x = 0, double y = 0) : x(x), y(y) {}

	bool operator == (const vector2& rhs) const 
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const 
	{
		return x != rhs.x? x < rhs.x: y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const 
	{
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const 
	{
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const 
	{
		return vector2(x * rhs, y * rhs);
	}

	// 벡터의 길이
	double norm() const {return hypot(x, y);}

	vector2 normalize() const
	{
		return vector2(x / norm(), y / norm());
	}

	// x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	double polar() const {return fmod(atan2(y, x) + 2 * PI, 2 * PI);}

	// 내적
	double dot(const vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	// 외적
	double cross(const vector2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	// rhs에 사영
	vector2 project(const vector2& rhs) const
	{
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

int N;
vector2 center[50];
int radius[50];

const double INFTY = 1e200;
const double EPSILON = 1e-9;

vector<double> solve2(double a, double b, double c)
{
	double d = b*b - 4*a*c;
	if(d < -EPSILON)
		return vector<double>();

	if(d < EPSILON)
		return vector<double>(1, -b / (2 * a));

	vector<double> ret;
	ret.push_back((-b - sqrt(d)) / (2*a));
	ret.push_back((-b + sqrt(d)) / (2*a));
	return ret;
}

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius)
{
	double a = dir.dot(dir);
	double b = 2 * dir.dot(here - center);
	double c = center.dot(center) + here.dot(here) - 2 * center.dot(here) - radius * radius;

	vector<double> sols = solve2(a, b, c);
	if(sols.empty() || sols[0] < EPSILON)
		return INFTY;

	return sols[0];
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact)
{
	return (dir -dir.project(contact - center) * 2).normalize();
}

void simulate(vector2 here, vector2 dir)
{
	dir = dir.normalize();

	int hitCount = 0;
	while(hitCount < 100)
	{
		int circle = -1;
		double time = INFTY * 0.5;

		for(int i=0; i < N; i++)
		{
			double cand = hitCircle(here, dir, center[i], radius[i] + 1);
			if(cand < time)
			{
				time = cand;
				circle = i;
			}
		}

		if(circle == -1)
			break;

		if(hitCount++)
			cout << " ";
		cout << circle;

		here = here + dir * time;
		dir = reflect(dir, center[circle], here);
	}

	cout << '\n';
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int x, y, dx, dy;
		cin >> x >> y >> dx >> dy >> N;

		vector2 here, dir;
		here = vector2(x,y);
		dir = vector2(dx,dy);

		for(int i=0; i < N; i++)
		{
			int x, y, r;
			cin >> x >> y >> r;
			center[i] = vector2(x,y);
			radius[i] = r;
		}

		simulate(here, dir);
	}
	return 0;
}