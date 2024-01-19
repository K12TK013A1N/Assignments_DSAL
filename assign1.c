#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
  for(int i=1;i<argc;i++){
      FILE *ptr;
      ptr = fopen(argv[i],"r");
      int a = 0;
      if(ptr == NULL){printf("ERROR NO FILE");}
      else{
      int a;
      fscanf(ptr,"%d",&a);
      int min = a;
      int max = a;
      int sum = a;
      int line = 1;
      while(fscanf(ptr,"%d",&a)!=EOF){
        sum+=a;
        line++;
        if(a>=max){max=a;}
        if(a<=min){min=a;}
      }
      float avg1;
      avg1 = (float)sum / line;
      FILE *fw;
      if(argc == 2){char name[] = "output.txt";
      fw = fopen(name,"w");}
      else{char name[] = "";
      sprintf(name,"output%d.txt",i);
      fw = fopen(name,"w");}

      fprintf(fw,"lines = %d\n", line);
      fprintf(fw,"min %d\n",min);
      fprintf(fw,"max = %d\n",max);
      fprintf(fw,"Sum = %d\n",sum);
      fprintf(fw,"avg = %.2f\n",avg1);
  }
  }

  return 0;
}