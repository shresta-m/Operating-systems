#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
         int n,h;
         pid_t pid;
         printf("Enter the size of array \n");
         scanf("%d",&n);
         int a[n];
         printf("Enter the array elements to be sorted\n");
         for(int i=0;i<n;i++)
         {
         scanf("%d",&a[i]);
         }
         h=n/2;
         pid = vfork();
         if(pid == -1)
         printf("fork failed \n");
         else if(pid >0)
         {
         //This is parent block 
           int temp;
          for(int i=0;i<h;i++){
          for(int j=0;j<h-1;j++)
          {
          if(a[j] >a[j+1])
          {
          temp=a[j];
          a[j]=a[j+1];
          a[j+1]=temp;
         }
         }
         }
          
         }
         else
         {
          //This is child block 
          int temp;
          for(int i=h;i<n;i++){
          for(int j=h;j<n-1;j++)
          {
          if(a[j] < a[j+1])
           {temp=a[j];
          a[j]=a[j+1];
          a[j+1]=temp;
         }
         }
         }
         exit(0);
         }
         printf("Required output array : \n");
          for(int i=0;i<n;i++)
         printf("%d\t",a[i]); 
         printf("\n");  
         return 0;
         }
         
         
         
         
         
         
         
