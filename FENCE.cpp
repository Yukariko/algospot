#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
int N;
int fence[20001];
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}

// [left,right) 구간에서 찾아낼 수 있는 가장 큰 직사각형의 넓이를 반환
int cutting(int left, int right)
{
	if(left == right) return fence[left];
	const int mid = (left+right)/2;
	int ret = max(cutting(left,mid),cutting(mid+1,right));

	int pLeft = mid;
	int pRight = mid+1;
	int len = min(fence[pLeft],fence[pRight]);
	ret = max(ret,len * 2);
	for(;pLeft > left || pRight < right;)
	{
		// 0 - left, 1 - right
		int select;
		if(pLeft == left) select = 1;
		else if(pRight == right) select = 0;
		else select = fence[pLeft - 1] < fence[pRight + 1];
		if(select == 0)
		{
			pLeft--;
			len = min(len,fence[pLeft]);
		}
		else
		{
			pRight++;
			len = min(len,fence[pRight]);
		}
		ret = max(ret,(pRight - pLeft + 1) * len);
	}
	return ret;
}

int main()
{
	int C;
	scanf("%d ",&C);

	for(;C--;)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&fence[i]);
		}
		printf("%d\n",cutting(0,N-1));
	}
	return 0;
}