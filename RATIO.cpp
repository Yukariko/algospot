#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

int main()
{

	int T;
	cin >> T;


	while(T--)
	{
		long long X, Y;
		cin >> X >> Y;

		long long current = Y * 100 / X;
		if(current >= 99)
		{
			cout << "-1\n";
			continue;
		}

		long long first=0,last=2000000000;
		for(int i=0; i < 100; i++)
		{
			long long mid = (first + last) / 2;
			long long next = (Y+mid) * 100 / (X+mid);
			if(current < next)
				last = mid-1;
			else
				first = mid+1;
		}
		cout << first << '\n';
	}
	return 0;
}
