#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

class BigInt
{
public:

	// constructor 
	BigInt(){}
	BigInt(string str)
	{
		for (int i = str.size(); i--;) {
			num.push_back(str[i] - '0');
		}
	}
	BigInt(const BigInt &ref) : num(ref.num){}
	BigInt(const vector<int> &n) : num(n) {}

	// member function
	vector<int>& getNum() { return num; }
	
	int size() const { return num.size(); }

	void normalize()
	{
		return;
		int upper = 0;

		num.push_back(0);

		for (int i = 0; i<num.size(); i++) {
			num[i] += upper;
			if (num[i] < 0)	{
				upper = (abs(num[i])+9) / 10;
				num[i] += upper * 10;
				upper = -upper;
			}
			else if (num[i] >= 10) {
				upper = num[i] / 10;
				num[i] %= 10;
			}
			else upper = 0;
		}
		while(num.size() > 1 && num.back() == 0) num.pop_back();
	}

	void pow(int n)
	{
		vector<int> ret(n, 0);
		for(int i = 0;i < num.size();i++)ret.push_back(num[i]);
		num = ret;
	}


	string getString()
	{
		if (num.size() == 0) return string("0");
		string ret;

		for (int i = num.size(); i--;) {
			if(num[i] < 0) {
				ret.push_back('-');
				ret.push_back(abs(num[i]) + '0');
			}
			else {
				ret.push_back(num[i] + '0');
			}
		}
		return ret;
	}

	static BigInt karatsuba(BigInt &p,BigInt &q)
	{
		vector<int> &a = p.getNum(), &b = q.getNum();
		int an = a.size(), bn = b.size();

		if (an < bn) return karatsuba(q,p);
		if (an == 0 || bn == 0) return BigInt(vector<int>());
		if (an <= 50) return p*q;
		int half = an / 2;

		BigInt a0(vector<int>(a.begin(), a.begin() + half));
		BigInt a1(vector<int>(a.begin() + half, a.end()));

		BigInt b0(vector<int>(b.begin(), b.begin() + MIN(bn, half)));
		BigInt b1(vector<int>(b.begin() + MIN(bn, half), b.end()));

		BigInt z2 = karatsuba(a1, b1);
		BigInt z0 = karatsuba(a0, b0);

		a0 = a0 + a1;
		b0 = b0 + b1;

		BigInt z1 = karatsuba(a0,b0);

		z1 = z1 - z0;
		z1 = z1 - z2;

		z1.pow(half);
		z2.pow(half * 2);
		BigInt ret;
		ret = ret + z0 + z1 + z2;
		return ret;
	}


	// operator
	BigInt operator +(const BigInt &b)
	{
		BigInt ret;
		vector<int> &rNum = ret.getNum();
		int end = MAX(num.size(), b.size());
		for (int i = 0; i<end; i++)
		{
			int k = 0;
			if (num.size() > i)
				k += num[i];
			if (b.size() > i)
				k += b[i];
			rNum.push_back(k);
		}
		ret.normalize();
		return ret;
	}

	BigInt operator -(const BigInt &b)
	{
		BigInt ret;
		vector<int> &rNum = ret.getNum();
		int end = MAX(num.size(), b.size());
		for (int i = 0; i<end; i++)
		{
			int k = 0;
			if (num.size() > i)
				k = num[i];
			if (b.size() > i)
				k -= b[i];
			rNum.push_back(k);
		}
		ret.normalize();
		return ret;
	}


	BigInt operator *(BigInt &b)
	{
		int an = num.size(), bn = b.size();
		if(MAX(an,bn) > 50) return karatsuba(*this, b);

		BigInt ret(vector<int>(an + bn + 1, 0));
		vector<int> &rNum = ret.getNum();
		for(int i=0; i < an; i++)
			for(int j=0; j < bn; j++)
				rNum[i+j] += num[i] * b[j];
		ret.normalize();
		return ret;
	}

	int operator [] (int pos) const
	{
		return num[pos];
	}


private:
	vector<int> num;

};

int hugs(const string& members, const string& fans)
{
	vector<int> as(members.size()), bs(fans.size());
	for(int i=0;i<members.size();i++) as[i] = (members[i] == 'M');
	for(int i=0;i<fans.size();i++) bs[fans.size() - i - 1] = (fans[i] == 'M');
	BigInt a(as),b(bs);
	BigInt ret = a * b;

	int res = 0;
	for(int i=members.size() - 1; i < fans.size(); i++)
	{
		if(ret[i] == 0) res++;
	}
	return res;
}

int main()
{
	int C;
	scanf("%d ",&C);
	for(;C--;)
	{
		char a[200001],b[200001];
		gets(a);
		gets(b);
		printf("%d\n",hugs(a,b));
	}
}