#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const char *str[] = {
	"+FX","+YF","-FX","-YF"
};

const int next_to[2][4] = {
	{0,0,2,2},
	{1,3,1,3}
};

char bit[32];

int solve(int pos, int state)
{
	if(pos < 0)
		return state;
	return solve(pos-1, next_to[bit[pos]][state]);
}

int main()
{

	int T;
	cin >> T;
	while(T--)
	{
		int N, P, Q, L;
		cin >> N >> P >> L;

		int left = P % 3;

		Q = (P + L + 3) / 3;
		P /= 3;

		string ans = "";

		while(P < Q)
		{
			int pos = 0;
			for(int i=P; i; i/=2)
				bit[pos++] = i % 2;

			int find = solve(pos-1,0);
			ans += str[find];

			P++;
		}	

		cout << ans.substr(left,L) << endl;
	}	

	return 0;
}
