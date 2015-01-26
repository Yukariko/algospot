#include <cstdio>
#include <iostream>

using namespace std;

int H,W;
char board[21][21];
int spaceCount;

// 4���� ������ ����� ��ġ
// block[������ȣ][����ȣ][y,x]
const int block[4][3][2] = {
		{{0,0},{0,1},{1,1}},
		{{0,0},{0,1},{1,0}},
		{{0,0},{1,0},{1,1}},
		{{0,0},{1,0},{1,-1}}
};

// ��ǥ�� board ������ ����� false, �ƴϸ� true
bool inBoard(int y, int x)
{
	return !(y < 0 || y >= H || x < 0 || x >= W);
}

// �ش� ��ǥ�� �־��� ������ ä�� ���� �� ������ true, �ƴϸ� false
bool blockCheck(int y, int x, int blockCase)
{
	for(int blockNum=0; blockNum < 3; blockNum++)
	{
		const int newY = y + block[blockCase][blockNum][0], newX = x + block[blockCase][blockNum][1];
		if(!inBoard(newY, newX) || board[newY][newX] != '.') return false;
	}
	return true;
}

// �ش� ��ǥ�� �־��� ������ ä�� ����
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

	// �� �˻� ���� ��, ������� �����ִٸ� 0, �� ä�����ִٸ� 1
	// �� �˻����� �ʾҴٸ�, ���� �� ��ǥ�� �̵�
	if(y == H) return !spaceCount;
	if(x == W) return countCover(y+1,0);
	if(board[y][x] != '.') return countCover(y,x+1);
	
	int ret = 0;

	// 4���� ������ �ϳ��� �־�� �ϼ��� �Ǵ� ������ ������ ����
	for(int blockCase=0; blockCase < 4; blockCase++)
	{
		// ������ ���� ������ ������ ���� ��������
		if(!blockCheck(y,x,blockCase)) continue;

		// ������ ä���ְ� ���
		fillBlock(y,x,blockCase,'#');
		spaceCount -= 3;
		
		ret += countCover(y,x+1);

		// ���� ������ �ֱ� ���� �ٽ� ����
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