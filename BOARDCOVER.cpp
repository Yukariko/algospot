#include <cstdio>
#include <iostream>

using namespace std;

int H,W;
char board[21][21];
int spaceCount;

// 4가지 조각의 상대적 위치
// block[조각번호][점번호][y,x]
const int block[4][3][2] = {
		{{0,0},{0,1},{1,1}},
		{{0,0},{0,1},{1,0}},
		{{0,0},{1,0},{1,1}},
		{{0,0},{1,0},{1,-1}}
};

// 좌표가 board 범위를 벗어나면 false, 아니면 true
bool inBoard(int y, int x)
{
	return !(y < 0 || y >= H || x < 0 || x >= W);
}

// 해당 좌표에 주어진 조각을 채워 넣을 수 있으면 true, 아니면 false
bool blockCheck(int y, int x, int blockCase)
{
	for(int blockNum=0; blockNum < 3; blockNum++)
	{
		const int newY = y + block[blockCase][blockNum][0], newX = x + block[blockCase][blockNum][1];
		if(!inBoard(newY, newX) || board[newY][newX] != '.') return false;
	}
	return true;
}

// 해당 좌표에 주어진 조각을 채워 넣음
void fillBlock(int y,int x, int blockCase, char shape)
{
	for(int blockNum=0; blockNum < 3; blockNum++)
	{
		const int newY = y + block[blockCase][blockNum][0], newX = x + block[blockCase][blockNum][1];
		board[newY][newX] = shape;
	}
}

int countCover(int y, int x)
{

	// 다 검색 헀을 때, 빈공간이 남아있다면 0, 다 채워져있다면 1
	// 다 검색하지 않았다면, 다음 빈 좌표로 이동
	if(y == H) return !spaceCount;
	if(x == W) return countCover(y+1,0);
	if(board[y][x] != '.') return countCover(y,x+1);
	
	int ret = 0;

	// 4가지 조각을 하나씩 넣어보고 완성이 되는 조각이 있으면 증가
	for(int blockCase=0; blockCase < 4; blockCase++)
	{
		// 조각을 넣을 공간이 없으면 다음 조각으로
		if(!blockCheck(y,x,blockCase)) continue;

		// 조각을 채워넣고 재귀
		fillBlock(y,x,blockCase,'#');
		spaceCount -= 3;
		
		ret += countCover(y,x+1);

		// 다음 조각을 넣기 위해 다시 복구
		spaceCount += 3;
		fillBlock(y,x,blockCase,'.');
	}

	return ret;
}

int main()
{
	int C;
	scanf("%d",&C);

	for(;C--;)
	{
		scanf("%d%d",&H,&W);
		spaceCount = 0;

		for(int i=0;i<H;i++)
		{
			for(int j=0;j<W;j++)
			{
				scanf(" %c",&board[i][j]);
				if(board[i][j] == '.') spaceCount++;
			}
		}
		printf("%d\n",countCover(0,0));
	}

	return 0;
}