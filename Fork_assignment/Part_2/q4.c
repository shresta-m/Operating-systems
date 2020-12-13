#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int fib(int n) 
{ 
    if (n <= 1) 
        return n; 
    return fib(n - 1) + fib(n - 2); 
} 
int main()
{
         pid_t pid;
         int n;
         printf("Enter the value of n\n");
         scanf("%d",&n);
         pid=fork();
         if(pid==-1)
         printf("fork failed\n");
         else if(pid==0)
         {
         //printf("\nThis is the child block\n");
          printf("Prime series : ");
         printf("\n");
         int ct=0,t=0,i=1,j=1;
         while(t<n)  
         {  
         j=1;  
         ct=0;  
         while(j<=i)  
         {  
            if(i%j==0)  
            ct++;  
            j++;   
         }  
         if(ct==2)  
         {  
            printf("%d\t ",i);  
            t++;  
         }  
         i++;  
         } 
         printf("\n");
         }
         else 
         {
         int fact;
        // printf("\nTHis is parent block \n");
          printf("Fibonacci series :");
          printf("\n");
         for(int i=1;i<=n;i++)
         {
         printf("%d\t",fib(i));
         }
         printf("\n");
         }
         wait(NULL);
return 0;
}
