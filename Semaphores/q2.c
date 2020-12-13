#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#include<unistd.h>
#define N 5
void *producer(void *param);
void *consumer(void *param);
int buf[N];
int in=0,out=0,counter=0;
int flag[]={0,0};
int turn=0;
void lock(int self)
{
    //flag is set to 1 ,so that it can acquire the lock
    flag[self] = 1;
    //but the chance to acquire lock  is given to other thread 
    turn = 1-self;
    // Wait until the other thread looses the desire
    // to acquire lock or it is your turn to get the lock.
    while (flag[1-self]==1 && turn==1-self) ;
}
void unlock(int self)
{
    flag[self] = 0;
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
void *producer(void *param)
{
	int data=3,i=0;
	while(i<20)
	{		
		while(counter==N) ;
		lock(0);
		buf[in]=data;
		printf("Producer :Producing index %d\n",in);
		in=(in+1)%N;
		++i;
		counter++;
		unlock(0);
	}
	pthread_exit(0);
}
void *consumer(void *param)
{
	int data,i=0;
	while(i<20)
	{
		while(counter==0);
		lock(1);
		data=buf[out];
		printf("Consumer :Consuming index %d\n",out);
		out=(out+1)%N;
		++i;
		counter--;
		unlock(1);
	}
	pthread_exit(0);
}