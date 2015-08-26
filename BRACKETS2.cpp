#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

const char *open = "({[";
const char *close = ")}]";

int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		string a;
		cin >> a;

		stack<int> last_bracket;

		bool ans = true;

		for(int i=0; a[i]; i++)
		{
			for(int j=0; open[j]; j++)
				if(a[i] == open[j])
					last_bracket.push(j);
			for(int j=0; close[j]; j++)
			{
				if(a[i] == close[j])
				{
					if(last_bracket.empty() || j != last_bracket.top())
					{
						ans = false;
						break;
					}
					else
						last_bracket.pop();
				}
			}

		}
		if(!last_bracket.empty())
			ans = false;
		if(ans)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}