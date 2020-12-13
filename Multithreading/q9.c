#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
int f1 =1,f2 =1,f=1;
void *fib1(void *param);
void *fib2(void *param);
int main()
{
    int n;
    printf("Enter the number of terms in fibonacci series \n");
    scanf("%d",&n);
    printf("Fibonnaci series :\n");
    pthread_t tid1,tid2;
    pthread_attr_t attr1,attr2;
    printf("0\n1\n");//first 2 elements in the fibonacci series are printed
    for(int i=2;i<=n;i++)
    {
    int *n1 = (int *)malloc(sizeof(int));
    int *n2 = (int *)malloc(sizeof(int));
    n1[0] = i-1;
    n2[0] = i-2;

    pthread_attr_init(&attr1);//in the first thread fib(n-1) value is calculated
    pthread_create(&tid1,&attr1,fib1,(void *)n1);

    pthread_attr_init(&attr2);//in the second thread fib(n-2) value is calculated 
    pthread_create(&tid2,&attr2,fib2,(void *)n2);

    //join 2 threads
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    //finally both values are added : fib(n) = fib(n-1)+ fib(n-2)
    f = f1+f2;
    printf("%d\n",f);
    }
    return 0;
}
void *fib1(void *param)
{
    int *x = (int *)param;
    int n=x[0];
    int a = 0, b = 1, c, i; 
    if (n == 0) 
        f1 = a; 
        else
        {
        for (i = 2; i <= n; i++)
        {
            c = a + b; 
            a = b; 
            b = c; 
        } 
        f1 = b;
        }  
    pthread_exit(0);
}
void *fib2(void *param)
{
    int *x = (int *)param;
    int n=x[0];
    int a = 0, b = 1, c, i; 
    if (n == 0) 
        f2 = a; 
        else
        {
        for (i = 2; i <= n; i++) { 
        c = a + b; 
        a = b; 
        b = c; 
    } 
    f2 = b;
        }
    pthread_exit(0);
}
