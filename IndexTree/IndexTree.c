#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int iData;

typedef struct IndexTree
{
	iData *tree;
	int len;
	int size;
	int start;
} IndexTree;


iData icmp(iData *p, iData *q);
iData ircmp(iData p, iData q);

void iUpdate(IndexTree *idt, int idx)
{
	while(idx > 1)
	{
		idx >>= 1;
		idt->tree[idx] = icmp(&idt->tree[idx<<1],&idt->tree[(idx<<1)+1]);
	}
}

void iInsert(IndexTree *idt, int idx, iData data)
{
	idx += idt->start;
	idt->tree[idx] = data;
	return iUpdate(idt, idx);
}

int iCount(IndexTree *idt, int count)
{
	int start = 1, end = idt->start;
	while(start < end)
	{
		start <<= 1;
		if(idt->tree[start] < count)
		{
			count -= idt->tree[start];
			++start;
		}
	}
	return start - end + 1;
}

iData iTop(IndexTree *idt)
{
	return idt->tree[1];
}

void iMake(IndexTree *idt, int left)
{
	for(int i=left>>1; i>0; i>>=1)
	{
		int right = i << 1;
		for(int j=i; j < right; j++)
			idt->tree[j] = icmp(&idt->tree[j<<1],&idt->tree[(j<<1)+1]);
	}
}

IndexTree *CreateIndexTree(int len, iData *init)
{
	IndexTree *idt = (IndexTree *)malloc(sizeof(IndexTree));
	idt->len = len;
	
	idt->start = 1;
	while(idt->start < idt->len)
		idt->start <<= 1;

	idt->size = idt->start << 1;


	idt->tree = (iData *)malloc(sizeof(iData) * idt->size);
	memset(idt->tree, 0, sizeof(iData) * idt->size);

	if(init)
	{
		for(int i=0; i < idt->len; i++)
			idt->tree[idt->start + i] = init[i];
		iMake(idt, idt->start);
	}
	return idt;
}

void iDestroy(IndexTree *idt)
{
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
	IndexTree *idt = CreateIndexTree(10,a);

	printf("%d\n",iTop(idt));
	iDestroy(idt);
	return 0;
}