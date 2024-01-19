#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void enqueue(int x);
void dequeue();
void display(FILE *x);
 
struct node{
  int data;
  struct node *next;
};
struct node *front=0;
struct node *rear=0;
struct node *newnode=0;


int main(int argc, char *argv[])
{
  FILE *ptr;
  FILE *pw;
  pw = fopen("output.txt","w");
  ptr = fopen(argv[1],"r");
  if(ptr==NULL){char d[] = "No Input File"; fprintf(pw,"%s\n",d); return 0;}
  else
  {
    int n1 =0;
    int n2=0;
    int n3 =0;
    char a1[100];
    char a2[]="enqueue";
    char a3[]="dequeue";
    char a4[]="display";
    while(fscanf(ptr,"%s",a1)!=EOF)
    {
      if(n1 == 1)
      {
        fprintf(pw,"Inserted Value: %d\n",atoi(a1));
        enqueue(atoi(a1)); 
        n1=0;
      }
      if(!strcmp(a1,a2)){n1 =1;}

      if(!strcmp(a1,a3)){n2=1;}
      if(n2==1)
      {
      if(front==0){char q1[]="Queue is Empty"; fprintf(pw,"%s\n",q1);}
      else{fprintf(pw,"deleted Value: %d\n",front->data);}
      dequeue(); 
      n2=0;
      }

      if(!strcmp(a1,a4)){n3=1;}
      if(n3 ==1){display(pw); n3 =0;}
    }
  }
  return 0;
}

void enqueue(int x)
{
  newnode=(struct node*)malloc(sizeof(struct node));
  newnode->data = x;
  newnode->next = 0;
  if(rear==0&&front==0)
  {
    front = rear = newnode;
    rear->next=front;
  } 
  else
  {
    rear->next = newnode;
    rear = newnode;
    rear->next = front;
  }

}
  void dequeue()
  {
    struct node *temp;
    temp = front;
    if(front==0 &&rear == 0){int m=0;}
    else if(front == rear)
    {
      front = rear = 0;
      free(temp);
    }
    else
    {
      front = front->next;
      rear->next = front;
      free(temp);
    }
  }
  

void display(FILE *x)
{
  struct node *temp;
  temp = front;
  if(front==0&&rear==0){char c[]="Queue is Empty\n"; fprintf(x,"%s",c);}
  else
  {
    char b[] = "Elements of the queue:";
    fprintf(x,"%s",b);
    while(temp->next!=front)
    {
      fprintf(x," %d",temp->data);
      temp = temp->next;
    }
    fprintf(x," %d",temp->data);
  }
  char e = '\n';
  fprintf(x,"%c",e);
}
