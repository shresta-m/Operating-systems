#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int fib(int n)
{
         int fib_x=0,fib_y=0;
         if(n == 1)
         {
          return 0;
         }
         if(n == 2)
         {
         return 1;
         }
         else
         {
         pid_t c1 = vfork();
         if(c1 == 0)
         {
          fib_x = fib(n-1);
          exit(0);
         }
         else
         {
         pid_t c2 = vfork();
         if(c2 == 0)
         {
         fib_y = fib(n-2);
         exit(0);
         }
         else
         {
         wait(NULL);
         return fib_x+fib_y;
         }
         }
         }
         }
         
int main()
{
         int n;
         printf("Enter the value of n\n");
         scanf("%d",&n);
         printf("Fibonacci series : \n");
         for(int i=1;i<=n;i++)
         printf("%d\n",fib(i));
         return 0;
}

