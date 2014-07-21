#define MAX_stack 10
typedef int DATA;
typedef struct stack{DATA data;struct stack *next;}stack;
stack *head[MAX_stack],*tail[MAX_stack];
void push(int index,DATA val)
{
  stack *p=head[index];
  head[index]=(stack *)malloc(sizeof(stack));
  head[index]->data=val;
  head[index]->next=p;
}
DATA pop(int index)
{
  stack *p=head[index];
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
  head[index]=(stack *)malloc(sizeof(stack));
  head[index]->data=0;
  head[index]->next=0;
  tail[index]=head[index];
}
void destroy(int index)
{
  for(;!isEmpty(index);)pop(index);
}
stack *find(int index,DATA val)
{
  stack *p=head[index];
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
