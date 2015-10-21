#include <bits/stdc++.h>

using namespace std;

struct RMQ
{
	int n;

	vector<int> rangeMin;
	RMQ(const vector<int>& array)
	{
		n = array.size();
		int k=1;
		while(k < n)
			k *= 2;
		k *= 2;
		rangeMin.resize(k);
		init(array, 0, n-1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node)
	{
		if(left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		return rangeMin[node] = min(init(array, left, mid, node * 2), init(array, mid+1, right, node * 2 + 1));
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if(right < nodeLeft || left > nodeRight)
			return INT_MAX;
		if(left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	int query(int left, int right)
	{
		return query(left, right, 1, 0, n-1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight)
	{
		if(index < nodeLeft || nodeRight < index)
			return rangeMin[node];

		if(nodeLeft == nodeRight)
			return rangeMin[node] = newValue;

		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

	int update(int index, int newValue)
	{
		return update(index, newValue, 1, 0, n-1);
	}
};

const int MAX_N = 100001;

vector<vector<int>> a;

int no2serial[MAX_N], serial2no[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void preorder(int here, int d, vector<int>& b)
{
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	nextSerial++;

	depth[here] = d;
	locInTrip[here] = b.size();

	for(auto &pick : a[here])
	{
		b.push_back(no2serial[here]);
		preorder(pick, d+1, b);
	}
	b.push_back(no2serial[here]);
}

int main()
{
	int T;
	scanf("%d",&T);

	while(T--)
	{
		int N, Q;
		scanf("%d%d",&N,&Q);

		a.clear();
		a.resize(N+1);
		for(int i=1; i < N; i++)
		{
			int n;
			scanf("%d",&n);
			a[n].push_back(i);
		}

		nextSerial = 0;
		vector<int> b;
		preorder(0, 0, b);

		RMQ q(b);

		while(Q--)
		{
			int a, b;
			scanf("%d%d",&a,&b);
			int lu = locInTrip[a], lv = locInTrip[b];
			if(lu > lv)
				swap(lu,lv);
			int ancient = serial2no[q.query(lu,lv)];
			printf("%d\n", depth[a] + depth[b] - 2 * depth[ancient]);
		}
	}
	return 0;
}