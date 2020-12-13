#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
          pid_t pid;
          int n,i,j;
          printf("enter the value of n, where first  n terms  of the series will be  displayed \n");
          scanf("%d",&n);
          pid=fork();
          if(pid==-1)
          printf("fork failed\n");
          else if(pid>0)
          {
          //printf("THis is parent block \n");
          printf("The odd series: ");
          for(j=1,i=1;j<=n;i=i+2,j++)
          {
          printf("%d\t",i);
          }
          printf("\n");
          }
          else
          {
        //  printf("this is the child block\n");
          printf("The even series: ");
          for(j=1,i=0;j<=n;i=i+2,j++)
          {
          printf("%d\t",i);
          }
          }
          printf("\n");
return 0;
 }

 
