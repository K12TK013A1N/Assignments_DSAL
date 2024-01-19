#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct node
{
  int data;
  struct node *left;
  struct node *right;
};

struct node *getnewnode(int data)
{
  struct node *newnode;
  newnode = (struct node*)malloc(sizeof(struct node));
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}

struct node* insert(struct node *newroot, int data, FILE *fo)
{
  if(newroot==NULL)
  {
    fprintf(fo,"%d inserted\n",data);
    newroot = getnewnode(data);
    return newroot;
  }
  else if(data<=newroot->data)
  {
    newroot->left = insert(newroot->left,data,fo);
    return newroot;
  }
  else if(data>newroot->data)
  {
    newroot->right = insert(newroot->right,data,fo);
    return newroot;
  }
}

bool search(struct node* root, int data)
{
  if(root == NULL){return false;}
  else if(root->data == data){return true;}
  else if(data < root->data)
  {
    return search(root->left,data);
  }
  else
  {
    return search(root->right,data);
  }
}

void preorder(struct node* root, FILE *fo)
{
  if (root == NULL){return;}
  fprintf(fo,"%d ",root->data);
  preorder(root->left,fo);
  preorder(root->right,fo);
}
void inorder(struct node* root, FILE *fo)
{
  if(root == NULL){return;}
  inorder(root->left,fo);
  fprintf(fo,"%d ",root->data);
  inorder(root->right,fo);
}
void postorder(struct node* root, FILE *fo)
{
  if(root==NULL){return;}
  postorder(root->left,fo);
  postorder(root->right,fo);
  fprintf(fo,"%d ",root->data);
}

void maximum(struct node* root, FILE *fo)
{
  if(root==NULL){fprintf(fo,"\n"); return;}
  while(root->right != NULL)
  {
    root = root->right;
  }
  fprintf(fo,"%d\n",root->data);
}

void minimum(struct node* root, FILE *fo)
{
  if(root==NULL){fprintf(fo,"\n"); return;}
  while(root->left!=NULL)
  {
    root = root->left;
  }
  fprintf(fo,"%d\n", root->data);
}

struct node* find(struct node* root, int data)
{
  if(root == NULL){return NULL;}
  else if(root->data == data){return root;}
  else if(data < root->data)
  {
    return find(root->left,data);
  }
  else
  {
    return find(root->right,data);
  }
}


void getpredecessor(struct node* root, int key, FILE *fo)
{
  if(root==NULL){fprintf(fo,"Tree is empty\n");}
  else{
    struct node* current;
    if(find(root,key)==NULL)
    {
      fprintf(fo,"%d does not exist\n",key);
      return;
    }
    else
    {
      current = find(root,key);
      struct node* predecessor;
      struct node* child;
      if(current->left != NULL)
      {
        struct node* temp;
        temp = current->left;
        while(temp->right!= NULL)
        {
          temp = temp->right;
        }
        fprintf(fo,"%d\n",temp->data);
      }
      else
      {
        predecessor = NULL;
        child = root;
        while(child != current){
          if(child->data < key)
          {
            predecessor = child;
            child = child->right;
          }
          else
          {
            child = child->left;
          }
        }
        if(predecessor!=NULL)
        {
          fprintf(fo,"%d\n",predecessor->data);
        }
        else{
          fprintf(fo,"predecessor of %d doesn't exist",current->data);
        }
      }
    }
 }
}

void getsuccessor(struct node* root,int key,FILE *fo)
{
  if(root==NULL){fprintf(fo,"Tree is empty\n"); return;}
  else{
    if(find(root,key)==NULL)
    {
      fprintf(fo,"%d does not exist\n",key);
    }
    else
    {
      struct node* current;
      current = find(root,key);
      if(current->right!=NULL)
      {
        struct node* temp;
        temp = current->right;
        while(temp->left!=NULL)
        {
          temp = temp->left;
        }
        fprintf(fo,"%d\n",temp->data);
      }
      else
      {
        struct node* parent = root;
        struct node* successor = NULL;
        while(parent!=current)
        {
          if(parent->data > current->data)
          {
            successor = parent;
            parent = parent->left;
          }
          else
          {
            parent = parent->right;
          }
        }
        if(successor!=NULL){fprintf(fo,"%d\n",successor->data);}
        else{fprintf(fo,"successor of %d does not exist\n",current->data);}
      }
    }
  }
}

int main(int argc, char *argv[])
{
  struct node* root;
  root = NULL;

  FILE *fptr;
  fptr = fopen(argv[1],"r");

  FILE *fo;
  fo = fopen("output.txt","w");
 
  char a[21];
  char a1[] = "insert";
  char a2[] = "inorder";
  char a3[] = "preorder";
  char a4[] = "postorder";
  char a5[] = "maximum";
  char a6[] = "minimum";
  char a7[] = "successor";
  char a8[] = "predecessor";
  char a9[] = "search";
  int si = 0;
  int ss = 0;
  int sp = 0;
  int sr = 0;
  while(fscanf(fptr,"%s",a)!=EOF)
  {
    if(si==1)
    {
      root = insert(root,atoi(a),fo);
      si = 0;
    }

    if(ss==1)
    {
      getsuccessor(root,atoi(a),fo);
      ss = 0;
    }

    if(sp == 1)
    {
      getpredecessor(root,atoi(a),fo);
      sp=0;
    }

    if(sr == 1)
    {
      if(search(root,atoi(a))==true){fprintf(fo,"%d found\n",atoi(a));}
      else{fprintf(fo,"%d not found\n",atoi(a));}
      sr = 0;
    }

    if(!strcmp(a,a1)){si = 1;}
    if(!strcmp(a,a2)){inorder(root,fo); fprintf(fo,"\n");}
    if(!strcmp(a,a3)){preorder(root,fo); fprintf(fo,"\n");}
    if(!strcmp(a,a4)){postorder(root,fo); fprintf(fo,"\n");}
    if(!strcmp(a,a5)){maximum(root,fo);}
    if(!strcmp(a,a6)){minimum(root,fo);}
    if(!strcmp(a,a7)){ss = 1;}
    if(!strcmp(a,a8)){sp = 1;}
    if(!strcmp(a,a9)){sr = 1;}
  }

  return 0;
}