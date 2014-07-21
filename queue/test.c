#define MAX_QUEUE 10
typedef int DATA;
typedef struct queue{DATA data;struct queue *next;}queue;
queue *head[MAX_QUEUE],*tail[MAX_QUEUE];
void push(int index,DATA val)
{
  tail[index]->data=val;
  tail[index]->next=(queue *)malloc(sizeof(queue));
  tail[index]=tail[index]->next;
  tail[index]->data=0;
  tail[index]->next=0;
}
DATA pop(int index)
{
  queue *p=head[index];
  DATA result=head[index]->data;
  head[index]=head[index]->next;
  free(p);
  return result;
}
int isEmpty(int index)
{
  return !head[index];
}
void init(int index)
{
  head[index]=(queue *)malloc(sizeof(queue));
  head[index]->data=0;
  head[index]->next=0;
  tail[index]=head[index];
}
void destroy(int index)
{
  for(;!isEmpty(index);)pop(index);
}
queue *find(int index,DATA val)
{
  queue *p=head[index];
  for(;p;p=p->next)if(p->data==val)return p;
  return 0;
}
main()
{
  init(0);
  push(0,1);push(0,2);push(0,3);
  printf("%d\n",pop(0));
  printf("%d\n",pop(0));
  printf("%d\n",pop(0));
}
