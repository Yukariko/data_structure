typedef int tData;
typedef struct NODE{
  tData data;
  struct NODE *left,*right;
}NODE;
typedef struct BST{
  NODE *root;
  int count;
}BST;
BST *CreateBST()
{
  BST *bst=(BST *)malloc(sizeof(BST));
  bst->root=(NODE *)malloc(sizeof(NODE));
  bst->root->left=bst->root->right=0;
  bst->count=0;
  return bst;
}
NODE *MakeNode(tData data)
{
  NODE *node=(NODE *)malloc(sizeof(NODE));
  node->data=data;
  node->left=node->right=0;
  return node;
}
void insert(NODE *node,tData data)
{
  if(data < node->data)
  {
    if(node->left==0)
    {
      node->left=MakeNode(data);
    }
    else insert(node->left,data);
  }
  else
  {
    if(node->right==0)
    {
      node->right=MakeNode(data);
    }
    else insert(node->right,data);    
  }
}
void bInsert(BST *bst,tData data)
{
  if(bst->count==0)
  {
    bst->root->data=data;
  }
  else insert(bst->root,data);
  bst->count++;
}
main()
{
  
}
