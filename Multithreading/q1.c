//QUESTION:
//(1)Generate armstrong number within a range
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
void *runner(void *param);
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
  int n = order(x); //here the order of the number is calculated 
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
    int n,result,number;
    printf("Enter the number till which armstrong number should be generated \n");
    scanf("%d",&n);
    //since the armstrong numbers till n needs to be generated,n threads are created 
    //where,each number is assigned to one thread and calcualtion is done and printed if it is armstrong number
    pthread_t tid[n];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    printf("Armstrong series:\n");
    for(int i=1;i<=n;i++)
    {
        int *num = (int *)malloc(2*sizeof(int));
        result = 0;
        num[0] = i;//here each number is stored in num[0] 
        pthread_create(&tid[i],&attr,runner,(void *)num);//in thread ,the sum of each number is calculated                            
    }
    //joining all n threads
    for(int i=1;i<n;i++)
    {
    pthread_join(tid[i] ,NULL);  
    }
    
    return 0;      
}

void *runner(void *param)
{
    int *num = (int *)param;
    num[1] = armstrong(num[0]);//here the sum is calculated and stored in num[1] variable
    if(num[0] == num[1])//and checking if sum == number and printed if it is equal
         {
                printf("%d\n",num[0]);
         }
    pthread_exit(0);
}
