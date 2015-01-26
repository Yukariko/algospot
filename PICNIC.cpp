#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int N,M;
bool areFriends[10][10];

// taken[i] = i번째 학생이 이미 짝을 찾았으면 true, 아니면 false
bool taken[10];

int countPairings()
{
	// 아직 짝이 지어지지 않은 학생을 번호가 빠른 순으로 구한다.
	int child;
	for(child=0; child < N; child++)
	{
		if(!taken[child]) break;
	}

	// 모든 학생이 짝을 찾았으므로 짝짓기 성공
	if(child == N) return 1;
	
	int result = 0;

	// 이 학생과 짝지을 학생을 정한다.
	taken[child] = true;
	for(int otherChild=0;otherChild < N;otherChild++)
	{
		if(!taken[otherChild] && areFriends[child][otherChild])
		{
			taken[otherChild] = true;
			result += countPairings();
			taken[otherChild] = false;
		}
	}
	taken[child] = false;
	return result;
}

int main()
{
	int C;
	scanf("%d",&C);

	for(;C--;)
	{
		scanf("%d%d",&N,&M);

		memset(areFriends, 0, sizeof(areFriends));
		memset(taken, 0, sizeof(taken));

		for(int i=0;i<M;i++)
		{
			int X,Y;
			scanf("%d%d",&X,&Y);
			areFriends[X][Y]=areFriends[Y][X]=true;
		}

		printf("%d\n",countPairings());
	}
	return 0;
}