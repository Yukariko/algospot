#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;

int clk[16];

// swtch[i][] = i번 스위치를 누르면 변경되는 시계의 index를 담은 배열. 끝은 -1로 구분
const int swtch[10][6] = {
		{0,1,2,-1}, // 0
		{3,7,9,11,-1}, // 1
		{4,10,14,15,-1}, // 2
		{0,4,5,6,7,-1}, // 3
		{6,7,8,10,12,-1}, // 4
		{0,2,14,15,-1}, // 5
		{3,14,15,-1}, // 6
		{4,5,7,14,15,-1}, // 7
		{1,2,3,4,5,-1}, // 8
		{3,4,5,9,13,-1} // 9
};

// n번 스위치를 눌렀을 때 시계의 시간을 변경함
void setClock(int n)
{
	for(int i=0;swtch[n][i] != -1; i++)
	{
		const int num = swtch[n][i];
		clk[num] += 3;

		if(clk[num] == 15)
		{
			clk[num] = 3;
		}
	}
}

int min(int a,int b){return a>b?b:a;}

// 모든 시계가 12시를 가리키면 true, 아니면 false
bool isSolve()
{
	for(int i=0;i<16;i++)
	{
		if(clk[i] != 12)
		{
			return false;
		}
	}
	return true;
}

// pos : 누를 스위치의 번호
// count : 지금까지 누른 횟수
int solve(int pos, int count)
{
	if(isSolve()) return count;
	if(pos == 10) return INF;

	int ret = INF;

	// 각 스위치를 0~3번 누르고 재귀
	for(int i=0;i<4;i++)
	{
		ret = min(ret,solve(pos+1, count+i));
		setClock(pos);
	}
	return ret;
}

int main()
{
	int C;
	scanf("%d",&C);

	for(;C--;)
	{
		for(int i=0;i<16;i++)
		{
			scanf("%d",&clk[i]);
		}
		int res = solve(0,0);		
		printf("%d\n",res == INF? -1: res);
	}
	return 0;
}