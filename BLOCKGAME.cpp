#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int L[4][3][2] = {
	{
		{0,0},{1,0},{1,1}
	},
	{
		{0,0},{0,1},{1,1}
	},
	{
		{0,0},{0,1},{-1,1}
	},
	{
		{0,0},{1,0},{0,1}
	}
};

const int B[2][2][2] = {
	{
		{0,0},{1,0}
	},
	{
		{0,0},{0,1}
	}
};

char a[5][6];
char cache[1<<25];

vector<int> moves;

int getIdx()
{
	int ret = 0;
	for(int i=0; i < 5; i++)
	{
		for(int j=0; j < 5; j++)
		{
			ret *= 2;
			ret += a[i][j] == '#';
		}
	}
	return ret;
}

bool isOK(int& board, int y, int x)
{
	return !(y < 0 || y >= 5 || x < 0 || x >= 5 || (board & (1<<(y*5 + x))));
}

bool canPut(int& board, int p, int q, int shape)
{
	for(int i=0; i < 3; i++)
	{
		int y=p + L[shape][i][0], x=q + L[shape][i][1];
		if(!isOK(board, y,x))
			return false;
	}

	for(int i=0; i < 3; i++)
	{
		int y=p + L[shape][i][0], x=q + L[shape][i][1];
		board |= 1 << (y * 5 + x);
	}
	return true;
}

bool canPut2(int& board, int p, int q, int shape)
{
	for(int i=0; i < 2; i++)
	{
		int y=p + B[shape][i][0], x=q + B[shape][i][1];
		if(!isOK(board, y,x))
			return false;
	}

	for(int i=0; i < 2; i++)
	{
		int y=p + B[shape][i][0], x=q + B[shape][i][1];
		board |= 1 << (y * 5 + x);
	}
	return true;
}


void pop(int& board, int p, int q, int shape)
{
	for(int i=0; i < 3; i++)
	{
		int y=p + L[shape][i][0], x=q + L[shape][i][1];
		board ^= 1 << (y * 5 + x);
	}
}

void pop2(int& board, int p, int q, int shape)
{
	for(int i=0; i < 2; i++)
	{
		int y=p + B[shape][i][0], x=q + B[shape][i][1];
		board ^= 1 << (y * 5 + x);
	}
}

char solve(int board)
{
	char& ret = cache[board];
	if(ret != -1)
		return ret;

	ret = 0;
	for(int i=0; i < moves.size(); i++)
	{
		if((moves[i] & board) == 0 && !solve(board | moves[i]))
		{
			ret = 1;
			break;
		}
	}
	return ret;
}


int main()
{
	for(int i=0; i < 5; i++)
	{
		for(int j=0; j < 5; j++)
		{
			int board = 0;
			for(int k=0; k < 4; k++)
			{
				if(canPut(board,i,j,k))
				{
					moves.push_back(board);
					pop(board,i,j,k);
				}
			}
			for(int k=0; k < 2; k++)
			{
				if(canPut2(board,i,j,k))
				{
					moves.push_back(board);
					pop2(board,i,j,k);
				}
			}
		}
	}

	int T;
	cin >> T;

	while(T--)
	{
		memset(cache, -1, sizeof(cache));

		for(int i=0; i < 5; i++)
			cin >> a[i];

		int ans = solve(getIdx());
		if(ans)
			cout << "WINNING" << '\n';
		else
			cout << "LOSING" << '\n';
	}
	return 0;
}