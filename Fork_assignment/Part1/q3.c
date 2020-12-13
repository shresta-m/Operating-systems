#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<sys/types.h>
int power(int x, unsigned int y) 
{ 
    if (y == 0) 
        return 1; 
    if (y % 2 == 0) 
        return power(x, y / 2) * power(x, y / 2); 
    return x * power(x, y / 2) * power(x, y / 2); 
} 
int order(int a) 
{ 
    int n = 0; 
    while (a) { 
        n++; 
        a=a/10; 
    } 
    return n; 
} 
int armstrong(int x)
{  
int rem;
  int n = order(x); 
    int temp = x, sum = 0; 
    while (temp) { 
        int rem = temp % 10; 
        sum += power(rem, n); 
        temp = temp / 10; 
    } 
  return sum;
}

int main()
{
         int n,result ,num;
         pid_t pid;
         printf("Enter the value of n ,where armstrong numbers till n should be generated \n");
         scanf("%d",&n);
         printf("In the child block ,sum is calculated and checking if sum = number is done in parent \n");
         for(int i=1;i<n;i++)
         {
         num=i;
         result =0;
          pid = vfork();
         if(pid == -1)
         {printf("fork failed \n");}
         if(pid == 0)
         {
         //printf("This is child block \n");
         result = armstrong(num);
         exit(0);
         }
         if(pid>0)
         {
         //printf("This is parent block \n");
         if(result == num)
         {
         printf("%d\n",num);
         }
         }
         }
         return 0;
         }
         
         
         
         
         
         
