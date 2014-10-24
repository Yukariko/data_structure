typedef int iData;
typedef struct IndexTree {
  iData *tree;
  int size;
  int (*compare)(iData,iData);
} IndexTree;

int iGetSize(int size)
{
  int i;
  for(i=1;i<size;i<<=1);
  return i<<1;
}

void iUpTree(IndexTree *indexTree, int pos)
{
  for(;pos/2;pos/=2)
  {
    if(indexTree->compare(indexTree->tree[pos],indexTree->tree[pos/2]))
    {
      indexTree->tree[pos/2]=indexTree->tree[pos];
    }
    else break;
  }
}

void iInitTree(IndexTree *indexTree, iData *init,int size)
{
  int i,pos = indexTree->size >> 1;
  for(i=0;i<size;i++)
  {
    indexTree->tree[pos+i] = init[i];
  }
  for(i=0;i<size;i++)
  {
    iUpTree(indexTree, pos+i);
  }
}

IndexTree *CreateIndexTree(iData *init, int size, int (*compare)(idata,idata))
{
  IndexTree *indexTree;
  indexTree = (IndexTree *)malloc(sizeof(IndexTree));
  indexTree->size = iGetSize(size);
  indexTree->tree = (iData *)malloc(sizeof(iData) * (indexTree->size + 1));
  indexTree->compare = compare;
  iInitTree(indexTree,init,size);
  return indexTree;
}

main()
{
}
