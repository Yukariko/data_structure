#include <iostream>
#include <vector>

using namespace std;

template<typename T = long long>
struct matrix
{
	int N, M;
	vector< vector<T> > a;
	static const long long MOD = 1000000;

	matrix() : N(2), M(2), a(vector< vector<T> >(N, vector<T>(M, 0))) {}
	matrix(int N, int M) : N(N), M(M), a(vector< vector<T> >(N, vector<T>(M, 0)))	{}
	matrix(const vector< vector<T> > &a) : a(a), N(a.size()), M(a[0].size()) {}
	matrix(const matrix<T> &mat) : N(mat.N), M(mat.M), a(mat.a) {}

	matrix operator% (long long m) const
	{
		matrix ans(a);
		for(int i=0; i < a.size(); i++)
			for(int j=0; j < a[i].size(); j++)
				ans.a[i][j] %= m;
		return ans;
	}

	matrix<T> operator* (const matrix<T> &q) const
	{
		matrix<T> ans(N, q.M);
		for(int i=0; i < N; i++)
		{
			for(int j=0; j < q.M; j++)
			{
				ans.a[i][j] = 0;
				for(int p=0; p < M; p++)
					ans.a[i][j] += a[i][p] * q.a[p][j];
			}
		}
		return ans;
	}

	static matrix<T> calcPow(matrix<T> mat, long long p, long long m)
	{
		mat = mat % m;
		if(p == 1)
			return mat;

		if(p & 1)
			return (mat * calcPow(mat * mat, (p-1)/2, m)) % m;

		return calcPow(mat * mat, p/2, m);
	}

	matrix<T> pow(long long p, long long m) const
	{
		matrix<T> ans(a);
		return calcPow(ans, p, m);
	}

	static long long fibo(long long n)
	{
		matrix<long long> m(2,2);
		m.a[0][0] = 1;
		m.a[0][1] = 1;
		m.a[1][0] = 1;
		m.a[1][1] = 0;

		if(n==1 || n==2)
			return 1;

		matrix<long long> ans = m.pow(n-2,m.MOD);
		return (ans.a[0][0] + ans.a[0][1]) % m.MOD;
	}
};