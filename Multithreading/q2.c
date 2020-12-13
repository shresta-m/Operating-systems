//QUESTION:
//(2) Ascending Order sort  and Descending order sort 
//here i have created 2 threads ,where 1st thread is assigned to carry out asceding order sort for the input array
//and 2nd thread is assigned to carry out descending order sort for the input array
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
void *asc(void *param);
void *desc(void *param);
int x[100],y[100];//Here, x array stores the array sorted in ascending order and y array stores descending order
struct node
{
    int *array;
    int size;
};
typedef int(*compare)(int x,int y);
int asc_sort(int a,int b)
{
         return (a-b);
}
int desc_sort(int a,int b)
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
    int m,n;
    printf("Enter the size of array\n");
    scanf("%d",&n);
    int a[n];
    struct node *elements = (struct node *)malloc(sizeof(struct node));
    elements->array = (int *)malloc(n*sizeof(int));
    elements->size =n;
    printf("Enter the array elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        elements->array[i] = a[i];
    }
    pthread_t tid,tid1;
    pthread_attr_t attr,attr1;
    //2 threads are created
    pthread_attr_init(&attr);//this first thread is used for descending order sort 
    pthread_create(&tid,&attr,asc,(void *)elements);

    pthread_attr_init(&attr1);//this thread is used for ascending order sort 
    pthread_create(&tid1,&attr1,desc,(void *)elements);
    
    //joining 2 threads
    pthread_join(tid,NULL);
    pthread_join(tid1,NULL);

    printf("\nAscending order sort :\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",x[i]);
    }
    printf("\n");
    printf("\nDescending order sort :\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",y[i]);
    }
    printf("\n");  
    free(elements);
return 0;
}
void *asc(void *param)
{
    struct node *a= (struct node *)param;
    int n= a->size;
    sort(a->array,n,asc_sort);
    for(int i=0;i<n;i++)
    x[i]= a->array[i];
   
    pthread_exit(0);
}
void *desc(void *param)
{
    struct node *a= (struct node *)param;
    int n= a->size;
    sort(a->array,n,desc_sort);
    for(int i=0;i<n;i++)
    y[i]= a->array[i];

    pthread_exit(0);
}

