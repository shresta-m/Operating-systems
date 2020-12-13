//QUESTION:
//Computation of Mean, Median, Mode for an array of integers.
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
void *mean(void *param);
void *median(void *param);
void *mode(void *param);
struct node
{
    int *value;//this value array pointer stores the array values
    float mean,median;
    int mode;
    int size;//size is the array size
};
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int main()
{
    int n;
    struct node *array = (struct node *)malloc(sizeof(struct node));
    printf("Enter the size of array\n");
    scanf("%d",&n);
    array->size = n;
    int a[n];
    array->value = (int *)malloc(n*sizeof(int));
    printf("Enter the array elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        array->value[i]=a[i];
    }
    pthread_t tid,tid1,tid2;
    pthread_attr_t attr,attr1,attr2;
    //3 threads are created ,where each thread is assigned to calculate mean,median and mode
    pthread_attr_init(&attr); 
    pthread_create(&tid,&attr,mean,array);
    pthread_attr_init(&attr1); 
    pthread_create(&tid1,&attr1,median,array);
    pthread_attr_init(&attr2); 
    pthread_create(&tid2,&attr2,mode,array);
    
    //joining all 3 threads
    pthread_join(tid,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    printf("Mean : %f\n",array->mean);
    printf("Median : %f\n",array->median);
    printf("Mode : %d\n",array->mode);
    printf("\n");  
    free(array);
return 0;
}
//mean of an array = sum of all elements/number of elements
void *mean(void *param)
{
    struct node *a= ((struct node *)param);
    int n = a->size;
    int sum =0;
    for(int i=0;i<n;i++)
    {
        sum = sum+a->value[i];//sum of all elements is calculated
    }
    a->mean = (double)sum / (double)n;
    
    pthread_exit(0);
}
//median of a sorted  array :
// midlle element ,if the array size id odd
//average of middle 2 elements ,if the array size is even
void *median(void *param)
{
    struct node *temp = ((struct node *)param);
    int *a = temp->value;
    qsort(a, temp->size, sizeof(int), cmp);//array is sorted here
    if (temp->size % 2 == 0)
    {
        temp->median = ((float)a[temp->size / 2] + (float)a[(temp->size / 2) - 1]) / 2;
    }
    else
        temp->median = a[temp->size / 2];

    pthread_exit(0);
}
//here the occurrences of each number in the array is counted and the value with highest occurence is displayed
void *mode(void *param)
{
    struct node *temp = ((struct node *)param);
    int *a = temp->value;
    int n = temp->size;

    qsort(a, temp->size, sizeof(int), cmp);
    int maxValue = 0, maxCount = 0, i, j;

   for (i = 0; i < n; ++i) {
      int count = 0;
      
      for (j = 0; j < n; ++j) {
         if (a[j] == a[i])
         ++count;
      }
      
      if (count > maxCount) {
         maxCount = count;
         maxValue = a[i];
      }
   }
    temp->mode = maxValue;

    pthread_exit(0);
}
