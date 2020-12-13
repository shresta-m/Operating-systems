#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int binarysearch(int arr[], int beg, int end, int x) 
{ 
 
    while (end >= beg) { 
        int mid = beg + (end - beg) / 2; 
        if (arr[mid] == x) {
        printf("Element is present at index : %d\n",mid+1);
        if(arr[mid-1] == x)
        binarysearch(arr,beg,mid-1,x);
        if(arr[mid+1] == x)
        binarysearch(arr,mid+1,end,x);
            break;
            }
       else if(arr[mid]<x)
       beg = mid+1;
       else
       end = mid-1;
}
}
 
int main()
{
         int n,x,h;
         printf("Enter the size of array\n");
         scanf("%d",&n);
         int a[n];
         pid_t pid;
         printf("Enter the array elements\n");
         for(int i=0;i<n;i++)
         {
         scanf("%d",&a[i]);
         }
         printf("enter the element to be searched \n");
         scanf("%d",&x); 
         h=n/2;
         pid=vfork();
         if(pid == -1)
         printf("fork failed\n");
         
          if(pid > 0)
         {
         //This is the parent block 
           int temp;
          for(int i=0;i<h;i++){
          for(int j=0;j<h-1;j++)
          {
          if(a[j] >a[j+1])
            {temp=a[j];
          a[j]=a[j+1];
          a[j+1]=temp;
         }
         }
         }
         binarysearch(a,0,h-1,x);
         }
         if(pid == 0)
         {
         //This is child block 
          int temp;
          for(int i=h;i<n;i++){
          for(int j=h;j<n-1;j++)
          {
          if(a[j] >a[j+1])
          {
          temp=a[j];
          a[j]=a[j+1];
          a[j+1]=temp;
         }
         }
         }
         binarysearch(a,h,n-1,x);
         exit(0);
         }
         return 0;
         }
         
         
