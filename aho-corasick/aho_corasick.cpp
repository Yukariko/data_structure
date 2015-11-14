#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

template <char tok = 'A'>
struct Trie
{
	int no;
	Trie *node[26];
	Trie *fail;

	vector<int> output;

	Trie() : no(-1), fail(NULL)
	{
		memset(node, 0, sizeof(node));
	}

	void push(const string &str, int idx, int sIdx=0)
	{
		if(str[sIdx] == 0)
		{
			no = idx;
			return;
		}

		Trie *&next = node[str[sIdx]-tok];
		if(next == 0)
			next = new Trie;

		return next->push(str, idx, sIdx+1);
	}

	int find(const string& str, int sIdx=0)
	{
		if(str[sIdx] == 0)
			return no;

		Trie *&next = node[str[sIdx]-tok];

		if(next == 0)
		{
			if(fail)
			{
				cout << "!";
				return fail->find(str, sIdx+1);
			}
			return -2;
		}

		return next->find(str, sIdx+1);
	}

	void setFailure()
	{
		queue<Trie*> q;

		fail = this;
		q.push(this);

		while(!q.empty())
		{
			Trie *here = q.front();
			q.pop();

			for(int edge=0; edge < 26; ++edge)
			{
				Trie *child = here->node[edge];
				if(!child)
					continue;

				if(here == this)
					child->fail = this;
				else
				{
					Trie *t = here->fail;
					while(t != this && t->node[edge] == NULL)
						t = t->fail;
					if(t->node[edge])
						t = t->node[edge];
					child->fail = t;
				}

				child->output = child->fail->output;
				if(child->no != -1)
					child->output .push_back(child->no);
				q.push(child);
			}
		}
	}
};