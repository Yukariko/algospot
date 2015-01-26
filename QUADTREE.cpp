#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

char quad[1001];
char backQuad[1001];
int backPos;
int quadBlock[21][4];
const int order[4] = {2,3,0,1};

// 쿼드트리의 각 조각의 길이를 반환하는 함수
// pos: 현재 quad 문자의 위치
int getQuadLen(int pos)
{
	if(!quad[pos]) return 0;
	int ret = 1;
	if(quad[pos] == 'x')
	{
		for(int count=0;count<4;count++)
		{
			ret += getQuadLen(pos + ret);
		}
	}
	return ret;
}
void getBackQuad(int pos)
{
	if(!quad[pos]) return;
	backQuad[backPos++] = quad[pos];
	if(quad[pos] == 'x')
	{
		int nextPos[4];
		for(int i=pos+1,count=0;count<4;count++)
		{
			nextPos[count] = i;
			i += getQuadLen(i);
		}

		for(int i=0;i<4;i++)
			getBackQuad(nextPos[order[i]]);
	}
}

string reverse(string::iterator &it)
{
	char head = *it;
	it++;
	if(head != 'x') return string(1,head);
	string nextQuad[4];
	for(int i=0;i<4;i++)
	{
		nextQuad[i] = reverse(it);
	}
	string ret = "x";
	for(int i=0;i<4;i++)
	{
		ret += nextQuad[order[i]];
	}
	return ret;
}
int main()
{
	int C;
	scanf("%d ",&C);

	for(;C--;)
	{
		gets(quad);
		backPos = 0;
		getBackQuad(0);
		backQuad[backPos]=0;
		puts(backQuad);
		/*
		JM BOOK SOLUTION
		string ret(quad);
		string::iterator it = ret.begin();
		puts(reverse(it).c_str());
		*/
	}
	return 0;
}