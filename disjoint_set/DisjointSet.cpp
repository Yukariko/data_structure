#include <bits/stdc++.h>

using namespace std;

struct DisjointSet {
	vector<int> group;
	DisjointSet(int N)
	{
		group.resize(N);
		for(int i=0; i < N; i++)
			group[i] = i;
	}

	int find(int n)
	{
		if(group[n] == n)
			return n;
		return group[n] = find(group[n]);
	}

	void merge(int p, int q)
	{
		p = find(p);
		q = find(q);
		if(p != q)
			group[p] = q;
	}

	int group_num()
	{
		vector<bool> check(group.size(), false);
		int ans = 0;
		for(int i=0; i < group.size(); i++)
			if(check[find(i)] == false)
				check[find(i)] = true, ans++;
		return ans;
	}
};

int main()
{

	return 0;
}