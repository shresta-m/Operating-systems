#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
         int a[100],odd_sum=0,even_sum=0;
         int n;
         pid_t pid;
         printf("Enter the value of n \n");
         scanf("%d",&n);
         for(int i=0,j=1;i<n,j<=n;i++,j++)
         {
         a[i]=j;
        // printf("%d\n",a[i]);
         }
         pid=fork();
         if(pid == -1)
         printf("fork failed \n");
         if(pid>0)
         {
        // printf("This is the parent block \n");
         printf("Sum of odd terms : ");
         for(int i=0;i<n;i++)
         {
         if((a[i]%2)!=0)
         odd_sum=odd_sum+a[i];
         }
         printf("%d \n",odd_sum);
         }
         if(pid==0)
         {
        // printf("\nThis is child block \n");
         printf("Sum of even terms : ");
         for(int i=0;i<n;i++)
         {
         if((a[i]%2)==0)
         even_sum=even_sum+a[i];
         }
         printf("%d\n",even_sum);
         }
         return 0;
}


