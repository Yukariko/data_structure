const static int ASC = 1;
const static int DESC = 2;
typedef struct Pack{
  int *arr;
  int *pack;
  int size;
  int packWidth;
  int packSize;
  int min,max;
}Pack;
Pack *CreatePack(int size,int packWidth)
{
  Pack *p=(Pack *)malloc(sizeof(Pack));
  p->arr=(int *)malloc(sizeof(int) * (size + 1));
  p->pack=(int *)malloc(sizeof(int) * (size / packWidth + 2));
  memset(p->arr,0,sizeof(int) * (size + 1));
  memset(p->pack,0,sizeof(int) * (size / packWidth + 2));
  p->size = size;
  p->packWidth = packWidth;
  p->packSize = size / packWidth + 1;
  p->min = size + 1;
  p->max = 0;
  return p;
}
void pInsert(Pack *p,int pos)
{
  p->arr[pos]++;
  p->pack[pos/p->packWidth]++;
  p->min=p->min > pos ? pos : p->min;
  p->max=p->max < pos ? pos : p->max;
}
void pDelete(Pack *p,int pos,int opt)
{
  if(opt == 0) // all
  {
    p->pack[pos/p->packWidth] -= p->arr[pos];
    p->arr[pos]=0;
  }
  else
  {
    p->pack[pos/p->packWidth]-=opt;
    p->arr[pos]-=opt;
  }
}
int pFind(Pack *p,int pos)
{
  int i,k,s=0;
  for(i=p->min/p->packWidth;i<=p->packSize;i++)
  {
    if(s + p->pack[i]>=pos)break;
    s += p->pack[i];
  }
  i*=p->packWidth;
  k=i+p->packWidth;
  for(;i<k;i++)
  {
    s+=p->arr[i];
    if(s>=pos)return i;
  }
  return -1;
}
int pCount(Pack *p,int pos, int opt)
{
  int i,k=pos/p->packWidth,s=0;
  if(opt == ASC)
  {
    for(i=p->min/p->packWidth;i<k;i++)
    {
      s += p->pack[i];
    }
    i*=p->packWidth;
    k=pos;
    for(;i<k;i++)
    {
      s += p->arr[i];
    }
  }
  else
  {
    for(i=p->packSize;i>=k;i--)
    {
      s += p->pack[i];
    }
    i=(i+1)*p->packWidth;
    k=pos;
    for(;i<=k;i++)
    {
      s -= p->arr[i];
    }
  }
  return s;
}
void pFree(Pack *p)
{
  free(p->arr);
  free(p->pack);
  free(p);
}
void pInit(Pack *p)
{
  memset(p->arr,0,sizeof(int)*p->size);
  memset(p->pack,0,sizeof(int)*p->packSize);
}
main()
{
  Pack *p = CreatePack(100,20);
  int arr[5] = {1,43,20,35,70};
  for(int i=0; i<5; i++) pInsert(p,arr[i]);
  printf("%d %d\n",pFind(p , 3), pCount(p,35));
}
