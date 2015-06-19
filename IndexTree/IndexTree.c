#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int iData;

typedef struct IndexTree
{
	iData **tree;
	int start;
	int len;
	int depth;
} IndexTree;


iData icmp(iData *p, iData *q);
iData ircmp(iData p, iData q);

void iUpdate(IndexTree *idt, int idx)
{
	for(int i=idt->depth-1; i>=0; i--)
	{
		idx >>= 1;
		idt->tree[i][idx] = icmp(&idt->tree[i+1][idx<<1],&idt->tree[i+1][(idx<<1)+1]);
	}
}

void iInsert(IndexTree *idt, int idx, iData data)
{
	idx -= idt->start;
	idt->tree[idt->depth][idx] = data;
	iUpdate(idt, idx);
}

iData iFind(IndexTree *idt, int depth, int idx, int start, int end)
{
	if(depth == idt->depth)
		return idt->tree[depth][idx];
	
	int diff = idt->depth - depth;
	if((start >> diff) < idx && idx < (end >> diff))
		return idt->tree[depth][idx];

	if((idx << 1) < (start >> (diff - 1)))
		return iFind(idt, depth+1, (idx << 1) + 1, start, end);

	if((idx << 1) + 1 > (end >> (diff - 1)))
		return iFind(idt, depth+1, (idx << 1), start, end);

	return ircmp(iFind(idt, depth+1, idx << 1, start, end),iFind(idt, depth+1, (idx << 1) + 1, start, end));
}

iData iGet(IndexTree *idt, int start, int end)
{
	start -= idt->start;
	end -= idt->start;
	return iFind(idt, 0, 0, start, end);
}

int iCount(IndexTree *idt, int count)
{
	int pos = 0;
	for(int i=0; i < idt->depth; i++)
	{
		for(int z=1 << i; pos < z; pos++)
		{
			if(idt->tree[i][pos] < count)
				count -= idt->tree[i][pos];
			else
				break;
		}
		pos <<= 1;
	}

	for(;count > 0;)
	{
		if(idt->tree[idt->depth][pos] >= count)
			return pos + idt->start;
		else
			count -= idt->tree[idt->depth][pos];
		pos++;
	}
	return pos + idt->start;
}

iData iTop(IndexTree *idt)
{
	return idt->tree[0][0];
}

IndexTree *CreateIndexTree(int start, int len, iData *init)
{
	IndexTree *idt = (IndexTree *)malloc(sizeof(IndexTree));
	idt->start = start;
	idt->len = len;

	for(idt->depth=0; (1<<idt->depth) < idt->len;idt->depth++);

	idt->tree = (iData **)malloc(sizeof(iData *) * idt->depth);

	for(int i=0; i <= idt->depth; i++)
		idt->tree[i] = (iData *)malloc(sizeof(iData) * (1 << i));

	for(int i=0;i <= idt->depth; i++)
		memset(idt->tree[i], 0, sizeof(iData) * (1 << i));

	if(init)
	{
		for(int i=0; i < idt->len; i++)
			idt->tree[idt->depth][i] = init[i];
		for(int i=0; i < idt->len; i++)
			iUpdate(idt, i);
	}
	return idt;
}

void iDestroy(IndexTree *idt)
{
	for(int i=0;i<idt->depth;i++)
		free(idt->tree[i]);
	free(idt->tree);
	free(idt);
}

iData icmp(iData *p, iData *q)
{
	return *p + *q;
}

iData ircmp(iData p, iData q)
{
	return p + q;
}

int main()
{
	iData a[10] = {7,5,3,8,2,6,9,4,1,10};
	IndexTree *idt = CreateIndexTree(0,10,a);

	printf("%d\n",iTop(idt));
	printf("%d",iGet(idt,0,2));
	return 0;
}