typedef int DATA;
typedef struct stack{DATA data;struct stack *next;}stack;
stack *head,*tail;
push(DATA val)
{
  tail->data=val;
  tail->next=(stack *)malloc(sizeof(stack));
  tail=tail->next;
  tail->data=0;
  tail->next=0;
  
}
DATA pop()
{
  stack *p=head;
  DATA result=head->data;
  head=head->next;
  free(p);
  return result;
}
init()
{
  head=(stack *)malloc(sizeof(stack));
  head->data=0;
  head->next=0;
  tail=head;
}
