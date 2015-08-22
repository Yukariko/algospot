#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <map>

using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;

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

bool isInside(vector2 q, const vector<vector2>& p)
{
	int crosses = 0;
	for(int i=0; i < p.size(); i++)
	{
		int j = (i + 1) % p.size();

		if((p[i].y > q.y) != (p[j].y > q.y))
		{
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if(q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

double area(const vector<vector2>& p)
{
	double ret = 0;
	for(int i=0; i < p.size(); i++)
		ret += p[i].cross(p[(i + 1) % p.size()]);
	return fabs(ret) / 2.0;
}

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x)
{
	double det = (b-a).cross(d-c);
	if(fabs(det) < EPSILON)
		return false;
	x = a + (b-a) * ((c-a).cross(d-c) / det);
	return true;
}

double ccw(vector2 a, vector2 b)
{
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b)
{
	return ccw(a-p,b-p);
}

bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{
	if(b < a)
		swap(a, b);
	if(d < c)
		swap(d, c);

	if(ccw(a, b, c) != 0 || b < c || d < a)
		return false;

	if(a < c)
		p = c;
	else
		p = a;
	return true;
}

bool inBoundingRectangle(vector2 p, vector2 a, vector2 b)
{
	if(b < a)
		swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
	if(!lineIntersection(a,b,c,d,x))
		return parallelSegments(a,b,c,d,x);
	return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}

typedef vector<vector2> polygon;

polygon cutPoly(const polygon& p, const vector2& a, const vector2& b)
{
	int n = p.size();

	vector<bool> inside(n);
	for(int i=0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;

	polygon ret;

	for(int i=0; i < n; i++)
	{
		int j = (i + 1) % n;

		if(inside[i])
			ret.push_back(p[i]);

		if(inside[i] != inside[j])
		{
			vector2 cross;
			assert(lineIntersection(p[i],p[j],a,b,cross));
			ret.push_back(cross);
		}
	}
	return ret;
}

// Sutherland-Hodgman
polygon intersection(const polygon& p, double x1, double y1, double x2, double y2)
{
	vector2 a(x1,y1), b(x2,y1), c(x2,y2), d(x1,y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}

polygon giftWrap(const vector<vector2>& points)
{
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while(true)
	{
		vector2 ph = hull.back(), next = points[0];
		for(int i=1; i < n; i++)
		{
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if(cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}

		if(next == pivot)
			break;

		hull.push_back(next);
	}
	return hull;
}

bool polygonIntersects(const polygon& p, const polygon& q)
{
	int n = p.size(), m = q.size();
	if(isInside(p[0],q) || isInside(q[0], p))
		return true;

	vector2 t;
	for(int i=0; i < n; i++)
		for(int j=0; j < m; j++)
			if(segmentIntersection(p[i], p[(i+1)%n], q[j], q[(j+1)%m], t))
				return true;
	return false;
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		int N;
		cin >> N;

		vector<vector2> nerd, notNerd;

		for(int i=0; i < N; i++)
		{
			int isnerd, x, y;
			cin >> isnerd >> x >> y;

			if(isnerd)
				nerd.push_back(vector2(x,y));
			else
				notNerd.push_back(vector2(x,y));
		}
		
		polygon nerdHull = giftWrap(nerd);
		polygon notNerdHull = giftWrap(notNerd);
		if(polygonIntersects(nerdHull, notNerdHull))
			cout << "THEORY IS INVALID\n";
		else
			cout << "THEORY HOLDS\n";
	}
	return 0;
}