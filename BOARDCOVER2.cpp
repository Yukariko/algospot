#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<pair<int,int>>> rotations;
int blockSize;

vector<string> rotate(const vector<string>& arr)
{
	vector<string> ret(arr[0].size(), string(arr.size(),' '));
	for(int i=0; i < arr.size(); i++)
		for(int j=0; j < arr[0].size(); j++)
			ret[j][arr.size()-i-1] = arr[i][j];
	return ret;
}

void generateRotations(vector<string> block)
{
	rotations.clear();
	rotations.resize(4);

	for(int rot=0; rot < 4; rot++)
	{
		int originY = -1, originX = -1;
		for(int i=0; i < block.size(); i++)
			for(int j=0; j < block[i].size(); j++)
				if(block[i][j] == '#')
				{
					if(originY == -1)
					{
						originY = i;
						originX = j;
					}

					rotations[rot].push_back(make_pair(i-originY, j-originX));
				}

		block = rotate(block);
	}

	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}

int H, W, R, C;
bool covered[10][10];

int best;

bool correct(int y, int x)
{
	return !(y < 0 || y >= H || x < 0 || x >= W);
}

bool setting(int y, int x, const vector<pair<int,int> >& block, int delta)
{
	if(delta == 1)
	{
		for(int i=0; i < block.size(); i++)
		{
			int Y = y + block[i].first;
			int X = x + block[i].second;

			if(!correct(Y,X) || covered[Y][X])
				return false;
		}
	}
	
	for(int i=0; i < block.size(); i++)
		covered[y + block[i].first][x + block[i].second] = delta == 1;

	return true;
}

void search(int placed, int notcover)
{
	if(placed + notcover / blockSize <= best)
		return;

	int y = -1, x = -1;
	for(int i=0; i < H; i++)
	{
		for(int j=0; j < W; j++)
			if(covered[i][j] == false)
			{
				y = i;
				x = j;
				break;
			}
		if(y != -1)
			break;
	}

	if(y == -1)
	{
		best = max(best, placed);
		return;
	}

	for(int i=0; i < rotations.size(); i++)
	{
		if(setting(y,x,rotations[i],1))
		{
			search(placed+1, notcover - blockSize);
			setting(y,x,rotations[i],-1);
		}
	}

	covered[y][x] = true;
	search(placed, notcover - 1);
	covered[y][x] = false;
}


int main()
{
	int T;
	cin >> T;

	while(T--)
	{
		cin >> H >> W >> R >> C;

		vector<string> board(H);
		for(int i=0; i < H; i++)
			cin >> board[i];

		vector<string> block(R);
		for(int i=0; i < R; i++)
			cin >> block[i];

		generateRotations(block);

		int notcover = 0;
		for(int i=0; i < H; i++)
			for(int j=0; j < W; j++)
			{
				covered[i][j] = board[i][j] == '#';
				notcover += board[i][j] == '.';
			}

		best = 0;
		search(0, notcover);

		cout << best << endl;
	}
	return 0;
}