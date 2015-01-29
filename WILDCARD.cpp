#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;


char pattern[101];
int N;

int checkWildCard(const string &str, int sPos, int pPos)
{
	if(sPos == str.size())
	{
		return !pattern[pPos] || (pattern[pPos] == '*' && !pattern[pPos+1]);
	}
	if(!pattern[pPos]) return false;

	char tok = pattern[pPos];
	char match = str[sPos];
	if(tok == '*')
	{
		if(!pattern[pPos+1]) return true;
		for(;sPos < str.size(); sPos++)
		{
			if(checkWildCard(str, sPos, pPos+1)) return true;
		}
		return false;
	}
	return (tok == '?' || tok == match)? checkWildCard(str, sPos+1, pPos+1) : false;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		vector<string> name;
		gets(pattern);
		scanf("%d ",&N);
		for(int i=0;i<N;i++)
		{
			char temp[101];
			gets(temp);
			name.push_back(string(temp));
		}
		sort(name.begin(), name.end());
		for(int i=0;i<N;i++)
			if(checkWildCard(name[i],0,0))
				puts(name[i].c_str());
	}
}