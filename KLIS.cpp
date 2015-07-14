#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

int N;
long long K;
int a[501];
int idx[100001];

long long cache[501][501];
vector<int> v[501];

long long cacheSet(int pos, int cnt)
{
	long long &ret = cache[pos][cnt];
	if(ret != -1)
		return ret;

	ret = 0;
	if(cnt == 0)
		return ret = 1;

	for(vector<int>::iterator it = v[pos].begin(); it != v[pos].end(); ++it)
	{
		ret += cacheSet(idx[*it], cnt-1);
		if(ret > K)
			break;
	}

	return ret;
}

string solve(int pos, int cnt, long long skip)
{
	if(cnt == 0)
		return "";

	for(vector<int>::iterator it = v[pos].begin(); it != v[pos].end(); ++it)
	{
		int &nIdx = idx[*it];
		if(cache[nIdx][cnt-1] && skip <= cache[nIdx][cnt-1])
			return to_string(*it) + " " + solve(nIdx, cnt-1, skip);
		else
			skip -= cache[nIdx][cnt-1];
	}
	return "";
}

int LIS(int *a,int size)
{
  int *b = new int[size];
  int k=0;
  b[k++] = a[0];
  for(int i=1;i<size;i++)
  {
    int *j = lower_bound(b,b+k,a[i]);
    if(j==b+k)
      b[k++]=a[i];
    else
      *j=a[i];
  }
  delete b;
  return k;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> N >> K;
		for(int i=1; i <= N; i++)
		{
			cin >> a[i];
			idx[a[i]] = i;
		}

		for(int i=0; i <= N; i++)
		{
			v[i].clear();
			for(int j=i+1; j <= N; j++)
				if(a[i] < a[j])
					v[i].push_back(a[j]);
			sort(v[i].begin(), v[i].end());
		}

		memset(cache, -1, sizeof(cache));

		int lis = LIS(a+1, N);
		cout << lis << endl;
		cacheSet(0, lis);
		cout << solve(0, lis, K) << endl;
	}
	return 0;
}