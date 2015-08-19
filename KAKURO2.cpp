#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int map[21][21];
int Q;

struct query
{
	int y, x, d, sum, visit;
	int cnt;

	query(int Y, int X, int D, int S) : y(Y), x(X), d(D), sum(S), visit(0), cnt(0) {}

	void push(int idx)
	{
		visit |= 1 << idx;
		sum -= idx;
		cnt--;
	}

	void pop(int idx)
	{
		visit ^= 1 << idx;
		sum += idx;
		cnt++;
	}
};

vector<query> hint;
int hintIdx[21][21][2];

vector<pair<int,int> > dot;

bool complete;

void solve(int pos)
{
	if(complete)
		return;
	if(pos == dot.size())
	{
		complete = true;
		return;
	}

	const int& y = dot[pos].first;
	const int& x = dot[pos].second;

	query& hintH = hint[hintIdx[y][x][1]];
	query& hintW = hint[hintIdx[y][x][0]];

	int visit = hintH.visit | hintW.visit;

	for(int i=1; i <= 9 && hintH.sum >= i && hintW.sum >= i; i++)
	{
		if((visit & (1<<i)) == 0)
		{
			if(hintH.cnt == 1 && hintH.sum != i)
				continue;
			if(hintW.cnt == 1 && hintW.sum != i)
				continue;
	
			hintH.push(i);
			hintW.push(i);

			map[y][x] = i;
			solve(pos+1);

			if(complete)
				return;

			hintH.pop(i);
			hintW.pop(i);
		}
	}
}

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		hint.clear();
		dot.clear();
		complete = false;

		cin >> N;
		for(int i=0; i < N; i++)
		{
			for(int j=0; j < N; j++)
			{
				cin >> map[i][j];
				if(map[i][j] == 1)
					dot.push_back(make_pair(i,j));
			}
		}

		cin >> Q;
		for(int i=0; i < Q; i++)
		{
			int y, x, d ,s;
			cin >> y >> x >> d >> s;
			hint.push_back(query(y-1,x-1,d,s));
		}

		for(int i=0; i < Q; i++)
		{
			int y = hint[i].y;
			int x = hint[i].x;
			if(hint[i].d == 0)
				for(int j=x+1; map[y][j] == 1; j++)
				{
					hintIdx[y][j][0] = i;
					hint[i].cnt++;
				}
			else
				for(int j=y+1; map[j][x] == 1; j++)
				{
					hintIdx[j][x][1] = i;
					hint[i].cnt++;
				}
		}

		solve(0);

		for(int i=0; i < N; i++)
		{
			for(int j=0; j < N; j++)
				cout << map[i][j] << " ";
			cout << '\n';
		}
	}
	return 0;
}