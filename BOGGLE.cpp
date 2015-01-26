#include <cstdio>
#include <iostream>

using namespace std;

const int dx[8] = { -1,	-1, -1,  1, 1, 1,  0, 0 };
const int dy[8] = { -1,	 0,  1, -1, 0, 1, -1, 1 };

char board[5][5];

// 5 x 5 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환

bool inRange(int y, int x)
{
	return !(y < 0 || y >= 5 || x < 0 || x >= 5);
}

bool hasWord(int y,int x, const string &word)
{
	if(!inRange(y, x)) return false;

	if(board[y][x] != word[0]) return false;

	if(word.size() == 1) return true;

	for(int direction=0; direction < 8; direction++)
	{
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if (hasWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}

int main()
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			scanf(" %c",&board[i][j]);
		}
	}
	string str = "YES";
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(hasWord(i,j,str))
			{
				cout << "yes";
				return 0;
			}
		}
	}
	cout << "no";
	return 0;
}