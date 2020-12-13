//QUESTION :
//4.Generation of Prime Numbers upto a limit supplied as Command Line Parameter.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
void *runner(void *param);
int main(int argc ,char *argv[])
{
    if(argc!=2)
    {
        printf("Incorrect usage !!\n Use ./<filename> n\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    //here, n threads are created ,where each thread checks for one number and prints if it is prime
    pthread_t tid[n];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int *num;
    printf("The prime series till %d :\n",n);
    for(int i=1;i<n;i++)
    {
        num = (int *)malloc(sizeof(int));
        num[0] = i;
        pthread_create(&tid[i],&attr,runner,(void *)num);  
    }
    //joining all  n threads
    for(int i=1;i<n;i++)
    {
    pthread_join(tid[i],NULL);  
    }  
    free(num); 
    return 0;
}
//prime number means it is divisible by 1 and itself
void *runner(void *param)
{
    int *number = (int *)param;
    int n=number[0];
    int flag =0;
    //so here loop iterates from i= 2 to n/2 and if n is divisible by i,then flag is set to 1,which means not prime 
     for (int i = 2; i <= n / 2; ++i) {
        // condition for non-prime
        if (n % i == 0) {
            flag = 1;
            break;
        }
    }
    //after the for loop, if the flag value is 0 ,then its prime and that number is printed
     if (flag == 0)
          { printf("%d \n", n);
           }  
pthread_exit(NULL);
}
