#include <iostream>
#include <cstring>

using namespace std;

struct wTree
{
	bool end;
	int no;
	wTree *node[26];

	wTree() : end(false), no(-1)
	{
		memset(node, 0, sizeof(node));
	}

	void push(string &str, int idx, int sIdx=0)
	{
		if(str[sIdx] == 0)
		{
			no = idx;
			return;
		}

		wTree *&next = node[str[sIdx]-'A'];
		if(next == 0)
			next = new wTree;

		return next->push(str, idx, sIdx+1);
	}

	int find(char *str, int sIdx=0)
	{
		if(str[sIdx] == 0)
			return no;

		wTree *&next = node[str[sIdx]-'A'];

		if(next == 0)
			return -2;

		return next->find(str, sIdx+1);
	}
};
