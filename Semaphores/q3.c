#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
int myrand(int n);
void *producer(void *param);
void *consumer(void *param);
struct dict
{
char word[30];
char meaning1[60];
char meaning2[60];
struct dict *nptr;
};
struct dict *head=NULL;
int n=0;
pthread_mutex_t mutex;
void *producer(void *param)
{
do
{
pthread_mutex_lock(&mutex);
printf("\nProducer :\n");
struct dict *t=head;
struct dict *temp=(struct dict *)malloc(sizeof(struct dict));
temp->nptr=NULL;
printf("Enter the word into dictionary: ");
gets(temp->word);
printf("Enter the primary meaning: ");
gets(temp->meaning1);
printf("Enter the secondary meaning: ");
gets(temp->meaning2);
if(head==NULL)
{
head=temp;
}
else
{
temp->nptr=head;
head=temp;
}
n=n+1;
pthread_mutex_unlock(&mutex);
int wait_time = myrand(3);
sleep(wait_time);
}while(1);
}

void *consumer(void *param)
{
do
{
pthread_mutex_lock(&mutex);
printf("\nConsumer\n");
if(n!=0)
{
char s[30];
printf("Enter word for search: ");
gets(s);
struct dict *t=head;
while(t!=NULL)
{
if(strcmp(t->word,s)==0)
{
printf("Primary meaning  : %s\n",t->meaning1);
printf("Secondary meaning  : %s\n",t->meaning2);
break;
}
else
t=t->nptr;
}
if(t==NULL)
printf("Counldn't find the word in the dictionary\n");
}
else
printf("There are no words in dictionary yet\n");
pthread_mutex_unlock(&mutex);
int wait_time = myrand(3);
sleep(wait_time);
}while(1);
}
 // Returns a random number between 1 and n
int myrand(int n)
{
   time_t t;
   srand((unsigned)time(&t));
   return (rand() % n + 1);
}
int main()
{
pthread_t tid1,tid2;
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_create(&tid1,&attr,producer,NULL);
pthread_create(&tid2,&attr,consumer,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
return 0;
}
