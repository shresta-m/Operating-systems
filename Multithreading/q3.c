//QUESTION:
//3. Implement a multithreaded version of binary search. By default, you can implement a search
//for the first occurrence and later extend to support multiple occurrence (duplicated elements
//search as well)
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
struct node 
{
    int *elements;//elements will have the array values
    int size,x;//here size is array size and x is the search element
    int *fh,*sh;//fh contains the first half of array and sh conatins second half od array
};
void *runner(void *param);
void *runner1(void *param);
//here binary search function works  for searching the  multiple occurrences of search elements 
int binarysearch(int arr[], int beg, int end, int x) 
{ 
 
    while (end >= beg) { 
        int mid = beg + (end - beg) / 2; 
        //this is for multiple occurrence of the seacrh element ,if mid == x,then print that index 
        //and also check at mid+1 and mid-1 index ,if it is equal to x,beacuse the array is sorted
        if (arr[mid] == x) 
        {
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
    int n;
    printf("Enter the size of array\n");
    scanf("%d",&n);
    int a[n];
    int h = n/2;
    int z = n-h;
    struct node *array = (struct node *)malloc(sizeof(struct node));
    array->size =n;
    array->elements = (int *)malloc(n*sizeof(n));
    array->fh = (int *)malloc(h*sizeof(h));
    array->sh = (int *)malloc(z*sizeof(z));

    printf("Enter the array elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        array->elements[i]=a[i];
    }
    int b[n];
    printf("enter the element to be searched \n");
    scanf("%d",&array->x); 
    printf("1st half and 2nd half is sorted separately and the element is searched in the two halfs\n");
    //2 threads are created ,where each thread is assigned to carry out the binary search function in each respective halves
    pthread_t tid,tid1;
    pthread_attr_t attr,attr1;

    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,array);

    pthread_attr_init(&attr1);
    pthread_create(&tid1,&attr1,runner1,array);
    
    //joining 2 threads
    pthread_join(tid ,NULL);
    pthread_join(tid1 ,NULL);

    for(int i=0;i<h;i++)
    {
        b[i]=array->fh[i];
    }
    for(int i=h;i<n;i++)
    {
        b[i]=array->sh[i];
    }
    
    printf("The array after sorting each half separately\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",b[i]);
    }
    printf("\n");
    
    free(array);
return 0;
}
//in each runner code,first the respective halves is sorted and binary search is carried out
void *runner(void *param)
{
    struct node *temp1= ((struct node *)param);
    int *a= temp1->elements;
    int n = temp1->size;
    int h = n/2;
    int s= temp1->x;
    int temp;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<h-1;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    for(int i=0;i<h;i++)
    {
        temp1->fh[i] = a[i];
    }
    binarysearch(a,0,h-1,s);

    pthread_exit(0);
}
void *runner1(void *param)
{
    struct node *temp1= ((struct node *)param);
    int *a= temp1->elements;
    int n = temp1->size;
    int h = n/2;
    int s= temp1->x;
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
        for(int i=h;i<n;i++)
        {
            temp1->sh[i] = a[i];
        }
        binarysearch(a,h,n-1,s);

    pthread_exit(0);
}
