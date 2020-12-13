#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef int(*compare)(int x,int y);
int asc(int a,int b)
{
         return (a-b);
}
int desc(int a,int b)
{
         return (b-a);
}
void sort(int *arr,int n,compare comp)
{
   int i,j,temp;
   for(i=0;i<n;i++){
   for(j=0;j<n-1;j++)
   {
   if(comp(arr[j],arr[j+1])>0)
     {temp=arr[j];
     arr[j]=arr[j+1];
     arr[j+1]=temp;
     }
   }
}
}
int main()
{
         int a[100];
         int n;
         pid_t pid;
         printf("Enter the size of array \n");
         scanf("%d",&n);
         printf("Enter the array elements to be sorted\n");
         for(int i=0;i<n;i++)
         {        
         scanf("%d",&a[i]);
         }
        
         pid=fork();
         if(pid == -1)
         printf("fork failed \n");
         if(pid>0)
         {
        //This is the parent block 
         printf("Ascending order sort: \n");
         sort(a,n,asc);
         for (int i = 0; i < n; ++i) 
         {
            printf("%d\t", a[i]);
          }
          printf("\n");
         }
         if(pid==0)
         {
        // This is child block 
         printf("Descending order sort: \n");
         sort(a,n,desc);
         for (int i = 0; i < n; ++i) 
         {
            printf("%d\t", a[i]);
         }
         printf("\n");
         }
return 0;
}


