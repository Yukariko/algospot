#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct SuffixComparator
{
	const vector<int>& group;
	int t;
	SuffixComparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
	bool operator() (int a, int b)
	{
		if(group[a] != group[b])
			return group[a] < group[b];
		return group[a + t] < group[b + t];
	}
};

vector<int> getSuffixArray(const string& s)
{
	int n = s.size();

	int t = 1;
	vector<int> group(n+1);
	for(int i=0; i < n; i++)
		group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n);
	for(int i=0; i < n; i++)
		perm[i] = i;

	while(t < n)
	{
		SuffixComparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

		t *= 2;
		if(t >= n)
			break;

		vector<int> newGroup(n+1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for(int i=1; i < n; i++)
			if(compareUsing2T(perm[i-1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i-1]];
		group = newGroup;
	}
	return perm;
}

int commonPrefix(const string& s, int i, int j)
{
	int k=0;
	while(i < s.size() && j < s.size() && s[i] == s[j])
		i++, j++, k++;
	return k;
}

int maxSubstrings(const string& s, int K)
{
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	for(int i=0; i + K <= a.size(); i++)
		ret = max(ret, commonPrefix(s, a[i], a[i+K-1]));
	return ret;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int K;
		string a;
		cin >> K >> a;
		cout << maxSubstrings(a, K) << '\n';
	}
	return 0;
}