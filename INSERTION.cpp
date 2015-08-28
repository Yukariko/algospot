#include <iostream>
#include <algorithm>

using namespace std;

template<typename KeyType>
class treap
{
public:
	struct Node
	{
		KeyType key;
		int priority, size;
		Node *left, *right;

		Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

		void setLeft(Node *newLeft)
		{
			left = newLeft;
			calcSize();
		}
		void setRight(Node *newRight)
		{
			right = newRight;
			calcSize();
		}

		void calcSize()
		{
			size = 1;
			if(left)
				size += left->size;
			if(right)
				size += right->size;
		}
	};
	typedef pair<Node*,Node*> NodePair;

	treap() : root(NULL) {}

	NodePair split(Node *root, KeyType key)
	{
		if(root == NULL)
			return NodePair(NULL, NULL);
		if(root->key < key)
		{
			NodePair rs = split(root->right, key);
			root->setRight(rs.first);
			return NodePair(root, rs.second);
		}
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(ls.first, root);
	}

	Node *insert(Node *root, Node *node)
	{
		if(root == NULL)
			return node;

		if(root->priority < node->priority)
		{
			NodePair splitted = split(root, node->key);
			node->setLeft(splitted.first);
			node->setRight(splitted.second);
			return node;
		}
		else if(node->key < root->key)
			root->setLeft(insert(root->left, node));
		else
			root->setRight(insert(root->right, node));
		return root;
	}

	void insert(KeyType key)
	{
		Node *node = new Node(key);
		root = insert(root, node);
	}

	Node *merge(Node *a, Node *b)
	{
		if(a == NULL)
			return b;
		if(b == NULL)
			return a;
		if(a->priority < b->priority)
		{
			b->setLeft(merge(a, b->left));
			return b;
		}
		a->setRight(merge(a->right, b));
		return a;
	}

	Node *erase(Node *root, KeyType key)
	{
		if(root == NULL)
			return root;

		if(root->key == key)
		{
			Node *ret = merge(root->left, root->right);
			delete root;
			return ret;
		}
		if(key < root->key)
			root->setLeft(erase(root->left, key));
		else
			root->setRight(erase(root->right, key));
		return root;
	}

	void erase(KeyType key)
	{
		root = erase(root, key);
	}

	Node *kth(Node *root, int k)
	{
		int leftSize = 0;
		if(root->left != NULL)
			leftSize = root->left->size;
		if(k <= leftSize)
			return kth(root->left, k);
		if(k == leftSize + 1)
			return root;
		return kth(root->right, k - leftSize - 1);
	}

	KeyType kth(int k)
	{
		return kth(root, k)->key;
	}

	int countLessThan(Node *root, KeyType key)
	{
		if(root == NULL)
			return 0;
		if(root->key >= key)
			return countLessThan(root->left, key);
		int ls = (root->left? root->left->size : 0);
		return ls + 1 + countLessThan(root->right, key);
	}

	int countLessThan(KeyType key)
	{
		return countLessThan(root, key);
	}

private:
	Node *root;
};

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N;
		cin >> N;

		vector<int> a(N);
		for(int i=0; i < N; i++)
			cin >> a[i];

		treap<int> tr;
		for(int i=1; i <= N; i++)
			tr.insert(i);

		vector<int> ans(N);
		for(int i=N-1; i >= 0; i--)
		{
			ans[i] = tr.kth(i - a[i] + 1);
			tr.erase(ans[i]);
		}

		for(int i=0; i < N; i++)
			cout << ans[i] << " ";
		cout << '\n';
	}
	return 0;
}