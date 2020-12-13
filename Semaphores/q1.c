#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#define N 5
void *producer(void *param);
void *consumer(void *param);
int buffer[N];
int in = 0, out = 0;
void *producer(void *param)
{
    int data = 0,i = 0;
    while(i < 10)
    {
        while((in+1) % N == out); 
        buffer[in] = data++;
        printf("Producing data to the index %d : %d\n", in, buffer[in]);
        in = (in + 1) % N;
        i++;
    }
    pthread_exit(0);
}
void *consumer(void *param)
{
    int data;
    while(1)
    {
        while(in == out);
        data = buffer[out];
        printf("Consuming data at the index %d : %d\n", out, data);
        out = (out+1) % N;
    }
        pthread_exit(0);
}
int main()
{	
	pthread_t tid[2];	
	pthread_create(&tid[0],NULL,producer,NULL);
	pthread_create(&tid[1],NULL,consumer,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	return 0;
}

