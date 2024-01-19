#include <stdio.h>
#include <string.h>
int partition1(int a[], int lb, int ub);
void swap(int *a, int *b);
void quicksort(int a[],int lb, int ub);
void printer(int a[],int c);
int main(int argc, char *argv[])
{
  FILE *ptr;
  ptr = fopen(argv[1],"r");
  if(ptr == NULL){printf("No file");}
  else
  {
    int a;
    int n =0;
    while(fscanf(ptr,"%d",&a)!=EOF)
    {
      n++;
    }
    rewind(ptr);
    int arr[n];
    int x;
    int i =0;
    while(fscanf(ptr,"%d",&x)!=EOF)
    {
      arr[i] = x;
      i++;
    }
    
    quicksort(arr,0,n-1);
    printer(arr,n);
    return 0;
  }
}
int partition1(int a[], int lb, int ub)
{
  int start = lb;
  int end = ub;
  int pivot = a[lb];
  while(start<end)
  {
    while(a[start]<=pivot)
    {
      start++;

    }
    while(a[end]>pivot)
    {
      end--;
    }
    if(end>start)
    {
      swap(a+start,a+end);
    }
  }
  swap(a+lb,a+end);
  return end;
}
void swap(int *a, int *b)
{
  int c = *a;
  *a = *b;
  *b = c;
}
void quicksort(int a[],int lb, int ub)
{
  if(lb<ub)
  {
    int pos = partition1(a,lb,ub);
    quicksort(a,lb,pos-1);
    quicksort(a,pos+1,ub);
  }
}

void printer(int a[],int c)
{
  FILE *pw;
  pw = fopen("quicksort.txt","w");
  for(int i=0; i<c;i++)
  {
    fprintf(pw,"%d\n",a[i]);
  }
}

